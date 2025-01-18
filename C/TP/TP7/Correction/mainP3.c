/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : mainP3.c
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 3, lecture dans un fichier
*
*/

#include "individu.h"
#include <stdlib.h>


int main()
{
	FILE* fichier;
	t_indiv IndCourant, suspect;
	char adn_test[100];
	
	/* ouverture du fichier*/
	fichier = fopen( "ADN.txt", "r");
	if (!fichier)
	{
		fprintf( stderr, "Ouverture de fichier impossible\n");
		return EXIT_FAILURE;
	}

	/* saisie adn recherchée */
	printf( "Veuillez saisir une séquence d'ADN à tester:\n");
	scanf( "%s", adn_test);

	/* parcourt du fichier */
	suspect.similarite = 0;
	suspect.nom = NULL;
	suspect.adn = NULL;
	while (!feof(fichier))
	{
	
		/* lecture de l'individu courant */
		lireIndividu( fichier, &IndCourant);
		calculerSimilarite( &IndCourant, adn_test);

		/* test si plus suspect */
		if (IndCourant.similarite > suspect.similarite)
		{
			desallouerIndividu( suspect);
			suspect = IndCourant;
		}
		else
		{
			desallouerIndividu( IndCourant);
		}
		
	}

	/* fermeture du fichier */
	fclose( fichier);
	
	/* affichage du suspect */
	printf( "%s est notre suspect (score=%.2f%%)\n", suspect.nom, 100*suspect.similarite );
	desallouerIndividu( suspect);

	return EXIT_SUCCESS;


}