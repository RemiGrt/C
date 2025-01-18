/*=========================================
*
*    oO  Lecture pour TP Labyrinthe    Oo
*
*==========================================
*
* File : lecture.c
* Date : 5 octobre 10
* Author : Louise Huot, Hilaire Thibault
* 
* Contient la fonction de lecture du labyrinthe
* dans un fichier
*
*===========================================
*/


#include "affichage.h"
#include <stdio.h>

/* Fonction lectureLaby
But: lit le fichier fileName et créé le labyrinthe
Paramètre:
 - fileName: nom du fichier à lire
 - laby : tableau représentant le labyrinthe
Retour: renvoit 1 si tout c'est bien passé, et 0 sinon 
*/

int lectureLaby( char fileName[20], int laby[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2] )
{
	FILE* fichier; 
	int x,y;
	
	/* ouverture du fichier */
	fichier = fopen( fileName, "r");
	if (!fichier)
		return 0;
	
	/* lecture coordonnées départ et arrivée */
	fscanf( fichier, "%d %d", &depart[0], &depart[1]);
	fscanf( fichier, "%d %d", &arrivee[0], &arrivee[1]);
	
	/* lecture du tableau
	!!! Attention à l'ordre des boucles !!! */
	for( y=0; y<TAILLE_Y; y++)
		for( x=0; x<TAILLE_X; x++)
			fscanf( fichier, "%d", &(laby[x][y]) );
	
	/* fermeture */
	return !fclose(fichier);
}
