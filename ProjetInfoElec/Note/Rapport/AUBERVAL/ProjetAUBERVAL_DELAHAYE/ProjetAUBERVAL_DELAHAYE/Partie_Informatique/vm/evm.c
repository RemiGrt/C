//
// Machine Virtuelle
// evm.c
// A compléter avec votre code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vm_codops.h"

#define DEBUG 1

int pc=0;
int sp=1;
int code[100];
int stack[100]; // Pile d'exécution
int var[100];
int v=0;
int i=0;

void readBin(char *filename){
	FILE* file=fopen(filename,"r");

	int N;
	int i=0;
	int l;

	fscanf(file, "%d ",&N);
	if (DEBUG) printf("Nombre de lignes :%d \n", N);

	while (i<=N)
	{
		
		fscanf(file, "%d : ",&l);
		if (DEBUG) printf("%d : ", l);
		fscanf(file, "%d ",&code[i]);
		if (DEBUG) printf("%d \n", code[i]);
		i++;
	}
}

void run (){
	
	/*if (DEBUG){
		for(i=0;i<20;i++){
			printf("code[%d]=%d\n",pc,code[pc]);
			pc++;
		}
	}*/

	while (code[pc]!=I_HALT)
	{i++;
		//if (DEBUG) printf("code[%d] : %d \n",pc, code[pc]);
		switch (code[pc])
		{
			case I_PUSHI : stack[sp]=code[++pc];
			if (DEBUG) printf("stack[%d] : %d \n",sp, stack[sp]);
			pc++;
			sp++;
			break;

			case I_ADD : stack[sp-1]=stack[sp]+stack[sp-1];
			pc++;
			sp--;
			if (DEBUG) printf("Resultat addition stack[%d] : %d \n",sp, stack[sp]);
			break;

			case I_MULT : 
			//if (DEBUG) printf("stack[sp-2]=%d, stack[sp-1]=%d,stack[sp-2]=%d\n",stack[sp-2],stack[sp-1],stack[sp-2]);
			stack[sp-2]=stack[sp-1]*stack[sp-2];
			pc++;
			sp=sp-2;
			if (DEBUG) printf("Resultat mult stack[%d] : %d \n",sp, stack[sp]);
			break;

		// PUSH registre met le contenu du registre dans la pile (empilement).
			case I_PUSH : 
			stack[sp]=var[v];
			sp++;
			v++;
			break;

		//POP registre récupère le contenu de la pile et le stocke dans le registre (dépilage).
			case I_POP : 
			var[v]=stack[sp];
			sp--;
			v++;
			break;

		// Si c'est égal alors on passe à l'instruction suivante sinon on cherche JF
			case I_EQ :
			if (stack[sp]==stack[sp-1]){
				pc++;
			}else{
				while (code[pc]!=I_JF) pc++;
			}
		        break; 

			case I_GT : 
			if (stack[sp]>stack[sp-1]){
				stack[sp-1]=1;
				pc++;
			}else{
				stack[sp-1]=0;
				while (code[pc]!=I_JF) pc++;
			}
			break;

			case I_LS :
			if (stack[sp]<stack[sp-1]){
				stack[sp-1]=1;
				pc++;
				sp--;
			}else{
				stack[sp-1]=0;
				while (code[pc]!=I_JF) pc++;
			}
			break;

			//case I_AND :
			
		//JF : si EQ est faux alors va à la ligne de l'étiquette qui suit JF
			case I_JF : 
			pc = code[pc+1];
			break;

			case I_J : 
			pc= code[pc+1];
			break;

			default : pc++;
		}
	}
}

int main (int argc, char *argv[])
{
	
	readBin(argv[1]);

	run();

	if (DEBUG) printf("Resultat : %d \n", stack[sp]);

	return 0;
}
