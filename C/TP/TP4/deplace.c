#include <stdio.h>
#include "affichage.h"

// donne les coordonne de la case voisine de la case depart
// en fonction de direction
// 0, 1, 2 ,3 = nord, est, sud, ouest
int deplace(int departX, int departY, \
             int *voisineX, int *voisineY, int direction){
  // gestion erreur
  if(direction > 3 || direction < 0){
    printf("Parametre direction invalide\n");
    return 0;
  }
  if(departX == 0 &&  direction == 3){
    printf("Parametres direction  et depart invalide\n");
    return 0;
  }
  if(departX == TAILLE_X &&  direction == 1){
    printf("Parametres direction  et depart invalide\n");
    return 0;
  }
  if(departY == 0 &&  direction == 0){
    printf("Parametres direction  et depart invalide\n");
    return 0;
  }
  if(departX == TAILLE_Y &&  direction == 2){
    printf("Parametres direction  et depart invalide\n");
    return 0;
  }

  
  switch (direction){
    case 0 :
        *voisineX=departX;
        *voisineY=departY-1;
        break;
    case 1 :
        *voisineX=departX+1;
        *voisineY=departY;
        break;
    case 2 :
        *voisineX=departX;
        *voisineY=departY+1;
        break;
    case 3 :
        *voisineX=departX-1;
        *voisineY=departY;
        break;
    }

  return 1;
}
