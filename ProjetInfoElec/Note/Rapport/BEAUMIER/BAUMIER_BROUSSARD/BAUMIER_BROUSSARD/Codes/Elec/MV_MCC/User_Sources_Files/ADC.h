/********************************************************************************
Titre : ADC.h
Auteur : Thomas Broussard
Date : 21/02/17
--------------------------------
Description : Librairie contenant les fonctions du fichier ADC.c


********************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__

/*===============================================================================
  FUNCTION:     initADC1_SingleMode(unsigned int Pin, char* Port,unsigned int Resolution)
  DESCRIPTION:  Initialisation d'une patte en ADC1 , mode single , sans interruption
  PARAMETERS:   Numéro de la patte, Port de la patte, Résolution de la conversion
  RETURNS:   	rien   
  REQUIREMENTS: Avoir activé au moins une patte en mode analogique
===============================================================================*/
void initADC1_SingleMode(unsigned int Resolution);


/*===============================================================================
  FUNCTION:     Start_ADC1_Conversion
  DESCRIPTION:  Réalise une conversion sur l'ADC1 (sans interruption)
  PARAMETERS:   Aucun
  RETURNS:   	Résultat de la conversion (en décimal)
  REQUIREMENTS: l'ADC1 doit être initialisé et activé
===============================================================================*/
int Start_ADC1_Conversion(int Channel);

/*===============================================================================
  FUNCTION:     initADC1_ContinuousMode
  DESCRIPTION:  Initialisation d'une patte en ADC1,en mode continu => avec interruption à chaque fin de conversion
  PARAMETERS:   Numéro de la patte, Port de la patte, Résolution de la conversion
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution);

/*===============================================================================
  FUNCTION:     Disable_ADC1
  DESCRIPTION:  Désactive l'ADC1
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Disable_ADC1(void);

/*===============================================================================
  FUNCTION:     Enable_ADC1
  DESCRIPTION:  Active l'ADC1
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Enable_ADC1(void);

/*===============================================================================
  FUNCTION:     Start_ADC1
  DESCRIPTION:  Démarre une conversion sur l'ADC1
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Start_ADC1(void);

/*===============================================================================
  FUNCTION:     Calibration_ADC1
  DESCRIPTION:  Permet de calibrer l'ADC1
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Calibration_ADC1(void);

/*===============================================================================
  FUNCTION:     Select_Channel_ADC
  DESCRIPTION:  Choix du channel à convertir
  PARAMETERS:   Pin de la patte 
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Select_Channel_ADC(unsigned int Channel);

#endif