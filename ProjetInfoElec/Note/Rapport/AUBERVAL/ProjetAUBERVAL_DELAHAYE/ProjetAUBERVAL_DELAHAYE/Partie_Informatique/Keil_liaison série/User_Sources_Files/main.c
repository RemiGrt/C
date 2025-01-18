/********************************************************************************
|   commentaires : Illustration communication serie UART 
|									 Interruption reception
|   auteur: Arouna DARGA
********************************************************************************/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
//#include "evm.h"
#include "vm_codops.h"
/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/
#define DEBUG 1

/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
/* var globale modifier dans la routine IT: volatile
   variable appele SEMAPHORE car synchronise 
	 le main et la routine interruption
	 mis a '1' dans la routine interruption si un caractere est recu
	 mis a '0' dans le main si avant la lecture du caractere
*/
volatile unsigned char Drapeau_Caractere_Recu;  
volatile unsigned char Caractere_Recu;  
int pc=0;
int sp=1;
int CodeSegment[1000];
int stack[100]; // Pile d'exécution
int var[100];
int v=0;
int i=0;
int nblignes=0;
/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/
void initPattePA5_LedVerte(void);
void Init_UART2_Avec_Interrupt (unsigned int BaudRate);
void run (void);


/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{

    initPattePA5_LedVerte();
    Init_UART2_Avec_Interrupt (9600);

   while(1)   // Boucle principale ou infinie
   {
	i=0;
			//eteindre led
			GPIOA->ODR&=~(1<<5);  
			
			if (Drapeau_Caractere_Recu==1){
			nblignes=Caractere_Recu;
			}
			
			while (Drapeau_Caractere_Recu==1 && i<nblignes)
			{
				Drapeau_Caractere_Recu=0;
				//allume LED
				GPIOA->ODR|=(1<<5);
				
				CodeSegment[i]=Caractere_Recu;
				i++;
				//USART2->TDR = Caractere_Recu;
			}
			//eteindre
			GPIOA->ODR&=~(1<<5); 
			
			run();
   }
   // Fin : Le CPU n'arrivera jamais ici
}
// FIN FONCTION MAIN


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
		Drapeau_Caractere_Recu=1; /* semaphore mis a 1 pour signaler au main que caractere recu */
		
		Caractere_Recu=USART2->RDR;
		
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
void run (void){
	
	/*if (DEBUG){
		for(i=0;i<20;i++){
			printf("code[%d]=%d\n",pc,code[pc]);
			pc++;
		}
	}*/
	i=0;
	while (CodeSegment[pc]!=I_HALT)
	{i++;
		//if (DEBUG) printf("code[%d] : %d \n",pc, code[pc]);
		switch (CodeSegment[pc])
		{
			case I_PUSHI : stack[sp]=CodeSegment[++pc];
			pc++;
			sp++;
			break;

			case I_ADD : stack[sp-1]=stack[sp]+stack[sp-1];
			pc++;
			sp--;
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
				stack[sp-1]=1;
				pc++;
				sp--;
			}else{
				while (CodeSegment[pc]!=I_JF) pc++;
			}
		        break; 

			case I_GT : 
			if (stack[sp]>stack[sp-1]){
				stack[sp-1]=1;
				pc++;
			}else{
				stack[sp-1]=0;
				while (CodeSegment[pc]!=I_JF) pc++;
			}
			break;

			case I_LS :
			if (stack[sp]<stack[sp-1]){
				stack[sp-1]=1;
				pc++;
				sp--;
			}else{
				stack[sp-1]=0;
				while (CodeSegment[pc]!=I_JF) pc++;
			}
			break;

			case I_AND :
				if ((stack[sp]==1) && (stack[sp-1]==1)){
				stack[sp-1]=1;
				pc++;
				sp--;
				}
				else {
				stack[sp-1]=1;
				pc++;
				sp--;
				}
				break;
				
			
		//JF : si EQ est faux alors va à la ligne de l'étiquette qui suit JF
			case I_JF : 
			pc = CodeSegment[pc+1];
			break;

			case I_J : 
			pc= CodeSegment[pc+1];
			break;

			default : pc++;
		}
	}
}
