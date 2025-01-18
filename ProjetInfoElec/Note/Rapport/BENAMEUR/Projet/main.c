/********************************************************************************
|   commentaires : Illustration communication serie UART 
|									 Interruption reception
|   auteur: Arouna DARGA
********************************************************************************/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */

#include "vm_codops.h"
/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
		 
IDR : registre sur 16 bits xxxx xxxx xxxx xxxx, on ecrit en hexa et il faut mettre le bon bit à 1
ODR : idem
			
-------------------------------------------------------------------------------*/
#define senseValue ((GPIOC -> IDR & 0x0080)>>7)
#define onOffPWM ((GPIOA -> IDR & 0x0200)>>9)
#define boutonPoussoir ((GPIOC -> IDR & 2000) >>13)
#define capteur1 ((GPIOC -> IDR & 0x0040)>>6)
#define capteur2 ((GPIOC -> IDR & 0x0100)>>8)

/*-------------------------------------------------------------------------------
 PINS UTILISEES
-------------------------------------------------------------------------------*/
/*
PC7 : Entree pour donner le sens (pour la demo)
PA9 : Entree pour activer ou desactiver la PWM
PA5 : Sortie, force le sens du moteur (connecte a l'PHASE sur DRV8835
PA8 : sortie, pour la PWM, connecte a l'ENBL du DRV8835 
PC13 : (bouton poussoir) pour démarrer le grafcet

*/
/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/
void InitBouton1(void);
void initPattePA5_LedVerte(void);
void Init_UART2_Avec_Interrupt (unsigned int BaudRate);
void InitPinSense(void);				// PIN PC7 pour faire le test a l'oscillo
void InitPinOnOffPWM(void);			// PIN PA9 pour faire le test a l'oscillo
void InitCapteurPosition1(void);		// PIN PC3
void InitCapteurPosition2(void);		// PIN PC2
void Run(void);
void ReadBinary(char* file);
void initPC8PC9(void);
void InitTimer1(void);						// PIN PA8 pour la PWM
void InitTIM3Interrupt(void);
void TIM3_IRQHandler (void);
void Run(void);
void SetPWM(int dutyCycle);
void ClearPWM(void);
void Sense(int value);						// PIN PA5 pour le sens du moteur
void MiseAJourEntree(void);
void MiseAJourSortie(void);
void InitBoutonStart(void);				// PC5

/*------------------------------------------------------------------------------
  Ordre dans le tableau variable
------------------------------------------------------------------------------*/
/*
# etat0 			0					Not used
# etat1 			1					Not used
# etat2 			2 				Not used
# etat3				3 				Not used
# capt_pos1 	4
# capt_pos2		5
# outPWM 			6			1  ON,  0 OFF
# outSense 		7			1  FORWARD, 0 REVERSE
# capt_metal	8	
*/
#define capt_pos1 	4 		// PIN PC3
#define capt_pos2		5			// PIN PC2
#define outPWM 			6			// PIN PA9 pour le test a l'oscillo pour activer le sens du moteur (PIN PA8)
#define outSense 		7			// PIN PC7 pour le test a l'oscillo pour activer le sens du moteur (PIN PA5)
#define capt_metal	8			// 

/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
volatile unsigned char Caractere_Recu;  /* var globales modifier dans la routine IT: volatile*/

#define PILE_MAX 100
#define CODE_MAX 100
#define VAR_MAX 100 

int pc = 0;
int sp = -1;


int pile[PILE_MAX];

int code[CODE_MAX];

int variable[VAR_MAX];

int dutyCycle = 75;

