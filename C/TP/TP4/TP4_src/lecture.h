/*=========================================
*
*    oO  Lecture pour TP Labyrinthe    Oo
*
*==========================================
*
* File : lecture.h
* Date : 5 octobre 10
* Author : Louise Huot, Hilaire Thibault
* 
* Contient la fonction de lecture du labyrinthe
* dans un fichier
*
*===========================================
*/

#ifndef __LECTURE_H__
#define __LECTURE_H__


#include "affichage.h"


/* Fonction lectureLaby
But: lit le fichier fileName et créé le labyrinthe
Paramètre:
 - fileName: nom du fichier à lire
 - laby : tableau représentant le labyrinthe
Retour: renvoit 1 si tout c'est bien passé, et 0 sinon 
*/
int lectureLaby( char fileName[20], int laby[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2] );

#endif
