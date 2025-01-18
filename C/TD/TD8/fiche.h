#ifndef __FICHE_H__
#define __FICHE_H__
#include <stdio.h>
/* déclaration du type "fiche" */
typedef struct
{
char* nom;
char* prenom;
int age;
} t_fiche;
/* création d’un tableau de fiches
il faudra désallouer ce tableau après */
t_fiche* creerTableauFiches( char* nomFichier, int* pNbFiches);
/* remplit une fiche depuis un fichier */
void remplirFiche( FILE* fichier, t_fiche* pFiche);
/* désalloue les chaines de caractères d’une fiche */
void detruireFiche( t_fiche* pFiche);
/* détruit le tableau de fiches */
void detruireTableauFiches( t_fiche* fiches, int nbFiches);
/* affiche une fiche */
void afficherFiche( t_fiche fiche);
#endif