/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
	/*
		Declaration variables locales 
	*/
    	
	/* 
		Initialiser les peripheriques utiles à l'application  : 
    En general on regroupe les initialisation dans une  ou plusieurs fonctions 
    Ces instructions ou appel de fonctions seront exécutées une seule fois  
  */
	//	InitBouton1();													// pour activer le grafcet
    initPattePA5_LedVerte();								// Utile pour un débug visuel rapide
		Init_UART2_Avec_Interrupt(9600);				// L'UART va permettre de gérer le rapport cyclique de la PWM, et donc la vitesse du moteur de la chaine de production 
    initPC8PC9();														// Pour tester la VM
		InitPinSense();
   	InitPinOnOffPWM();
		InitTimer1();								// timer 1 utiisé pour la PWM pour configurer le pont H du moteur
		InitTIM3Interrupt();
	  InitCapteurPosition1();		// PIN PC6
    InitCapteurPosition2();		// PIN PC8
		InitBoutonStart();					// PC5
	
	/* tableau de code pour verifier le bon fonctionnement de la VM
		ce dernier effectue un & avec 2 variables d'entrees liées à 2 PIN
		le resultat est afficher sur la LED		*/
		code[0] = I_PUSH;
		code[1] = 0;								// varible[0] : PIN0  soit PC8
		code[2] = I_PUSH;
		code[3] = 1;								// varible[1] : PIN1  soit PC9
		code[4] = I_AND;
		code[5] = I_POP;
		code[6] = 2;								// varible[2] : LED
		code[7] = I_HALT;

/* Pour un grafcet simple de la chaine de production
		le tapis avancera dès lors que le capteur de position 1 est activé
		dès que le second capteur est activé, le tapis fonctionnera dans l'autre sens jusqu'a l'activation du premier capteur
*/
/*		Le code binaire suivant représentait un grafcet simple a 4 etats et 4 transistions
			Nous pensions travailler avec ce code afin de lier la VM et la mise a jour de la PWM
			Néanmoins, ce code ne prend pas en compte les problemes de stabilite du grafcet
			On ne peut donc pas utilise ce code par il oblige la VM a etre bloquante

		variable[capt_pos1] = 0;
		variable[capt_pos2] = 0;
		variable[outPWM] = 0;
		variable[outSense] = 0;
	
		code[0] = 101;
		code[1] =4;
		code[2] =100;
		code[3] =1;
		code[4] =11;
		code[5] =201;
		code[6] =0;
		code[7] =100;
		code[8] =1;
		code[9] =102;
		code[10] =6;
		code[11] =100;
		code[12] =1;
		code[13] =102;
		code[14] =7;
		code[15] =100;
		code[16] =1;
		code[17] =101;
		code[18] =5;
		code[19] =11;
		code[20] =201;
		code[21] =15;
		code[22] =100;
		code[23] =1;
		code[24] =100;
		code[25] =0;
		code[26] =102;
		code[27] =7;
		code[28] =100;
		code[29] =1;
		code[30] =101;
		code[31] =5;
		code[32] =11;
		code[33] =201;
		code[34] =22;
		code[35] =100;
		code[36] =0;
		code[37] =100;
		code[38] =0; 
		code[39] =101;
		code[40] =4;
		code[41] =11;
		code[42] =201;
		code[43] =35;
		code[44] =200;
		code[45] =0;
		code[46] =400;
*/
   while(1)  
   {
			/* Test Pour verifier le fonctionnement de la VM seule, utilisant 2 PINS en entrees et la LED en sortie
		 lire la donnée en pin0
		 la mettre dans le tableau variable à l'indice 0
		 lire la donnée en pin1
		 la mettre dans le tableau variable à l'indice 1
*/
			pc = 0;
			variable[0] = ((GPIOC -> IDR & 0x0100)>>8);						// lecture de la pin0
			variable[1] = ((GPIOC -> IDR & 0x0200)>>9);						// lecture de la pin1 
			Run();
		//  variable[0] = 1;
		//	variable[1] = 1;	 
		 if(variable[2] == 0)
				GPIOA->ODR &= ~(1<<5);	// bit 5 à '0'	 	extinction de la LED
		 else
				GPIOA->ODR |= (1<<5);	  // bit 5 à '1'		allumage de la LED
		
	// Programme de base pour fonctionner le moteur avec 2 pins pour activer le moteur et determiner son sens
		 /*
		 if(onOffPWM)
				SetPWM(dutyCycle);
		 else
			  ClearPWM();
		 Sense(senseValue);
		 */
	/*	 MiseAJourEntree();
		 
		 variable[outPWM] = variable[capt_pos1];
		
		 variable[outSense] = variable[capt_pos2];
		 
		 MiseAJourSortie();*/
		Run();
		pc = 0;
		
	}
   // Fin : Le CPU n'arrivera jamais ici
}
// FIN FONCTION MAIN

