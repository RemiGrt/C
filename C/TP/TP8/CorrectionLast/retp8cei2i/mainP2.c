/*=====================================
 *
 *        oO  ARBRE   Oo
 *
 *=====================================
 *
 * File : mainP2.c
 * Date : 26 nov 10
 * Author : Hilaire Thibault
 *
 *=====================================
 *
 * Partie 2 : affichage d'arbres
 */


#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

#include "lectureInfixee.h"
#include "equation.h"

int main()
{
  char buffer[200];
  char* s = buffer;
  t_noeud* arbre;
	
  /* saisie */
  printf("Veuillez saisir une expression\n");
  while ( (*s++ = getchar()) != '\n' );
  *s=0;
		
  /* création */	
  arbre = creerArbreDepuisInfixee(buffer);
	
  /* affichage */
  printf("Notation infixée:\n");
  afficherInfixee( arbre);
  printf("\nNotation post-fixée\n");
  afficherPostfixee( arbre);	
  printf("\n");
	
  /* destruction*/
  detruireArbre(arbre);

  return EXIT_SUCCESS;
}
