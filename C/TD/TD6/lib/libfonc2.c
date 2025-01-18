#include <stdio.h>
#include "ex2.h"

void affichePersonne(t_personne pers){
  printf("Nom:\t%s\n", pers.nom);
  printf("Prenom:\t%s\n", pers.prenom);
  printf("Nee le:\t%d/%d/%d\n",pers.datedenaissance.jour,\
         pers.datedenaissance.mois,pers.datedenaissance.annee);
  printf("Age:\t%d\n",pers.age);
  printf("Adresse:\t%s\n%s\n%s\n",pers.adresse[0],pers.adresse[1],
         pers.adresse[2]);
}

void litPersonne(FILE *fichier, t_personne *pers){
  fscanf(fichier,"%s",pers->nom);
  fscanf(fichier,"%s",pers->prenom);
  fscanf(fichier,"%d",&(pers->datedenaissance.jour));
  fscanf(fichier,"%d",&(pers->datedenaissance.mois));
  fscanf(fichier,"%d",&(pers->datedenaissance.annee));
  fscanf(fichier,"%d",&(pers->age));
  fscanf(fichier,"%s",pers->adresse[0]);
  fscanf(fichier,"%s",pers->adresse[1]);
  fscanf(fichier,"%s",pers->adresse[2]);

}
