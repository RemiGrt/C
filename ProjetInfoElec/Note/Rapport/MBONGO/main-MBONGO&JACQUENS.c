/*
	Etudiants : MBONGO SELDIE & JACQUENS ANISSA
	Description : Ce programme :
	- génère la PWM sur la patte PA8
	- gère la liaison série 
	- affecte les differentes entrées et sorties en fonction du scénario
	- Fait fonctionner la machine virtuelle sur le micro-contrôleur
*/

#include <stdio.h>
#include <string.h>

//Instructions assembleur
#define I_ADD 0
#define I_MULT 1
#define I_PUSHI 100
#define I_HALT 400
#define I_PUSH 101
#define I_EQ 11
#define I_POP 102
#define I_JF 200 
#define I_J 201
#define I_LS 4
#define I_AND 9
#define I_SUB 8
#define I_NEG 7
#define I_GT 2
#define I_OR 3
#define I_NOT 5



#define BUT1 (1UL<<13)
#define LED  (1UL<<5) 


#include "stm32f0xx.h"   // definition des registre de stm32f0xxx : CMSIS 



char Caractere_Recu[10];  
int k=0;


//Prototypes
void initPattePA5_LedVerte(void);
void initPatte_PC13(void); //bouton poussoir
void Init_UART2_Avec_Interrupt (unsigned int BaudRate); //Liaison série
void USART2_IRQHandler(void);

void initPatte_PC5(void);	//capteur start
void initPatte_PC6(void);	//capteur position 1
void initPatte_PC8(void); //capteur position 2
void initPattePA12_moteur(void); //phase sens moteur 

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);//fonction qui génère la PWM avec une fréquence de 10khz

void run(void); 
void vm_code(void);
int CodeComplet(void);

#define N 100

int variable[N];
int code[N];

//Programme principal

