#include <stdio.h>

char line[100];

int main()
{
	FILE *fin=fopen("and.bin","r");
	
	fgets(line,100,fin);
	printf("%s\n",line);
	fclose(fin);
	return(0);

}