#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>



int factorielle(int nb){
	int fact=1;
	for(int i=nb;i>0;i--)
		fact=fact*i;
	
	return fact;
}

int factorielle_recursif(int nb){
	if(nb==0){
		return 1;
	} else {
		return nb*factorielle_recursif(nb-1);
	}
}

// nb =4
// return 4*factorielle_recursif(nb-1)
//        4*factorielle_recursif(3) 	
//        4*3*factorielle_recursif(2)
//		  4*3*2*factorielle_recursif(1)
//		  4*3*2*1*factorielle_recursif(0)	
// 		  4*3*2*1*1	

float fonction(float x,int *ok){
	if(x>=2){
		*ok=1;
		return sqrt((x-1)*(x-2));
		
	} else{
		*ok=0;
		return 0;
	}
}

//Ex4

int puiss(int x, int k, int *pnbapp){
	(*pnbapp)++;
	if(k==0){
		return 1;
	} else if (k%2==0){
		return puiss(x,k/2,pnbapp)*puiss(x,k/2,pnbapp);
	} else {
		return puiss(x,k/2,pnbapp)*puiss(x,k/2,pnbapp)*x;
	}	
}


// Calculates log2 of number.  
double Log2( double n )  
{  
    // log(n)/log(2) is log2.  
	printf("log2 %lf\n",(log( n ) / log( 2 )));
    return log( n ) / log( 2 );  
}

int bit(int n, int i)
{
    return (n >> i) & 0x1;
}

/*
  3^6 
= 3^(4+2) 
= 3^(2^2+2^1) = (3^110) 
= 3^2^2 * 3^2^1

  4^5
= 4^(4+1)
= 4^(2^2+2^0)
= 4^2^2 * 4^2^0
*/



int nb_bits(int n)
{
    return (int)((log2(n)) + 1);
}

int puissance_binaire(int a, int b)
{
    int r = 1;
	int pow = a;
    
	 printf("nb bit %d\n",nb_bits(b));
    for ( int i = nb_bits(b); i >= 0; i--)
    {
		printf("\t i:%d\n",i);
		if (bit(b, i) == 1)
			for(int j=i+1;j>=0;j--){
             r = pow * r;
			 printf("i:%d r:%d\n",i,r);
			 }
			 
		
    /*    if (bit(i, b) == 1)
            r = r * r * a;
		else
            r = r * r;
		*/
    }
    return r;
}

int main(){
	//ex1
	int bob=log(3);
	/*
	int nb;
	printf("Ex 1: Nb factorielle: ");
	scanf(" %d",&nb);
	printf("%d!= %d\n",nb,factorielle(nb));
	printf("fonction recursive %d!= %d\n",nb,factorielle_recursif(nb));
	
	//ex2
	float x;
	float y;
	
	printf("Ex 2:\n x: ");
	scanf(" %f",&x);
	

	//Sol 1
	printf("Solution 1\n");
	int ok=2;
	y=fonction(x,&ok);
	printf("OK %d\n",ok);
	printf("Fonction de %f: %f\n",x,y);
	//Sol 2
	printf("Solution 2\n");
	int* pok;
	int okval=3;
	pok=&okval;
	y=fonction(x,pok);
	printf("OK %d\n",*pok);
	printf("Fonction de %f: %f",x,y);
	*/
	//ex3
	int x3,k3;
	printf("Nb puiss:\n");
	int nbapp=0;
	int* pnbapp;
	pnbapp = &nbapp;
	scanf("%d %d",&x3,&k3);
	printf("Recursif %d^%d:%d\n",x3,k3,puiss(x3,k3,&nbapp));
	printf("Binaire %d^%d:%d\n",x3,k3,puissance_binaire(x3,k3));
	printf("Nombre d'appel:%d\n",nbapp);
	printf("Nombre d'appel:%lf\n",floor(Log2(k3))+1);
	return 0;
	
	/* Ex4 */
	



}

// Ex3
/*int a = 27;
int chose(int a); 
int machin();
int chose(int a) { return a+17+machin(); }
int machin() { return a; }
int main() { 
int a = 1; // a = 1
a = chose(a); //a = 27+17+27=71
printf("%d\n", a); 
return 0; 
}*/


// Question 4.2
// 1 appel                                      k <=18
// 2 appels            k<=9                                     k<=9
// 4 appels k<=4                k<=4                   k<=4                k<=4
// 8     k<=2 k<=2            k<=2 k<=2           k<=2  k<=2               k<=2 k<=2 
// 16  k<=1 k<=1 k<=1 k<=1  k<=1 k<=1 k<=1 k<=1  k<=1 k<=1 k<=1 k<=1     k<=1 k<=1 k<=1 k<=1
// 32  k<=0
//  
// = 63

// Question 4.3
// si p est paire 