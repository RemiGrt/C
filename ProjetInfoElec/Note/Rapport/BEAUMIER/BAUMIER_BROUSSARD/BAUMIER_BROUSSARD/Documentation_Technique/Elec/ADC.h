/**
* \file 
*			ADC.h
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			21 février 2017
* \brief 
*			Librairie contenant les fonctions du fichier ADC.c
*/

#ifndef __ADC_H__
#define __ADC_H__


/** 
 * \fn  void initADC1_SingleMode(unsigned int Resolution)
 * \brief 
 *			Initialisation d'une patte en ADC1, mode single, sans interruption \n
 * 		\b Avoir activé au moins une patte en mode analogique
 * \param[in] 
 *			Resolution		Résolution de la conversion
 */
void initADC1_SingleMode(unsigned int Resolution);


/** 
 * \fn  int Start_ADC1_Conversion(int Channel)
 * \brief 
 *			Réalise une conversion sur l'ADC1, sans interruption \n
 *			\b/!\ L'ADC1 doit être initialisé et activé \b/!\
 * \param[in] 
 *			Channel				Channel choisi
 * \return 
 *			Résultat de la conversion en décimal
 */
int Start_ADC1_Conversion(int Channel);

/** 
 * \fn  void initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution)
 * \brief 
 *			Initialisation d'une patte en ADC1,en mode continu, avec interruption à chaque fin de conversion
 * \param[in] 
 *			Pin				Numéro de la patte
 * \param[in] 
 *			Port			Port de la patte
 * \param[in] 
 *			Resolution		Résolution de la conversion
 */
 void initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution);

/** 
 * \fn  void Disable_ADC1(void)
 * \brief 
 *			Désactive l'ADC1
 */
void Disable_ADC1(void);

/** 
 * \fn  void Enable_ADC1(void)
 * \brief 
 *			Active l'ADC1
 */
void Enable_ADC1(void);

/** 
 * \fn  void Start_ADC1(void)
 * \brief 
 *			Démarre une conversion sur l'ADC1
 */
void Start_ADC1(void);

/** 
 * \fn  void Calibration_ADC1(void)
 * \brief 
 *			Permet de calibrer l'ADC1
 */
void Calibration_ADC1(void);

/** 
 * \fn  void Select_Channel_ADC(unsigned int Channel)
 * \brief 
 *			Choix du channel à convertir
 * \param[in] 
 *			Channel			Channel choisi
 */
void Select_Channel_ADC(unsigned int Channel);

#endif
