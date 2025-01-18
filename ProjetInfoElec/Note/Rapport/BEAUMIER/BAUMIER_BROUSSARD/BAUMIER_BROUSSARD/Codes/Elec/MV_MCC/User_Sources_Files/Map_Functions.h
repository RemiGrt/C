/*
 Definition des fonctions utiles pour générer facilement les E/S du microcontrôleur
*/	
			
#ifndef __MAP_FUNCTIONS_H__			
#define __MAP_FUNCTIONS_H__			

// Fonctions générales
void RAZ_Tableau_int(int * Tab, int Debut, int Taille);
void Write_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src);
void Read_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src);
	
// Fonctions d'entrées numériques
void Initialisation_Entrees_GPIO(void);
void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille);
void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille);

// Fonctions de sorties numériques
void Initialisation_Sorties_GPIO(void);
void Ecriture_Sorties_GPIO(int *Tab, int Debut, int Taille);

// Fonctions ADC
void Initialisation_Entrees_ADC(void);
int Lecture_Entree_ADC(int Channel, int NB_Mesures);


// Fonctions PWM
void Initialisation_Sorties_PWM(void);
void Activer_PWM(int Num_PWM);
void Desactiver_PWM(int Num_PWM);

#endif			
