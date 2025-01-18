/**
* \file 
*			UART.c
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Contient les fonctions permettant d'initialiser des broches du microcontroleur
*/
#include "stm32f0xx.h"  
#include "string.h"
#include "InitPins.h" 
#include "UART.h"

/** 
 * \fn  void InitUART2(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
 * \brief 
 *			Initialise une connexion UART2 \n
 *			\b/!\ Il faut au moins une patte Tx et une patte Rx pour l'USART2 (exemple : PA2 et PA3) \b/!\
 * \param[in] 
 *			Vitesse			Vitesse de communication
 * \param[in] 
 *			Nb_Data			Nombre de bits de donnees
 * \param[in] 
 *			STOP			Nombre de bits de STOP
 * \param[in] 
 *			*Parite			Parite
 * \param[in] 
 *			*Interrupt		Type d'interruption ("Interrupt" ou "NoInterrupt")
 */
void InitUART2(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	// Activation de l'horloge UART2 
	RCC->APB1ENR|=(1<<17);
	
	// Configuration des parametres de communication
	// Vitesse de communication
	USART2->BRR = (SystemCoreClock / Vitesse);
	
	// Nombre de bits de donnees : 7 , 8 ou 9 (par defaut : inchange)
	switch (Nb_Data)
	{
		case 8 : // 8 bits de donnees
			USART2->CR1 &=~ (1<<12);
			USART2->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de donnees
			USART2->CR1 |= 	(1<<12);
			USART2->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de donnees
			USART2->CR1 &=~ (1<<12);
			USART2->CR1 |= 	(1<<28);	
			break;
		default :
			break;
	}
	
	// Nombre de bits de stop : 1, 2 ou 1.5 (par defaut)
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
	
	// Parite
	if (strcmp(Parite,"Paire") == 0) 
	{
		USART2->CR1 |=(1<<10);
	}
	else // Pas de parite
	{
		USART2->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART2->CR1 |=(1<<2); // Activation de la reception
	USART2->CR1 |=(1<<3); // Activation de la transmission
	USART2->CR1 |=(1<<0); // Activation de l 'USART2
	
	// Activation du mode interruption
	// Interruption pour la Reception uniquement
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
	
	// Interruption pour la Reception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART2->CR1 |= (1<<6);
		USART2->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART2_IRQn);
	}
	
}

/** 
 * \fn  void InitUART1(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
 * \brief 
 *			Initialise une connexion UART1 \n
 *			\b/!\ Il faut au moins une patte Tx et une patte Rx pour l'USART1 (exemple : PA9 et PA10) \b/!\
 * \param[in] 
 *			Vitesse			Vitesse de communication
 * \param[in] 
 *			Nb_Data			Nombre de bits de donnees
 * \param[in] 
 *			STOP			Nombre de bits de STOP
 * \param[in] 
 *			*Parite			Parite
 * \param[in] 
 *			*Interrupt		Type d'interruption ("Interrupt" ou "NoInterrupt")
 */
void InitUART1(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	
	// Activation de l'horloge USART1
	RCC->APB2ENR|=(1<<14);
	
	// Configuration des parametres de communication
	
	// Vitesse de communication
	USART2->BRR = (SystemCoreClock / Vitesse);
	
	// Nombre de bits de donnees
	switch (Nb_Data)
	{
		case 8 : // 8 bits de donnees
			USART1->CR1 &=~ (1<<12);
			USART1->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de donnees
			USART1->CR1 |= 	(1<<12);
			USART1->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de donnees
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
	
	// Parite
	if (strcmp(Parite,"Paire") == 0) // Parite activee
	{
		USART1->CR1 |=(1<<10);
	}
	else // Pas de parite
	{
		USART1->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART1->CR1 |=(1<<2); // Activation de la reception
	USART1->CR1 |=(1<<3); // Activation de la transmission
	USART1->CR1 |=(1<<0); // Activation de l 'USART3
	
	// Activation du mode interruption
	// Interruption pour la Reception uniquement
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
	
	// Interruption pour la Reception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART1->CR1 |= (1<<6);
		USART1->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART1_IRQn);
	}
}

/** 
 * \fn  void InitUART4(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
 * \brief 
 *			Initialise une connexion UART4 \n
 *			\b/!\ Il faut au moins une patte Tx et une patte Rx pour l'USART4 \b/!\
 * \param[in] 
 *			Vitesse			Vitesse de communication
 * \param[in] 
 *			Nb_Data			Nombre de bits de donnees
 * \param[in] 
 *			STOP			Nombre de bits de STOP
 * \param[in] 
 *			*Parite			Parite
 * \param[in] 
 *			*Interrupt		Type d'interruption ("Interrupt" ou "NoInterrupt")
 */
void InitUART4(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption)
{
	
	// Activation de l'horloge USART4
	RCC->APB1ENR|=(1<<19);
	
	// Configuration des parametres de communication
	
	// Vitesse de communication
	USART4->BRR = SystemCoreClock / Vitesse;
	
	// Nombre de bits de donnees
	switch (Nb_Data)
	{
		case 8 : // 8 bits de donnees
			USART4->CR1 &=~ (1<<12);
			USART4->CR1 &=~ (1<<28);	
			break;
		case 9 : // 9 bits de donnees
			USART4->CR1 |= 	(1<<12);
			USART4->CR1 &=~ (1<<28);	
			break;
		case 7 : // 7 bits de donnees
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
	
	// Parite
	if (strcmp(Parite,"Paire") == 0) // Parite activee
	{
		USART4->CR1 |=(1<<10);
	}
	else // Pas de parite
	{
		USART4->CR1 &=~(1<<10);
	}
	
	// Activation des composants
	USART4->CR1 |=(1<<2); // Activation de la reception
	USART4->CR1 |=(1<<3); // Activation de la transmission
	USART4->CR1 |=(1<<0); // Activation de l 'USART3
	
	// Activation du mode interruption
	// Interruption pour la Reception uniquement
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
	
	// Interruption pour la Reception ET la transmission 
	else if (strcmp(Interruption,"RxTxInterrupt") == 0)
	{
		USART4->CR1 |= (1<<6);
		USART4->CR1 |= (1<<5);
		NVIC_EnableIRQ(USART3_4_IRQn);
	}
}
