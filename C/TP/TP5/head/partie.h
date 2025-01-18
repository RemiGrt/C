#ifndef __partie__
#define __partie__
#include "carte.h"
#define NAMESIZE 20

typedef struct{
  t_jeu jeu;
  int nbCartes;
  char name[NAMESIZE];
}t_main;

typedef struct{
  t_jeu jeu;
  int posPioche;
}t_pioche;

typedef struct{
  t_main j0;
  t_main j1;
  t_pioche pioche;
}t_partie;

void initPartie(t_partie *partie, char joueur0[], char joueur1[]);
void distrib(t_partie *partie, int joueur);
void afficheMain(t_main joueur);
void afficheJoueur(t_main joueur);
int calculMain(t_main main);
#endif
