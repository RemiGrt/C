#include <stdio.h>

int main(void)
{
  FILE* f=fopen("test.asm","r"); //ouverture du fichier passé dans la console
	if (f==NULL){
		printf("Ouverture du fichier impossible\n");
		//exit (1);
	}
  char tab[128];
  fscanf(f,"%[^\n]",tab);
  printf("%s\n",tab);
  return 0;
}
