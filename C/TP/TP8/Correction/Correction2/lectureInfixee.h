/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : arbre.c
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Mise en oeuvre du Shunting-yard algorithm
* pour créer un AST (abstract syntax tree) à partir d'une écriture infixée
* ref: http://en.wikipedia.org/wiki/Shunting-yard_algorithm
*/


#ifndef __INFIXEE_H__
#define __INFIXEE_H__

#include "arbre.h"


/* crée un arbre depuis une chaine de caractères à notation infixée 
Cette fonction renvoie NULL si une erreur a eu lieu */
t_noeud* creerArbreDepuisInfixee( char* str);


#endif
