#ifndef __carte__
#define __carte__
#define NBCarte 52
#define carte_coeur NBCarte*1/4
#define carte_carreau NBCarte*2/4
#define carte_trefle NBCarte*3/4


typedef enum{
  coeur,
  pique,
  carreau,
  trefle
}t_couleur;

typedef struct{
  int valeur;
  t_couleur couleur;
}t_carte;

typedef t_carte t_jeu[NBCarte];

void affiche(t_carte carte);
void rempli(t_jeu jeu);
void afficheJeu(t_jeu jeu);
void melange(t_jeu jeu, int permut);

#endif
