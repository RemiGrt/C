#include <stdio.h>

typedef struct {
unsigned int field1 :4;
unsigned int :3;
signed int field2:1;
//unsigned int :0;
unsigned int field3:6;

char field4 :5;
} t_reg ;

void binaire(t_reg valeur){
	
	
}

int main(){
	
	t_reg a;
	printf("Size of int: %d\n",sizeof(int));
	
	a.field1 = 0x9;   //   1001
	a.field2 = 0x1;   //      1
	a.field3 = 0x33 ; // 100001
	a.field4 = 0x17;  //  10001
	
	//affiche(a);
	printf("%d\n", *(&a));
	
}









