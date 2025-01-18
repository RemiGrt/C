#include <stdio.h>
#include <string.h>

#define I_ADD 0
#define I_MULT 1
#define I_PUSHI 100
#define I_HALT 400
#define I_PUSH 101
#define I_EQ 12
#define I_POP 102
#define I_JF 200 
#define I_J 201
#define I_LS 13
#define I_AND 300
#define I_SUB 66
#define I_NEG 67
#define I_GT 68
#define I_OR 69
#define I_NOT 70



#define BUT1 (1UL<<13)
#define BUT2 (1UL<<14) 
#define LED  (1UL<<5) 


#include "stm32f0xx.h"   // defintion des registre de stm32f0xxx : CMSIS 



char Caractere_Recu[10];  // var globales modifier dans la routine IT: volatile
int k=0;
int newCode = 0;


//Prototypes
void initPattePA5_LedVerte(void);
void initPatte_PC13(void);
void Init_UART2_Avec_Interrupt (unsigned int BaudRate);
void USART2_IRQHandler(void);

void initPatte_PC5(void);	//capteur 1
void initPatte_PC6(void);	//capteur 2
void initPatte_PC8(void); //capteur 3
void initPattePA12_moteur(void); //phase

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);

void run(void);
void newOpcode(void);
int verificationOpcodeComplet(void);

int variable[100];
int opcode[300];

//Programme principal