int main (void)
{	
	int var_verif=0;
	int old_but0 = 0;
	int capt0 = 0;
	int capt1 = 0;
	int capt2 = 0;
	int a, b, c, d;
	
	//initialisation des sorties
	variable[12]=0;
	variable[13]=0;
	variable[14]=0;
	variable[15]=0;
	
	initPattePA5_LedVerte(); //Initialisation de la patte PA5
	initPattePA12_moteur(); //Initialisation de la patte PA12
	initPatte_PC13(); //Initialisation de la patte PC13

    Config_PA8_Mode_OutputPWM_TIM1_CH1(); //Génère la PWM pour moteur sur la patte PA8
	TIM1->CR1 |=(1<<0);

	Init_UART2_Avec_Interrupt (9600); //Initialisation de la liaison série
	
	
	//code scenario tapis
	
	//if((capt0 == 0) && (variable[3] == 1)
	
	code[0] = 101;  //on fait push de 1
	code[1] = 1;								// si c'est faux on fait le JF
	code[2] = 200; //JF
	code[3] = 14;								// si c'est vrai on fait le push
	code[4] = 101; // on fait le push de 13
	code[5] = 13;  	// on fait le not 
	code[6] = 70;  
	code[7] = 102; //pop de 13
	code[8] = 13;
	code[9] = 101; //push de 12
	code[10] = 12;
	
	code[11] = 70; //not
	code[12] = 102; //pop de 12
	code[13] = 12;	
	code[14] = 101; //push de 1
	code[15] = 1; //si faux 								
	code[16] = 200; // JF
	code[17] = 26; //on passe à la ligne 26
	code[18] = 100; //pushi de 0
	code[19] = 0;
	code[20] = 102; //pop de 15
	code[21] = 15; 
	code[22] = 100; //pushi de 1
	code[23] = 1;
	code[24] = 102; //pop de 14
	code[25] = 14;
	
	code[26] = 101; //push de 2
	code[27] = 2; 							//Si faux 
	code[28] = 200; //JF
	code[29] = 38; //on passe à la ligne 38	
	code[30] = 100; //pushi 0
	code[31] = 0;
	code[32] = 102; //pop 14
	code[33] = 14;
	code[34] = 100; //pushi de 1
	code[35] = 1;
	code[36] = 102; //pop 15
	code[37] = 15;

	code[38] = 400; //fin
	
	
	while(1)   // Boucle principale ou infinie
	{		
		
		
	//Lecture des entrées
		//on gère le bouton poussoir PC13
		a = GPIOC->IDR & (1<<13);
		if (a) //boutton actif à l'etat bas
				variable[0] = 0; //boutton relaché
		else variable[0] = 1; //boutton enfoncé
		
		if ((old_but0 == 0) && (variable[0] == 1)) //Le bouton est sur front montant
	  variable[1] = 1;
		else	variable[1] = 0;
		if ((old_but0 == 1) && (variable[0] == 0)) //front descendant bouton
			variable[2] = 1;
		else variable[2] = 0;
		
		
		//capteur permettant de gérer le start
		b = GPIOC->IDR & (1<<5);
		if (b) //capteur actif à l'etat haut		
			variable[3] = 1; //capteur actif
		else variable[3] = 0; //capteur non actif

		if ((capt0 == 0) && (variable[3] == 1)) ////le bouton est sur front montant capteur
			variable[4] = 1;
		else variable[4] = 0;
		
		if ((capt0 == 1) && (variable[3] == 0)) //le bouton est sur front descendant
			variable[5] = 1; //front descendant
		else variable[5] = 0;
		
		//capteur1 : il gère le sens du moteur : Position1 PC6
		c = GPIOC->IDR & (1<<6);
		if (c) //capteur actif à l'etat haut		
			variable[6] = 1; //capteur actif
		else variable[6] = 0; //capteur non actif

		if ((capt1 == 0) && (variable[6] == 1)) //le capteur est sur front montant
			variable[7] = 1; //front montant
		else variable[7] = 0; //sinon 

		if ((capt1 == 1) && (variable[6] == 0)) //le bouton est sur front descendant bouton
			variable[8] = 1;
		else variable[8] = 0;
		
		//capteur2 il gère le sens du moteur : Position2 => PC8
		d = GPIOC->IDR & (1<<8);
		if (d) //le capteur est actif à l'etat haut	
			variable[9] = 1; //capteur actif
		else variable[9] = 0; //le capteur n'est pas actif
		
		if ((capt2 == 0) && (variable[9] == 1)) //front montant capteur
			variable[10] = 1;
		else variable[10] = 0;
		
		//cette variable permet de dire si l'opcode est complet, on la passe à 1 lorsque le code est complet
		var_verif = CodeComplet(); 
		if(var_verif == 1) //le code est complet 
		{
			run(); // appel à la fonction run() qui exécute la VM
		}
			
		
/*************affectation des sorties*************************/
		if (variable[12] == 1) //valeur de la LED, chaque appui sur le bouton allume la led
			GPIOA->ODR |= (LED);//ici on allume la led 
		else GPIOA->ODR &= ~(LED); //ici on éteint la led 
		
		
		/*Marche arrêt du moteur */
		if (variable[13] == 1) //on gère la valeur du moteur quand c'est en marche ou arêté 
			TIM1->CCR1 = 25; ////la PWM est générée avec un rapport cyclique de 25%
		else TIM1-> CCR1 = 0; //le moteur est éteint on arrête la PWM => ça passe à 0 
	  
		//sens1 du moteur
		if (variable[14] == 1) //le moteur tourne dans un sens
			GPIOA->ODR |= (1<<12); //la phase à 1 sur la patte PA12
		else GPIOA->ODR &= ~ (1<<12);
		
		//sens2 du moteur
		if (variable[15] == 1) //le moteur tourne dans l'autre sens
			GPIOA->ODR &= ~(1<<12); //la phase à 0 sur la patte 12
		else GPIOA->ODR |=  (1<<12);
		//détection des fronts
		old_but0 = variable[0];
		capt0 = variable[3];
		capt1 = variable[6];
		capt2 = variable[9];
	         	
	}

}


//Fonction run(), elle implémente la machine virtuelle sur le microcontroleur.

