#include "arbre.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

t_noeud* creerNoeud( float val, char* ch, t_noeud* filsG, t_noeud* filsD)
{
    t_noeud* nouveau_noeud = malloc(sizeof(t_noeud));
    nouveau_noeud->val = val;
    nouveau_noeud->ch = ch;
    nouveau_noeud->filsG = filsG;
    nouveau_noeud->filsD = filsD;
    return nouveau_noeud;
}

t_noeud* creerNoeudOp(t_noeud* filsG, char* ch, t_noeud* filsD)
{
    assert(*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/' || *ch == '^');
    return creerNoeud(-1, ch, filsG, filsD);
}

t_noeud* creerFeuilleReel(float val)
{
    return creerNoeud(val, NULL, NULL, NULL);
}

t_noeud* creerFeuilleVar(char* ch)
{
    return creerNoeud(-2, ch, NULL, NULL);
}

void affichageNoeud(t_noeud* n)
{
    if (n->filsG == NULL && n->filsD == NULL) {
        if (n->ch == NULL) {
            printf(" %f ", n->val);
        }
        else {
            printf(" %s ", n->ch);
        }
    }
    else {
        printf("(");
        affichageNoeud(n->filsG);
        printf(" %s ", n->ch);
        affichageNoeud(n->filsD);
        printf(")");
    }
}
