////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  EI2I3 - Correction TD4 ex 4												      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  04/11/2016														      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Puissance k ème récursive												      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Pour calculer x k (x réel, k entier positif), on peut utiliser le principe de récursion suivant :			      //
//  • si k = 0, alors le résultat est 1.										      //
//  • si k = 2 × p (k est pair), alors on calcule (selon le même principe) m = x p , puis le résultat est m × m.	      //
//  • si k = 2 × p + 1 (k est impair), alors on calcule (selon le même principe) m = x p , puis le résultat est x × m × m.    //
//  1. Écrire la fonction récursive puiss qui prend en entrée x et k et qui calcule x k selon le principe décrit ci-dessus.   //
//  2. Dans le cas du calcul de x 18 , combien d’appels seront fait à la fonction puiss					      //
//  3. Dans le calcul de x k avec k = 2p, combien d’appels seront fait à la fonction puiss (la réponse dépend bien sûr	      //
//  de p).														      //
//  4. Ré-écrire la fonction puiss sans utiliser la récursivité (mais en utilisant un principe similaire, basé sur l’écriture //
//  binaire de k).*/													      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

// Retourne la valeure du bit d'indice i de n
int bit(int n, int i)
{
  // Decalage à droite de i bit puis masque pour obetinr le LSB
  return (n >> i) & 0x1;
}

// Retourne le nombre de bit de n
int nb_bits(int n)
{
  return (int)(log2(n))+1;
}

// Retourne a^b
int puissance_binaire(int a, int b)
{
  int r = 1;
  int i;
  for (i = nb_bits(b); i >=0; i--)
    {
      if (bit(b, i) == 1)
	r = r * r * a;
      else
	r = r * r;
    }
  return r;
}

// Retourne x^k
// pnbapp: pointeur vers le nombre d'appel de puissance_recursive
int puissance_recursive(int x, int k, int *pnbapp){
  (*pnbapp)++;
  if(k==0){
    return 1;
  } else if (k%2==0){
    return puissance_recursive(x,k/2,pnbapp)*puissance_recursive(x,k/2,pnbapp);
  } else {
    return puissance_recursive(x,k/2,pnbapp)*puissance_recursive(x,k/2,pnbapp)*x;
  }	
}

int main(){
  int nb, puis;
  int* pnbapp;
  printf("Nb Puisance:");
  scanf("%d %d",&nb,&puis);
  printf("Recursive        :%d^%d:%d\n",nb,puis,puissance_recursive(nb,puis,pnbapp));
  printf("Calcul nb appel  :%d\n",(int)(pow( 2,nb_bits(puis)+1)));
  printf("Nb appel recursif:%d\n",*pnbapp);
  printf("Binaire          :%d^%d:%d\n",nb,puis,puissance_binaire(nb,puis));
  return 0;
}
