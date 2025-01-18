#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carte.h"
#include "partie.h"


int main(){
  srand(time(NULL));

  
  
  t_partie partie;
  char tab0[]="Bob";
  char tab1[]="Michel";
  char reponse[10];
  initPartie(&partie,tab0, tab1);
  printf("Nom des joueurs\n");
  afficheJoueur(partie.j0);
  afficheJoueur(partie.j1);
  printf("Pioche:\n");
  afficheJeu(partie.pioche.jeu);
  printf("Distribution:\n");
  distrib(&partie, 0);
  distrib(&partie, 1);
  distrib(&partie, 0);
  distrib(&partie, 1);
  afficheJoueur(partie.j0);
  afficheMain(partie.j0);
  afficheJoueur(partie.j1);
  afficheMain(partie.j1);
  //printf("%d",calculMain(partie.j1));
  printf("\nNouvelle carte?");
  scanf("%s",reponse);
  while(reponse[0]=='o' && reponse[1]=='u' && reponse[2]=='i' &&
     calculMain(partie.j1)<21){
     distrib(&partie, 1);
     afficheJoueur(partie.j1);
     afficheMain(partie.j1);
     printf("\n");
     if(calculMain(partie.j1)<21){
       printf("\nNouvelle carte?");
       scanf("%s",reponse);
     }
  }
  printf("\n");
}
