#include "fiche.h"
#include <stdlib.h>
#include <string.h>
#define NBOCTET 50
/* remplit une fiche depuis un fichier */
void remplirFiche( FILE* fichier, t_fiche* pFiche){
  char nom[50];
  char prenom[50];
  int age;
  /* lecture des valeurs */
  fscanf( fichier, "%s %s %d", prenom, nom, &age);
  /* allocation et recopie */
  pFiche->nom = (char*) malloc( strlen(nom)+1 );
  if (pFiche->nom)
    strcpy( pFiche->nom, nom);
  pFiche->prenom = (char*) malloc( strlen(prenom)+1 );
  if (pFiche->prenom)
    strcpy( pFiche->prenom, prenom);
  pFiche->age = age;
}

void remplirFiche2(FILE* fichier, t_fiche *fiche){
  printf("remplir Fiche\n");
  // Allocation dynamique d'un espace de taille nom
  // Initialisation du pointeur fiche->nom sur cette zone
  fiche->nom = (char*)malloc(NBOCTET);
  if(fiche->nom == NULL)printf("Erreur d'allocation mémoire\n");

  // Meme chose pour le prenom
  fiche->prenom = (char*)malloc(NBOCTET);
  if(fiche->prenom == NULL)printf("Erreur d'allocation mémoire\n");

  // Lecture du fichier
  // Les 3 derniers arguments de scanf sont des adresses
  // (c.a.d des pointeurs). Voir TD6 exercice 2
  fscanf(fichier,"%s %s %d", fiche->nom, fiche->prenom, &(fiche->age));
  printf( "remplir Fiche: %s %s a %d ans\n", fiche->nom, fiche->prenom, fiche->age);
  
}


/* création d’un tableau de fiches
il faudra désallouer ce tableau après */
t_fiche* creerTableauFiches( char* nomFichier, int* pNbFiches){
  int i;
  t_fiche* fiches = NULL;
  t_fiche* pFicheCour;
  FILE* fichier = fopen( nomFichier, "r");
  if (fichier){
    /* lecture du nbre de fiches */
    fscanf( fichier, "%d", pNbFiches);
    /* allocation du tableau de t_fiches */
    fiches = (t_fiche*) malloc ( *pNbFiches * sizeof(t_fiche) );
    pFicheCour = fiches;
    /* lecture une à une des fiches */
    if (fiches){
      for( i=0; i<*pNbFiches; i++){
        remplirFiche2( fichier, pFicheCour++);
      }
}
    /* fermeture du fichier */
    fclose( fichier);
}
  return fiches;
}

/* désalloue les chaines de caractères d’une fiche */
void detruireFiche( t_fiche* pFiche){
  if (pFiche->nom)
    free( pFiche->nom);
  if (pFiche->prenom)
    free( pFiche->prenom);
  pFiche->nom = NULL;
  pFiche->prenom = NULL;
}

/* détruit le tableau de fiches */
void detruireTableauFiches( t_fiche* fiches, int nbFiches){
  int i;
  t_fiche* pFicheCour = fiches;
  if (fiches)
    {
      /* désalloue le contenu de chaque partie */
      for( i=0; i<nbFiches; i++)
        {
          detruireFiche( pFicheCour++ );
        }
      /* désalloue le tableau de fiches */
      free( fiches );
    }
}

/* affiche une fiche */
void afficherFiche( t_fiche fiche){
  printf( "%s %s a %d ans\n", fiche.nom, fiche.prenom, fiche.age);
}



int main(){
  t_fiche* fiches;
  int i, nbFiches;
  /* création du tableau de fiches */
  fiches = creerTableauFiches( "fichier.txt", &nbFiches);
  /* affiche les fiches */
  for( i=0; i<nbFiches; i++)
    afficherFiche( fiches[i]);
  /* destruction des fiches */
  detruireTableauFiches( fiches, nbFiches);
  return EXIT_SUCCESS;
}
