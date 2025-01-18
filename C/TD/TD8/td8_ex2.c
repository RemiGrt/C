#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBOCTET 50

/* Question 1                    */
/* Definition strucuture t_fiche */
typedef struct{
  char* nom;
  char* prenom;
  int age;
}t_fiche;

/* Question 2                  */
/* Definition de la fonction remplirFiche */
/* Argument: pointeur sur descripteur de fichier, pointeur sur t_fiche */
/* Retour: void */
void remplirFiche(FILE* fichier, t_fiche *fiche){
  
  // Allocation dynamique d'un espace de taille nom
  // Initialisation du pointeur fiche->nom sur cette zone
  fiche->nom = (char*)malloc(NBOCTET);
  if(fiche->nom == NULL)printf("Erreur d'allocation mémoire\n");

  // Meme chose pour le prenom
  fiche->prenom = (char*)malloc(NBOCTET);
  if(fiche->prenom == NULL)printf("Erreur d'allocation mémoire\n");

  // Lecture du fichier
  // fiche etant de type pointeur, on utilise "->" pour accéder à ses champs
  // Rappel: Les 3 derniers arguments de scanf sont des adresses
  // char* nom, char *prenom sont des adresses
  // on utilise le & pour age
  fscanf(fichier,"%s %s %d", fiche->nom, fiche->prenom, &(fiche->age));
}

/* Question 3 */
/* Definition de la fonction creerTableauFiche */
/* Creation d'un tableau de t_fiche à partir du contenu d'un fichier  */
/* Argument: pointeur sur descripteur de fichier, pointeur sur nbFiche */
/* Retour: pointeur sur t_fiche */
t_fiche* creerTableauFiches(FILE* fichier, int* nbFiche){
  
  fscanf(fichier,"%d", nbFiche);
  printf("Il y a %d fiches dans le fichier\n",*nbFiche);
  
  t_fiche *ptabFiche;
  ptabFiche=(t_fiche*)malloc((*nbFiche)*sizeof(t_fiche));
  if(ptabFiche == NULL)printf("Erreur d'allocation mémoire\n");

  for(int i=0; i<(*nbFiche); i++){
    remplirFiche(fichier, &ptabFiche[i]);
  }
  return ptabFiche;
}

/* Question 4 */
/* Définition de la fonction freeFiche */
/* Libere l'espace mémoire alloué à la création d'une t_fiche */
/* Argument: pointeur sur t_fiche */
void freeFiche(t_fiche *pFiche){
  free(pFiche->nom);
  free(pFiche->prenom);
}

/* Question 4 suite*/
/* Définition de la fonction freeTabFiche */
/* Libere l'espace mémoire allouée à la création d'un tableau de t_fiche */
/* Argument: pointeur sur t_fiche */
void freeTabFiche(t_fiche *pTabFiche, int nbFiche){
  for(int i=0;i<nbFiche;i++){
    freeFiche(&pTabFiche[i]);
  }
  free(pTabFiche);
}

/* affiche une t_fiche */
void afficheFiche(t_fiche* fiche){
  printf( "%s %s a %d ans\n", fiche->nom, fiche->prenom, fiche->age);
}                  

int main(){
  FILE* fichier;
  int nbFiche;
  fichier = fopen("fichier.txt","r");
  if(fichier==NULL){
    printf("Ouverture fichier NOK\n");
    return 0;
  }
  printf("Ouverture fichier OK\n");
  t_fiche* tableauFiche=NULL;
  tableauFiche=creerTableauFiches(fichier, &nbFiche);

  // Fermeture fichier
  fclose(fichier);
  
  
  for(int i=0;i<nbFiche;i++){
    afficheFiche(&tableauFiche[i]);
  }

  freeTabFiche(tableauFiche, nbFiche);
  
}
