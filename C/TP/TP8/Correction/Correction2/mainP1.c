#include <stdio.h>
#include "arbre.h"

int main(int argc, char *argv[])
{
    t_noeud* arbre = creerNoeudOp( creerFeuilleReel(12), "+", creerNoeudOp(
                creerFeuilleReel(4), "*", creerFeuilleVar("x") ) );
    affichageNoeud(arbre);
    return 0;
}
