#include <stdio.h>
#include <stdlib.h>
#include "individu.h"
#define SIZETAB 10

int main(){
  if(DEBUG)printf("\033[34;01m mainP1 \033[00m\n");

  t_individu tabindividu[SIZETAB];

  
  FILE* fichier=fopen("ADN.txt","r");
  if(fichier==NULL){
    printf("Lecture fichier Nok\n");
    exit(EXIT_FAILURE);
  }

  for(int i=0;i<SIZETAB;i++){
    remplifiche(&tabindividu[i], fichier);
  }

  for(int i=SIZETAB-1;i>-1;i--){
    affiche(&tabindividu[i]);
    detruit(&tabindividu[i]);
  }
  
  fclose(fichier);

}
