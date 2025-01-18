#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"





// Question 2
t_noeud* creerNoeud(float val, char* ch, t_noeud* droit, t_noeud* gauche){
  // Creation Noeud
  t_noeud* noeud=(t_noeud*)malloc(sizeof(noeud));
  if(noeud==NULL){
    printf("Error Malloc\n");
    exit(EXIT_FAILURE);
  }

  // Reservation de l'espace mémoire pour le tableau
  noeud->ch=(char*)malloc(strlen(ch)+1);
  if(noeud->ch==NULL){
    printf("Error Malloc\n");
    exit(EXIT_FAILURE);
  }
  strcpy(noeud->ch,ch);

  noeud->val=val;
 
  noeud->droit=droit;
  noeud->gauche=gauche;

  return noeud;

}

// Question 3
t_noeud* creerNoeudOp(char* ch, t_noeud* droit, t_noeud* gauche){
  return creerNoeud(0, ch, droit, gauche);
}

t_noeud* creerFeuilleReel( float val){
  return creerNoeud(val, NULL, NULL, NULL);
}

t_noeud* creerFeuilleVar( char* ch){
  return creerNoeud(0, ch, NULL, NULL);

}




