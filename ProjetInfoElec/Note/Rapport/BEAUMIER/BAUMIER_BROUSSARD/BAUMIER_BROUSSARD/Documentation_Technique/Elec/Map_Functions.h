/**
* \file Map_Functions.h
* \author Jeanne Baumier & Thomas Broussard
* \date 6 fevrier 2017
* \brief Librairie liée au fichier Map_Functions.c
*/
			
#ifndef __MAP_FUNCTIONS_H__			
#define __MAP_FUNCTIONS_H__			

// Fonctions generales

/** 
 * \fn  void RAZ_Tableau_int(int * Tab, int Debut, int Taille)
 * \brief 
 *			Met a zero un ensemble de cases contenues dans un tableau d'entiers
 * \param[in] 
 *			Tab			Tableau a remettre a zero
 * \param[in] 
 *			Debut				Case de debut
 * \param[in] 
 *			Taille					Taille du tableau a remettre a zero
 */
void RAZ_Tableau_int(int * Tab, int Debut, int Taille);

/** 
 * \fn  void Write_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
 * \brief 
 *			Copie les informations d'un tableau Src vers un tableau Dest, avec un decalage lors de la copie, selon le pas donne
 * \param[in] 
 *			Tab_Dest			Tableau de destination
 * \param[in] 
 *			Tab_Src				Tableau source
 * \param[in] 
 *			Pas					Pas choisi
 * \param[in] 
 *			Debut_Dest		Debut de la destination
 * \param[in] 
 *			Taille_Src			Taille source
 */
void Write_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src);

/** 
 * \fn  void Read_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
 * \brief 
 *			Lire les informations d'un tableau Src (tableau variable[]) vers un tableau Dest (tableau "trie"), avec un decalage lors de la lecture, selon le pas donne
 * \param[in] 
 *			Tab_Dest			Tableau de destination
 * \param[in] 
 *			Tab_Src				Tableau source
 * \param[in] 
 *			Pas					Pas choisi
 * \param[in] 
 *			Debut_Dest		Debut de la destination
 * \param[in] 
 *			Taille_Src			Taille source
 */
void Read_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src);
	
// Fonctions d'entrees numeriques

/** 
 * \fn  void Initialisation_Entrees_GPIO(void)
 * \brief 
 *			Initialise l'ensemble des entrees numeriques definies
 */
void Initialisation_Entrees_GPIO(void);
/** 
 * \fn  void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille)
 * \brief 
 *			A partir d'un tableau d'entier, on verifie l'ensemble des entrees definies dans Map_Entrees[SIZE_IN] \n On doit egalement preciser les cases de debut et de fin du tableau
 * \param[in] 
 *			Tab					Tableau 
 * \param[in] 
 *			Debut				Case de debut
 * \param[in] 
 *			Taille					Taille
 */
void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille);

/** 
 * \fn  void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille)
 * \brief 
 *			Determine la valeur des fronts de chaque entree en fonction de la valeur actuelle et de la valeur precedente 
 * \param[in] 
 *			*Valeur_Actuelle			Valeur actuelle 
 * \param[in] 
 *			*Valeur_Precedente		Valeur precedente
 * \param[in] 
 *			*Front_Montant				Front_Montant
 * \param[in] 
 *			*Front_Descendant		Front_Descendant
 * \param[in] 
 *			Debut								Debut
 * \param[in] 
 *			Taille								Taille : nombre de cases a remplir pour le tableau - donc nombre d'entree pour lesquelles nous voulons relever les etats
 */
void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille);

// Fonctions de sorties numeriques

/** 
 * \fn  void Initialisation_Sorties_GPIO(void)
 * \brief 
 * 		Initialise l'ensemble des sorties numeriques definies
 */
void Initialisation_Sorties_GPIO(void);

/** 
 * \fn  void Ecriture_Sorties_GPIO(int *Tab, int Debut, int Taille)
 * \brief 
 * 		A partir d'un tableau d'entier, on actualise l'ensemble des sorties definies dans Map_Sorties[SIZE_OUT] \n On doit egalement preciser la case de debut du tableau, et la taille du tableau a lire
 * \param[in] 
 *			*Tab								Tableau
 * \param[in] 
 *			Debut				Case de debut
 * \param[in]  
 *			Taille			Taille du tableau
 */
void Ecriture_Sorties_GPIO(int *Tab, int Debut, int Taille);

// Fonctions ADC

/** 
 * \fn void Initialisation_Entrees_ADC(int Resolution)
 * \brief 
 * 		Initialise l'ensemble des entrees ADC definies, sans les activer
 * \param[in]  
 *			Resolution			Resolution souhaitee
 */
void Initialisation_Entrees_ADC(void);

/** 
 * \fn  int Lecture_Entree_ADC(int Num_ADC, int NB_Mesures)
 * \brief 
 * 		Realise une serie de mesures sur l'entree ADC selectionnee, puis rnevoie la moyenne de ces valeurs
 * \param[in]  
 *			Num_ADC			Num_ADC
 * \param[in]  
 *			NB_Mesures			NB_Mesures
 */
int Lecture_Entree_ADC(int Channel, int NB_Mesures);


// Fonctions PWM

/** 
 * \fn  void Initialisation_Sorties_PWM(void)
 * \brief 
 * 		Initialise l'ensemble des timer et des entrees PWM
 */
void Initialisation_Sorties_PWM(void);

/** 
 * \fn  void Activer_PWM(int Num_PWM, int Frequence, int Duty_Cycle)
 * \brief 
 * 		Active l'interruption lie au signal PWM souhaite, en modifiant sa frequence et son rapport cyclique
 * \param[in]  
 *			Num_PWM			PWM pour lequel on souhaite activer l'interruption
 * \param[in]  
 *			Frequence			Frequence du PWM
 * \param[in]  
 *			Duty_Cycle			Rapport cyclique du PWM
 */
void Activer_PWM(int Num_PWM, int Frequence, int Duty_Cycle);

/** 
 * \fn  void Desactiver_PWM(int Num_PWM) 
 * \brief 
 * 		Desactive le signal PWM en question
 * \param[in]  
 *			Num_PWM			Numero du PWM que l'on souhaite desactiver
 */
void Desactiver_PWM(int Num_PWM);

#endif			
