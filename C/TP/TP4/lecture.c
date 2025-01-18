#include <stdio.h>
#include <affichage.h>

#define DEBUG 1

int lecture(char nomfichier[], int lab[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2]){

  if(DEBUG)printf("Labyrinthe: Call labyrinthe\n");
  FILE* fichier=fopen(nomfichier, "r");
  if(fichier==NULL){
    if(DEBUG)printf("Labyrinthe: Ouverture fichier NOK\n");
    return 0;
  }
  
  
  // Scan des 4 premieres valeurs du fichiers
  if(DEBUG)printf("Labyrinthe: 1er scanf\n");
  fscanf(fichier,"%d %d %d %d",&depart[0],&depart[1],&arrivee[0],&arrivee[1]);
  if(DEBUG)printf("Depart: %d %d, Arrivee: %d %d \n",depart[0],depart[1],arrivee[0],arrivee[1]);
  if(DEBUG)printf("Labyrinthe: 2e scanf\n");
  // Scan du reste du lab 
    for(int y=0;y<TAILLE_Y;y++)
        for(int x=0;x<TAILLE_X;x++)
          fscanf(fichier,"%d",&lab[x][y]);
    
  

  fclose(fichier);
  if(DEBUG)printf("Labyrinthe: return\n");
  return 1;

}
