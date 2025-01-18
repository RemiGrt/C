/**
* \file 
*			UART.h
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Librairie contenant les fonctions du fichier UART.c
*/
#ifndef __UART_H__
#define __UART_H__

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
extern void InitUART2(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);


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
extern void InitUART1(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);

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
extern void InitUART4(int Vitesse, unsigned int Nb_Data, unsigned int STOP, char *Parite, char *Interruption);

#endif
