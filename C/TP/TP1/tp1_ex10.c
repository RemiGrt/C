#include <stdio.h>


void main(){
	
	int ent = 0;
	char car = 'b';
	scanf("%i %c", &ent, &car);
	
	while(ent != -1){
		
		if(ent == 0){
			printf("\n");
		}
		else {
			for(int i=ent;i--;i>0){
			printf("%c", car);
			}
		}
		scanf("%i %c", &ent, &car);
	}
	
	
	printf("#");
	
	
}

