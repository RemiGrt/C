#include <stdio.h>
#include "ex2.h"
#include "libfonc2.h"


int main(){
  t_personne bob;
  FILE *fichier=fopen("td2_ex2.txt","r");
  if(fichier==NULL){
    printf("Ouverture fichier NOK\n");
    return 0;
  }
  litPersonne(fichier, &bob); 
  affichePersonne(bob);
}