void run()
{
	int stack[100];
	int sp=-1,pc=0;
	
	
	while(code[pc]!=I_HALT)
	{
		switch (code[pc]) 
		{

			case I_PUSHI :				
			stack[++sp]=code[pc+1];			
			pc=pc+2;
			break;
			
			case I_PUSH:
			stack[++sp]=variable[code[pc+1]];
			pc=pc+2;
			break;
			
			case I_POP:
			variable[code[pc+1]]=stack[sp];
			pc=pc+2;
			break;
		
			case I_ADD :
			stack[sp-1]=stack[sp]+stack[sp - 1];
			sp--;
			pc++;
			break;
		
			case I_SUB :
			stack[sp-1]=stack[sp]-stack[sp - 1];
			sp--;
			pc++;
			break;

			case I_NEG :
			stack[sp]=0-stack[sp];
			pc++;
			break;

			case I_MULT :
					
			stack[sp-1]=stack[sp]*stack[sp - 1];
			sp--;			
			pc++;
			break;
			
			case I_EQ:
		
			if (stack[sp - 1] == stack[sp]) 
				stack[sp - 1]=1;
			else stack[sp - 1]=0;
			sp--;
			pc++;	
			break;
		
			case I_LS:
			if (stack[sp-1]>stack[sp]) 
			{
				stack[sp-1]=1;
			}
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_GT :
			if (stack[sp-1]<stack[sp]) 
				stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_NOT:
			stack[sp]=!(stack[sp]);
			pc++;	
			break;

			case I_AND:
			if (stack[sp-1] && stack[sp]) 
				stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_OR:
			if (stack[sp-1]||stack[sp]) 
				stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_J:
			if(stack[sp] == 1)
			{
				pc=code[pc+1];
			}
			else
			{
				pc+=2;
			}	 
			break;
			
			case I_JF:
			if(stack[sp] != 1)
			{
				pc=code[pc+1];
			}
			else
			{
				pc+=2;
			}	 
			break;
		
		}
		
	}

}




//Initialisation de la patte PA5 en sortie (LED verte)
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
	 GPIOA->ODR&=(~LED);
}

//Initialisation de la patte PA12 en sortie qui déterminera le sens du moteur 
void initPattePA12_moteur(void)
{
   RCC->AHBENR |=(1UL<<17);     // Activation horloge du GPIOA
   GPIOA->MODER &=~(1UL<<25);   // choix mode General Purpose Output bit b11 à '0'
   GPIOA->MODER |=(1UL<<24);    // choix mode General Purpose Output bit b10 à '1'
   GPIOA->OTYPER &=~(1UL<<12);   // choix techno de sortie Push-Pull : bit b5 à '0'
   GPIOA->PUPDR &=~(1UL<<25);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOA->PUPDR &=~(1UL<<24);   // desactivation resistance de tirage: bit b10 à '0'
   GPIOA->OSPEEDR&=~(1UL<<25);  // bit b11 à '0'
   GPIOA->OSPEEDR|=(1UL<<24);  // bit b10 à '0'
	 GPIOA->ODR&=~(1<<12);
}

//Initialisation de la patte PC13 => gère le bouton
void initPatte_PC13(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     // Activation horloge du GPIOB
   GPIOC->MODER &=~(1<<27);   // choix mode General Purpose Output bit b19 à '0'
   GPIOC->MODER &=~(1<<26);    // choix mode General Purpose Output bit b18 à '0'
   GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b10 à '0'
}

//Initialisation de la patte PC5 en entrée capteurStart)
void initPatte_PC5(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     
   GPIOC->MODER &=~(1<<11);   
   GPIOC->MODER &=~(1<<10);    
   GPIOC->PUPDR &=~(1<<11);   
   GPIOC->PUPDR &=~(1<<10);   
}

//Initialisation de la patte PC6 en entrée (capteurPosition1)
void initPatte_PC6(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     
   GPIOC->MODER &=~(1<<13);   
   GPIOC->MODER &=~(1<<12);    
   GPIOC->PUPDR &=~(1<<13);  
   GPIOC->PUPDR &=~(1<<12);
}  

//Initialisation de la patte PC8 en entrée (capteurPosition2)
void initPatte_PC8(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;	
   GPIOC->MODER &=~(1<<17);						
   GPIOC->MODER &=~(1<<16);    				
   GPIOC->PUPDR &=~(1<<17);   				
	 GPIOC->PUPDR &=~(1<<16);
}


