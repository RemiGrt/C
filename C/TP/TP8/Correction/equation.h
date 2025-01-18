/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : equation.h
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Manipulation d'une équation
*/

#ifndef __EQUATION_H__
#define __EQUATION_H__


#include "arbre.h"

/* affiche le noeud, mais pas les fils */
void afficherNoeud( t_noeud* arbre);

/* afficher une équation sous forme infixée */
void afficherInfixee( t_noeud* arbre);

/* afficher une équation sous forme postfixée */
void afficherPostfixee( t_noeud* arbre);

/* evaluer un arbre */
int evaluer( t_noeud* arbre);

/* dériver par rapport à une variable 
en considérant que les autres sont indépendantes */
void deriver( t_noeud* arbre, char* var);

/* simplifier un arbre
En applicquant les règles suivantes :
x+0 ou 0+x => x
x-0 => x 
1*x ou 1*x => x
0*x ou x*0 => 0
x^1 => x
x^0 => 1
x/1 => x */
t_noeud* simplifier( t_noeud* arbre);

#endif
