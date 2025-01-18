#include <stdio.h>
#include <string.h>
#include "partie.h"


void initPartie(t_partie *partie, char joueur0[], char joueur1[]){
 rempli(partie->pioche.jeu);
 melange(partie->pioche.jeu, 100);
 partie->pioche.posPioche=0;
 partie->j0.nbCartes=0;
 partie->j1.nbCartes=0;
 // Init tableau des noms
 char empty[NAMESIZE] = "                   ";
 strcpy(partie->j0.name,empty);
 strcpy(partie->j1.name,empty);
 strcpy(partie->j0.name,joueur0);
 strcpy(partie->j1.name,joueur1);
}

void distrib(t_partie *partie, int joueur){
  switch(joueur){
  case 0:
    partie->j0.jeu[partie->j0.nbCartes] = partie->pioche.jeu[partie->pioche.posPioche];
    partie->j0.nbCartes++;
    break;
  case 1:
    partie->j1.jeu[partie->j1.nbCartes] = partie->pioche.jeu[partie->pioche.posPioche];
    partie->j1.nbCartes++;
    break;
  }
  partie->pioche.posPioche++;
}

void afficheMain(t_main joueur){
  for(int i=0; i< joueur.nbCartes;i++){
    affiche(joueur.jeu[i]);
  }
}

void afficheJoueur(t_main joueur){
  printf("\n");
  for(int i=0;i<NAMESIZE;i++){
    printf("%c", joueur.name[i]);
  }
  printf("\n");
}

int calculMain(t_main main){
  int sumJ0=0, asPresent=0;
  for(int i=0; i<main.nbCartes;i++){
    sumJ0+=main.jeu[i].valeur;
    if(main.jeu[i].valeur==1) asPresent=1;
  }
  if(sumJ0<11 && asPresent==1){
    sumJ0+=10;
  }
  return sumJ0;
}
