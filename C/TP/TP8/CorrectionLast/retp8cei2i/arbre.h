/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : arbre.h
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Manipulation d'un arbre
*/

#ifndef __ARBRE_H__
#define __ARBRE_H__


/* définition d'un noeud */
typedef struct s_noeud
{
	float val;
	char* ch;
	struct s_noeud* filsG;
	struct s_noeud* filsD;
} t_noeud;


/* création d'un noeud général*/
t_noeud* creerNoeud( float val, char* ch, t_noeud* filsG, t_noeud* filsD);

t_noeud* creerNoeudOp( t_noeud* filsG, char* ch, t_noeud* filsD);

/* création d'une feuille réelle */
t_noeud* creerFeuilleReel( float val);

/* création d'une feuille avec une variable */
t_noeud* creerFeuilleVar( char* ch);

/* détruire un arbre */
void detruireArbre( t_noeud* arbre);

/* indique le nb de fils d'une noeud
0 si c'est une feuille */
int nbFils( t_noeud* noeud);

/* duplique un arbre */
t_noeud* dupliquer( t_noeud* arbre);

#endif