int main (void)
{	
	int opcodeFull=0;
	int old_but0 = 0;
	int old_capt0 = 0;
	int old_capt1 = 0;
	int old_capt2 = 0;
	
	//initialisation des sorties
	variable[12]=0;
	variable[13]=0;
	variable[14]=0;
	variable[15]=0;
	
	
	
	initPattePA5_LedVerte();
	initPattePA12_moteur();
	initPatte_PC13();

  Config_PA8_Mode_OutputPWM_TIM1_CH1(); // PWM pour moteur
	TIM1->CR1 |=(1<<0);

	Init_UART2_Avec_Interrupt (9600);
	
	/*//LED maintenue allumée + moteurChangement de sens
	opcode[0] = 101;
	opcode[1] = 1;
	opcode[2] = 200;
	opcode[3] = 14;
	opcode[4] = 101;
	opcode[5] = 14;
	opcode[6] = 70;
	opcode[7] = 102;
	opcode[8] = 14;
	opcode[9] = 101;
	opcode[10] = 12;
	opcode[11] = 70;
	opcode[12] = 102;
	opcode[13] = 12;
	opcode[14] = 400;*/
	
	/*
	//tab variable
	0 but0
	1 risebut0
	2 fallbut0
	3 capt0-start
	4 risecapt0
	5 fallcapt0
	6 capt1-position1
	7 risecapt1
	8 fallcapt1
	9 capt2-position2
	10 risecapt2
	11 fallcapt2
	12 LED0
	13 Moteur-onOff
	14 Moteur-sens1
	15 Moteur-sens2
	*/	
	
	/*//opcode scenario tapis
	opcode[0] = 101;
	opcode[1] = 4;
	opcode[2] = 200;
	opcode[3] = 14;
	opcode[4] = 101;
	opcode[5] = 13;
	opcode[6] = 70;
	opcode[7] = 102;
	opcode[8] = 13;
	opcode[9] = 101;
	opcode[10] = 12;
	opcode[11] = 70;
	opcode[12] = 102;
	opcode[13] = 12;
	
	opcode[14] = 101;
	opcode[15] = 7; //opcode[15] = 1; //opcode[15] = 7;
	opcode[16] = 200;
	opcode[17] = 26;
	opcode[18] = 100;
	opcode[19] = 0;
	opcode[20] = 102;
	opcode[21] = 15;
	opcode[22] = 100;
	opcode[23] = 1;
	opcode[24] = 102;
	opcode[25] = 14;

	opcode[26] = 101;
	opcode[27] = 10; //opcode[27] = 2; //opcode[27] = 10;
	opcode[28] = 200;
	opcode[29] = 38;
	opcode[30] = 100;
	opcode[31] = 0;
	opcode[32] = 102;
	opcode[33] = 14;
	opcode[34] = 100;
	opcode[35] = 1;
	opcode[36] = 102;
	opcode[37] = 15;

	opcode[38] = 400;*/
	
	
	while(1)   // Boucle principale ou infinie
	{		
		opcodeFull = verificationOpcodeComplet();
		
		
	//Lecture des entrées
		//boutton
		if (GPIOC->IDR & (1<<13)) //boutton actif à l'etat bas
		{			
			variable[0] = 0; //boutton relaché
		}
		else
		{
			variable[0] = 1; //boutton enfoncé
		}

		if ((old_but0 == 0) && (variable[0] == 1)) //front montant bouton
		{
			variable[1] = 1;
		}
		else
		{
			variable[1] = 0;
		}
		
		if ((old_but0 == 1) && (variable[0] == 0)) //front descendant bouton
		{
			variable[2] = 1;
		}
		else
		{
			variable[2] = 0;
		}
		
		//capteur1
		if (GPIOC->IDR & (1<<5)) //capteur actif à l'etat haut
		{			
			variable[3] = 1; //capteur actif
		}
		else
		{
			variable[3] = 0; //capteur non actif
		}

		if ((old_capt0 == 0) && (variable[3] == 1)) //front montant capteur
		{
			variable[4] = 1;
		}
		else
		{
			variable[4] = 0;
		}
		
		if ((old_capt0 == 1) && (variable[3] == 0)) //front descendant bouton
		{
			variable[5] = 1;
		}
		else
		{
			variable[5] = 0;
		}
		
		//capteur1
		if (GPIOC->IDR & (1<<6)) //capteur actif à l'etat haut
		{			
			variable[6] = 1; //capteur actif
		}
		else
		{
			variable[6] = 0; //capteur non actif
		}

		if ((old_capt1 == 0) && (variable[6] == 1)) //front montant capteur
		{
			variable[7] = 1;
		}
		else
		{
			variable[7] = 0;
		}
		
		if ((old_capt1 == 1) && (variable[6] == 0)) //front descendant bouton
		{
			variable[8] = 1;
		}
		else
		{
			variable[8] = 0;
		}
		
		//capteur2
		if (GPIOC->IDR & (1<<8)) //capteur actif à l'etat haut
		{			
			variable[9] = 1; //capteur actif
		}
		else
		{
			variable[9] = 0; //capteur non actif
		}

		if ((old_capt2 == 0) && (variable[9] == 1)) //front montant capteur
		{
			variable[10] = 1;
		}
		else
		{
			variable[10] = 0;
		}
		
		
		
		
		
		
		
		if(opcodeFull == 1)
		{
			run();
		}
			
		
		//affectation des sorties
		if (variable[12] == 1)
		{
			GPIOA->ODR |= (LED);
		}
		else
		{
			GPIOA->ODR &= ~(LED);
		}
		
		//moteur_onOff
		if (variable[13] == 1)
		{
			TIM1->CCR1 =50;
		}
		else
		{
			TIM1->CCR1 =0;
		}
	  
		//moteur_sens1
		if (variable[14] == 1)
		{
			GPIOA->ODR |= (1<<12);
		}
		
		//moteur-sens2
		if (variable[15] == 1)
		{
			GPIOA->ODR &= ~(1<<12);
		}
		
		
		old_but0 = variable[0];
		old_capt0 = variable[3];
		old_capt1 = variable[6];
		old_capt2 = variable[9];
	         	
	}

}



