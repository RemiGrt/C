#include <stdio.h>


int factorielle(int i){
	int fact=1;
	for(i; i>0 ; i--){
		fact=fact * i;
	}
	return fact;
}

int factorielle2(int i){
	int fact=i;
	while(i!=1){
		i--;
		fact=fact * i;
	}
	return fact;
}

void main(){
	
	int a;
	
	
	scanf("%d", &a);
	
	printf("factorielle de %i est %i %i", a,factorielle(a),factorielle2(a));
	
}