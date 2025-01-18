#ifndef __individu__
#define __individu__

#include <stdio.h>
#define SIZE_N 50
#define SIZE_SEQ 10000
#define DEBUG 1
#define COL "\033[34;01m"
#define NCOL "\033[00m"
                 

typedef struct{
  char* nom; // Contient nom et prenom
  char* sequence;
  // Partie 3
  float simil; // pourcentage de similarité avec une chaine donnee
}t_individu;

void remplifiche(t_individu *individu, FILE* fichier);
void affiche(t_individu* individu);
void detruit(t_individu* individu);


void calculSimilarite(t_individu* individu, char* seq);




#endif
