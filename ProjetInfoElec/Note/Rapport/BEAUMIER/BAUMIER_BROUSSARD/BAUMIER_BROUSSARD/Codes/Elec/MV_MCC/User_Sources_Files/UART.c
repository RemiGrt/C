//#############################################################
// Auteur : Thomas Broussard
// Date : 10/02/17
// Titre : Init.pins.c
//------------------------------------------------------------
// Description  :
//	Contient les fonctions permettant d'initialiser des broches du microcontrôleur
//	
//
//
//
//
//#############################################################
#include "stm32f0xx.h"  
#include "string.h"
#include "InitPins.h" 
#include "UART.h"

/*===============================================================================
  FUNCTION:     InitUART2
  DESCRIPTION:  Initialise une connexion UART2 
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   	rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART2 (exemple : PA2 et PA3)
===============================================================================*/
void InitUART2(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	// Activation de l'horloge UART2 
	RCC->APB1ENR|=(1<<17);
	
	// Configuration des paramètres de communication
	// Vitesse de communication
	USART2->BRR = (SystemCoreClock / Vitesse);
	
	// Nombre de bits de données : 7 , 8 ou 9 (par défaut : inchangé)
	switch (Nb_Data)
	{
		case 8 : // 8 bits de données
			USART2->CR1 &=~ (1<<12);
			USART2->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de données
			USART2->CR1 |= 	(1<<12);
			USART2->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de données
			USART2->CR1 &=~ (1<<12);
			USART2->CR1 |= 	(1<<28);	
			break;
		default :
			break;
	}
	
	// Nombre de bits de stop : 1, 2 ou 1.5 (par défaut)
	switch(STOP)
	{
		case 1 : 	// 1 bit de STOP
				USART2->CR2 &=~(1<<13);
				USART2->CR2 &=~(1<<12);
			break;
		case 2 : 	// 2 bit de STOP
				USART2->CR2 |=(1<<13);
				USART2->CR2 &=~(1<<12);
			break;
		default :// 1.5 bit de STOP
				USART2->CR2 |=(1<<13);
				USART2->CR2 |=(1<<12);
			break;
	}
	
	// Parité
	if (strcmp(Parite,"Paire") == 0) 
	{
		USART2->CR1 |=(1<<10);
	}
	else // Pas de parité
	{
		USART2->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART2->CR1 |=(1<<2); // Activation de la réception
	USART2->CR1 |=(1<<3); // Activation de la transmission
	USART2->CR1 |=(1<<0); // Activation de l 'USART2
	
	// Activation du mode interruption
	// Interruption pour la Réception uniquement
	if (strcmp(Interruption,"RxInterrupt") == 0)
	{
		USART2->CR1|=(1<<5);									// Activer la demande IT pour la reception
		USART2->CR1 &=~ (1<<6);
		NVIC_EnableIRQ(USART2_IRQn);
	}
	
	// Interruption pour la transmission uniquement
	else if (strcmp(Interruption,"TxInterrupt") == 0)
	{
		USART2->CR1 |=	(1<<6);
		USART2->CR1 &=~ (1<<5);
		NVIC_EnableIRQ(USART2_IRQn);
	}
	
	// Interruption pour la Réception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART2->CR1 |= (1<<6);
		USART2->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART2_IRQn);
	}
	
}

