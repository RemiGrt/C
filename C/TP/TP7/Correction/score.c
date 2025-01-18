/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : score.c
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Algorithme de degré de ressemblance
*/

#include <string.h>
#include <stdlib.h>

/* Fonction qui retourne le maxi de 3 nombres
Paramètres :
- a,b,c : trois entiers dont on veut le maximum
Retour :
- le maximum des trois */
int maxi( int a, int b, int c)
{
	if (a>b)
		return (a>c)?a:c;
	else
		return (b>c)?b:c;
}


/* Fonction qui calcule la similarité entre deux chaînes en 
utilisant l'algorithme de Needleman et Wunsch
Paramètres :
- ch1 et ch2 : deux chaines de caractères
Retour :
- indice de similarité (entier) */
int NeedlemanWunsh( char* ch1, char* ch2)
{
	int i,j, cout, max;
	int l1 = strlen(ch1) + 1;
	int l2 = strlen(ch2) + 1;
	int* d = (int*) malloc( sizeof(int) * l1*l2 );
	
	/* initialisation */
	for( i=0; i<l1; i++)
		d[ i*l2 ] = 0;
	for( j=0; j<l2; j++)
		d[ j ] = 0;
		
	/* double boucle */
	for( i=1; i<l1; i++)
		for( j=1; j<l2; j++)
		{
			cout =  ( ch1[i-1]==ch2[j-1] ) ? 1 : -1;
			d[ i*l2+j ] = maxi( d[ (i-1)*l2+j ] - 1, d[ i*l2+j-1 ] - 1, d[ (i-1)*l2+j-1] + cout);
		}
		
	/* recherche de la meilleure valeur */
	max = d[0];
	for( i=1; i<l1*l2; i++)
		if (max<d[i])
			max = d[i];

	/* désallocation */
	free(d);
	
	return max;
}


/* Fonction qui calcule le pourçentage d'inclusion d'une chaine dans une autre
Paramètres :
- ch1 et ch2 : deux chaines de caractères
Retour :
- le pourçentage d'inclusion (réel entre 0 et 1)*/
float pourcentageInclusion( char* ch1, char* ch2)
{
	int l1 = strlen(ch1);
	int l2 = strlen(ch2);
	int mini = (l1<l2) ? l1 : l2;
	return ( (float) NeedlemanWunsh( ch1, ch2) ) /  mini;
}