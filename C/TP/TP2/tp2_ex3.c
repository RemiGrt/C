#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
int main(){
	// Ouverture Fichier
	FILE *fichier;
	fichier=fopen("grille.txt","r");
	if(fichier==NULL){
		printf("Fichier non ouvert\n");
		return EXIT_FAILURE;
	}
	int tab[9][9];
	int tabverif[9]={0,0,0,0,0,0,0,0,0};
	// Recopie dans tableau
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		fscanf(fichier,"%d", &tab[i][j]);
		}
	}
	
	fclose(fichier);
	
	// AFFICHAGE
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		printf("----");
		}
		printf("-\n");
		for(int j=0;j<9;j++){
			printf("| %d ",tab[i][j]);
		}
		printf("|\n");
	}
	for(int j=0;j<9;j++){
		printf("----");
	}
	printf("-\n");
	// END AFFICHAGE
	
	// Verification ligne
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		// Incremente les occurences 
		// -- sert à placer les indexes de 1 à 9 vers 0 à 8
		 tabverif[tab[i][j]]++;
		}
		for(int j=0;j<9;j++){	 
		 if(DEBUG) printf("%d ",tabverif[j]);
		}
		if(DEBUG) printf("\n");
		
		for(int j=0;j<9;j++){
		 // Print Erreur  
		 if(tabverif[j]>1) printf("Erreur ligne %d, il y a %d occurence de %d\n",i,tabverif[j],j);
		 // reinitialisation de tabverif
		 tabverif[j]=0;	
		}
		
	}
	printf("\n");
	
	
	
	// Verification colonne
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			// On intervertit i et j
		 tabverif[tab[j][i]]++;
		}
		for(int j=0;j<9;j++){ 
		 if(DEBUG) printf("%d ",tabverif[j]);
		}
		if(DEBUG) printf("\n");
		
		for(int j=0;j<9;j++){
		 if(tabverif[j]>1) printf("Erreur colonne %d, il y a %d occurence de %d\n",i,tabverif[j],j);
		 tabverif[j]=0;	
		}
		
	}
}