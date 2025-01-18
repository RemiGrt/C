
#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>


// Question 1
typedef struct s_noeud t_noeud;
struct s_noeud{
  char* ch;
  float val;
  t_noeud* droit;
  t_noeud* gauche;
};

// Question 2
t_noeud* creerNoeud(float val, char* ch, t_noeud* droit, t_noeud* gauche);

//Question 3
t_noeud* creerNoeudOp(char* ch, t_noeud* droit, t_noeud* gauche);
t_noeud* creerFeuilleReel( float val);
t_noeud* creerFeuilleVar( char* ch);



#endif
