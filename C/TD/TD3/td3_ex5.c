#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10

int main(void) {
	int i,j,k;
	/* compteurs pour les boucles */
	int m,n,p,q;
	/* tailles */
	float sum;
	/* utilis´ e comme somme partielle pour le produit */
	float A[TAILLE][TAILLE];
	float B[TAILLE][TAILLE];
	float C[TAILLE][TAILLE];
	FILE* fichier;
	/* ouverture du fichier */
	fichier = fopen("matrices.txt", "r");
	if (fichier==NULL) {
		printf("Erreur d’ouverture de fichier\n"); exit(1); }
	
	/* lecture la matrice A */
	fscanf( fichier, "%d %d", &m, &n);
	for( i=0; i<m; i++)
		for( j=0; j<n; j++)
		fscanf( fichier, "%f", &(A[i][j]) );

	/* lecture de la matrice B */
	fscanf( fichier, "%d %d", &p, &q);
	for( i=0; i<p; i++)
		for( j=0; j<q; j++)
		fscanf( fichier, "%f", &(B[i][j]) );
	
	/* affichage de la matrice B */
	printf("matrice B\n");
	for( i=0; i<p; i++) {
		for( j=0; j<q; j++) {
		printf("%f ",B[i][j]); }
		printf("\n"); 
	}
	
	/* test si C est calculable */
	if (n!=p) {
		printf("Les dimensions ne correspondent pas!\n");
		exit(1);
	}

	/* calcul de C */
	for( i=0; i<m; i++) {
		for( j=0; j<q; j++) {
			sum = 0;
			for( k=0; k<n; k++) {
				sum = sum + A[i][k]*B[k][j];
			}
			C[i][j] = sum;
		}
	}
	
	/* affichage de la matrice C */
	printf("\nMatrice C\n");
	for( i=0; i<m; i++) {
		for( j=0; j<q; j++) {
		printf("%f ",C[i][j]);
	}
	printf("\n"); }
	/* et on n’oublie pas la fermture du fichier */ fclose( fichier);
	return EXIT_SUCCESS;
}
