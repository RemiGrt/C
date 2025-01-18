/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : individu.h
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Fonctions de manipulation d'individus
*/

#include "individu.h"
#include "score.h"
#include <string.h>
#include <stdlib.h>



/* Fonction de lecture d'un individu dans le fichier
(les chaînes lues sont recopiées)
Paramètres :
- pInd : pointeur sur un t_indiv
- fichier : pointeur sur un FILE
*/
void lireIndividu( FILE* fichier, t_indiv* pInd)
{
	char ADN[10000];
	char nom[50], prenom[50];
	
	/* lecture du nom et de l'ADN */
	fscanf( fichier, "%s", nom);
	fscanf( fichier, "%s", prenom);
	fscanf( fichier, "%s", ADN);
	
	/* allocation et recopie du nom  */
	pInd->nom = (char*) malloc( strlen(nom) + strlen(prenom) + 2 );
	if ( pInd->nom==NULL )
	{
		fprintf (stderr, "(creerIndividu) : Erreur d'allocation\n");
		return;
	}
	strcpy( pInd->nom, nom);
	strcat( pInd->nom, " ");
	strcat( pInd->nom, prenom);
	
	/* allocation et recopie de l'adn  */
	pInd->adn = (char*) malloc( strlen(ADN)+1 );
	if ( pInd->adn==NULL )
	{
		fprintf (stderr, "(creerIndividu) : Erreur d'allocation\n");
		free( pInd->nom );
		return;
	}
	strcpy( pInd->adn, ADN);
}



/* Fonction qui affiche un individu 
Paramètres :
- Ind : le t_indiv à afficher
Retour : aucun*/
void afficherIndividu( t_indiv Ind)
{
	/* affichage du nom, du prénom et de la séquence ADN */
	printf( "Nom : %s\n", Ind.nom);
	printf( "ADN: %s\n", Ind.adn);
	printf( "Similarité : %f\n", Ind.similarite);
}




/* Fonction qui désalloue toute la mémoire allouée à la création d'un individu
Paramètres :
- pInd : le t_indiv dont il faut désallouer les chaines
Retour : aucun*/
void desallouerIndividu( t_indiv Ind)
{
  printf("DEBUG AV Ind.nom %p\n",Ind.nom);
  printf("DEBUG AV Taille Ind.nom %lu\n",strlen(Ind.nom));
  
  if (Ind.nom)
    free( Ind.nom);
  printf("DEBUG AP Ind.nom %p\n",Ind.nom);
  printf("DEBUG AP Taille Ind.nom %lu\n",strlen(Ind.nom));
  
  if (Ind.adn)
    free( Ind.adn);
}



/* Fonctin qui calcule le pourcentage de ressemblance entre l'adn d'un individu et une chaine donnée
Paramètres :
- pInd : pointeur vers l'individu en question
- adn : chaine qu'il faut comparer avec l'adn de l'individu
Retour : aucun*/
void calculerSimilarite( t_indiv* pInd, char* adn)
{
	pInd->similarite = pourcentageInclusion( pInd->adn, adn);
}


/* indique si un individu est intéressant (c-à-d a une similarité + grande qu'un individu dans le tableau)
Paramètres :
- tabIndiv : tableau d'individus
- nbIndiv : taille du tableau d'individus
- Ind : individu dont on veut regarder s'il a sa place
Retour :
- Booléen VRAI si l'individu est intéressant  */
int individuEstInteressant( t_indiv* tabIndiv, int nbIndiv, t_indiv Ind)
{
	int i=0;
	/* tant qu'on n'a pas regardé tous les individus du tableau et que l'individu est moins similaire que l'individu courant, on passe à l'individu suivant dans le tableau */
	while ( (i<nbIndiv) && (Ind.similarite <= tabIndiv->similarite) )
	{
		i++;
		tabIndiv++;
	}
	return (i<nbIndiv);	/* on est sorti parce qu'arrivé à la fin du tableau ou parce que l'individu est intéressant ? */
}

/* insere un individu dans le tableau d'individus interessants
Paramètres :
- tabIndiv : tableau d'individus
- nbIndiv : taille du tableau d'individus
- Ind : individu dont on veut regarder s'il a sa place */
void insererIndividu( t_indiv* tabIndiv, int nbIndiv, t_indiv Ind)
{
	int i = 0;
	t_indiv IndTemp;

	/* trouve où le mettre */
	while (Ind.similarite <= tabIndiv->similarite)
	{
		i++;
		tabIndiv++;
	}

	/* déplace tous les autres individus */
	while (i<nbIndiv)
	{
		/* insère cet individu */
		IndTemp = *tabIndiv;
		*tabIndiv = Ind;
		/* passe au suivant */
		Ind = IndTemp;
		tabIndiv++;
		i++;
	}
	/* désallouer le dernier */
	desallouerIndividu(Ind);
}

	
