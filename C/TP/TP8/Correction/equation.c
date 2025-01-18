/*=====================================
*
*        oO  ARBRE   Oo
*
*=====================================
*
* File : equation.c
* Date : 26 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Manipulation d'une équation
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "equation.h"


/* affiche le noeud, mais pas les fils */
void afficherNoeud( t_noeud* arbre)
{
	if (arbre->ch)
		printf("%s", arbre->ch);
	else if (arbre->val==(int)arbre->val)
		printf("%d", (int)arbre->val);
	else
		printf("%f", arbre->val);
}


/* afficher une équation sous forme infixée */
void afficherInfixee( t_noeud* arbre)
{
	switch ( nbFils(arbre) )
	{
		case 2:
			printf("(");
			afficherInfixee( arbre->filsG);
			afficherNoeud( arbre);
			afficherInfixee( arbre->filsD);
			printf(")");
			break;
		case 1:
			afficherNoeud( arbre);
			printf("(");
			afficherInfixee( arbre->filsG);
			printf(")");	
			break;
		case 0:
			afficherNoeud( arbre);
	}
}


/* afficher une équation sous forme postfixée */
void afficherPostfixee( t_noeud* arbre)
{
	if (arbre)
	{
		/* affichage du fils gauche */
		if (arbre->filsG)
		{
			afficherPostfixee( arbre->filsG);
			printf(" ");
		}
			
		/* affichage du fils droit */
		if (arbre->filsD)
		{
			afficherPostfixee( arbre->filsD);
			printf(" ");
		}
			
		/* affichage du noeud en lui-même */
		afficherNoeud( arbre);
	}
}


void remplacerNoeud( t_noeud* noeud, float val)
{
	/* recopie la valeur */
	noeud->val = val;
	/* désalloue la chaine */
	if (noeud->ch)
		free(noeud->ch);
	noeud->ch = NULL;
	/* désalloue les fils */
	detruireArbre( noeud->filsG);
	noeud->filsG = NULL;
	detruireArbre( noeud->filsD);
	noeud->filsD = NULL;	
}


/* evaluer un arbre */
int evaluer( t_noeud* arbre)
{
	int g,d;
	/* évaluation de chacun des deux fils */
	g=d=1;
	if (arbre->filsG)
		g = evaluer(arbre->filsG);
	if (arbre->filsD)
		d = evaluer(arbre->filsD);
	/* calcul du noeud */
	if (nbFils(arbre)>0)
	{
		if ( !strcmp( arbre->ch, "+") && g && d )
			remplacerNoeud( arbre, arbre->filsG->val + arbre->filsD->val );
		else if ( !strcmp( arbre->ch, "-") && g && d )
			remplacerNoeud( arbre, arbre->filsG->val - arbre->filsD->val );
		else if ( !strcmp( arbre->ch, "*") && g && d )
			remplacerNoeud( arbre, arbre->filsG->val * arbre->filsD->val );
		else if ( !strcmp( arbre->ch, "/") && g && d )
			remplacerNoeud( arbre, arbre->filsG->val / arbre->filsD->val );
		else if ( !strcmp( arbre->ch, "^") && g && d )
			remplacerNoeud( arbre, pow( arbre->filsG->val, arbre->filsD->val) );
		else if ( !strcmp( arbre->ch, "sin") && g )
			remplacerNoeud( arbre, sin(arbre->filsG->val) );

	}
	/* renvoie si c'est évaluable */
	return arbre->ch==NULL;
}



/* dériver par rapport à une variable 
en considérant que les autres sont indépendantes */
void deriver( t_noeud* arbre, char* var)
{
	t_noeud *u, *v, *up, *vp;
	/* valeur */
	if (arbre->ch==NULL)
		arbre->val = 0;
	/* variable */
	else if (nbFils(arbre)==0)
	{
		if (!strcmp(arbre->ch,var))
		{
			/* dx/dx = 1 */
			free(arbre->ch);
			arbre->ch=NULL;
			arbre->val = 1;
		}
		else
		{
			/* dy/dx = 0 car on suppose toutes les variables indépendantes */
			free(arbre->ch);
			arbre->ch=NULL;
			arbre->val = 0;
		}
	}
	/* opérateur + */
	else if (!strcmp(arbre->ch,"+"))
	{
		/* (u+v)' => u'+v' */
		deriver( arbre->filsG, var);
		deriver( arbre->filsD, var);
	}
	else if (!strcmp(arbre->ch,"-"))
	{
		/* (u-v)' => u'-v' */
		deriver( arbre->filsG, var);
		deriver( arbre->filsD, var);
	}
	else if (!strcmp(arbre->ch,"*"))
	{
		/* (u*v)' => u'*v+u*v' */
		up = dupliquer(arbre->filsG);
		deriver( up, var);
		vp = dupliquer(arbre->filsD);
		deriver( vp, var);
		u = arbre->filsG;
		v = arbre->filsD;
		strcpy( arbre->ch, "+");
		arbre->filsG = creerNoeudOp( up, "*", v );
		arbre->filsD = creerNoeudOp( u, "*", vp );
	}
	else if (!strcmp(arbre->ch,"/"))
	{
		/* (u/v)' => (u'v - v'u)/v^2 */
		up = dupliquer(arbre->filsG);
		deriver( up, var);
		vp = dupliquer(arbre->filsD);
		deriver( vp, var);
		u = arbre->filsG;
		v = arbre->filsD;
		strcpy( arbre->ch, "+");
		arbre->filsG = creerNoeudOp( creerNoeudOp(up,"*",v), "-", creerNoeudOp(vp,"*",u) );
		arbre->filsD = creerNoeudOp( dupliquer(v), "^", creerFeuilleReel(2) );
	}
	else if (!strcmp(arbre->ch,"^"))
	{
		
		if (!evaluer(arbre->filsD))
			printf( "on ne gère pas la dérivée pour u^v si v n'est pas une constante\n");
		else
		{
			/* (u^k)' => k*u^(k-1)*u' */
			up = dupliquer(arbre->filsG);
			deriver( up, var);
			u = arbre->filsG;
			v = arbre->filsD;
			strcpy( arbre->ch, "*");;
			arbre->filsG = dupliquer(v);
			v->val--;
			arbre->filsD = creerNoeudOp( creerNoeudOp( u, "^", v), "*", up);
		}
	}
	else if (!strcmp(arbre->ch,"sin"))
	{
		/* sin(u) => u'*cos(u) */
		up = dupliquer(arbre->filsG);
		deriver( up, var);
		u = arbre->filsG;
		strcpy( arbre->ch, "*");	/* 2 octets alloués en trop, mais c pas grave */
		arbre->filsG = up;
		arbre->filsD = creerNoeudOp( u, "cos", NULL);	/* bon, c'est vrai, le cosinus n'est pas défini dans evaluer... */
	}

}


