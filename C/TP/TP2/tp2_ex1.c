#include <stdio.h>
#define DEBUG 0

int main(){
	FILE *fichier, *fichierTriee;

	fichier = fopen("valeurs.txt", "r");
	fichierTriee = fopen("valeurs-triees.txt", "w");
	if(fichier==NULL){
		printf("Erreur d'ouverture\n");
		return 0;
	} else {
		printf("Ouverture OK\n");
	}
	if(fichierTriee==NULL){
		printf("Erreur d'ouverture\n");
		return 0;
	} else {
		printf("Ouverture OK\n");
	}
	float tab[100],temp;
	int i=0,ret,nbElt;
	
	do{
		ret=fscanf(fichier, "%f", &tab[i]);
		i++;
	} while(ret!=EOF);
	
	nbElt = --i;
	
	if(DEBUG){
		printf("%d\n ",nbElt);
		for(i=--i; i>=0;i--){
		printf("%f ",tab[i]);
		}
	}
	
	/* Tri du Tableau */
	for(int i=0; i<nbElt;i++){
		for(int j=i+1; j<nbElt;j++){
			if(tab[j]<= tab[i]){
					temp=tab[i];
					tab[i]=tab[j];
					tab[j]=temp;
			}	
		}
	}
	
	/* Ecriture dans fichier */
	for(int i=0; i<nbElt; i++){
		fprintf(fichierTriee, "%f\n",tab[i]);
	}
	
	
	if(DEBUG){
		printf("%d\n ",nbElt);
		for(i=0; i<nbElt;i++){
		printf("%f ",tab[i]);
		}
	}
	
	fclose(fichier);
	fclose(fichierTriee);
}