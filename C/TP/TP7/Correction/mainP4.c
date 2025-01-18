/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : mainP4.c
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Partie 4, les 10 plus probables
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "score.h"
#include "individu.h"


int main()
{
	FILE* fichier;
	t_indiv IndCourant;
	t_indiv* tabIndiv;
	char adn_test[100];
	int i, N, nbIndividu=0;
	
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
	
	/* saisie du nombre d'individus max à garder */
	printf( "Veuillez saisir le nombre N d'individu à garder:\n");
	scanf( "%d", &N);
	
	/* allocation de N individus */
	tabIndiv = (t_indiv*) malloc (N*sizeof(t_indiv));
	if (!tabIndiv)
	{
		fprintf (stderr, "(main) : Erreur d'allocation\n");
		return EXIT_FAILURE;
	}

	/* parcourt du fichier */
	while (!feof(fichier))
	{
	
		/* lecture de l'individu courant */
		lireIndividu( fichier, &IndCourant);
		calculerSimilarite( &IndCourant, adn_test);

		/* test si plus suspect */
		if (nbIndividu<N)
		{
			insererIndividu( tabIndiv, nbIndividu, IndCourant);
			nbIndividu++;
		}
		else if (individuEstInteressant( tabIndiv, nbIndividu, IndCourant))
		{
			insererIndividu( tabIndiv, nbIndividu, IndCourant);
		}
		else
		{
			desallouerIndividu( IndCourant);
		}
		
	}

	/* fermeture du fichier */
	fclose( fichier);
	
	/* affichage du suspect */
	printf( "Les %d individus qui ont la plus grande similarité sont\n", nbIndividu);
	for( i=0; i<nbIndividu; i++)
	{
		printf( "%s (score=%.2f%%)\n", tabIndiv[i].nom, 100*tabIndiv[i].similarite );
		desallouerIndividu( tabIndiv[i]);
	}
	free(tabIndiv);

	return EXIT_SUCCESS;


}


