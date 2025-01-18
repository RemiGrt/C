/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : mainP1.c
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 1 : création d'arbres
*/

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

int main()
{

	/* 12+ 4*x */
	//t_noeud* arbre = creerNoeudOp( creerFeuilleReel(12), "+", creerNoeudOp( creerFeuilleReel(4), "*", creerFeuilleVar("x") ) );
	
	/* (12+x)*(6/25)^2 */
	t_noeud* n1 = creerNoeudOp( creerFeuilleReel(12), "+", creerFeuilleVar("x") );
	t_noeud* n2 = creerNoeudOp( creerFeuilleReel(6), "/", creerFeuilleReel(25) );
		
	t_noeud* arbre = creerNoeudOp( n1, "*", creerNoeudOp( n2, "^", creerFeuilleReel(2) ) );
	
	detruireArbre(arbre);

	return EXIT_SUCCESS;
}