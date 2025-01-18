#include <stdio.h>
#include <stdlib.h>
#include "individu.h"
#include "score.h"
#define SIZETAB 1000

int main(){
  if(DEBUG)printf("\033[34;01m mainP3 \033[00m\n");

  t_individu tabindividu[SIZETAB];

  
  FILE* fichier=fopen("ADN.txt","r");
  if(fichier==NULL){
    printf("Lecture fichier Nok\n");
    exit(EXIT_FAILURE);
  }

  int i=0;
  //while(!feof(fichier)){
  // MANQUE SCORE.H
  while(i<10){
  remplifiche(&tabindividu[i], fichier);
    i++;
  }
  if(DEBUG)printf(" mainP3 nbindividu %d\n", i);

  for(i=i;i>-1;i--){
    affiche(&tabindividu[i]);
    detruit(&tabindividu[i]);
  }
  if(DEBUG)printf(" mainP3 nbindividu %d", i);

  fclose(fichier);

}