void Run(void)											// code de la machine virtuelle qui execute le code binaire
{
	while(code[pc] != I_HALT)
	{
//		printf("pc : %d, sp : %d valeur pile : %d commande : %d \n", pc, sp,pile[sp], code[pc]);
		switch(code[pc])
		{
				case I_PUSHI:
							sp++;
							pile[sp] = code[pc + 1];
							pc = pc +2;
							break;

			case I_MULT :
							pile[sp - 1 ] = pile[sp - 1] * pile[sp];
							sp --;
							pc ++;
							break;

			case I_ADD :
							pile[sp - 1 ] = pile[sp - 1] + pile[sp];
							sp --;
							pc ++;
							break;
				
		 	 case I_NOT : 
							if(pile[sp] == 0)
											pile[sp] = 1;
							else
											pile[sp] = 0;
               				
       				pc ++;  
       				break;
               				
			case I_AND :
						if (pile[sp] && pile[sp -1])
										pile[sp-1] = 1;
						else 
										pile[sp-1] = 0;
						sp --;
						pc ++;     
						break;    
				
			case I_OR :
						if (pile[sp] || pile[sp -1])
										pile[sp-1] = 1;
						else 
										pile[sp-1] = 0;
					
						sp --;
						pc ++;     
						break;

			case I_EQ :
						if (pile[sp - 1 ] == pile[sp])
										pile[sp-1] = 1;
						else
										pile[sp-1] = 0;

						sp --;
						pc ++;
						break;
                                
			case I_LS :
						if (pile[sp - 1 ] < pile[sp])
											pile[sp-1] = 1;
						else
											pile[sp-1] = 0;

						sp --;
						pc ++;
						break;
                                
			case I_LE :
						if (pile[sp - 1 ] <= pile[sp])
											pile[sp-1] = 1;
						else
											pile[sp-1] = 0;

						sp --;
						pc ++;
						break;
						
			case I_GT :
						if (pile[sp - 1 ] > pile[sp])
											pile[sp-1] = 1;
						else
											pile[sp-1] = 0;

						sp --;
						pc ++;
						break;
						
			case I_GE :
						if (pile[sp - 1 ] >= pile[sp])
											pile[sp-1] = 1;
						else
											pile[sp-1] = 0;
						sp --;
						pc ++;
						break;
						
			case I_INC :
						pile[sp] = pile[sp] + 1;
						pc ++;
						break;

			case I_DEC :
						pile[sp] = pile[sp] - 1;
						pc ++;
						break;

			case I_POP :
						variable[code[pc + 1]] = pile[sp];
						sp --;
						pc = pc + 2;    
						break;

			case I_PUSH:
						pile[sp+1] =  variable[code[pc+1]];
						sp++;
						pc = pc + 2 ;
						break;

			case I_JF :
						if (pile[sp] == 0)
										pc = code[pc+1] ;
						else 
										pc = pc +2;
						break;

			case I_JP :
						pc = code[pc +1];
						break;

			case I_JT :
						if (pile[sp] == 1)
									pc = code[pc+1];
						else 
								pc = pc +2;
						break;
						 
			}
/*		printf("etat pile \n");
		for(i=0; i<=sp; i++)
			printf("indice %d, %d \n", i, pile[i]);
*/	
	}
}


