#include "individu.h"
#include <stdlib.h>
#include <string.h>


void remplifiche(t_individu *individu, FILE* fichier){
  if(DEBUG)printf("\t DEBUG remplifiche \n");
  
  char seq[SIZE_SEQ];
  char nom[SIZE_N];
  char prenom[SIZE_N];
  
  fscanf(fichier, "%s %s %s", nom, prenom, seq);
  
  individu->nom=     (char*)malloc(strlen(nom) + strlen(prenom) + 2 );
  if(individu->nom==NULL){
    fprintf (stderr, "Remplifiche : Erreur d'allocation\n");
    return;
  }
  strcpy( individu->nom, nom);
  strcat( individu->nom, " ");
  strcat( individu->nom, prenom);
  
  individu->sequence=(char*)malloc(strlen(seq)+1);
  if(individu->sequence==NULL){
    fprintf (stderr, "Remplifiche : Erreur d'Allocation 2\n");
    free(individu->nom);
    return;
  }

  strcpy(individu->sequence, seq);
  
}

void affiche(t_individu* individu){
  if(DEBUG)printf("\033[34;01m affiche \033[00m\n");
  if(individu!=NULL){
  printf("Nom: %s \nSequence: ",individu->nom);
  for(int i=0;i<30;i++){
    printf("%c", *(individu->sequence+i));
  }
  printf("\n");
  }else{
    printf("Affichage Impossible\n");
  }
}

void detruit(t_individu* individu){
  if(DEBUG)printf("\t DEBUG detruit \n");
  if(individu==NULL){
    printf("Fonction detruit, Pointeur Null\n"); 
  }else{
    if(DEBUG)printf("\t DEBUG individu->nom %p\n",individu->nom); 
    if(DEBUG)printf("\t DEBUG individu->sequence %p\n",individu->sequence);
    free(individu->nom);
    free(individu->sequence);
    //free(individu); !! Si individu a été crée dynamiquement
  }
}

