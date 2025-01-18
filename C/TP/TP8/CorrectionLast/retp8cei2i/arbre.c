/*=====================================
 *
 *        oO  ARBRE   Oo
 *
 *=====================================
 *
 * File : arbre.c
 * Date : 26 nov 10
 * Author : Hilaire Thibault
 *
 *=====================================
 *
 * Manipulation d'un arbre
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

int cmpt=0;


/* création d'un noeud général */
t_noeud* creerNoeud( float val, char* ch, t_noeud* filsG, t_noeud* filsD)
{
  /* allocation mémoire pour le noeud */
  t_noeud* N = (t_noeud*) malloc( sizeof(t_noeud) );
  if (!N)
    {
      fprintf( stderr, "Problème mémoire\n");
      exit(EXIT_FAILURE);
    }
  /* recopie de la valeur */
  N->val = val;
  /* recopie de la chaine */
  if (ch)
    {
      N->ch = (char*) malloc( strlen(ch)+1 );
      if (!N->ch)
        {
          fprintf( stderr, "Problème mémoire\n");
          exit(EXIT_FAILURE);
        }
      strcpy( N->ch, ch);
    }
  else
    {
      N->ch = NULL;
    }
  /* liens vers les fils */
  N->filsG = filsG;
  N->filsD = filsD;
	
  return N;
}

/* création d'un noeud avec un opérateur ou une fonction */
t_noeud* creerNoeudOp( t_noeud* filsG, char* ch, t_noeud* filsD)
{
  return creerNoeud( 0, ch, filsG, filsD);
}


/* création d'une feuille réelle */
t_noeud* creerFeuilleReel( float val)
{
  return creerNoeud( val, NULL, NULL, NULL);	
}


/* création d'une feuille avec une variable */
t_noeud* creerFeuilleVar( char* ch)
{
  return creerNoeud( 0, ch, NULL, NULL);
}


/* détruire un arbre */
void detruireArbre( t_noeud* arbre)
{
  if (arbre)
    {
      /* détruire la chaine de car */
      if (arbre->ch)
        {
          free(arbre->ch);
        }
      /* détruit le fils gauche */
      if (arbre->filsG)
        {
          detruireArbre(arbre->filsG);
        }
      /* détruit le fils droit */
      if (arbre->filsD)
        {
          detruireArbre(arbre->filsD);
        }
      /* détruit le noeud */
      free(arbre);
    }
}

/* indique le nb de fils d'une noeud
   0 si c'est une feuille */
int nbFils( t_noeud* noeud)
{
  /*	int i = 0;
	if (arbre->filsG)
        i++;
	if (arbre->filSD)
        i++;
	return i;
  */
  return (noeud->filsG!=NULL) + (noeud->filsD!=NULL);
}

/* duplique un arbre */
t_noeud* dupliquer( t_noeud* arbre)
{
  t_noeud *dG=NULL, *dD=NULL;
  /* duplication à gauche */
  if (arbre->filsG)
    dG = dupliquer(arbre->filsG);
  /* duplication à droite */
  if (arbre->filsD)
    dD = dupliquer(arbre->filsD);
  /* duplication noeud */
  return creerNoeud( arbre->val, arbre->ch, dG, dD);
}

