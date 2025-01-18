//#############################################################
// Auteur : Thomas Broussard
// Date : 10/02/17
// Titre : Init.pins.h
//------------------------------------------------------------
// Description  :
//	Contient les fonctions du fichier Initpins.c
//	
//
//
//
//
//#############################################################

#ifndef __INITPINS_H__
#define __INITPINS_H__
/*===============================================================================
  FUNCTION:     initPatte_OUT
  DESCRIPTION:  Configuration d'une patte (définie par l'utilisateur) en tant que sortie numérique
  PARAMETERS:   Numéro de la patte, Port de la patte, Résistance de tirage ("Pull-Up" ou "Pull-Down")
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
extern  void initPatte_OUT(unsigned int N, char* Port, char *RPull);

/*===============================================================================
  FUNCTION:     initPatte_IN
  DESCRIPTION:  Configuration d'une patte (définie par l'utilisateur) en tant qu'entrée numérique
  PARAMETERS:   Numéro de la patte, Port de la patte, résistance de tirage ("Pull-up" ou "Pull-Down")
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
extern  void initPatte_IN(unsigned int N, char* Port, char* RPull);

/*===============================================================================
  FUNCTION:     initPatte_IN_Interruption
  DESCRIPTION:  Configuration d'une patte (définie par l'utilisateur) en tant qu'entrée numérique AVEC INTERRUPTION
  PARAMETERS:   Numéro de la patte , Port de la patte , Choix du front d'interruption ("Montant" ou "Descendant")
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
extern  void initPatte_IN_Interruption(unsigned int N,char* Port,char* RPull, char* Front);

/*===============================================================================
  FUNCTION:     Select_EXTICR
  DESCRIPTION:  Initialise automatiquement le registre EXTICR en indiquant la patte souhaitée
  PARAMETERS:   Numéro de la patte , Port de la patte
	RETURNS:   	rien   
  REQUIREMENTS: Utiliser le mode interruption externe
===============================================================================*/
extern  void Select_EXTICR(unsigned int N, char* Port);

/*===============================================================================
  FUNCTION:     initPatte_AF
  DESCRIPTION:  Initialise une patte avec la fonction alternative souhaitée
  PARAMETERS:   Numéro de la patte , Port de la patte, Résistance de tirage, Numéro de la fonction alternative
	RETURNS:   	rien   
  REQUIREMENTS: rien
===============================================================================*/
extern  void initPatte_AF(unsigned int Pin, char* Port,char* RPull, unsigned int Num_AF);

/*===============================================================================
  FUNCTION:     Init_Analogic_Mode
  DESCRIPTION:  Initialise une patte en mode analogique, pour les ADC/DAC
  PARAMETERS:   Numéro de la patte , Port de la patte
	RETURNS:   		rien   
  REQUIREMENTS: rien
===============================================================================*/
extern void Init_Analogic_Mode(int Pin, char *Port);
#endif
