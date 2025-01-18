/********************************************************************************
| CLASS:			Polytech-Paris-UPMC, CFA-UPMC, EI-2I3-HF 
| PROGRAM:			main.c
|
********************************************************************************/

#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include "vm_codops.h"
#include <stdio.h>
#include <stdlib.h>

#include "PWM_PA8.h"
#include "initpc.h"
//#define PRESCALER_TIM2      191
//#define PRESCALER_TIM3      0

#define DEBUG 0
#define BaseDeTemps 1145
#define LED_Verte_Nucleo    (1UL<<5)

/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
int pc=0;
int sp=0;
int code[100];
int stack[100];
int var[100];
int v=0;


/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);  

void Init_UART2_Sans_Interrupt (unsigned int BaudRate);

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);  
void initPattePA5_LedVerte(void);
void run ();
void initPattePC13(void);
void AttenteActiveSansParametre(unsigned int DureeEnMilliSeconde);
void initPattePC13_BoutonPoussoirBleu_Interruption(void);
//unsigned char UART2_ReadChar_bloquant(void);
//void UART2_WriteChar_bloquant(unsigned char data);
// unsigned char UART2_ReadChar_Nonbloquant(void);


volatile unsigned int MarcheArretClignotementLedVerte=1;
volatile unsigned int CompteurPressionBouton;

/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
   
   /* == Arrivé ICI le MCU est initialise
		 Avec les parametre par défaut définis dans le fichier 
		 rest configurer : frequence de travail defini 
		 dans le system_stm32f0xx_SYSCLK_48MHz_GeneAvecRC_Int_8MHz.c	
	*/
	/*---------------------------------------------------------------------------
	  Initialisez les variables
	---------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------
	  Initialisez le matériel : périphériques... 
	---------------------------------------------------------------------------*/

	 Config_PA8_Mode_OutputPWM_TIM1_CH1();	
 initPattePC13_BoutonPoussoirBleu_Interruption();
	// Config_PB1_Mode_OutputPWM_TIM3_CH4(); 
initPattePA5_LedVerte();
	/*initPattePC5();*/
	initPattePC6();
	initPattePC8();
	initPattePC9();

	//TIM3->CR1 |=(1<<0); 							    // Start Timer TIM3
	//Init_UART2_Sans_Interrupt (9600);
    // Demarrage du Timer TIM1 en dernier
   	pc=0;
    sp=0;
	
		code[0]=I_PUSH;
		code[1]=0;
	  code[2]=I_PUSH;
	  code[3]=1;
	  code[4]=I_AND;
		code[5]=I_POP;
		code[6]=2;
		code[7]=I_HALT;
	  var[2]=1;
		//run();
   TIM1->CR1 |=(1<<0); 
		
  	while(1)   // Boucle principale ou infinie
   	{
   		 /*lire pinouille 0 et mettre dans var[0]
		 Mettre la valeur de la patte dans var[0]*/
		 //
		/*lire pinouille 1 et mettre dans var[1]
		 Mettre la valeur de la patte dans var[0]*/
		 //
/***************************************************************************
			Si le capteur de presence est a 1
			alors on arrete de faire tourner le moteur.
			On attend alors pendant un certain temps grace a la fonction
				 AttenteActiveSansParametre(250)
			Qui servira pour attendre que la barquette soit remplie, puis le moteur redemarera
		
***************************************************************************/
/*	 Cette partie en commantaire aurait du servir pour tester les pattes 
		PC6 PC8 PC9
	Le but était de mettre en marche le timer ou non, selon ce que doit 
	renvoyer un capteur à savoir 0 ou 1
*****************************************************************************/
//		  if(  ( GPIOC->OTYPER &=~(1UL<<6))==1)//PC6
//		 {
//			  TIM1->CR1 &=~(1<<0); 							    // Stop Timer TIM1	     
//		 }
//	
//		 else
//	
//		  AttenteActiveSansParametre(250); //250ms
//		 
//		  if(  ( GPIOC->OTYPER &=~(1UL<<8))==1)//PC8
//		 {
//			  TIM1->CR1 &=~(1<<0); 							    // Stop Timer TIM1		     
//		 }
//	
//		 else
//		 {
//	    TIM1->CR1 |=(1<<0); 							    // Start Timer TIM1
//		 }
//		  AttenteActiveSansParametre(250); //250ms
//		 if(  ( GPIOC->OTYPER &=~(1UL<<9))==1)//PC9
//		 {
//			  TIM1->CR1 &=~(1<<0); 							    // Stop Timer TIM1							     
//		 }
//	
//		 else
//		 {
//	    TIM1->CR1 |=(1<<0); 			// Start Timer TIM1
//		 }
//		  if ((GPIOC->IDR &(1<<13))==(1<<13)) // le bit b13 de VarReg vaut '1' 
//	  { 
//			//eteindre led
//			GPIOA->ODR&=~(1<<5);  // bit b13 à '0' 
//	   } 
//	   else  // le bit b2 de VarReg vaut '0' 
//	   {  
//			// Allume Led
//		  GPIOA->ODR|=(1<<5);   // bit b5 à '1'
//			//cpt=cpt+1;
//			}

	AttenteActiveSansParametre(250); //250ms
/************************************************************************/
/************************************************************************/
		 
		 //;
		 /*suivant la var[2]
			allumer ou pas LED
		 */ 
		 //var[0]=GPIOC->IDR &(1<<13); 
		 //GPIOC->IDR &(1<<13))==(1<<13)) // le bit b13 de VarReg vaut '1' 
	
		 //pc=0;
  
		 //   sp=0;
		 //var[0]=1;
		 //var[1]=1;
		 //run();
		 
		 /*if (var[2]==1){
			GPIOA->ODR |=(1<<5); // Allumer la LED
			 //var[2]=0;
			 //sleep(10);
			 AttenteActiveSansParametre(250);
		 }else{
			GPIOA->ODR &=~(1<<5);// Eteindre la LED
			//var[2]=1;
			//sleep(10);
			 AttenteActiveSansParametre(250);
		 }*/
			

   }
   // Fin : Le CPU n'arrivera jamais ici
}

