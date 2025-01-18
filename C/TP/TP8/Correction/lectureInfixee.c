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
* Mise en oeuvre du Shunting-yard algorithm
* pour créer un AST (abstract syntax tree) à partir d'une écriture infixée
* ref: http://en.wikipedia.org/wiki/Shunting-yard_algorithm
*/

#include "lectureInfixee.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbre.h"

#define MAXPILE 50

/* Associativité des opérateurs */
typedef enum 
{
	ASSOC_AUCUNE=0,
	ASSOC_GAUCHE,
	ASSOC_DROITE
} t_associativite;


/* Identificateurs */
typedef struct
{
	char* ch;		/* chaine associée */
	int prior;		/* priorité (précédence) */
	int assoc;		/* associativité (gauche ou droite) */
	int arite;		/* nb d'opérateurs */
	int fonction;	/* indique si c'est une fonction (opérateur préfixé avec parenthèse) */
} t_id;


/* définition des identificateurs 
opérateurs, fonctions et parenthèse ouvrante
(tout ce que l'on met dans la pile des opérateurs) 
Attention: pas d'opérateur unaire "-" !!! */
t_id Identif[]={
	{ "^", 		3, ASSOC_DROITE, 2, 0 },
	{ "*", 		2, ASSOC_GAUCHE, 2, 0 },
	{ "/", 		2, ASSOC_GAUCHE, 2, 0 },
	{ "+", 		1, ASSOC_GAUCHE, 2, 0 },
	{ "-", 		1, ASSOC_GAUCHE, 2, 0 },
	{ "sin", 	0, ASSOC_AUCUNE, 1, 1 },
	{ "(", 		0, ASSOC_AUCUNE, 0, 0 },
};


/* pile d'élements d'arbre, réalisés avec un tableau et un entier */
t_noeud* pileNoeud[MAXPILE];
int posPileNoeud = 0;

/* vide la pile de noeuds, pour quand il y a eu un problème de lecture 
il faut donc désallouer tout ce qui a été alloué */
void viderPileNoeud()
{
	while (posPileNoeud>0)
	{
		detruireArbre( pileNoeud[ --posPileNoeud ] );
	}
}


/* empile un réel dans la pile de noeuds */
void empilerReel( float val)
{
	pileNoeud[ posPileNoeud++ ] = creerFeuilleReel(val);
}

/* empile une variable dans la pile de noeuds */
void empilerVar( char* ch)
{
	pileNoeud[ posPileNoeud++ ] = creerFeuilleVar(ch);
}

/* récupère le bon nombre de noeuds dans la pile de noeuds, construit un nouveau noeud/arbre, et l'empile */
void empilerNoeud( t_id* idCour)
{
	t_noeud *noeud1, *noeud2;

	if (idCour->arite>posPileNoeud)
	{
		printf("Erreur: pas assez d'arguments pour %s\n", idCour->ch);
		viderPileNoeud();
	}
	if (idCour->arite==1)
	{
		/* opérateur/fonction à un seul opérande */
		noeud1 = pileNoeud[ --posPileNoeud ];
		pileNoeud[ posPileNoeud++ ] = creerNoeudOp( noeud1, idCour->ch, NULL);
	}
	else
	{
		/* opérateur/fonction à deux opérandes */
		noeud2 = pileNoeud[ --posPileNoeud ];
		noeud1 = pileNoeud[ --posPileNoeud ];
		pileNoeud[ posPileNoeud++ ] = creerNoeudOp( noeud1, idCour->ch, noeud2);
	}
}


/* indique si l'identificateur est un opérateur */
int estOperateur( t_id* id)
{
	return id && (id->prior)>0;
}


/* indique si l'identificateur est une fonction prédéfinie */
int estFonction( t_id* id)
{
	return id && id->fonction;
}


/* renvoit l'identificateur associé à une chaine de caractère
renvoit NULL si l'id n'est pas trouvé*/
t_id* quelIdentificateur( char* str)
{
	int i;
	for( i=0; i<sizeof(Identif)/sizeof(t_id); i++)
	{
		if ( !strcmp(Identif[i].ch, str) ) 
			return Identif+i;
	}
	return NULL;
}

/* renvoit le type du caractère 
0 -> appartient à un nom
1 -> appartient à un nombre
2 -> espace
code ascii sinon */
int typeCaractere( char c)
{
	if (isspace(c))
		return 2;
	else if (isalpha(c) || c=='_' )
		return 3;
	else if (isdigit(c) || c=='.')
		return 1;
	else return (int) c;
}


/* trouve le prochain token de la chaine
-> le token est recopié dans token
-> le pointeur sur la chaine est avancé pour le prochain appel */
void prochainToken( char* token, char** pStr)
{
	char c;

char* toto = token;
	
	/* fin de chaine */
	if (!**pStr)
	{
		*token='\0';
		return;
	}
	/* enlève les espace */
	while (isspace(**pStr))
		(*pStr)++;
	/* trouve le prochain caractère qui n'est pas comme les précédents (ou qu'il est une parenthèse) */
	do
	{
		c = **pStr;
		*(token++) = **pStr;
		/* passe au suivant, espaces ignorés */
		do
		{
			(*pStr)++;
		}
		while (isspace(**pStr));
	} while ( (c==(**pStr) || typeCaractere(c)==typeCaractere(**pStr)) && (c!=')' && c!='(') );
	/* fini le mot */	
	*token='\0';	
		
//printf("token=%s\n",toto);
		
}