/*===============================================================================
  FUNCTION:     InitUART1
  DESCRIPTION:  Initialise une connexion UART 1
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   	rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART1 (exemple : PA9 et PA10)
===============================================================================*/
void InitUART1(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	
	// Activation de l'horloge USART1
	RCC->APB2ENR|=(1<<14);
	
	// Configuration des paramètres de communication
	
	// Vitesse de communication
	USART2->BRR = (SystemCoreClock / Vitesse);
	
	// Nombre de bits de données
	switch (Nb_Data)
	{
		case 8 : // 8 bits de données
			USART1->CR1 &=~ (1<<12);
			USART1->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de données
			USART1->CR1 |= 	(1<<12);
			USART1->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de données
			USART1->CR1 &=~ (1<<12);
			USART1->CR1 |= 	(1<<28);	
			break;
		default :
			break;
	}
	
	// Nombre de bits de stop
	switch(STOP)
	{
		case 1 : 	// 1 bit de STOP
				USART1->CR2 &=~(1<<13);
				USART1->CR2 &=~(1<<12);
			break;
		case 2 : 	// 2 bit de STOP
				USART1->CR2 |=(1<<13);
				USART1->CR2 &=~(1<<12);
			break;
		default :// 1.5 bit de STOP
				USART1->CR2 |=(1<<13);
				USART1->CR2 |=(1<<12);
			break;
	}
	
	// Parité
	if (strcmp(Parite,"Paire") == 0) // Parité activée
	{
		USART1->CR1 |=(1<<10);
	}
	else // Pas de parité
	{
		USART1->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART1->CR1 |=(1<<2); // Activation de la réception
	USART1->CR1 |=(1<<3); // Activation de la transmission
	USART1->CR1 |=(1<<0); // Activation de l 'USART3
	
	// Activation du mode interruption
	// Interruption pour la Réception uniquement
	if (strcmp(Interruption,"RxInterrupt") == 0)
	{
		USART1->CR1 |=	(1<<6);
		USART1->CR1 &=~ (1<<5);
		NVIC_EnableIRQ(USART1_IRQn);
	}
	
	// Interruption pour la transmission uniquement
	else if (strcmp(Interruption,"TxInterrupt") == 0)
	{
		USART1->CR1 &=~ (1<<6);
		USART1->CR1 |= 	(1<<5);
		NVIC_EnableIRQ(USART1_IRQn);
	}
	
	// Interruption pour la Réception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART1->CR1 |= (1<<6);
		USART1->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART1_IRQn);
	}
}

/*===============================================================================
  FUNCTION:     InitUART4
  DESCRIPTION:  Initialise une connexion UART 4
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   	rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART4 (exemple : PC10 et PC11)
===============================================================================*/
void InitUART4(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	
	// Activation de l'horloge USART4
	RCC->APB1ENR|=(1<<19);
	
	// Configuration des paramètres de communication
	
	// Vitesse de communication
	USART4->BRR = SystemCoreClock / Vitesse;
	
	// Nombre de bits de données
	switch (Nb_Data)
	{
		case 8 : // 8 bits de données
			USART4->CR1 &=~ (1<<12);
			USART4->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de données
			USART4->CR1 |= 	(1<<12);
			USART4->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de données
			USART4->CR1 &=~ (1<<12);
			USART4->CR1 |= 	(1<<28);	
			break;
		default :
			break;
	}
	
	// Nombre de bits de stop
	switch(STOP)
	{
		case 1 : 	// 1 bit de STOP
				USART4->CR2 &=~(1<<13);
				USART4->CR2 &=~(1<<12);
			break;
		case 2 : 	// 2 bit de STOP
				USART4->CR2 |=(1<<13);
				USART4->CR2 &=~(1<<12);
			break;
		default :// 1.5 bit de STOP
				USART4->CR2 |=(1<<13);
				USART4->CR2 |=(1<<12);
			break;
	}
	
	// Parité
	if (strcmp(Parite,"Paire") == 0) // Parité activée
	{
		USART4->CR1 |=(1<<10);
	}
	else // Pas de parité
	{
		USART4->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART4->CR1 |=(1<<2); // Activation de la réception
	USART4->CR1 |=(1<<3); // Activation de la transmission
	USART4->CR1 |=(1<<0); // Activation de l 'USART3
	
	// Activation du mode interruption
	// Interruption pour la Réception uniquement
	if (strcmp(Interruption,"RxInterrupt") == 0)
	{
		USART4->CR1 |=	(1<<6);
		USART4->CR1 &=~ (1<<5);
		NVIC_EnableIRQ(USART3_4_IRQn);
	}
	
	// Interruption pour la transmission uniquement
	else if (strcmp(Interruption,"TxInterrupt") == 0)
	{
		USART4->CR1 &=~ (1<<6);
		USART4->CR1 |= 	(1<<5);
		NVIC_EnableIRQ(USART3_4_IRQn);
	}
	
	// Interruption pour la Réception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART4->CR1 |= (1<<6);
		USART4->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART3_4_IRQn);
	}
}