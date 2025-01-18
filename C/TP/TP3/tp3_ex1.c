#include <stdio.h>
#include <stdlib.h>

#define NBCOLONNE 19
#define NBLIGNE 26

int LitCylindre(char *fichierName, char cylindre[NBLIGNE][NBCOLONNE]){
  FILE* fichier = fopen(fichierName, "r");
  if(fichier == NULL){
    // Ouverture du fichier NOK
    return 1;
  }


  // i 0 j 0 cylindre[0][0]
  // i 0 j 1 cylindre[1][0]
  // i 0 j 2 cylindre[2][0]
  // i 0 j 3 cylindre[3][0]
  for(int i=0; i<NBCOLONNE; i++)
    for(int j=0; j<NBLIGNE; j++)
      fscanf( fichier , "%c" , &(cylindre[j][i]) );	

  fclose(fichier);
  return 0;
}

void AfficheCylindre(char cylindre[NBLIGNE][NBCOLONNE]){
  for(int i=0; i<NBLIGNE; i++){
    for(int j=0; j<NBCOLONNE; j++){
      printf("  %c ",cylindre[i][j]);	
    }
    printf("\n");
  }
}




int main(){
  char fichierName[] = "jefferson.txt";

  char cylindre[NBLIGNE][NBCOLONNE];
 
  if((LitCylindre(fichierName,cylindre))){
    printf("Ouverture du fichier NOK\n");
    return 0;
  }else{
    printf("Ouverture du fichier OK\n");
  }
  

  AfficheCylindre(cylindre);
  return 0;
}