void initPC8PC9(void)								// PINS PC8 et PC9 pour tester la VM
{
   RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
   GPIOC->MODER &=~(1UL<<16);   // bit 17 à '0'
   GPIOC->MODER &=~(1UL<<17);   // bit 16 à '0'
   GPIOC->PUPDR &=~(1UL<<16);   //  bit b16 à '0'
   GPIOC->PUPDR &=~(1UL<<17);   //  bit b17 à '0'

	 GPIOC->MODER &=~(1UL<<18);   // bit 18 à '0'
   GPIOC->MODER &=~(1UL<<19);   // bit 19 à '0'
   GPIOC->PUPDR &=~(1UL<<18);   // bit b18 à '0'
   GPIOC->PUPDR &=~(1UL<<19);   // bit b19 à '0'
}

void InitPinSense(void)							// Pin PC7
{
	RCC->AHBENR |= (1UL<<19);
	GPIOC->MODER &=~(1UL<<14);
	GPIOC->MODER &=~(1UL<<15);
	GPIOC->PUPDR &=~ (1UL<<14);
	GPIOC->PUPDR &=~ (1UL<<15);
}
void InitPinOnOffPWM(void)					// Pin PA9
{
	 RCC->AHBENR |=(1UL<<17);     //horloge du GPIOA
   GPIOA->MODER &=~(1UL<<18);   // bit  à '0'		entree
   GPIOA->MODER &=~(1UL<<19);   // bit  à '0'
   GPIOA->PUPDR &=~(1UL<<18);   //  bit  à '0'
   GPIOA->PUPDR &=~(1UL<<19);   //  bit  à '0'
}
void InitCapteurPosition1(void)			// PIN PC6
{
	 RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
   GPIOC->MODER &=~(1UL<<12);   // bit  à '0'
   GPIOC->MODER &=~(1UL<<13);   // bit  à '0'
   GPIOC->PUPDR &=~(1UL<<12);   //  bit  à '0'
   GPIOC->PUPDR &=~(1UL<<13);   //  bit  à '0'
}
void InitCapteurPosition2(void)			// PIN PC8
{
	 RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
	 GPIOC->MODER &=~(1UL<<16);   // bit  à '0'
   GPIOC->MODER &=~(1UL<<17);   // bit  à '0'
   GPIOC->PUPDR &=~(1UL<<16);   // bit  à '0'
   GPIOC->PUPDR &=~(1UL<<17);   // bit  à '0'
}



void InitBoutonStart(void)				// PC5
{
	 RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
	 GPIOC->MODER &=~(1UL<<10);   // bit  à '0'
   GPIOC->MODER &=~(1UL<<11);   // bit  à '0'
   GPIOC->PUPDR &=~(1UL<<10);   // bit  à '0'
   GPIOC->PUPDR &=~(1UL<<11);   // bit  à '0'
}
/*
Le bouton poussoir va permmettre de lancer le grafcet
Sans son utilisation, le grafcet fonctionnerait de manière permanente
*/
void InitBouton1(void)							// PIN PC13
{
	RCC->AHBENR |=(1<<19);     // Activation horloge du GPIOC
	GPIOC->MODER &=~(1<<27);   // choix mode General Purpose Output bit b26 à '0'
	GPIOC->MODER &=~(1<<26);   // choix mode General Purpose Output bit b27 à '0' // config en entree
	GPIOC->OSPEEDR&=~(1<<26);  // 
	GPIOC->OSPEEDR&=~(1<<27);  // 
	GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b11 à '0'
	GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b10 à '0'
}


