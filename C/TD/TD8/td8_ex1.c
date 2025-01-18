#include <stdio.h>

typedef struct{
  char* nom;
  char* prenom;
  int age;


}t_fiche;

void remplirFiche(FILE* fichier, t_fiche *fiche){

  char nom[50];
  char prenom[50];
  int age;
  fscanf(fichier,"%s %s %s", fiche->nom, fiche->prenom, fiche->age);

  fiche->nom = (char*) malloc(sizeof

}
