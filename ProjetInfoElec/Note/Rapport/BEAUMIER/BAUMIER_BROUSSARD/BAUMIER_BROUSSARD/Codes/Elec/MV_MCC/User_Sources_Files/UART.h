//#############################################################
// Auteur : Thomas Broussard
// Date : 10/02/17
// Titre : Init.pins.h
//------------------------------------------------------------
// Description  :
//	Contient les fonctions du fichier UART.c
//	
//
//
//
//
//#############################################################

#ifndef __UART_H__
#define __UART_H__

/*===============================================================================
  FUNCTION:     InitUART2
  DESCRIPTION:  Initialise une connexion UART2 
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   		rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART2 (exemple : PA2 et PA3)
===============================================================================*/
extern void InitUART2(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);

/*===============================================================================
  FUNCTION:     InitUART1
  DESCRIPTION:  Initialise une connexion UART1
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   		rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART1 (exemple : PA9 et PA10)
===============================================================================*/
extern void InitUART1(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);

/*===============================================================================
  FUNCTION:     InitUART4
  DESCRIPTION:  Initialise une connexion UART 4
  PARAMETERS:   Vitesse de communication, Nombre de bits de données, Nombre de bits de STOP, Parité, Type d'interruption souhaitée
	RETURNS:   	rien   
  REQUIREMENTS: Il faut au moins une patte Tx et une patte Rx pour l'USART4 (exemple : PC10 et PC11)
===============================================================================*/
extern void InitUART4(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);

#endif
