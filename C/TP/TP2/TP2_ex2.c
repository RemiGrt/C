#include <stdio.h>
#define DEBUG 1

int main(){
	FILE *fichier, *fichierTriee;
	fichier=fopen("valeurs.txt","r");
	fichierTriee=fopen("valeurs-triees2.txt","w");
	if(fichier ==NULL || fichierTriee==NULL){
		printf("Error Open File");
	}else{
		printf("Open File\n");
	}
		
	float tab[100], temp;
	int ret,i=0, nbElt,permut;
	do{
		ret=fscanf(fichier, "%f", &tab[i]);
		i++;
	}while(ret!=EOF);
		
	nbElt = --i;
	
	if(DEBUG)printf("%d",nbElt);
	
	for(int i=0;i<nbElt;i++){
		permut=0;
		for(int j=1;j<nbElt-i;j++){
			
			if(tab[j-1]> tab[j]){
				permut=1;
				temp = tab[j];
				tab[j]=tab[j-1];
				tab[j-1]=temp;	
			}			
		}
		if(permut==0)break;
	}
	
	for(int i=0; i < nbElt; i++){
		fprintf(fichierTriee,"%f\n",tab[i]);
	}
	
	
	fclose(fichier);
	fclose(fichierTriee);
}