#include <stdio.h>



void minimum(){
	int tab[5] = {1,2,3,4,0};
	int min=tab[0];
	for(int i=0;i<sizeof(tab)/sizeof *(tab);i++){
		if(tab[i] <= min)
			min = tab[i];
		
	}
	printf("min %i\n",min);
	printf("size %i\n",sizeof(tab));
	printf("tab %i\n",*(tab+1));
}


void occurence(){
	int n=5;
	int tab[n];
	int element;
	int nb=0;
	printf("\nTab: ");
	for(int i=0; i<n;i++){
		scanf(" %i", tab+i);		
	}
	printf("\nElement: ");
	scanf(" %i", &element);
	
	for(int i=0; i<n;i++){
		if(tab[i]==element) nb++;		
	}
	printf("nb: %i", nb);
}

void palindrome(){
	const int n=5;
	int tab[n];
	int element;
	int nb=0;
	printf("\nTab: ");
	for(int i=0; i<n;i++){
		scanf(" %i", tab+i);		
	}
	for(int i=0; i<n;i++){
		//printf("tab[i] %i tab[n-i] %i",tab[i], tab[n-1-i]);
		if(tab[i] != tab[n-1-i]){ 
			printf("pas un palindrome");
			break;
		}
		
			
	}
}

void doublon(){
	int tab[5]={1,2,2,4,4};
	for(int i=0;i<5;i++){
		for(int k=i+1;k<5;k++){
			if(tab[k]==tab[i]) tab[k]=0;
		}
	}
	
	for (int i=0;i<5;i++){
		printf("%i", tab[i]);
	}
	
}

void main(){
	//minimum();
	//occurence();
	//palindrome();
	doublon();
}