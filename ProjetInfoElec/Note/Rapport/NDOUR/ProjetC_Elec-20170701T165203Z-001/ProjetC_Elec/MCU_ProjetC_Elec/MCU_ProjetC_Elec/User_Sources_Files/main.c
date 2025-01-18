/********************************************************************************
| |   auteurs: Chrisnie &  Seynabou
********************************************************************************/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include <stdio.h>
#include "vm_codops.h"
#include "PWM.h"
#include "gpio.h"
#include "UART.h"

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


//void run(void);


/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
	//appel des fonctions
	initPattes(); 
	Config_PA8_Mode_OutputPWM_TIM1_CH1();
	// Demarrage du Timer TIM1 en dernier
    TIM1->CR1 |=(1<<0); 
	//initPattePA5_LedVerte();
	sp=-1;
	
	//Bycode à exécuter
	  code[0]= I_PUSH;
	  code[1]=0;
	  code[2]=I_PUSH;
	  code[3]=1;
	  code[4]=I_AND;
	  code[5]=I_POP;
		code[6]=2;
		code[7]=I_HALT;
	while(1)   // Boucle principale ou infinie
   {
		 /*pc=0;
		 sp=-1;*/
		 //Lecture des pattes PA0 et PA1
		 var[0]= GPIOA->IDR &(1<<0);
		 var[1]= GPIOA->IDR &(1<<1);
		 		  
		 //run();

		 var[2]=var[0]|var[1];
		 //Led verte s'allume si var[2] vaut 1, 0 sinon
		 GPIOA->ODR |=(var[2]<<5);
		 
		 //Machine Virtuelle
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
	}
		/*GPIOA->ODR |=(var[2]<<5);
		GPIOA->ODR |=(var[1]<<4);
	  GPIOA->ODR |=(var[0]<<6);*/
	}
}
// FIN FONCTION MAIN


/*void run()
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
}*/