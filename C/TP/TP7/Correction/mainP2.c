/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : mainP2.c
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 2, tests du pourcentage d'inclusion
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "score.h"

int main()
{
	char ch1[50], ch2[50];
	
	/* saisie */
	printf( "Veuillez deux chaines: ");
	scanf( "%s", ch1);
	scanf( "%s", ch2);

	/* affichage du résultat */
	printf( "Pourcentage d'inclusion : %f\n", pourcentageInclusion(ch1,ch2) );
	
	return EXIT_SUCCESS;
}