#include <stdio.h>
#include <stdlib.h>
#define TAILLE 1024
#define DYN 0
/* affiche info sur le tableau */
void aff_info (int *p)
{
  printf("%p -> p[0]=%i\n",p,*p);
}
/* créé nouveau tableau */
int * tab_nouv (int n)
{
  
  int i;
  #if DYN
  int *t = (int*) malloc( TAILLE*sizeof(int) );
  #else
  int t[TAILLE];
  #endif
  for (i=0; i<TAILLE; ++i)
    t[i]=n;
  return t;
}

int main ()
{
  int t1[TAILLE] ;
  int t2[1] ;
  int t3[TAILLE] ;
  int t4[1] ;
  int *t5 = tab_nouv(4);
  int *t6 = tab_nouv(2);
  /* Affiche les adresses des tableaux statiques et de deux "tableaux" créés par tab_nouv()
   */
  printf("Tableaux statiques:\n");
  aff_info(t1);
  aff_info(t2);
  aff_info(t3);
  aff_info(t4);
  printf("Tableaux dynamiques (?):\n") ;
  aff_info(t5);
  aff_info(t6);
  return EXIT_SUCCESS;
}