//Configuration de la patte PA8 en sortie pour la PWM
void Config_PA8_Mode_OutputPWM_TIM1_CH1(void) 
{
	// 1. Activer les horloges des périphériques concernées
	// 1.1 APB peripheral clock enable register 2 (RCC_APB2ENR)
	// Bit b11 TIM1EN: TIM1 timer clock enable
		// 0: TIM1 clock disabled
		// 1: TIM1 clock enabled
	RCC->APB2ENR |= (1<<11);

	//  1.2 Horloge du GPIOA
	// registre AHB peripheral clock enable register  (RCC_AHBENR)
	// bit b17 GPIOAEN '1'
	RCC->AHBENR |= (1<<17) ;
	
	// 2. Configurer la ou les Pattes
	// 2.1 identifier la ou les pattes 
	// Nous utiliserons la patte PA8 car TIM1_CH1 est connecté via AF2
	// 2.2 Choix de Alternate Function pour la patte PA8
	// registre GPIOA_MODER 
	// bits b17b16 à "10"
	GPIOA->MODER |=(1<<17); 
	GPIOA->MODER &=~(1<<16);
	
	// 2.3 Choix de la fonction AF2 pour PA8
	// registre alternate function high register (GPIOx_AFRH) 
	// bits b3b2b1b0 à "0010" 
 	GPIOA->AFR[1] &=~((1UL<<3)|(1<<2)|(1<<0));  // bits b3b2b0 à "000"
	GPIOA->AFR[1] |=(1<<1); 

	// 2.4 choisir Push-pull pour la sortie 
	// registre Registre GPIO port output type register (GPIOx_OTYPER)
	// bit b8 à '0' : Push-pull
	GPIOA->OTYPER&=~(1<<8);
	GPIOA->OTYPER&=~(1<<9);
	
	// 2.5 Choisir la vitesse de rafraisissement
	// registre GPIO port output speed register (GPIOx_OSPEEDR)
	// Bits 2y+1:2y OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	// bits b17b16 à "00" : very low-speed
	GPIOA->OSPEEDR&=~(1<<17);
	GPIOA->OSPEEDR&=~(1<<16);
	

	/* 3. configurer le canal de sortie du  TIMER
		3.1 choix du mode output pour TIM1_CH1--> IC1 is mapped on TI1
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		Bits 1:0 CC1S: Capture/Compare 1 selection
			00: CC1 channel is configured as output
			01: CC1 channel is configured as input, IC1 is mapped on TI1
			10: CC1 channel is configured as input, IC1 is mapped on TI2
			11: CC1 channel is configured as input, IC1 is mapped on TRC. 
	*/
	TIM1->CCMR1 &=~(1<<1); 
	TIM1->CCMR1 &=~(1<<0);
	
	/* 3. configurer le canal de sortie du  TIMER
		3.2 choix du mode PWM mode 1
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		bits b6b5b4 OC1M[2:0]: OC1M: Output Compare 1 mode : "110": PWM Mode 1
	*/	
	TIM1->CCMR1 |=(1<<6);
	TIM1->CCMR1 |=(1<<5);
	TIM1->CCMR1 &=~(1<<4);
	
	/* 3. configurer le canal de sortie du  TIMER
		3.3 Activer le preload (prechargement automatique)
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		Bit b3 OC1PE:Output compare 1 preload enable
		    0: Preload register on TIMx_CCR2 disabled. TIMx_CCR2 can be written at anytime, the
			1: Preload register on TIMx_CCR2 enabled. Read/Write operations access the preload
    */
	TIM1->CCMR1|=(1<<3);


	/* 3. configurer le canal de sortie du  TIMER
		3.4 Definir l'état initial de la sortie : ici HIGH
		registre TIM1  capture/compare enable register (TIM1_CCER and TIM1_CCER)
		Bit b1 CC1P: Capture/Compare 1 output polarity
		0: OC1 active high
		1: OC1 active low

    */
	TIM1->CCER &=~(1<<1);
	
	
	/* 4. activation du mode compare
	   4.1 activation des sorties : Cas particulier du TIMER TIM1 
	    registre : TIM1 break and dead-time register (TIM1_BDTR)
		Bit 15 MOE: Main output enable
		This bit is cleared asynchronously by hardware as soon as the break input is active. It is set by
		software or automatically depending on the AOE bit. It is acting only on the channels which are
		configured in output.
		0: OC and OCN outputs are disabled or forced to idle state.
		1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in
		TIMx_CCER register).
	*/
	TIM1->BDTR |=(1<<15);

	/* 4. activation du mode compare
	   4.2 registre : TIMx capture/compare enable register (TIMx_CCER)
		bit b0 CC1E: Capture/Compare 1 output enable. refer to CC1E description
		0 Output Disabled (OCx=0, OCx_EN=0)
		1 OCx=OCxREF + Polarity, OCx_EN=1
	*/

	TIM1->CCER |= (1<<0);
   // 5. Configurer le Timing 
	// 5.1. Selection du mode de comptage du TIM1 
	// registre : TIMx control register 1 (TIMx_CR1)
	// Bit 4 DIR: Direction
	// 0: Counter used as upcounter
	// 1: Counter used as downcounter
	// Bit b4 à '0'
	TIM1->CR1 &=~(1<<4);
	
	// 5.2 Definition de la période ou fréquence du comptage 
	// Dans cet exemple nous souhaitons que le Timer compte 
	// le plus rapidement possible
	// divisons la frequence du timer par 48: soit TIM_PSC=47
	// ainsi frequenceTIMx_CLK=48x10^6/(47+1) =1 MHz 
	TIM1->PSC=47;

	// Nous souhaitons une periode de 10 kHz
	TIM1->ARR =25;  
	
	// 5. Rapport cyclique de 25% : division de la ARR par 4
	TIM1->CCR1 =0;

}

