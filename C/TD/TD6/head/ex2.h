#ifndef _ex2_
#define _ex2_

typedef char t_chaine[40];

typedef struct{
  int jour;
  int mois;
  int annee;
} t_date;

typedef struct{
  t_chaine nom;
  t_chaine prenom;
  t_date datedenaissance;
  int age;
  t_chaine adresse[3];
}t_personne;



#endif
