#include <stdio.h>
#include "td9.h"

int main(){

 t_liste* liste= initlist();  
 printf("%p\n",liste);
 printf("%lu\n",sizeof(liste));

 for(int i=0;i<4;i++){
   insereDebutListe(liste, i, 4);
 }

 int i=0;
 
 insereFinliste(liste,4,4);

 affiche(liste);

 supprimePremier(liste);
 affiche(liste);
 printf("Avant %p\n",liste);
 printf("Avant %p\n",liste->debut);
 printf("Avant %p\n",liste->debut->suivant);

 supprimeListe(liste);
 printf("Apres %p\n",liste);
 printf("Apres %p\n",liste->debut);
 printf("Apres %p\n",liste->debut->suivant);
 

}