/* crée un arbre depuis une chaine de caractères à notation infixée 
Basé sur le Shunting-yard algorithm */
t_noeud* creerArbreDepuisInfixee( char* str)
{
	char token[50];		/* chaine intermédiaire */
	float val;			/* valeur correspondante */
	char* conv;			/*  chaine pour la conversion */
	t_id* id, *idCour;	/* identificateurs */
	int pe;
	/* pile d'identificateur , réalisée avec un tableau et un entier*/
	t_id *pileId[MAXPILE];		
	int posPileId = 0;
	posPileNoeud = 0;
	
	/* récupère le 1er token */
	prochainToken( token, &str);

	/* itération sur tous les token */
	while (*token!='\0')
	{

		id = quelIdentificateur(token);
	    val = strtod( token, &conv);
	    
		/* est-ce que le token est un réel? */
		if (*conv=='\0')
		{
			/* créé une feuille et la rajoute dans la pile de noeud*/
			empilerReel( val);
		}
		
		/* est-ce que c'est une fonction ? */
		else if (estFonction(id))
		{
			/* on l'empile */
			pileId[ posPileId++ ] = id;
		}

		/* est-ce que c'est une virgule (séparateur pour l'appel d'une fonction) */
		else if (*token==',')
		{
			/* Jusqu'à ce que l'id au sommet de la pile soit une parenthèse fermante, dépiler les opérateurs et les afficher. */
			pe = 0;
			while (posPileId > 0)
			{
				idCour = pileId[ posPileId-1 ];
				if (!strcmp(idCour->ch,"("))
				{
					pe = 1;
					break;
				}
				else
				{
					empilerNoeud( idCour);
					posPileId--;
				}
			}
			/* Si aucune parenthèse n'est trouvée, alors il y a un problème... */
			if (!pe)
			{
				printf("Erreur: séparateurs ou parenthèses non concordantes\n");
				viderPileNoeud();
				return NULL;
			}

		}
		
		/* est-ce que c'est un opérateur ? */
		else if (estOperateur(id))
		{
			/* Tant qu'il existe un identificateur idCour au sommet de la pile tel que, ou bien id est associatif à gauche et est moins prioritaire (ou égal) à idCour, ou bien id est associatif à droite et est strictement moins prioritaire que idCour, alors dépilier idCour */
			while (posPileId>0)
			{
				idCour = pileId[ posPileId-1 ];
				if ( estOperateur(idCour) &&
					(  (id->assoc==ASSOC_GAUCHE && id->prior<=idCour->prior)
					|| (!id->assoc==ASSOC_DROITE && id->prior<id->prior) ) )
				{
					empilerNoeud( idCour);
					posPileId--;
				}
				else break;
			}
			/* met id dans la pile */
			pileId[ posPileId++ ] = id;
		}

		/* est-ce que c'est une parenthèse ouvrante ?*/
		else if (id && !strcmp(id->ch,"("))
		{
			pileId[ posPileId++ ] = id;
		}

		/* est-ce que c'est une parenthèse fermante ?*/
		else if (*token==')')
		{
			pe = 0;
			/* Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue */
			while (posPileId>0)
			{
				idCour = pileId[ posPileId-1 ];
				if (!strcmp(idCour->ch,"("))
				{
					pe = 1;
					break;
				}
				else
				{
					empilerNoeud( idCour );
					posPileId--;
                }
			}
			/* Si aucune parenthèse n'est trouvée, alors il y a un problème... */
			if (!pe)
			{
				printf("Erreur: séparateur ou parenthèses non concordantes\n");
				viderPileNoeud();
				return NULL;
			}

			/* Enlève la parenthèse ouvrante de la pile */
			posPileId--;
			/* Si l'identificateur au sommet de la pile est une fonction, on la rajoute sur la pile de noueds. */
			if (posPileId>0)
			{
				idCour = pileId[ posPileId-1 ];
				if (estFonction(idCour))
				{
					empilerNoeud( idCour );
					posPileId--;
				}
			}
		}

		/* sinon c'est rien de tout ça, on considère que c'est une variable */
		else
		{
			empilerVar( token);
		}
	    
    	/* prochain token */
    	prochainToken( token, &str);
    }
  
    /* Quand il n'y a plus de token à lire : on s'occupe des opérateurs qui restent dans la pile */
	while (posPileId>0)
	{
		idCour = pileId[ posPileId-1 ];
		if (!strcmp(idCour->ch,"("))
		{
			printf("Erreur: Parenthèses non concordantes\n");
			viderPileNoeud();
			return NULL;
        }
		empilerNoeud( idCour);
		posPileId--;
	}
	
	
	if (posPileNoeud != 1)
	{
		printf("Erreur: il reste des arguements non utilisés dans la pile\n");
		viderPileNoeud();
		return NULL;
	}
		

	return pileNoeud[0];
	
}