// FIN FONCTION MAIN

/* declarer les variables locales à la fonction main */
	//unsigned int cpt=0;
                               // variable pour compter
  /* Initialiser les peripheriques utiles à l'application  : 
     En general on regroupe les initialisation dans une  ou plusieurs fonctions 
     Ces instructions ou appel de fonctions seront exécutées une seule fois    */
    //initPattePB13_LedVerte();
    
  /* while(1)   // Boucle principale ou infinie
   {  if ((GPIOC->IDR &(1<<13))==(1<<13)) // le bit b13 de VarReg vaut '1' 
	  { 
			//eteindre led
			GPIOA->ODR&=~(1<<5);  // bit b13 à '0' 
	   } 
	   else  // le bit b2 de VarReg vaut '0' 
	   {  
			// Allume Led
		  GPIOA->ODR|=(1<<5);   // bit b5 à '1'
			//cpt=cpt+1;
			}
		 	//if (cpt==1000000){
			// Allume Led
		  //GPIOA->ODR&=~(1<<5);   // bit b5 à '1'
		  //AttenteActiveSansParametre(1000);
			//cpt=0;
	   }
   // Fin : Le CPU n'arrivera jamais ici*/
/*===============================================================================
  FUNCTION:     void initPattePA5_LedVerte(void)
  DESCRIPTION:  Configuration de la patte PA5 (PORT A, GPIOA) en mode sortie
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void initPattePA5_LedVerte(void)
{
   RCC->AHBENR |=(1<<17);     // Activation horloge du GPIOA
   GPIOA->MODER &=~(1<<11);   // choix mode General Purpose Output bit b11 à '0'
   GPIOA->MODER |=(1<<10);    // choix mode General Purpose Output bit b10 à '1'
   GPIOA->OTYPER &=~(1<<5);   // choix techno de sortie Push-Pull : bit b5 à '0'
   GPIOA->PUPDR &=~(1<<11);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOA->PUPDR &=~(1<<10);   // desactivation resistance de tirage: bit b10 à '0'
   GPIOA->OSPEEDR&=~(1<<11);  // bit b11 à '0'
   GPIOA->OSPEEDR&=~(1<<10);  // bit b10 à '0'
}
/*===============================================================================
  FUNCTION:     void Init_UART2_Sans_Interrup (unsigned int BaudRate)
  DESCRIPTION:  Configuration UART2 (PA2->Tx, PA3->Rx), hardware via USB debuger STLINK
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   unsigned int BaudRate
  RETURNS:   	rien   
  REQUIREMENTS: BaudRate depend de la frequence  
===============================================================================*/
void Init_UART2_Sans_Interrupt (unsigned int BaudRate){

  /*Activation horloge GPIOA pour la configuration des pattes PA2 et PA3*/
   RCC->AHBENR |=(1<<17); 
  /*Activation horloge UART2 pour la configuration de l'UART2 */
   RCC->APB1ENR|=(1<<17);       
   
// configuration des pattes
   // configuration PA2 (Tx)
   GPIOA->MODER |=(1<<5);      // choix Alternate Function pour PA2 bit b5 à '1'
   GPIOA->MODER &=~(1<<4);     // choix Alternate Function pour PA2 bit b4 à '0'
   GPIOA->AFR[0]&=~(1<<11);     // choix AF1 comme alternate function : bit b11 à '0'
   GPIOA->AFR[0]&=~(1<<10);     // choix AF1 comme alternate function : bit b10 à '0'
   GPIOA->AFR[0]&=~(1<<9);      // choix AF1 comme alternate function : bit b9 à '0'
   GPIOA->AFR[0]|=(1<<8);       // choix AF1 comme alternate function : bit b8 à '1'
   GPIOA->OTYPER &=~(1<<2);    // choix techno de sortie Push-Pull : bit b2 à '0'
   GPIOA->PUPDR &=~(1<<5);     // desactivation resistance de tirage: bit b5 à '0'
   GPIOA->PUPDR &=~(1<<4);     // desactivation resistance de tirage: bit b4 à '0'
   GPIOA->OSPEEDR&=~(1<<5);    // Vitesse de rafraichissement bit b5 à '0'
   GPIOA->OSPEEDR&=~(1<<4);    // Vitesse de rafraichissement bit b4 à '0'
   
  // configuration PA3 (Rx)
   GPIOA->MODER |=(1<<7);      // choix Alternate Function pour PA2 bit b5 à '1'
   GPIOA->MODER &=~(1<<6);     // choix Alternate Function pour PA2 bit b4 à '0'
   GPIOA->AFR[0]&=~(1<<15);     // choix AF1 comme alternate function : bit b11 à '0'
   GPIOA->AFR[0]&=~(1<<14);     // choix AF1 comme alternate function : bit b10 à '0'
   GPIOA->AFR[0]&=~(1<<13);      // choix AF1 comme alternate function : bit b9 à '0'
   GPIOA->AFR[0]|=(1<<12);       // choix AF1 comme alternate function : bit b8 à '1'
   GPIOA->PUPDR &=~(1<<7);     // desactivation resistance de tirage: bit b7 à '0'
   GPIOA->PUPDR &=~(1<<6);     // desactivation resistance de tirage: bit b6 à '0'
   
  //**configuration de USART2 *
   
   //* definition de la vitesse de communication
  //  USARTx_BRR  = Frequence du Module/Baude_Rate
   // ici nous voulons BaudeRate=96000 et la frequence du module vaut SystemCoreClock
   
   USART2->BRR=(SystemCoreClock/BaudRate);
  // * definition du format du train de bits *
	 USART2->CR1&=~((1<<12)|(1<<28));     // 8 bits de données, 1 bit START
   USART2->CR1&=~((1<<10));             // pas de Parité
   USART2->CR2&=~((1<<13)|(1<<12));     // 1 bit STOP
   USART2->CR1|=((1<<3)|(1<<2)|(1<<0)); // Activer USART3, Activer Reception, activer Transmission
}


