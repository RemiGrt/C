/********************************************************************************
|   Nom fichier : vm_codops.c
|   auteurs: BIDANEL Matthieu FRIAA Chiheb
|   
|   Descriptions : Machine virtuelle
|   
|   Commentaires : Machine virtuelle comprenant un langage que l'on créé
|
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "vm_codops.h"

#define DEBUG 1

int pc = 0;
int sp = -1;
int code[100]; //Tableau contenant le code
int stack[100]; //Pile dans laquelle va transiter les variables que l'on manipule et s'effectuer les opérations de la VM
int var[100]; //Tableau des variables
int jump[1000];

//On défini ici l'action effectuée pour chaque instruction créé
void run(){
	while(code[pc] != I_HALT){
		switch(code[pc]){ 
			case I_PUSHI : 
				sp++;
				stack[sp] = code[pc+1];
				pc = pc+2;
				#if DEBUG
				printf("\nstack pushi %d %d\n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_MULT :
				stack[sp-1] = stack[sp-1] * stack[sp];
				sp--;
				pc++;
				#if DEBUG
				printf("\nstack mult %d %d\n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_ADD : 
				stack[sp-1] = stack[sp-1] + stack[sp];
				sp--;
				pc++;
				#if DEBUG
				printf("\nstack add %d %d\n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_PUSH :
				sp++;
				stack[sp] = var[code[pc+1]];
				pc = pc+2;
				#if DEBUG
				printf("\nstack push %d %d \n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_POP : 
				var[code[pc+1]] = stack[sp];
				sp--;
				pc = pc+2;
				#if DEBUG
				printf("\nstack pop %d %d\n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_EQ :
				if(stack[sp]==stack[sp-1]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				#if DEBUG
				printf("\nstack eq %d %d \n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_J :
				pc = code[pc+1];
				#if DEBUG
				printf("\nstack j %d %d\n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_JF :
				if(stack[sp] == 0){
					pc = code[pc+1];
					sp--;
				}
				else{
					pc = pc + 2;
					sp--;
				}
				#if DEBUG
				printf("\nstack jf2 %d %d \n", stack[sp], stack[sp-1]);
				#endif
				break;
			case I_AND :
				stack[sp-1] = stack[sp-1] && stack[sp];
				sp--;
				pc++; //ajouté
				break;
			case I_OR :
				stack[sp-1] = stack[sp-1] || stack[sp];
				sp --;
				pc++; //ajouté
				break;
			case I_LS :
				if(stack[sp-1] < stack[sp]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				break;
			case I_GT :
				if(stack[sp-1] > stack[sp]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
				break;
			case I_NOT :
				stack[sp] = !(stack[sp]);
				pc++; //ajouté
				break;

		}
	}
}


void readBin(char* FileName){
	char line[100];
	int nbInst;
	int i;
	int co;
	int v;
	FILE* file = fopen(FileName, "r");
	fgets(line, 100, file);
	sscanf(line, "%d", &nbInst);
	for (i=0;i<nbInst;i++){
		fscanf(file,"%d: %d",&co, &v);
		code[co] = v;
		#if DEBUG
		printf("\ncode[co] %d \n", code[co]);
		#endif
	}
}


int main(int argc, char** argv){
	//Premier test avec un code écris à la main
	/*code[0] = I_PUSHI;
	code[1] = 1;
	code[2] = I_PUSHI;
	code[3] = 2;
	code[4] = I_PUSHI;
	code[5] = 3;
	code[6] = I_MULT;
	code[7] = I_ADD;
	code[8] = I_HALT;*/
	var[0] = 5;
	var[1] = 34;
	//Second test avec un fichier .txt que l'on transmet au programme (./vm_codops fichier.txt)
	readBin(argv[1]);
	run();
	printf("%d\n", var[1]); //On affiche B
	return 0;
}