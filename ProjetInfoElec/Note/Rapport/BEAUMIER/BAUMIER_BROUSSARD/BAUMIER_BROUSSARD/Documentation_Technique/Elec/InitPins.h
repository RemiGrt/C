/**
* \file 
*			InitPins.h
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Librairie contenant les fonctions du fichier InitPins.c
*/


#ifndef __INITPINS_H__
#define __INITPINS_H__

/** 
 * \fn  void initPatte_OUT(unsigned int N, char* Port, char *RPull)
 * \brief 
 *			Configuration d'une patte (définie par l'utilisateur) en tant que sortie numérique
 * \param[in] 
 *			N		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			*RPull	Résistance de tirage ("Pull-up" ou "Pull-Down")
 */
extern  void initPatte_OUT(unsigned int N, char* Port, char *RPull);

/** 
 * \fn  void initPatte_IN(unsigned int N, char* Port, char* RPull)
 * \brief 
 *			Configuration d'une patte (définie par l'utilisateur) en tant qu'entrée numérique
 * \param[in] 
 *			Pin		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Résistance de tirage
 */
extern  void initPatte_IN(unsigned int N, char* Port, char* RPull);

/** 
 * \fn  void initPatte_IN_Interruption(unsigned int N,char* Port,char* RPull, char* Front)
 * \brief 
 *			Configuration d'une patte (définie par l'utilisateur) en tant qu'entrée numérique AVEC INTERRUPTION
 * \param[in] 
 *			N		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Résistance de tirage ("Pull-up" ou "Pull-Down")
 * \param[in] 
 *			Front	Choix du front d'interruption ("Montant" ou "Descendant")
 */
extern  void initPatte_IN_Interruption(unsigned int N,char* Port,char* RPull, char* Front);

/** 
 * \fn  void Select_EXTICR(unsigned int N, char* Port)
 * \brief 
 *			Initialise automatiquement le registre EXTICR en indiquant la patte souhaitée
 *			\b/!\ Utiliser le mode interruption externe \b/!\
 * \param[in] 
 *			N		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
extern  void Select_EXTICR(unsigned int N, char* Port);

/** 
 * \fn  void initPatte_AF(unsigned int Pin, char* Port,char* RPull, unsigned int Num_AF)
 * \brief 
 *			Initialise une patte avec la fonction alternative souhaitée
 * \param[in] 
 *			Pin		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Résistance de tirage ("Pull-up" ou "Pull-Down")
 * \param[in] 
 *			Num_AF	Numéro de la fonction alternative
 */
extern  void initPatte_AF(unsigned int Pin, char* Port,char* RPull, unsigned int Num_AF);


/** 
 * \fn  void Init_Analogic_Mode(int Pin, char *Port)
 * \brief 
 *			Initialise une patte en mode analogique, pour les ADC/DAC
 * \param[in] 
 *			Pin		Numéro de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
extern void Init_Analogic_Mode(int Pin, char *Port);
#endif
