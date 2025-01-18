/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : individu.h
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Définitions de types (t_individu, etc.)
* et prototypes
*/

#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <stdio.h>

/* définition d'un individu */
typedef struct
{
	char* nom;				/* son nom */
	char* adn;				/* son adn */
	float similarite;		/* le calcul de similarité avec l'adn recherché */
} t_indiv;



/* Fonction de lecture d'un individu dans le fichier
(les chaînes lues sont recopiées)
Paramètres :
- pInd : pointeur sur un t_indiv
- fichier : pointeur sur un FILE
*/
void lireIndividu( FILE* fichier, t_indiv* pInd);



/* Fonction qui affiche un individu 
Paramètres :
- pInd : pointeur vers le t_indiv à afficher
Retour : aucun*/
void afficherIndividu( t_indiv Ind);



/* Fonction qui désalloue toute la mémoire allouée à la création d'un individu
Paramètres :
- pInd : pointeur vers le t_indiv à désallouer
Retour : aucun*/
void desallouerIndividu( t_indiv Ind);


/* Fonctin qui calcule le pourcentage de ressemblance entre l'adn d'un individu et une chaine donnée
Paramètres :
- pInd : pointeur vers l'individu en question
- adn : chaine qu'il faut comparer avec l'adn de l'individu
Retour : aucun*/
void calculerSimilarite( t_indiv* pInd, char* adn);




/* indique si un individu est intéressant (c-à-d a une similarité + grande qu'un individu dans le tableau)
Paramètres :
- tabIndiv : tableau d'individus
- nbIndiv : taille du tableau d'individus
- Ind : individu dont on veut regarder s'il a sa place
Retour :
- Booléen VRAI si l'individu est intéressant  */
int individuEstInteressant( t_indiv* tabIndiv, int nbIndiv, t_indiv Ind);

/* insere un individu dans le tableau d'individus interessants */
void insererIndividu( t_indiv* tabIndiv, int nbIndiv, t_indiv Ind);


#endif
