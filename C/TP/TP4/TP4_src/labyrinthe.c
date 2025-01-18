/*=========================================
*
*        oO  TP Labyrinthe    Oo
*
*==========================================
*
* File : labyrinthe.c
* Date : 5 octobre 10
* Author : Louise Huot, Hilaire Thibault
* 
* Contient le programme principal de résolution
* d'un algorithme
*
*===========================================
*/


#include "affichage.h"
#include "lecture.h"
#include <stdlib.h>
#include <stdio.h>

#define RECURSIF 1


/* Fonction qui indique les coordonnées d'un voisin de (x,y) en fonction de d
Paramètres:
- x,y : coordonnées de la case de départ
- nx,ny : pointeur vers les coordonnées de la nouvelle case
- d : direction (0: Nord, 1:Est, 2:Sud et 3:Ouest)
*/
void deplace( int x, int y, int* nx, int* ny, int d)
{
	switch (d)
	{
		case 0 : *ny=y-1; *nx=x; break;
		case 1 : *nx=x+1; *ny=y; break;
		case 2 : *ny=y+1; *nx=x; break;
		case 3 : *nx=x-1; *ny=y; break;
	}
/* De plus, il faudrait vérifier que les nouvelles coordonnées sont valides, c'est-à-dire
qu'elles sont >=0 et <TAILLE */
}


/* Fonction qui réalise l'expansion (de manière un peu bourrine, voir expansion2 pour une version plus fine
Paramètres:
- laby : tableau représentant le labyrinthe
- depart : coordonnées du point de départ
- arrivee : coordonnées du point d'arrivée
 */
int expansion1( int laby[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2])
{
	int r = 1;
	int x, y, d;
	int nx, ny;
	int avance = 1;
	int fini = 0;
	
	/* on marque la case de départ */
	laby[ depart[0] ][ depart[1] ] = r;
	
	while (avance && !fini)
	{
		avance=0;
		/* on itère sur toutes les cases */
		for( x=0; x<TAILLE_X; x++)
			for( y=0; y<TAILLE_Y; y++)
				if (laby[x][y]==r)
				{			
					/* et sur tous ses voisins */
					for( d=0; d<4; d++)
					{
						deplace(x,y,&nx,&ny,d);
						if (laby[nx][ny]==0)
						{
							laby[nx][ny] = r+1;
							avance=1;
						}
						if (nx==arrivee[0] && ny==arrivee[1])
							fini=1;
					}
				}
		afficheLabyrinthe( laby, depart, arrivee, 10);
		r++;
	}
				
	return !fini;
}

/* Fonction qui réalise l'expansion de manière RÉCURSIVE
(voir expansion1 pour une version plus bourrine)
Paramètres:
- laby : tableau représentant le labyrinthe
- depart : coordonnées du point de départ
- arrivee : coordonnées du point d'arrivée
 */
int expansion2( int laby[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2], int r)
{
	int x, y, d;
	int nx, ny;
	int ndepart[2];
	int fini;
	x = depart[0];
	y = depart[1];
	
	if (x!=arrivee[0] || y!=arrivee[1])
	{

		/* on marque la case de départ */
		laby[x][y] = r;
		r++;
		
		/* et on itère sur tous ses voisins */
		fini = 0;
		d = 0;
		do
		{
			deplace(x,y,&nx,&ny,d);
			if ( laby[nx][ny]==0 || laby[nx][ny]>r )
			{
				ndepart[0]=nx;
				ndepart[1]=ny;
				fini = expansion2( laby, ndepart, arrivee, r);
			}
			d++;
		} while ( d<4 && !fini);
		afficheLabyrinthe( laby, depart, arrivee, 10);

	}
	else
	{
		fini = 1;
		if (laby[x][y]>=r || laby[x][y]==0)
			laby[x][y] = r;
	}

	return fini;

}




/* Fonction qui effectue le nettoyage après la remontée
Paramètres:
- laby : tableau représentant le labyrinthe
*/
void nettoyage( int laby[TAILLE_X][TAILLE_Y])
{
	int x,y;
	for ( x=0; x<TAILLE_X; x++)
		for ( y=0; y<TAILLE_Y; y++)
			if ( laby[x][y] > 0)
				laby[x][y] = 0;

}

/* Fonction qui effectue la remontée du chemin (en mettant les cases du chemin à -2
Paramètres:
- laby : tableau représentant le labyrinthe
- depart : coordonnées du point de départ
- arrivee : coordonnées du point d'arrivée
*/
int remontee( int laby[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2])
{
	int x,y;
	int vx,vy;
	int r,d;
	
	/* on démarre de la case d'arrivée */
	x = arrivee[0];
	y = arrivee[1];
	r = laby[x][y];
	
	/* on itère tant qu'on est pas à la fin */
	while ( x!=depart[0] || y!=depart[1] )
	{
		/* on marque la case courante */
		laby[x][y] = -2;
		/* on parcourt les voisins jusqu'à trouver celui qui est à distance r-1 */
		d=0;
		do
		{
			deplace( x, y, &vx, &vy, d);
			d++;
		} while ( d<4 && laby[vx][vy]!=(r-1) );
		/* on vérifie qu'il n'y a pas de pb */
		if ( laby[vx][vy]!=(r-1) )
			return 0;
		/* on passe à la nouvelle case */
		r--;
		x = vx;
		y = vy;
		afficheLabyrinthe( laby, depart, arrivee, 10);
	}
//	laby[x][y] = -2;
//	afficheLabyrinthe( laby, depart, arrivee, 10);
	return 1; 
}




int main()
{
	/* tableau représentant le labyrinthe */
	int laby[TAILLE_X][TAILLE_Y];
	int depart[2], arrivee[2];

	/* lecture du labyrinthe */
	if ( !lectureLaby( "laby1.txt", laby, depart, arrivee) )
		return EXIT_FAILURE;
	
	/* initialisation de l'affichage */
	if ( !initAffichage() )
		return EXIT_FAILURE;

	/* on affiche le labyrinthe initial */
	afficheLabyrinthe( laby, depart, arrivee, 1000 );
	
	/* on résoud le labyrinthe */
	//expansion1( laby, depart, arrivee);
        #if RECURSIF
	expansion2( laby, depart, arrivee, 1);
        #else
        expansion1( laby, depart, arrivee);
        #endif
	afficheLabyrinthe( laby, depart, arrivee, 1000 );

	/* on remonte le chemin */
	if ( !remontee( laby, depart, arrivee) )
		fprintf( stderr, "problème à la remontée!\n");
	nettoyage( laby);


	/* on affiche le labyrinthe final */
	afficheLabyrinthe( laby, depart, arrivee, 0 );

	return EXIT_SUCCESS;
}
