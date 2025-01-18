#ifndef ARBRE
#define ARBRE

typedef struct s_noeud {
    float val;
    char* ch;
    struct s_noeud* filsG;
    struct s_noeud* filsD;
} t_noeud;

t_noeud* creerNoeud( float val, char* ch, t_noeud* filsG, t_noeud* filsD);
t_noeud* creerNoeudOp( t_noeud* filsG, char* ch, t_noeud* filsD);
t_noeud* creerFeuilleReel(float val);
t_noeud* creerFeuilleVar(char* ch);
void affichageNoeud(t_noeud* n);

#endif
