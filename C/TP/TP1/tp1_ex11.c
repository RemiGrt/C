#include <stdio.h>

#define DEBUG 0

/*
int main() { // d´ eclaration des variables 
char car_cour; // caract` ere courant 
char car_prec; // caract` ere precedant 
int n; // nbre d’occurence du caract` ere courant
// lecture du 1er caract` ere 
n=0; scanf("%c",&car_cour); car_prec=car_cour;
// boucle jusqu’` a obtenir un ’#’ 
while (car_cour!='#') { // le nouveau caract` ere est le meme que le pr´ ec´ edent ?? 
if (car_cour==car_prec) 
	{ n=n+1; } 
else 
	{ 
	if (car_prec!='\n') 
		printf("%d %c ",n,car_prec); 
	else printf("0 M\n"); 
	n=1; 
	}
// lecture du caract` ere suivant 
car_prec=car_cour; 
scanf("%c",&car_cour);
}
// affiche "-1 M" pour marquer la fin de fichier 
printf("-1 M\n");
return 0;
}
*/


void main(){
	
	char ncar=0, car=1;
	int i=0, nb=0;
	scanf("%c", &car);
	
	do {
		// Use Space before %c
		scanf("%c", &ncar);
		if(car=='\n'){
			printf("0 M\n");
		}
		else if(ncar == car){
			if(DEBUG) printf(" -- test1 car %c ncar %c \n", car, ncar);
			nb++;
		}
		else{
			if(DEBUG)  printf(" -- test2 nb %i car %c ncar %c \n", nb, car, ncar);
			if(nb>0){
				
					printf("%i %c ",nb+1,car);
				
			}
			else {
				printf("1 %c ",car);	
			}		
			
			//	printf("\n");	
			
			
			nb=0;
		}
		car = ncar;
		if(DEBUG) printf(" -- test3  nb %i car %c ncar %c \n", nb, car, ncar);	
	} while(ncar != '#' );
	
	printf("-1 M");

	
	
}