//Action à réaliser lorsqu'un caractère est reçu sur l'USART2
void USART2_IRQHandler(void)
{
	int i;
		if (USART2->ISR&(1<<5))
		{
			Caractere_Recu[k] =  USART2->RDR; //on stocke les caractères reçus
			if (Caractere_Recu[k] == '@') //si on reçoit un '@' c'est que la ligne entière dde code à été reçue
			{
				Caractere_Recu[k+1] = '\0';
				vm_code();
				for(i=0;i<(k+1);i++)
				{
					while(!(USART2->ISR & 1<<7))
					{
					}
					USART2->TDR = Caractere_Recu[i]; //on renvoie les caractères recus pour confirmer la réception du code
				}
				k=0;
			}
			else 
			{
				k++;
			}
		}


}

//Initialisation de l'interruption pour la liaison série lors de la réception d'un caractère
void Init_UART2_Avec_Interrupt (unsigned int BaudRate){

  unsigned int Num_AF=1;
	unsigned int Num_Patte;
	//Activation horloge GPIOA pour la configuration des pattes PA2 et PA3
   RCC->AHBENR |=(1<<17); 
   //Activation horloge UART2 pour la configuration de l'UART2
   RCC->APB1ENR|=(1<<17);       
   
   //configuration des pattes
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
      
   //configuration de USART2 
   
   // definition de la vitesse de communication
   // USARTx_BRR  = Frequence du Module/Baude_Rate
   // ici nous voulons BaudeRate=96000 et la frequence du module vaut SystemCoreClock
   
   USART2->BRR=(SystemCoreClock/BaudRate);
   // definition du format du train de bits
   USART2->CR1&=~((1<<12)|(1<<28));     // 8 bits de données, 1 bit START
   USART2->CR1&=~((1<<10));             // pas de Parité
   USART2->CR2&=~((1<<13)|(1<<12));     // 1 bit STOP
   USART2->CR1|=((1<<3)|(1<<2)|(1<<0)); // Activer USART3, Activer Reception, activer Transmission
   USART2->CR1|=(1<<5);									// Activer la demande IT pour la reception
	 NVIC_EnableIRQ(USART2_IRQn);					// demasquer la demande IT au niveau du controleur NVIC
}

//génère le nouvel code lorsque tous les caractères sont reçus
void vm_code(void){
	
	int identifiant,cd;
	
	if(strstr(Caractere_Recu,":")) //on recherche les : dans caractere_recu
	{
		sscanf(Caractere_Recu,"%d:%d@",&identifiant,&cd); //la ligne reçue est du type "%d:%d@", on récupère alors l'identifiant et l'opcode
		code[identifiant] = cd; //on le stocke dans le tableau d'opcode
	}
}

//vérification que l'opcode est complet pour ne pas rester coincé dans la machine virtuelle
int CodeComplet(void)
{
	int i;
	for(i=0;i<100;i++)
	//while(i<300)
	{
		//i++;
		if (code[i] == I_HALT)
		{
			return 1;
		}
	}
	return 0;	
}
