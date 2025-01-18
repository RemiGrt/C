#include <stdio.h>

void main(){
	
	int test=0xC;
	int a=4, b=2;
	printf("result %i\n", (a>b)?a:b);
	
	
	for(int i=1; i<=100 ; i++){
		
		if ( (i%3==0) || (i%10==3) ){
			printf("Fizz ");
		}
		else if (i%7==0 || i%10==7){
			printf("Buzz ");
		}
		else{
			printf("%i ", i);
		}
		
	}
	
	
}