/*=====================================
*
*     oO  Tri sélection   Oo
*
*=====================================
*
* File : tri-selection.c
* Date : 14 oct 12
* Author : Hilaire Thibault
*
*=====================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 100

int main()
{
	FILE* fichier;				/* descripteur de fichier */
	float T[TAILLE_MAX];		/* tableau à trier */
	float temp;
	int taille;					/* taille du tableau */
	int i,j;
	
	/* ouverture du fichier */
	fichier = fopen( "valeurs.txt", "r");
	if (fichier==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return EXIT_FAILURE;
	}

	/* lecture du fichier */
	fscanf( fichier, "%d", &taille);	
	for(i=0;i<taille;i++)
		fscanf( fichier, "%f", &T[i]);

	/* fermeture du fichier */
	fclose(fichier);

	/* tri à bulles */
	for(i=0;i<taille;i++)
	{
		for(j=1;j<(taille-i);j++)
			if (T[j-1]>T[j])
			{
				/* on échange T[j-1] avec T[j] */	
				temp = T[j-1];
				T[j-1] = T[j];
				T[j] = temp;
			}
		
	}

	/* sauvegarde dans le fichier */
	fichier = fopen( "valeurs-triees.txt", "w");
	if (fichier==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return EXIT_FAILURE;
	}
	fprintf( fichier, "%d\n",taille);
	for(i=0;i<taille;i++)
		fprintf( fichier, "%f\n",T[i]);
	fclose(fichier);

	return EXIT_SUCCESS;
}