/*===============================================================================
  FUNCTION:     unsigned char UART2_ReadChar_bloquant(void)
  DESCRIPTION:  Lecture caractere via USART2 PA2 (Tx), PA3 (Rx)
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   rien
  RETURNS:   	caractere lu  
  REQUIREMENTS: configurer USART2 
===============================================================================*/
unsigned char UART2_ReadChar_bloquant(void){
  //Attente que le registre de reception soit rempli par le code du caractere recu 
	 //   scrutation du bit b5 RXNE du registre Interrupt & status register (USARTx_ISR)
	 //   si ce bit passe a '1' c'est que le caractère est recu 
		 
			while (!(USART2->ISR & (1 << 5)))
			{
				// on reste dans cette boucle tant que le caracterse n'est pas arrivee 
				//  tant que bit b5 (RXNE) vaut '0' 
				
			}

  return((unsigned char)(USART2->RDR));
}


/*===============================================================================
  FUNCTION:     void run ()
  DESCRIPTION:  
  PARAMETERS:   rien
  RETURNS:   	   
  REQUIREMENTS:
===============================================================================*/

void run (){
	while (code[pc]!=I_HALT)
	{
		//if (DEBUG) printf("code[%d] : %d \n",pc, code[pc]);
		switch (code[pc])
		{
			case I_PUSHI : stack[sp]=code[++pc];
			//if (DEBUG) printf("stack[%d] : %d \n",sp, stack[sp]);
			pc++;
			sp++;
			break;

			case I_ADD : stack[sp-1]=stack[sp]+stack[sp-1];
			pc++;
			sp--;
			//if (DEBUG) printf("Resultat addition stack[%d] : %d \n",sp, stack[sp]);
			break;

			case I_MULT : 
			//if (DEBUG) printf("stack[sp-2]=%d, stack[sp-1]=%d,stack[sp-2]=%d\n",stack[sp-2],stack[sp-1],stack[sp-2]);
			stack[sp-2]=stack[sp-1]*stack[sp-2];
			pc++;
			sp=sp-2;
			//if (DEBUG) printf("Resultat mult stack[%d] : %d \n",sp, stack[sp]);
			break;

		// PUSH registre met le contenu du registre dans la pile (empilement).
			case I_PUSH : 
			stack[sp]=var[v];
			sp++;
			v++;
			break;

		//POP registre récupère le contenu de la pile et le stocke dans le registre (dépilage).
			case I_POP : 
			var[v]=stack[sp];
			sp--;
			v++;
			break;

		// Si c'est égal alors on passe à l'instruction suivante sinon on cherche JF
			case I_EQ :
			if (stack[sp]==stack[sp-1]){
				pc++;
			}else{
				while (code[pc]!=I_JF) pc++;
			}
		        break; 

			case I_GT : 
			if (stack[sp]>stack[sp-1]){
				stack[sp-1]=1;
				pc++;
			}else{
				stack[sp-1]=0;
				while (code[pc]!=I_JF) pc++;
			}
			break;

			case I_LS :
			if (stack[sp]<stack[sp-1]){
				stack[sp-1]=1;
				pc++;
				sp--;
			}else{
				stack[sp-1]=0;
				while (code[pc]!=I_JF) pc++;
			}
			break;

			case I_AND :
			if ((stack[sp-1]==1)&&(stack[sp-2]==1)){
				stack[sp-2]=1;
			}else{
				stack[sp-2]=0;
			}
			pc++;
			sp=sp-2;
			break;
			
		//JF : si EQ est faux alors va à la ligne de l'étiquette qui suit JF
			case I_JF : 
			pc = code[pc+1];
			break;

			case I_J : 
			pc= code[pc+1];
			break;

			default : pc++;
		}
	}
}
/*===============================================================================
  FUNCTION:     AttenteActiveSansParametre(void)
  DESCRIPTION:  On fait compter le CPU du MCU dans le vide! pour attendre
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: Ajuster la valeur max du compteur en fonction de la frequence du CPU
===============================================================================*/
void AttenteActiveSansParametre(unsigned int DureeEnMilliSeconde)
{
 // Faire attendre le CPU : Attente active car il comptera dans le vide
        unsigned int compteurUniteTemps;
        unsigned int compteurNombreUniteTemps;
   
        for (compteurNombreUniteTemps=0; compteurNombreUniteTemps<DureeEnMilliSeconde; compteurNombreUniteTemps++)
        {
          // boucle d'attente vide pour faire attendre le CPU 
                for (compteurUniteTemps=0; compteurUniteTemps<BaseDeTemps; compteurUniteTemps++)
                {
                    // boucle d'attente vide pour faire attendre le CPU            
            
                }
            
        }   
}
/*===============================================================================
  FUNCTION:     void UART2_WriteChar_bloquant(unsigned char data)
  DESCRIPTION:  ecrire caractere via USART2 PA2 (Tx), PA3 (Rx)
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   unsigned char data
  RETURNS:   	rien   
  REQUIREMENTS: configurer USART2 
===============================================================================
void UART2_WriteChar_bloquant(unsigned char data){
 Pour la transmission
	Attente que le registre de transmission de l'UART soit vide 
	scrutation du bit b7 (TXE): Transmit data register empty 
	du registre Interrupt & status register (USARTx_ISR)
	si ce bit passe a '1' c'est que le caractère est trannsmis 
	et le registre de transmission est vide

	while(!(USART2->ISR & 1 << 7))
	{
		 //tant que TXE est à '0' on attend ici! 
	}       
	// Arrivé ici c'est TXE vaut '1' : donc on peux envoyer un autre caractère 
	
	USART2->TDR = data; 			// ecriture du caractere dans le registre de transmission  
}*/

