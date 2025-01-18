#ifndef _td9_
#define _td9_
#include <stdlib.h>

//typedef struct t_element{
//  int x;
//  int y;
//  t_element* suivant;
//}

// 1a Structure element de la liste avec une auto reference
typedef struct s_pt t_pt;
struct s_pt{
  int x;
  int y;
  t_pt* suivant; 
};

// 1b
// Structure de la liste contenant le premier et le dernier elt
// pas forcement necessaire
typedef struct{
  t_pt* debut;
  t_pt* fin;
}t_liste;

// 2
t_liste* initlist( ){
  
  t_liste* liste=malloc(sizeof(t_liste));
  //t_pt* debut=malloc(sizeof(t_pt));
  //t_pt* debut=malloc(sizeof(t_pt));
  
  //if(t_liste==NULL)return NULL;
  
  //liste->debut->suivant=liste->fin;
  //liste->fin->suivant=NULL;
  return liste;
}

void insereDebutListe( t_liste* liste, int x, int y){
  if(liste==NULL)printf("liste non valide\n");
  t_pt* newPt=malloc(sizeof(t_pt));
  if(newPt==NULL)printf("Malloc Failed");
  newPt->x=x;
  newPt->y=y;
  if(liste->debut==NULL){  
    newPt->suivant=NULL;
    if(liste->fin==NULL){
      liste->fin=newPt;
    }
  }else{
    newPt->suivant=liste->debut;
  }
  liste->debut=newPt;  
}

void insereFinliste(t_liste* liste, int x, int y){
  if(liste==NULL)printf("liste non valide\n");
  t_pt* newPt=malloc(sizeof(t_pt));
  if(newPt==NULL)printf("Malloc Failed");
  newPt->x=x;
  newPt->y=y;
  if(liste->fin==NULL){
    liste->fin==newPt;
    if(liste->debut==NULL){
      liste->debut=newPt;
    }
  }else{
    liste->fin->suivant=newPt;
  }
  newPt->suivant=NULL;
  liste->fin=newPt;
}

void affiche(t_liste* liste){
  if(liste==NULL){
    printf("liste non valide\n");
  }else{
    int i=0;
    printf("Affichage\n");
    t_pt* courant=liste->debut;
    int moyx=0;
    int moyy=0;
    
    while(courant!=NULL){
      printf("Element %d x=%d, y=%d\n",i++,courant->x,courant->y);
      moyx+=courant->x;
      moyy+=courant->y;
      courant=courant->suivant;
    }
    printf("moyenne x %d y %d",moyx/i,moyy/i);
  }
}

void supprimePremier(t_liste* liste){
    if(liste==NULL){
    printf("liste non valide\n");
  }else if(liste->debut==NULL){
    printf("liste vide\n");
  }else{
    t_pt* save=liste->debut->suivant;
    free(liste->debut);
    liste->debut=save;
  }
}

 void supprimeListe(t_liste* liste){
    if(liste==NULL){
    printf("liste non valide\n");
  }
    else if(liste->debut==NULL){
    printf("liste vide\n");
  }
    else{
    while(liste->debut!=NULL){
    supprimePremier(liste);
  }
   
    free(liste);
  }
  }
 

#endif
