#include <stdlib.h>
#include <stdio.h>
#include "vm_codops.h"

#define MaxCode_size 1000
#define MaxStack_size 100
#define MaxVar_size 100

int code[MaxCode_size];
int stack[MaxStack_size];
int var [MaxVar_size];
int sp=-1;
int pc=0;	

void run()
{
  while(code[pc]!=I_HALT)
	{switch(code[pc])
		{case I_PUSHI: printf("run: I_PUSHI\n");// Remplit le stack par les valeurs 0 1 2 
			stack[++sp]=code[pc+1];
 			sp++; pc=pc+2; break;
		case I_ADD: printf("run: I_ADD\n");
			stack[sp-1]=stack[sp-1]+stack[sp];
			sp++; pc++; break;
		case I_MULT: printf("run: I_MULT\n");
			stack[sp-1]=stack[sp-1]*stack[sp];
			sp--; pc++; break;
		case I_PUSH : printf("run: I_PUSH\n");// On met a dans le stack
			stack[++sp]=var[code[pc+1]];
			pc+=2; break;
		case I_EQ : printf("run: I_EQ\n");// on compare a et pushi 0
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_AND : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_OR : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=0;} 
			else {
			sp--; 
			    stack[sp]=1;}
			pc++; break;
		case I_JF : printf("run: I_JF\n");
			if (stack[sp]==0){pc= code[pc+1];}  //jump
			else {pc+=2;}
			  break;
		case I_NOT : printf("run: I_NOT\n");// 
			stack[sp]=!stack[sp]; 
			pc++; break;
		case I_POP : printf("run: I_POP\n");// On affecte 1 ou 2 à b
			var[code[pc+1]]=stack[sp-1];
			pc+=2; break;
		case I_J : printf("run: I_J\n");// on écrit -1
			pc=code[pc+1];
			break;
		}

	printf("run: sp = %d \n", sp);
	printf("run: pc = %d \n", pc);
	printf("run: stack[sp] = %d \n", stack[sp]);
	}
	
}

void readBin (char* filename)

{   int nb1;
  int i, co, v;
  FILE* fichier = fopen(filename, "r");
  if (fichier==NULL) 
  { printf ("Erreur");
	exit(1);
	}

  fscanf(fichier,"%d", &nb1);
     printf("readBin: nb1= %d\n", nb1);
	for (i=0; i<nb1; i++)
        {
		fscanf(fichier,"%d:%d", &co, &v);
                code[co]=v;
		//printf("readBin: co = %d \n", co);
		//printf("readBin: v = %d \n", v);
		printf("readBin: code[%d]= %d\n", i, code[co]);
	}
 fclose(fichier);
}



int main(int argc,char *argv[])
{
 var[0]=1;
 var[1]=4;
	
 //readBin (argv[1]);
 readBin ("ex2.bin");
 printf("%s\n", argv[1]);
 run();
 //printf ("%d \n", stack[3]);// affiche POP b=1
 //printf ("%d \n", stack[5]);//affiche POP b=2
 printf ("b= %d \n", var[1]);
 
return 0;
}
