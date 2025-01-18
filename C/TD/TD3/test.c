#include <stdio.h>

void main(){
	FILE* fichier;
	fichier = fopen("matrices.txt", "r");
	if (fichier == NULL) printf("Ouverture NOK");
	
	int n, m;
	fscanf(fichier, "%d %d", &n, &m);
	printf("\n%d %d\n", n, m);
	
	int tab[n][m];
	
	for(int ligne=0; ligne<n;ligne++){
		for(int colonne=0; colonne<m;colonne++){
			fscanf(fichier, "%d", &tab[ligne][colonne]);
			printf("%d ", tab[ligne][colonne]);
		}
		printf("\n");
	}
			
	
			
	fclose(fichier);
	
	//int bob[3];
	int bob[] = {1,17,42};
	printf("\n%d", *(bob+1));
	
	
}