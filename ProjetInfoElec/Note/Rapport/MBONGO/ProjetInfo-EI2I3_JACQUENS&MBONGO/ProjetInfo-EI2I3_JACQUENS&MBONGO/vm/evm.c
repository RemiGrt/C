/*ce programme exécute le bytecode (.bin) généré par
l’assembleur*/

#include <stdio.h>
#include "vm_codops.h"



int pc=0;						//program counter
int sp = -1;						//sommet de la pile					
int code[100];						//tableau du code
int stack[100];						//pile
int variable[100]={0,1};

void run()
{
	int k, m;
	while(code[pc]!=I_HALT)
	{
		switch (code[pc]) 
		{

			case I_PUSHI :
			stack[++sp] = code[pc + 1];
			pc = pc + 2;
			printf("%d \n", stack[sp]);
			
			break;

			case I_SUB :
			k = stack[sp - 1];
			stack[sp - 1] = stack[sp] - k;
			sp = sp - 1;
			pc++;
			printf("%d \n", stack[sp]);
			
			break;
		
			case I_ADD :
			k = stack[sp - 1];			
			stack[sp - 1] = stack[sp] + k;
			sp = sp - 1;
			pc++;
			printf("%d \n", stack[sp]);
			break;
		
			case I_MULT :
			m = stack[sp - 1];			
			stack[sp - 1] = stack[sp] * m;
			sp = sp - 1;
			pc++;
			printf("%d \n", stack[sp]);
			break;

			/* case I_DIV :
			m = stack[sp - 1];			
			stack[sp - 1] = stack[sp] / m;
			sp = sp - 1;
			pc++;
			printf("%d \n", stack[sp]);
			break; */
			
			case I_EQ:
			if (stack[sp-1]==stack[sp]) 
			{
				stack[sp-1]=1;
			}
			else 
			{
				stack[sp-1]=0;
			}
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;
		
	
			case I_PUSH:
	
			stack[++sp]=variable[code[pc+1]];
			pc=pc+2;
			printf("%d\n",stack[sp]);
			break;
			
			case I_POP:
			variable[code[pc+1]]=stack[sp];
			printf("%d \n", variable[pc+1]);			
			pc=pc+2;
			break;

			case I_J:
			if(stack[sp] == 1)
			{
				pc=code[pc+1];
			}
			else
			{
				pc=pc+2;
			}	 
			break;
			
			case I_JF:
			if(stack[sp] != 1)
			{
				pc=code[pc+1];
			}
			else
			{
				pc=pc+2;
			}	 
			break;
			
			case I_NOT :
			stack[sp] != stack[sp];
			sp++;
			printf("run : I_NOT\n");
			break;

			case I_NEG :
			stack[sp]  = 0-stack[sp];
			pc++;
			printf("run : I_NOT\n");
			break;
		
			case I_OR:
			if(stack[sp] == 1 || stack[sp-1] == 1)
			{
				stack[sp-1] = 1;
			}
			else 
			{
				stack[sp-1]=0;
			}
			sp--;
			pc++;	
			printf("run : I_OR\n");
			break;

			case I_AND:
			if(stack[sp] == 1 && stack[sp-1] == 1)
			{
				stack[sp-1] = 1;
			}
			else 
			{
				stack[sp-1]=0;
			}
			sp--;
			pc++;	
			printf("run : I_AND\n");
			break;

			case I_GT:
			if(stack[sp-1]<stack[sp])
			{
				stack[sp-1] = 1;
			}
			else 
			{
				stack[sp-1] = 0;
			}
			sp--;
			pc++;	
			printf("run : I_GT\n");
			break;

			case I_LS:
			if(stack[sp-1]>stack[sp])
			{
				stack[sp-1] = 1;
			}
			else 
			{
				stack[sp-1] = 0;
			}
			sp--;
			pc++;	
			printf("run : I_LS\n");
			break;
		}
		
	printf("pc = %d, sp = %d, stack[0] = %d, stack[1] = %d, stack[2] = %d, stack[3] = %d\n", pc, sp, stack[0], stack[1], stack[2], stack[3]);
	printf("variable[0]=%d, variable[1]=%d, variable[2]=%d, variable[3]=%d\n", variable[0], variable[1], variable[2], variable[3]);
	}

}

int* readBin(char *filename, int *code)
{
	int i, j, ligne[100];
	FILE* fichier = fopen(filename, "r");
	if(fichier == NULL)
		{
			return NULL;
		}
	fscanf(fichier, "%d", &i);
	printf("Nombre de lignes : %d\n", i); 
	for(j=0; j<i; j++)
	{
		
	        fscanf(fichier, "%d:%d", &ligne[j], &code[j]); 
		printf("Numero de ligne : %d\n", ligne[j]);		
		printf("Contenu ligne : %d\n", code[j]);
	}
	fclose(fichier);
	return code;	
}

int main()
{	
	int* code2;
	code2 = readBin("ex2.bin", code);
	run();
	
	return(0);
}

