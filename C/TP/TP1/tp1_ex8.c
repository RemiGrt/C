#include <stdio.h>

void main(){
	
	int a, b, tmp, rest;
	
	
	scanf("%d", &a);
	scanf("%d", &b);
	
	if (b > a){
		tmp = b;
		b = a;
		a = tmp;
	}
	
	while(a%b != 0){
		rest =a%b;
		a=b;
		b=rest;
	}
	
	printf("PGCD %i", b);
		
		
	
	
	
}