/*===============================================================================
  FUNCTION:     void UART2_ReadChar_Nonbloquant(unsigned char data)
  DESCRIPTION:  ecrire caractere via USART2 PA2 (Tx), PA3 (Rx)
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   rien
  RETURNS:   	caractere   
  REQUIREMENTS: configurer USART2 
===============================================================================*/

/*unsigned char UART2_ReadChar_Nonbloquant(void){
  if((USART2->ISR & (1 << 5)))
  {
    return((unsigned char)(USART2->RDR));
  } 
  else
  {
    return 0;
  }
}*/

/*===============================================================================
  FUNCTION:     void initPattePC13(void)
  DESCRIPTION:  Configuration de la patte PC13 (PORT C, GPIOC) en mode sortie
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

//void initPattePC13(void)
//{
//   RCC->AHBENR |=(1<<19);     // Activation horloge du GPIOC
//   GPIOC->MODER &=~(1<<27);   // choix mode General Purpose Output bit b27 à '0'
//   GPIOC->MODER &=~(1<<26);    // choix mode General Purpose Output bit b26 à '1'
//   GPIOC->OTYPER &=~(1<<13);   // choix techno de sortie Push-Pull : bit b13 à '0'
//   GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b27 à '0'
//   GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b26 à '0'
//   GPIOC->OSPEEDR&=~(1<<27);  // bit b27 à '0'
//   GPIOC->OSPEEDR&=~(1<<26);  // bit b26 à '0'
//}

/*===============================================================================
  FUNCTION:     EXTI4_15_IRQHandler(void)
   DESCRIPTION:  Routine d'interruption : Attention fonction déclenchée matériellement
                    si changement d'état ou de niveau sur les pattes Numero 4  à 15. 
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void EXTI4_15_IRQHandler(void)
{
   // tache a faire si interruption externes des pattes Numerotées de 4 à 15
   // ici on a configuré uniquement la patte PC13
   // mais on verifier que c'est bien la patte 13 (PC13) qui demande interruption
    /* Verifier que c'est bien la patte PC13 qui demande interruption*/
  if(EXTI->PR&(1<<13))                 // Test du drapeau bit b13 (PR13) du registre EXTI_PR de demande interruption
	{
		/* Si on arrive ici c'est que c'est bien PC13 qui demande interruption*/
		EXTI->PR|=(1<<13);                // il faut acquiter la demande : on ecrit '1' pour effacer le drapeau !. 
		GPIOA->ODR ^=(1<<5); // Changer etat de la LED verte
		
		TIM1->CR1 ^=(1<<0);  //changer etat timer1 donc pwm
		
      
	}
      
}
  

