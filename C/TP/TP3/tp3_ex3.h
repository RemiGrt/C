#include <stdio.h>

#ifndef tp3_ex3
#define tp3_ex3

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


int chercheLettreRoue(char cylindre[NBLIGNE][NBCOLONNE], int nbRoue, char lettre){
  int i=0;
  //printf("\n");
  //printf("lettre :%c   ",lettre);
  while(cylindre[i][nbRoue] != lettre){
    //printf("%c",cylindre[i][nbRoue]);
    i++;
  }
  //printf("  ");
  return i;
}

void tourneRoue(char cylindre[NBLIGNE][NBCOLONNE], int nbRoue, int decal){
  char temp[NBLIGNE];
  // Recopie dans tableau temporaire
  //printf(" temp \n");
  for(int j=0;j<NBLIGNE;j++){
    temp[j]=cylindre[j][nbRoue];
    //  printf(" %c ",temp[j]);
    }
  // printf("\n");
  
// // remplie case de 0 -> decal-1
  for(int i=decal;i<NBLIGNE;i++){
    //printf(" i %d",i);
    cylindre[i-(decal)][nbRoue]=temp[i];
  }
 
 // remplie case de decal-1 -> TAILLE
  for(int i=0;i<decal;i++){
   //printf(" i %d",i);
    cylindre[NBLIGNE-decal+i][nbRoue]=temp[i];
  }
  //printf("\n");
 //printf(" cylindre  \n");
 for(int j=0;j<NBLIGNE;j++){
   //   printf("%c ",cylindre[j][nbRoue]);
   }
 //printf("\n");
}


#endif
