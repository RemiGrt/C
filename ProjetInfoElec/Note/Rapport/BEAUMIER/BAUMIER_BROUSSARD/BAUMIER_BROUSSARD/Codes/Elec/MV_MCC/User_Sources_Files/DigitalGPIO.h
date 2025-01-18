/********************************************************************************
Titre : Gestion_GPIO.h
Auteur : Thomas Broussard
Date : 22/02/17
--------------------------------
Description : Librairie contenant les fonctions du fichier Gestion_GPIO.c


********************************************************************************/

#ifndef __GESTION_GPIO_H__
#define __GESTION_GPIO_H__


/*===============================================================================
  FUNCTION:     DigitalWrite
  DESCRIPTION:  Force la valeur d'une Patte en Sortie Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte, Etat Logique (1 ou 0)
  RETURNS:   	rien
  REQUIREMENTS: La patte doit être initialisée en Sortie Numérique
===============================================================================*/
extern void DigitalWrite (unsigned int Pin, char * Port, unsigned int  Etat);

/*===============================================================================
  FUNCTION:     DigitalToggle
  DESCRIPTION:  Inverse la valeur d'une Patte en Sortie Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte
  RETURNS:   	rien
  REQUIREMENTS: La patte doit être initialisée en Sortie Numérique
===============================================================================*/
extern void DigitalToggle (unsigned int Pin, char * Port);
	
/*===============================================================================
  FUNCTION:     DigitalRead
  DESCRIPTION:  Lit la valeur d'une patte en mode Entrée Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte
  RETURNS:   	Etat logique de la patte (1 ou 0)
  REQUIREMENTS: La patte doit être initialisée en Entrée Numérique
===============================================================================*/
extern int DigitalRead (unsigned int Pin, char * Port);


#endif