/*===============================================================================
  FUNCTION:     void initPattePC13_BoutonPoussoirBleu_Interruption(void)
  DESCRIPTION:  Configuration de la patte PC13 (PORT C, GPIOC) en mode entrée simple
				+ activation demande interruption si front descendant
				+ démasquage de la demande au niveau du NVIC pour que ce CPU soit sensible
				  a la demande
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: Lire ce code avec le transparent de cours correspondant
===============================================================================*/
void initPattePC13_BoutonPoussoirBleu_Interruption(void)
{
    //1. Activer horloge du GPIOx concernée : ici GPIOC
    RCC->AHBENR |=(1<<19);     // Activation horloge du GPIOC
  //2. Configurer la patte en mode INPUT 
    GPIOC->MODER &=~(1<<27);   // choix  Input mode bit b27 à '0'
    GPIOC->MODER &=~(1<<26);   // choix  Input mode bit b26 à '0'
  //3.désactiver les résistances de tirages 
    GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b11 à '0'
    GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b10 à '0'
  //4. Activer horloge du périphérique :System configuration controller (SYSCFG)  
   RCC->APB2ENR|=(1<<0);
  //5.Relier la patte à une entrée du contrôleur  d’interruption externe (EXTI). 
  // la patte PC13 a relier à l'entrée EXTI13
  // il faut ecrire "0010" sur les bites b7b6b5b4 du registre SYSCFG_EXTICR4
  // avec l'interface CMSIS, SYSCFG_EXTICR4 = SYSCFG->EXTICR[3]
    SYSCFG->EXTICR[3] &=~((1<<7)|(1<<6)|(1<<4));
	SYSCFG->EXTICR[3] |=(1<<5);
  //6. Activer l’entrée 13 du EXTI 
    EXTI->IMR|=(1<<13);
  //7. Indiquer la nature électrique du signal de déclenchement
  // Ici nous souhaitons du Front descendant car selon le schema electrique
  // de la carte si Bouton Appuyé PC13 ='0' si non '1'
    EXTI->FTSR|=(1<<13);
  //8. Activer ou démasquer le vecteur d’interruption au nviveau du NVIC: Utilisation de fonction CMSIS
  // pour que le CPU y soit sensible 
    NVIC_EnableIRQ(EXTI4_15_IRQn);
  // on peux donner une priorité à cette source d'interruption
  // on utilisera la fonction  NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
  // Comme il y a une seule demande d'interruption ce n'est pas nécessaire 
}


