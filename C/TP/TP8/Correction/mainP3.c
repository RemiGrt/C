/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : mainP2.c
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 3 : calculs
*/


#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

#include "lectureInfixee.h"
#include "equation.h"

int main()
{
	char buffer[200];
	char* s = buffer;
	t_noeud* arbre;
	
	/* saisie */
	printf("Veuillez saisir une expression\n");
	while ( (*s++ = getchar()) != '\n' );
	*(--s)=0;
		
	/* création */	
	arbre = creerArbreDepuisInfixee(buffer);
	
	/* evaluation */
	evaluer(arbre);
	deriver(arbre,"x");

	/* affichage */
	afficherInfixee( arbre);
	printf("\n");

	/* simplification */
	evaluer(arbre);
	arbre = simplifier(arbre);
	afficherInfixee( arbre);
	printf("\n");


	
	/* destruction*/
	detruireArbre(arbre);

	return EXIT_SUCCESS;
}