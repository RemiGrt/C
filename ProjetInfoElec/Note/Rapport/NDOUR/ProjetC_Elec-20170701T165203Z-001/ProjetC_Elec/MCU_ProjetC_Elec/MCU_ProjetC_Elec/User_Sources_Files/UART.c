#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include <stdlib.h>
#include <stdio.h>
#include "UART.h"
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
   
   /*configuration des pattes*/
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
}
