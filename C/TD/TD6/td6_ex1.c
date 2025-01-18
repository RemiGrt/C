#include <stdio.h>
#include "struct.h"
#include "libfonc.h"


void main(){
	t_complexe a;
	a.reel = 1;
	a.imaginaire = 2;
	affiche(a);
	printf("\n");
	// question 2
	printf("module: %f\n", module(a));

        // (1-i)*(3-0,5i)+2i
        t_complexe b,c,d;
        t_complexe sum;
        t_complexe prod;
      
        b.reel=1;
        b.imaginaire=-1;

        c.reel=3;
        c.imaginaire=-0.5;

        d.reel=0;
        d.imaginaire=2;
        affiche(b);
        affiche(c);
        affiche(d);
        
        produit(&prod,b,c);
        affiche(prod);
        
        somme(&sum,prod,d);
        affiche(sum);
        
        printf("\n");
}
