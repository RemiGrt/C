#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vm_codops.h"

#define MAX_CODESEGMENT_SIZE 1000
#define MAX_STACK_SIZE 100
#define MAX_VARS_SIZE 100

int pc;
int sp;

int codeSegment[MAX_CODESEGMENT_SIZE];

int pile[MAX_STACK_SIZE];

int vars[MAX_VARS_SIZE];

void readAssembly(FILE *fin)
{
	int nbinst;
	char line[100];
	int i;
	int pc,v;

	fgets(line,100,fin);
	sscanf(line,"%d",&nbinst);
	for (i=0;i<nbinst;i++)
	{
		fgets(line,100,fin);
		sscanf(line,"%d:%d",&pc,&v);
		codeSegment[i]=v;
	}
}

// Q5 : Fonction de debug qui affiche la pile jusqu'a son sommet 

void printPile()
{
	int i;

	printf("sp=%d\n",sp);
	for (i=0;i<=20;i++)
		printf("%d:%d ",i,pile[i]);
	printf("\n");
}

void printvars()
{
	printf("%d %d %d %d\n", vars[14], vars[15], vars[16], vars[17]);
}

// Q6 : Boucle principale d'exécution de la machine virtuelle 
//      On sort de cette fonction si l'instruction pointee
//      par pc est OP_HALT. On traitera les erreurs et on
//	pensera a ajouter des traces et des moyens de mise
//	au point

void run()
{
	while (codeSegment[pc]!=OP_HALT)
	{
		printf("%d: ",pc);
		switch (codeSegment[pc])
		{
			case OP_ADD:
				printf("add\n");
				pile[sp-1]=pile[sp-1]+pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_SUB:
				printf("sub\n");
				pile[sp-1]=pile[sp-1]-pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_MULT:
				printf("mult\n");
				pile[sp-1]=pile[sp-1]*pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_DIV:
				printf("div\n");
				pile[sp-1]=pile[sp-1]/pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_NEG:
				printf("neg\n");
				pile[sp]=-pile[sp]; 
				pc++ ; break;
			case OP_AND:
				printf("and\n");
				pile[sp-1]=((int)pile[sp-1] & (int)pile[sp]); 
				sp-- ; pc++ ; break;
			case OP_OR:
				printf("or\n");
				pile[sp-1]=((int)pile[sp-1] | (int)pile[sp]); 
				sp-- ; pc++ ; break;
			case OP_NOT:
				printf("not\n");
				pile[sp]=(1-(int)pile[sp]); 
				pc++ ; break;
			case OP_EQ:
				printf("eq\n");
				pile[sp-1]=(pile[sp-1]==pile[sp]) ? 1 : 0; 
				sp-- ; pc++ ; break;
			case OP_LS:
				printf("ls\n");
				pile[sp-1]=(pile[sp-1]<pile[sp]) ? 1 : 0; 
				sp-- ; pc++ ; break;
			case OP_GT:
				printf("gt\n");
				pile[sp-1]=(pile[sp-1]>pile[sp]) ? 1 : 0; 
				sp-- ; pc++ ; break;
			case OP_PUSH:
				printf("push %d\n",codeSegment[pc+1]);
				sp++;
				pile[sp]=vars[codeSegment[pc+1]];
				pc=pc+2; 
				break;
			case OP_POP:
				printf("pop %d\n",codeSegment[pc+1]);
				vars[codeSegment[pc+1]]=pile[sp];
				sp--;
				pc+=2;
				break;
			case OP_PUSHI:
				printf("pushi %d\n",codeSegment[pc+1]);
				sp++;
				pile[sp]=codeSegment[pc+1];
				pc+=2;
				break;
			case OP_JP:
				printf("jp %d\n",codeSegment[pc+1]);
				pc=codeSegment[pc+1];
				break;
			case OP_JF:
				printf("jf %d\n",codeSegment[pc+1]);
				if (pile[sp]==0)
					pc=codeSegment[pc+1];
				else
					pc=pc+2;
				sp--;
				break;
			default:
				printf("Instruction non reconnue\n");
				exit(1);
		}
		//printExecStack();
		printvars();
	}
}

int main(int argc, char **argv)
{
	int i;

	if (argc!=2)
	{
		printf("Usage : vm infile.bin\n");
	}
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
	{
		printf("Error opening read file %s\n",argv[1]);
		exit(1);
	}

	readAssembly(fin);
	fclose(fin);

	pc=0;
    	sp=-1;

	vars[1]=1; // but0'rise
	vars[6]=12; // an0=12
	vars[14]=1;

	run();

	return 0;
}
