#include <math.h>
#include <stdio.h>
#include "struct.h"

// Procedure d'affichage d'un nombre complexe 
void affiche(t_complexe a){
	printf("%f + j%f\n", a.reel, a.imaginaire);
}

// Fonction de calcul du module
float module(t_complexe a){
	return sqrt(pow(a.reel,2)+pow(a.imaginaire,2));
}

// Procedure de calcul de la somme
void somme(t_complexe *sum, t_complexe a, t_complexe b){
  sum->reel = a.reel + b.reel;
  sum->imaginaire = a.imaginaire + b.imaginaire;
}

// Procedure de calcul du produit
void produit(t_complexe *produit,t_complexe a, t_complexe b){
  produit->reel = a.reel* b.reel - (a.imaginaire*b.imaginaire);
  produit->imaginaire = a.imaginaire*b.reel + b.imaginaire*a.reel;
}