/* simplifier un arbre
En applicquant les règles suivantes :
x+0 ou 0+x => x
x-0 => x 
1*x ou 1*x => x
0*x ou x*0 => 0
x^1 => x
x^0 => 1
x/1 => x */	
t_noeud* simplifier( t_noeud* arbre)
{
	t_noeud* n;
	/* simplifier à gauche */
	if (arbre->filsG)
		arbre->filsG = simplifier(arbre->filsG);
	/* simplifier à droite */
	if (arbre->filsD)
		arbre->filsD = simplifier(arbre->filsD);
	/* simplifier le noeud en question */
	if (nbFils(arbre)==2)
	{
		/* 0+x -> x */
		if ( !strcmp(arbre->ch,"+") && arbre->filsG->val==0 && arbre->filsG->ch==NULL)
		{
			/* on détruit l'arbre (sauf le filsG) et on renvoie ce filsG */
			n = arbre->filsD;
			arbre->filsD = NULL;
			detruireArbre(arbre);	/* le filsG n'est pas détruit, car on a gardé son adresse et mis arbre->filsG à NULL */
			return n;
		}
		/* x+0 -> x */
		else if ( !strcmp(arbre->ch,"+") && arbre->filsD->val==0 && arbre->filsD->ch==NULL)
		{
			n = arbre->filsG;
			arbre->filsG = NULL;
			detruireArbre(arbre);
			return n;
		}
		/* x-0 -> x */
		else if ( !strcmp(arbre->ch,"-") && arbre->filsD->val==0 && arbre->filsD->ch==NULL)
		{
			n = arbre->filsG;
			arbre->filsG = NULL;
			detruireArbre(arbre);
			return n;
		}		
		/* 1*x -> x */
		else if ( !strcmp(arbre->ch,"*") && arbre->filsG->val==1 && arbre->filsG->ch==NULL)
		{
			/* on détruit l'arbre (sauf le filsG) et on renvoie ce filsG */
			n = arbre->filsD;
			arbre->filsD = NULL;
			detruireArbre(arbre);	/* le filsG n'est pas détruit, car on a gardé son adresse et mis arbre->filsG à NULL */
			return n;
		}
		/* x*1 -> x */
		else if ( !strcmp(arbre->ch,"*") && arbre->filsD->val==1 && arbre->filsD->ch==NULL)
		{
			n = arbre->filsG;
			arbre->filsG = NULL;
			detruireArbre(arbre);
			return n;
		}
		/* 0*x -> 0 */
		else if ( !strcmp(arbre->ch,"*") && arbre->filsG->val==0 && arbre->filsG->ch==NULL)
		{
			/* on détruit l'arbre */
			detruireArbre(arbre);
			return creerFeuilleVar(0);
		}
		/* 0*x -> 0 */
		else if ( !strcmp(arbre->ch,"*") && arbre->filsD->val==0 && arbre->filsD->ch==NULL)
		{
			/* on détruit l'arbre */
			detruireArbre(arbre);
			return creerFeuilleVar(0);
		}
		/* x^1 -> x */
		else if ( !strcmp(arbre->ch,"^") && arbre->filsD->val==1 && arbre->filsD->ch==NULL)
		{
			n = arbre->filsG;
			arbre->filsG = NULL;
			detruireArbre(arbre);
			return n;
		}
		/* x^0 -> 1 */
		else if ( !strcmp(arbre->ch,"^") && arbre->filsD->val==0 && arbre->filsD->ch==NULL)
		{
			/* on détruit l'arbre */
			detruireArbre(arbre);
			return creerFeuilleReel(1);
		}	
	}
	return arbre;
}