void run()
{
	int stack[100];
	int sp=-1,pc=0;
	
	
	while(opcode[pc]!=I_HALT)
	{
		switch (opcode[pc]) 
		{

			case I_PUSHI :				
			stack[++sp]=opcode[pc+1];			
			pc=pc+2;
			break;
			
			case I_PUSH:
			stack[++sp]=variable[opcode[pc+1]];
			pc=pc+2;
			break;
			
			case I_POP:
			variable[opcode[pc+1]]=stack[sp];
			pc=pc+2;
			break;
		
			case I_ADD :
			stack[sp-1]=stack[sp]+stack[sp-1];
			sp--;
			pc++;
			break;
		
			case I_SUB :
			stack[sp-1]=stack[sp]-stack[sp-1];
			sp--;
			pc++;
			break;

			case I_NEG :
			stack[sp]=0-stack[sp];
			pc++;
			break;

			case I_MULT :
			stack[sp-1]=stack[sp]*stack[sp-1];
			sp--;			
			pc++;
			break;
			
			case I_EQ:
			if (stack[sp-1]==stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;
		
			case I_LS:
			if (stack[sp-1]>stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_GT :
			if (stack[sp-1]<stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_NOT:
			stack[sp]=!(stack[sp]);
			pc++;	
			break;

			case I_AND:
			if (stack[sp-1]&&stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_OR:
			if (stack[sp-1]||stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			break;

			case I_J:
			if(stack[sp] == 1)
			{
				pc=opcode[pc+1];
			}
			else
			{
				pc+=2;
			}	 
			break;
			
			case I_JF:
			if(stack[sp] != 1)
			{
				pc=opcode[pc+1];
			}
			else
			{
				pc+=2;
			}	 
			break;
		
		}
		
	}

}





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


void initPatte_PC13(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     // Activation horloge du GPIOB
   GPIOC->MODER &=~(1<<27);   // choix mode General Purpose Output bit b19 à '0'
   GPIOC->MODER &=~(1<<26);    // choix mode General Purpose Output bit b18 à '0'
   GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b10 à '0'
}

void initPatte_PC5(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     
   GPIOC->MODER &=~(1<<11);   
   GPIOC->MODER &=~(1<<10);    
   GPIOC->PUPDR &=~(1<<11);   
   GPIOC->PUPDR &=~(1<<10);   
}

void initPatte_PC6(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;     
   GPIOC->MODER &=~(1<<13);   
   GPIOC->MODER &=~(1<<12);    
   GPIOC->PUPDR &=~(1<<13);  
   GPIOC->PUPDR &=~(1<<12);
}  

void initPatte_PC8(void)
{
   RCC->AHBENR |=RCC_AHBENR_GPIOCEN;	
   GPIOC->MODER &=~(1<<17);						
   GPIOC->MODER &=~(1<<16);    				
   GPIOC->PUPDR &=~(1<<17);   				
	 GPIOC->PUPDR &=~(1<<16);
}



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
	TIM1->ARR =99;  
	
	// 5. Rapport cyclique de 25% : division de la ARR par 4
	TIM1->CCR1 =0;

}


void USART2_IRQHandler(void)
{
	int i;
		if (USART2->ISR&(1<<5))
		{
			Caractere_Recu[k] =  USART2->RDR;
			if (Caractere_Recu[k] == '@')
			{
				Caractere_Recu[k+1] = '\0';
				newOpcode();
				for(i=0;i<(k+1);i++)
				{
					while(!(USART2->ISR & 1<<7)) //on attend de pouvoir écrire sur la liaison série
					{
					}
					USART2->TDR = Caractere_Recu[i];
				}
				k=0;
			}
			else 
			{
				k++;
			}
		}


}

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


void newOpcode(void){
	
	int identifiant,code;
	
	if(strstr(Caractere_Recu,":"))
	{
		sscanf(Caractere_Recu,"%d:%d@",&identifiant,&code); // on stocke identifiant et code dans deux variables pour les ranger dans opcode
		opcode[identifiant] = code;
	}
}

int verificationOpcodeComplet(void)
{
	int i;
	for(i=0;i<300;i++)
	{
		if (opcode[i] == I_HALT)
		{
			return 1;
		}
	}
	return 0;	
}
