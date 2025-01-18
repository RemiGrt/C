#include <stdio.h>

int appel;

float calculpuissance(float x, int k){
	int parite = k%2;
	appel++;
	printf("Appel %d\n",appel);
	if(k==0){return 1;}
	int exposant = (k - parite)/2;
	if(parite==0){
		return calculpuissance(x,exposant)*calculpuissance(x,exposant);
	}else
		return x*calculpuissance(x,exposant)*calculpuissance(x,exposant);
	}


int main(){
	
	float x;
	int k;
	
	scanf("%f %x", &x, &k);
	printf("Puissance: %f\n",calculpuissance(x,k));
	
}
