#include <stdio.h>
#include <lecture.h>
#include <affichage.h>


int main(){
  int lab[TAILLE_X][TAILLE_Y];
  int depart[2];
  int arrivee[2];
  int tempo = 0; // ms
  if(!lecture("./TP4_src/laby1.txt",lab,depart,arrivee)){
    printf("Ouverture fichier NOK\n");
    return 0;
  }
  printf("Ouverture fichier OK\n");

  if(initAffichage()==0){
    printf("Init Affichage NOK\n");
    return 0;
  }
  printf("Init Affichage OK\n");
 
  afficheLabyrinthe(lab, depart,  arrivee,  tempo);
  
  return 0;
  

}
