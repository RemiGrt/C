/*=====================================
*
*     oO  test de grille de sudoku   Oo
*
*=====================================
*
* File : loto.c
* Date : 25sept 09
* Author : Hilaire Thibault
*
*=====================================
*/

#include <stdio.h>
#include <stdlib.h>

/* *** constantes *** */
#define DIM 3
#define TAILLE DIM*DIM



int main()
{
	int grille[TAILLE][TAILLE];		/* création du tableau de sudoku */
	FILE* fichier;					/* pointeur de fichier */
	int i,j,k;
	int val[10];					/* tableau pour compter le nb d'occurence de chaque chiffre */
	
	/* ouverture du fichier */
	fichier = fopen( "grille.txt", "r");
	if (fichier==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return EXIT_FAILURE;
	}
	/* lecture du fichier */
	for(i=0;i<TAILLE;i++)
		for(j=0;j<TAILLE;j++)
			fscanf( fichier, "%d", &(grille[i][j]) );

	/* fermeture du fichier */
	fclose(fichier);
	
	/* affichage de la grille */
	for( i=0; i<TAILLE; i++)
	{
		/* ligne horizontale */
		for( j=0; j<TAILLE; j++)
			printf("----");
		printf("-\n");
		/* affichage de la ième ligne */
		for( j=0; j<TAILLE; j++)
			printf( "| %d ", grille[i][j]);
		printf("|\n");
	}
	/* dernière ligne horizontale */
	for( j=0; j<TAILLE; j++)
		printf("----");
	printf("-\n");


	/* vérification des lignes */
	for( i=0; i<TAILLE; i++)
	{
		/* initialisaion de val */
		for( k=1; k<=TAILLE; k++)
			val[k]=0;
			
		/* parcours la ligne */
		for( j=0; j<TAILLE; j++)
			/* on incrémente le nb d'occurences du chiffre présent à l'indice [i,j] de la grille */
			val[ grille[i][j] ] ++;			
		
		/* test si tous les chiffres sont présents 1 fois uniquement */
		for( k=1; k<=TAILLE; k++)
			if ( val[k] != 1 )
				printf( "Ligne %d : le nb %d apparait %d fois\n", i+1, k, val[k]);
	}

	/* pour chaque colonne j */
	for( j=0; j<TAILLE; j++)
	{
		/* initialisaion de val */
		for( k=1; k<=TAILLE; k++)
			val[k]=0;
			
		/* parcours la colonne */
		for( i=0; i<TAILLE; i++)
			/* on incrémente le nb d'occurences du chiffre présent à l'indice [i,j] de la grille */
			val[ grille[i][j] ] ++;			
		
		/* test si tous les chiffres sont présents 1 fois uniquement */
		for( k=1; k<=TAILLE; k++)
			if (val[k]!=1)
				printf( "Colonne %d : le nb %d apparait %d fois\n", j+1, k, val[k]);
	}

	return EXIT_SUCCESS;
}