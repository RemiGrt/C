/********************************************************************************
|   commentaires : Illustration communication serie UART 
|									 Interruption reception
|   auteur: Arouna DARGA
********************************************************************************/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include "vm_codops.h"

#define PC8 0
#define PC9 1
#define PA5 2
/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
volatile unsigned char Caractere_Recu;  /* var globales modifier dans la routine IT: volatile*/

/**************************structure de donnée**********************************/
	
int pc = 0;
int sp = -1;
int code[100];
int stack[100];
int var[100];

/********************************************************************************/








/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/
void initPattePA5_LedVerte(void);
void Init_UART2_Avec_Interrupt (unsigned int BaudRate);
void initPattePC8_entree(void);
void initPattePC9_entree(void);
void run(void);
void etat_led(int x);
/*------------------------------------------------------------------------------
  FIN FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/






/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
		int entree1;
		int entree2;
	  int sortie;
	
		initPattePC8_entree();
		initPattePC9_entree();
    initPattePA5_LedVerte();
		Init_UART2_Avec_Interrupt (9600);
	
		var[PC8]=0;
		var[PC9]=0;
	
		code[0]= I_PUSH;
		code[1]= PC8;    // adresse de PC8 dans var
		code[2]= I_PUSH;
		code[3]= PC9;		 // adresse de PC9 dans var
		code[4]= I_OR;
		code[5]= I_POP ; 
		code[6]= PA5;
		code[7]= I_HALT;
	
   while(1)   
   {
		 entree1=((GPIOC -> IDR & 0x0100)>>8);
		 entree2=((GPIOC -> IDR & 0x0200)>>9);
			var[PC8]= entree1;
			var[PC9]= entree2;
		  pc=0;
			run();
		  sortie=var[PA5];
			etat_led(sortie);
   }
}





void etat_led(int x)
{
		 if(x==0)
		 {
			 GPIOA->ODR &=~(1<<5);
		 }
		 
		 if(x==1)
		 {
			 GPIOA->ODR |=(1<<5);
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
			GPIOA->ODR |=(1<<5);
		}
		else if (Caractere_Recu=='E')
		{
			GPIOA->ODR &=~(1<<5);
		}
		Caractere_Recu++;
		USART2->TDR = Caractere_Recu;
		
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
  FUNCTION:     void initPattePC8(void)
  DESCRIPTION:  Configuration de la patte PC8 en mode entree
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void initPattePC8_entree(void)
{
   RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
   GPIOC->MODER &=~(1UL<<16);   // bit 17 à '0'
   GPIOC->MODER &=~(1UL<<17);   // bit 16 à '0'
   GPIOC->PUPDR &=~(1UL<<16);   //  bit b16 à '0'
   GPIOC->PUPDR &=~(1UL<<17);   //  bit b17 à '0'
}







/*===============================================================================
  FUNCTION:     void initPattePC9(void)
  DESCRIPTION:  Configuration de la patte PC9 en mode entree
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void initPattePC9_entree(void)
{
   RCC->AHBENR |=(1UL<<19);     //horloge du GPIOC
   GPIOC->MODER &=~(1UL<<18);   // bit 18 à '0'
   GPIOC->MODER &=~(1UL<<19);   // bit 19 à '0'
   GPIOC->PUPDR &=~(1UL<<18);   // bit b18 à '0'
   GPIOC->PUPDR &=~(1UL<<19);   // bit b19 à '0'
}






/*===============================================================================
  FUNCTION:     void Init_UART2_Sans_Interrup (unsigned int BaudRate)
  DESCRIPTION:  Configuration UART2 (PA2->Tx, PA3->Rx), hardware via USB debuger STLINK
                Vitesse limiter a 9600 par le Hardware USB debuger STLINK
  PARAMETERS:   unsigned int BaudRate
  RETURNS:   	rien   
  REQUIREMENTS: BaudRate depend de la frequence  
===============================================================================*/
void Init_UART2_Avec_Interrupt (unsigned int BaudRate){

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








/*===============================================================================
  FUNCTION:     void run(void)
  DESCRIPTION:  
  PARAMETERS:   rien
  RETURNS:   		rien   
===============================================================================*/

void run(void){
	while(code[pc] != I_HALT){
		switch(code[pc]){ 
			case I_PUSHI : 
				sp++;
				stack[sp] = code[pc+1];
				pc = pc+2;
				break;
			case I_MULT :
				stack[sp-1] = stack[sp-1] * stack[sp];
				sp--;
				pc++;
				break;
			case I_ADD : 
				stack[sp-1] = stack[sp-1] + stack[sp];
				sp--;
				pc++;
				break;
			case I_PUSH :
				sp++;
				stack[sp] = var[code[pc+1]];
				pc = pc+2;
				break;
			case I_POP : 
				var[code[pc+1]] = stack[sp];
				sp--;
				pc = pc+2;
				break;
			case I_EQ :
				if(stack[sp]==stack[sp-1]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				break;
			case I_J :
				pc = code[pc+1];
	break;
			case I_JF :
				if(stack[sp] == 0){
					pc = code[pc+1];
					sp--;
				}
				else{
					pc = pc + 2;
					sp--;
				}
				break;
			case I_AND :
				stack[sp-1] = stack[sp-1] && stack[sp];
				sp--;
				pc++;
				break;
			case I_OR :
				stack[sp-1] = stack[sp-1] || stack[sp];
				sp --;
				pc++;
				break;
		/*	case I_INF :
				if(stack[sp-1] < stack[sp]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				break;
			case I_SUP :
				if(stack[sp-1] > stack[sp]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				break;
*/
		}
	}
}