/*
	Timer 3 avec interruption qui permet de lire les entrées et exécuter les sorties de manière régulière
*/
void InitTIM3Interrupt(void)					
{
	// 1. Activer Horloge de TIMER3
		// 1: TIM3 clock enabled
	RCC->APB1ENR |= (1<<1); 
	
	// 2. Selection du mode de comptage du TIM3 
	// counter used as upcounter
	TIM3->CR1 &=~(1<<4);
	// 3. Definition de la période ou fréquence de débordement
	// divisons la frequence du timer par 48000: soit TIM_PSC=47999
	// ainsi Freq_Comptage=48x10^6/(47999+1) Hz=1000 Hz 
	// chaque 1/1000 s le TIMx s'incrémentera.
	TIM3->PSC=47999;
	
	// si on veut 0.5 s il faut compter 500 fois: TIMx_ARR=500-1=99
	TIM3->ARR =499 ;        


	   // Activation de la demande interruption 
	// le bit b0 de registre TIM3 DMA/Interrupt enable register (TIM3_DIER) à '1'
	TIM3->DIER|=(1<<0);
	
	// Demasquer la demande interruption pour que le CPU puisse executer la routine d'interruption
	NVIC_EnableIRQ(TIM3_IRQn);
	
	// Demarrage du Timer TIM3
	TIM3->CR1 |=(1<<0); 
}

//routine d'interruption pour lire les entrees et ecrire les sorties
void TIM3_IRQHandler (void)
{
   
   if((TIM3->SR & (1<<0))== 1) // vérifions que c'est bien le debordement qui demande interruption
    {
				MiseAJourEntree();
				MiseAJourSortie();
				TIM3->SR &= ~(1<<0);  		// reset du drapeau de demande interruption
    }
}
/**************************************************************************************
  FUNCTION:     Routine interruption void USART2_IRQHandler(void)
  DESCRIPTION:  Fonction declenchee par le hardware
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   une routine interruption ne prend jamais de parametre
  RETURNS:   	  une routine interruption ne renvoi jamais de parametre  
  REQUIREMENTS: Configurer USART2 et activer la demande interruption
Condition de declenchement :
								1. caractere recu si demande IT activer et demasquer au niveau de NVIC
								2. Fin de transmission si demande IT activer et demasquer au niveau de NVIC
***************************************************************************************/
void USART2_IRQHandler(void)
{
	if (USART2->ISR&(1<<5))
	{
		Caractere_Recu=USART2->RDR;
		if (Caractere_Recu=='A')
		{
//			GPIOA->ODR |=(1<<5);
			dutyCycle++;
		}
		else if (Caractere_Recu=='E')
		{
//			GPIOA->ODR &=~(1<<5);
			dutyCycle--;
		}
		Caractere_Recu++;
		USART2->TDR = Caractere_Recu;
		SetPWM(dutyCycle);
		
	}
}


