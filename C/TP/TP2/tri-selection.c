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
	int i,iter;
	int imin;					/* indice de l'élément le plus petit */

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

	/* tri par sélection */
	for(iter=0;iter<taille;iter++)
	{
		imin = iter;
		/* on trouve l'indice du plus petit élément, entre les indices iter et taille-1 */
		for(i=iter+1;i<taille;i++)
			/* si T[i]<T[imin] alors on a trouvé un nouvel indice du plus petit */
			if (T[i]<T[imin])
				imin = i;
		/* on échange T[iter] avec T[imin] */
		temp = T[imin];
		T[imin] = T[iter];
		T[iter] = temp;
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