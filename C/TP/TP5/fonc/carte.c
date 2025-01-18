#include <stdio.h>
#include <stdlib.h>
#include "carte.h"

#define SYMCOEUR "\xE2\x99\xA1"

void affiche(t_carte carte){
  printf(" ");
  printf("%d", carte.valeur);
  switch(carte.couleur){
  case coeur: 
    printf(SYMCOEUR);
    break;
  case trefle: 
    printf("\xE2\x99\xA3");
    break;
  case pique: 
    printf("\xE2\x99\xA0");
    break;
  case carreau: 
    printf("\xE2\x99\xA2");
    break;
  }
  printf(" ");
}

void rempli(t_jeu jeu){
  for(int i=0; i<NBCarte; i++){
   if(i<carte_coeur){
     jeu[i].valeur=i+1;
     jeu[i].couleur=coeur;
   }
   else if(i < carte_carreau){
     jeu[i].valeur=i+1-carte_coeur;
     jeu[i].couleur=carreau;
   }
   else if(i < carte_trefle){
      jeu[i].valeur=i+1-carte_carreau;
      jeu[i].couleur=trefle;
   }
   else{
      jeu[i].valeur=i+1-carte_trefle;
      jeu[i].couleur=pique;
   }
  }
    
}

void afficheJeu(t_jeu jeu){
for(int i=0;i<NBCarte;i++){
  if(i%13==0)printf("\n");
  affiche(jeu[i]);
  }
 printf("\n");
}

void melange(t_jeu jeu,int permut){
  t_carte temp;

  
  for(int i=0;i<permut;i++){
    long int a=(rand()/(RAND_MAX/51));
    long int b=(rand()/(RAND_MAX/51));
    temp = jeu[a];
    jeu[a] = jeu[b];
    jeu[b] = temp;
  }
}


