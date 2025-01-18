/**
* \file 
*			DigitalGPIO.h
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			22 fevrier 2017
* \brief  
*			Librairie contenant les fonctions du fichier Gestion_GPIO.c
*/

#ifndef __GESTION_GPIO_H__
#define __GESTION_GPIO_H__


/** 
 * \fn  int DigitalRead (unsigned int Pin, char * Port)
 * \brief 
 *			Lit la valeur d'une patte en mode Entree Numerique
 *			\n La patte doit etre initialisee en Entree Numerique 
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \return 
 *			Etat logique de la patte ('1' ou '0')
 */
void DigitalWrite (unsigned int Pin, char * Port, unsigned int  Etat);

/** 
 * \fn  void DigitalToggle (unsigned int Pin, char * Port)
 * \brief 
 *			Inverse la valeur d'une Patte en Sortie Numerique \n
 *			La patte doit etre initialisee en Sortie Numerique 
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
void DigitalToggle (unsigned int Pin, char * Port);
	
/** 
 * \fn  int DigitalRead (unsigned int Pin, char * Port)
 * \brief 
 *			Lit la valeur d'une patte en mode Entree Numerique
 *			\n La patte doit etre initialisee en Entree Numerique
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \return 
 *			Etat logique de la patte ('1' ou '0')
 */
int DigitalRead (unsigned int Pin, char * Port);


#endif