/*===============================================================================
  FUNCTION:     void initPattePA5_LedVerte(void)
  DESCRIPTION:  Configuration de la patte PA5 (PORT A, GPIOA) en mode sortie
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void initPattePA5_LedVerte(void)
{
   RCC->AHBENR |=(1UL<<17);     // Activation horloge du GPIOA
   GPIOA->MODER &=~(1UL<<11);   // choix mode General Purpose Output bit b11 à '0'
   GPIOA->MODER |=(1UL<<10);    // choix mode General Purpose Output bit b10 à '1'
   GPIOA->OTYPER &=~(1UL<<5);   // choix techno de sortie Push-Pull : bit b5 à '0'
   GPIOA->PUPDR &=~(1UL<<11);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOA->PUPDR &=~(1UL<<10);   // desactivation resistance de tirage: bit b10 à '0'
   GPIOA->OSPEEDR&=~(1UL<<11);  // bit b11 à '0'
   GPIOA->OSPEEDR|=(1UL<<10);  // bit b10 à '0'
}

/*===============================================================================
  FUNCTION:     void Init_UART2_Sans_Interrup (unsigned int BaudRate)
  DESCRIPTION:  Configuration UART2 (PA2->Tx, PA3->Rx), hardware via USB debuger STLINK
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   unsigned int BaudRate
  RETURNS:   	rien   
  REQUIREMENTS: BaudRate depend de la frequence  
===============================================================================*/
void Init_UART2_Avec_Interrupt (unsigned int BaudRate)					// PA2 : Tx, PA3 : Rx
{

  unsigned int Num_AF=1;
	unsigned int Num_Patte;
	/*Activation horloge GPIOA pour la configuration des pattes PA2 et PA3*/
   RCC->AHBENR |=(1<<17); 
   /*Activation horloge UART2 pour la configuration de l'UART2 */
   RCC->APB1ENR|=(1<<17);       
   
   /*configuration des pattes*/
   // configuration PA2 (Tx)
   GPIOA->MODER |=(1<<5);      // choix Alternate Function pour PA2 bit b5 à '1'
   GPIOA->MODER &=~(1<<4);     // choix Alternate Function pour PA2 bit b4 à '0'
	 Num_Patte=2;
   GPIOA->AFR[0] &=(~(0x0F<<4*Num_Patte));
	 GPIOA->AFR[0] |=((Num_AF&0x07)<<4*Num_Patte);
	
   GPIOA->OTYPER &=~(1<<2);    // choix techno de sortie Push-Pull : bit b2 à '0'
   GPIOA->PUPDR &=~(1<<5);     // desactivation resistance de tirage: bit b5 à '0'
   GPIOA->PUPDR &=~(1<<4);     // desactivation resistance de tirage: bit b4 à '0'
   GPIOA->OSPEEDR&=~(1<<5);    // Vitesse de rafraichissement bit b5 à '0'
   GPIOA->OSPEEDR&=~(1<<4);    // Vitesse de rafraichissement bit b4 à '0'
   
  // configuration PA3 (Rx)
   GPIOA->MODER |=(1<<7);      // choix Alternate Function pour PA2 bit b5 à '1'
   GPIOA->MODER &=~(1<<6);     // choix Alternate Function pour PA2 bit b4 à '0'
	 
	 Num_Patte=3;
	 GPIOA->AFR[0] &=(~(0x0F<<4*Num_Patte));  
	 GPIOA->AFR[0] |=((Num_AF&0x07)<<4*Num_Patte);
      
   /*configuration de USART2 */
   
   /* definition de la vitesse de communication
    USARTx_BRR  = Frequence du Module/Baude_Rate
    ici nous voulons BaudeRate=96000 et la frequence du module vaut SystemCoreClock
   */
   USART2->BRR=(SystemCoreClock/BaudRate);
   /* definition du format du train de bits */
   USART2->CR1&=~((1<<12)|(1<<28));     // 8 bits de données, 1 bit START
   USART2->CR1&=~((1<<10));             // pas de Parité
   USART2->CR2&=~((1<<13)|(1<<12));     // 1 bit STOP
   USART2->CR1|=((1<<3)|(1<<2)|(1<<0)); // Activer USART3, Activer Reception, activer Transmission
   USART2->CR1|=(1<<5);									// Activer la demande IT pour la reception
	 NVIC_EnableIRQ(USART2_IRQn);					// demasquer la demande IT au niveau du controleur NVIC
}

