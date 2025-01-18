/********************************************************************************
| |   auteurs: Chrisnie &  Seynabou
********************************************************************************/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include <stdio.h>
#include "vm_codops.h"
#include "PWM.h"
#include "gpio.h"
//#include "UART.h"

/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/


#define MaxCode_size 1000
#define MaxStack_size 100
#define MaxVar_size 100

int code[MaxCode_size];
int stack[MaxStack_size];
int var [MaxVar_size];
int sp;
int pc;	
int PWM;


/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/
/*void initPattePA5_LedVerte(void);
void Init_UART2_Sans_Interrupt (unsigned int BaudRate);*/
void run(void);
//void initPattes(void);

/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
	initPattes(); 
	//initPattePC13_BoutonPoussoirBleu_Interruption();
	/* Config_PA8_Mode_OutputPWM_TIM1_CH1();
	  // Demarrage du Timer TIM1 en dernier
			 TIM1->CR1 |=(1<<0); 
	/*unsigned int Caractere_Recu;
	Init_UART2_Sans_Interrupt (9600);*/
	sp=-1;
  pc=0;	
	/*
		Declaration variables locales 
	*/
   // unsigned char Caractere_Recu;
	
	/* 
		Initialiser les peripheriques utiles à l'application  : 
    En general on regroupe les initialisation dans une  ou plusieurs fonctions 
    Ces instructions ou appel de fonctions seront exécutées une seule fois  
  
		Init_UART2_Sans_Interrupt (9600);*/
    
	  /*code[0]= I_PUSH;
	  code[1]=0;
	  code[2]=I_PUSH;
	  code[3]=1;
	  code[4]=I_AND;
	  code[5]=I_POP;
		code[6]=2;
		code[7]=I_HALT;*/
		
	while(1)   // Boucle principale ou infinie
   {/*
		 if (PWM==1)
		 {
			 
			 GPIOA->ODR |=(1<<5); 
		 }
		 else 
		 {
			  GPIOA->ODR &=~(1<<5);
		 }
	 	 var[0]= GPIOA->IDR &(1<<0);
		 var[1]= GPIOA->IDR &(1<<1);
		 pc=0;		  
		 //run();
		 //var[2]=var[0]|var[1];*/
		 GPIOA->ODR =(1<<5);
		 /*if (GPIOA->IDR &(1<<4))
		 {
			 GPIOA->ODR |=(1<<5);
		 
	   }
		 else if (!GPIOA->IDR&(1<<4))
		 {
			 GPIOA->ODR &=~(1<<5);
		 }*/
 }
}
// FIN FONCTION MAIN


void run()
{
           while(code[pc]!=I_HALT)
	{switch(code[pc])
		{case I_PUSHI: printf("run: I_PUSHI\n");// Remplit le stack par les valeurs 0 1 2 
			stack[++sp]=code[pc+1];
 			sp++; pc=pc+2; break;
		case I_ADD: printf("run: I_ADD\n");
			stack[sp-1]=stack[sp-1]+stack[sp];
			sp++; pc++; break;
		case I_MULT: printf("run: I_MULT\n");
			stack[sp-1]=stack[sp-1]*stack[sp];
			sp--; pc++; break;
		case I_PUSH : printf("run: I_PUSH\n");// On met a dans le stack
			stack[++sp]=var[code[pc+1]];
			pc+=2; break;
		case I_EQ : printf("run: I_EQ\n");// on compare a et pushi 0
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_AND : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_OR : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=0;} 
			else {
			sp--; 
			    stack[sp]=1;}
			pc++; break;
		case I_JF : printf("run: I_JF\n");
			if (stack[sp]==0){pc= code[pc+1];}  //jump
			else {pc+=2;}
			  break;
		case I_NOT : printf("run: I_NOT\n");// 
			stack[sp]=!stack[sp]; 
			pc++; break;
		case I_POP : printf("run: I_POP\n");// On affecte 1 ou 2 à b
			var[code[pc+1]]=stack[sp-1];
			pc+=2; break;
		case I_J : printf("run: I_J\n");// on écrit -1
			pc=code[pc+1];
			break;
	
		}

	//printf("run: sp = %d \n", sp);
	//printf("run: pc = %d \n", pc);
	//printf("run: stack[sp] = %d \n", stack[sp]);
	}
}
/*void EXTI4_15_IRQHandler(void)
{
   // tache a faire si interruption externes des pattes Numerotées de 4 à 15
   // ici on a configuré uniquement la patte PC13
   // mais on verifier que c'est bien la patte 13 (PC13) qui demande interruption
    /* Verifier que c'est bien la patte PC13 qui demande interruption*/
 /* if(EXTI->PR&(1<<13))                 // Test du drapeau bit b13 (PR13) du registre EXTI_PR de demande interruption
	{
		/* Si on arrive ici c'est que c'est bien PC13 qui demande interruption*/
	/*	EXTI->PR|=(1<<13);                // il faut acquiter la demande : on ecrit '1' pour effacer le drapeau !. 
		PWM=!PWM; // Changer etat de la LED verte 
 }
      
}*/
/*void initPattes(void)
{
   RCC->AHBENR |=(1<<17);     // Activation horloge du GPIOA
	 RCC->AHBENR |=(1<<18);     // Activation horloge du GPIOB
   GPIOA->MODER &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<8)|(1<<11)); // choix mode General Purpose input pour PA0 et PA1  et output pour PA5
   GPIOA->MODER |=((1<<9)|(1<<10));   // choix mode General Purpose Output bitS pairs à '0' et bits impairs à 1
	 GPIOA->OTYPER &=~((1<<5)|(1<<4));  // choix techno de sortie Push-Pull : bits b0 à b15 à '0'GPIOBGPIOB->OTYPER &= 0x0000;
	 GPIOA->PUPDR &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<10)|(1<<11)|(1<<8)|(1<<9));   //Pins 0 et 1 en floting et Pin 5 en Push-pull
   GPIOA->OSPEEDR &=~(1<<11);   // PA5 à 0
	 GPIOA->OSPEEDR &=~(1<<10);   // PA5 à 0
}*/
