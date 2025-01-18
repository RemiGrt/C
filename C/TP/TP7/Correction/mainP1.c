/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : mainP1.c
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 1, tests des fonctions
*
*/


#include "individu.h"
#include <stdlib.h>

int main()
{
	FILE* fichier;
	t_indiv Ind[10];
	int i;
	
	/* ouverture du fichier*/
	fichier = fopen( "ADN.txt", "r");
	if (!fichier)
	{
		fprintf( stderr, "Ouverture de fichier impossible\n");
		return EXIT_FAILURE;
	}

	/* lecture des 10ers individus */
	for( i=0; i<10; i++)
		lireIndividu( fichier, &Ind[i]);

	/* affichage des 10ers (dans l'ordre inverse) */
	for( i=9; i>=0; i--)
		afficherIndividu( Ind[i]);

	/* désallouer les individus */
	for( i=0; i<10; i++)
		desallouerIndividu( Ind[i]);
	
	/* fermeture du fichier */
	fclose( fichier);

	return EXIT_SUCCESS;
}