void InitTimer1()									// PA8 pour la PWM
{
	//Activation des horloges des périphériques concernées
	// Bit b11 TIM1EN: TIM1 timer clock enable
	RCC->APB2ENR |= (1<<11);
	
	// Horloge du GPIOA  (à voir quelle pin utilisée)
	RCC->AHBENR |= (1<<17) ;
	
	// Configuration de la pin
	// Pin PA8 => TIM1_CH1 est connecté via AF2
	// PA8 => Alternate Function
	GPIOA->MODER |=(1<<17); 
	GPIOA->MODER &=~(1<<16);
	
	// Configuration de AF2 pour PA8
 	GPIOA->AFR[1] &=~((1UL<<3)|(1<<2)|(1<<0));  // bits b3b2b0 à "000"
	GPIOA->AFR[1] |=(1<<1); 										// bit b1 à '1'
	
	// Configuration en Push-pull pour la sortie 
	GPIOA->OTYPER&=~(11<<8);
	
	// Configuration du canal de sortie du TIMER
	//	00: CC1 channel is configured as output
	TIM1->CCMR1 &=~(11<<0);
	
	
	// configuration du canal de sortie du  TIMER
	// choix du mode PWM mode 1 : In upcounting, channel 1 is active as long as TIM1_CNT < TIM1_CCR else inactive
	// TIM1 capture/compare mode register 1 (TIM1_CCMR1)	
	TIM1->CCMR1 |=(1<<6);
	TIM1->CCMR1 |=(1<<5);
	TIM1->CCMR1 &=~(1<<4);
	
	//configuration du canal de sortie du  TIMER
	// Activer le preload (prechargement automatique)
	// TIM1 capture/compare mode register 1 (TIM1_CCMR1)
	// Bit b3 OC1PE: Output compare 1 preload enable
	TIM1->CCMR1|=(1<<3);
	
	// Configuraration du canal de sortie du  TIMER
	// Definition de l'état initial de la sortie : HIGH
	//0: OC1 active high
	TIM1->CCER &=~(1<<1);
	
	// activation du mode compare
	// activation des sorties : Cas particulier du TIMER TIM1 
	// This bit is cleared asynchronously by hardware as soon as the break input is active. It is set by
	// software or automatically depending on the AOE bit. It is acting only on the channels which are
	// configured in output.
	// 1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in	TIMx_CCER register).
	TIM1->BDTR |=(1<<15);

	// activation du mode compare
	// 1 OCx=OCxREF + Polarity, OCx_EN=1
	TIM1->CCER |= (1<<0);
	
  // Configuraration du Timing
	// 0: Counter used as upcounter
	TIM1->CR1 &=~(1<<4);
	
	// Definition de la période ou fréquence du comptage
	// division de la frequence du timer par 48: soit TIM_PSC=47
	// ainsi frequence TIMx_CLK=48x10^6/(4+1)environ 10 MHz 
	TIM1->PSC=4;

	// Nous souhaitons une periode de 100 kHz
	TIM1->ARR =99;  
	
	// Rapport cyclique de 50% : division de la ARR par 2
	//TIM1->CCR1 =10;	
}


void SetPWM(int duty)
{
	TIM1->CCR1 =duty;	
	
	// démarrage du timer
	TIM1->CR1 |=(1<<0); 
}

void ClearPWM()
{
	
	TIM1->CCR1 =0 ;	
	
	// démarrage du timer
	TIM1->CR1 |=(1<<0); 
	
}


// Utilisation de la pin PA5 (qui correspond à la LED) pour piloter le phase du pont H d'alimentation du moteur ce qui permet de pouvoir debugger
void Sense(int value)
{
	if (value == 1)
			// Configuration de la phase du DRV8835 pour que le moteur recule
				GPIOA->ODR |= (1<<5);	  // bit 5 à '1'		allumage de la LED
	else
		// Configuration de la phase du DRV8835 pour que le moteur avance
			GPIOA->ODR &= ~(1<<5);	  // bit 5 à '0'		extinction de la LED	
}

/*
	Cette fonction est appellée avant l'exécution de Run() de la VM afin de lier les PINS d'entrées du microcontroleur (capteur de présenses) au tableau de variable avec lequel travail la VM
*/
void MiseAJourEntree(void)
{	
	variable[capt_pos1] = onOffPWM;
	variable[capt_pos2] = senseValue;
}
/*
	Cette fonction est appellée après l'exécution de Run() de la VM afin de lier les PINS de sorties du microcontroleur (PWM et sens pour le moteru du tapis) au tableau de variable avec lequel travail la VM
*/
void MiseAJourSortie(void)
{
	// Mise a jour de l'activation de la PWM
	if (variable[outPWM] == 1)
		SetPWM(dutyCycle);
	else
		ClearPWM();

	// Mise a jour du sens
	Sense(variable[outSense]);
	
}




