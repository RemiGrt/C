/*------------------------------------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Utiliser USART2 (PA2 (Tx), PA3(Rx)) avec hardware USB vers UART de STLINK 
 *          Pas besoin de convertiseur USB-UART. 
 *          Le fichier retarget.c permet utilisation de formatage de la librairie stdio.h (printf)
 *          Utiliser stdio.h uniquement pendant la phase de conception (debug)
 * Date: 		12/02/17
 * Author:	Arouna DARGA
 *------------------------------------------------------------------------------------------------------
 * Note(s):	SER_envoiCaractere are used to redefine printf function
 *----------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Include Statements---------------------------------*/
#include "stm32f0xx.h"	                 // Specific Device header
#include "Serial.h"
/*-------------------------------------------------Define Statements----------------------------------*/


/*-------------------------------------------------Functions------------------------------------------*/


/**
  \fn          void configUsart2SansInterruption (unsigned int baudRate)
  \brief       Configure les pattes PA2 (Tx) et PA3 (Rx) pour USART2 
               configure USART2 en UART (8 bits donnees, 1 bit START, 1 bit STOP, pas de parite)
*/
	
void configUsart2SansInterruption (unsigned int baudRate)
{

  /*configuration des pattes*/
   RCC->AHBENR |=(1<<17);      // Activation horloge du GPIOA 
   // configuration PA2 (Tx)
   GPIOA->MODER |=(1<<5);      // choix Alternate Function pour PA2 bit b5 à '1'
   GPIOA->MODER &=~(1<<4);     // choix Alternate Function pour PA2 bit b4 à '0'
   GPIOA->AFR[0]&=~(1<<11);    // choix AF1 comme alternate function : bit b11 à '0'
   GPIOA->AFR[0]&=~(1<<10);    // choix AF1 comme alternate function : bit b10 à '0'
   GPIOA->AFR[0]&=~(1<<9);     // choix AF1 comme alternate function : bit b9 à '0'
   GPIOA->AFR[0]|=(1<<8);      // choix AF1 comme alternate function : bit b8 à '1'
   GPIOA->OTYPER &=~(1<<2);    // choix techno de sortie Push-Pull : bit b2 à '0'
   GPIOA->PUPDR &=~(1<<5);     // desactivation resistance de tirage: bit b5 à '0'
   GPIOA->PUPDR &=~(1<<4);     // desactivation resistance de tirage: bit b4 à '0'
   GPIOA->OSPEEDR&=~(1<<5);    // Vitesse de rafraichissement bit b5 à '0'
   GPIOA->OSPEEDR&=~(1<<4);    // Vitesse de rafraichissement bit b4 à '0'
   
  // configuration PA3 (Rx)
   GPIOA->MODER |=(1<<7);      // choix Alternate Function pour PA3 bit b7 à '1'
   GPIOA->MODER &=~(1<<6);     // choix Alternate Function pour PA3 bit b6 à '0'
   GPIOA->AFR[0]&=~(1<<15);    // choix AF1 comme alternate function : bit b15 à '0'
   GPIOA->AFR[0]&=~(1<<14);    // choix AF1 comme alternate function : bit b14 à '0'
   GPIOA->AFR[0]&=~(1<<13);    // choix AF1 comme alternate function : bit b13 à '0'
   GPIOA->AFR[0]|=(1<<12);     // choix AF1 comme alternate function : bit b12 à '1'
   GPIOA->PUPDR &=~(1<<7);     // desactivation resistance de tirage: bit b7 à '0'
   GPIOA->PUPDR &=~(1<<6);     // desactivation resistance de tirage: bit b6 à '0'
   
   /*configuration de USART2 */
   RCC->APB1ENR|=(1<<17);       // activation horloge de USART2

   // definition de la vitesse de communication
   // USARTx_BRR  = Frequence du Module/Baude_Rate
   // ici nous voulons BaudeRate=96000 et la frequence du module vaut SystemCoreClock
   USART2->BRR=(SystemCoreClock/baudRate);

   // definition du format du train de bits
   USART2->CR1&=~((1<<12)|(1<<28));         // 8 bits de données, 1 bit START
   USART2->CR1&=~((1<<10));                 // pas de Parité
   USART2->CR2&=~((1<<13)|(1<<12));         // 1 bit STOP
   USART2->CR1|=((1<<3)|(1<<2)|(1<<0));     // Activer USART2, Activer Reception, activer Transmission
}


/******************************************************************************
  \fn					char  usart2EnvoiCaractere(char ch)
  \brief			Envoi un caractere 
	\param			char monCaractere: caractere a envoye
	\returns		char monCaractere: caractere qui a ete envoye
********************************************************************************/

char usart2EnvoiCaractere(char monCaractere)
{

 if (monCaractere == '\n')
   {
    while ((USART2->ISR & USART_ISR_TXE) == 0)
    {
      // tant que le buffer de transmission est plein 
      // on attend ici
    }
  // envoi du retor charriot CR 
  USART2->TDR = 13;

  }

  while ((USART2->ISR & USART_ISR_TXE) == 0)
  {
    // tant que le buffer de transmission est plein 
    // on attend ici
  }

  // envoi de mon caractere 
  USART2->TDR = monCaractere; 
  if (monCaractere == 13)         // si le caractere est retour charriot
  {
    while ((USART2->ISR & USART_ISR_TXE) == 0)
    {
      // tant que le buffer de transmission est plein 
      // on attend ici
    }
    
    // envoi caractere nouvelle ligne
    USART2->TDR= 10;
    
  }
  return (monCaractere);
}

/******************************************************************************
  \fn         int usart2RecevoirCaractere(void)
  \brief      recois un caractere 
  \param      rien
  \returns    caractere recu
********************************************************************************/


/*===============================================================================
  FUNCTION:     uart2VerifSiCaractere(void)
  DESCRIPTION:  verifie si un caractere est disponible 
  PARAMETERS:   rien
    
  RETURNS:     int : 1 ou 0
  REQUIREMENTS: rien 
===============================================================================*/
int uart2VerifSiCaractere(void)
{
  // on renvoi le flag 
  return (USART2->ISR & (1<<5));
}


/*===============================================================================
  FUNCTION:     unsigned char uart2RecevoirCaractere(void)
  DESCRIPTION:  pour recevoir un caractere 
  PARAMETERS:   rien
    
  RETURNS:     unsigned char : Le caractere recu
  REQUIREMENTS: rien 
===============================================================================*/
unsigned char uart2RecevoirCaractere(void)
{
  while (uart2VerifSiCaractere()==0)
  {
    // tant que pas de caractere disponible 
    // on attend ici
  } 
  // lecture et renvoi du caractere
  return ((char)USART2->RDR);
}
