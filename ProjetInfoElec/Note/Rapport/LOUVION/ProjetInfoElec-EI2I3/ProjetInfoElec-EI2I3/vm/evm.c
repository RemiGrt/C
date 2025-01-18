//
// Machine Virtuelle
// evm.c
// A compléter avec votre code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vm_codops.h"

//#include <iostream>
#include <math.h>

#define debug 1

int pc = 0;
int sp = -1;
int stack[100];
int code[100];
int variable[100];
int a = 3, b;
int tab_conversion[32];
int i;

/*void conversion(int entier){

	int i;
	int total_add = 0;

	for(i = 31; i>0; i--){
		if (total_add + 2^i <= entier){
			tab_conversion[i] = 1;
			total_add += 2^i;
		}
		else tab[i] = 0;
	}
}*/

void run(){
	while(code[pc] != I_HALT){
		switch(code[pc]){
			
			case I_PUSHI : //100
			#if debug
				printf("run : PUSHI %d\n", code[pc+1]);
			#endif
				stack[++sp] = code[pc+1];
				pc += 2;
				break;
				
			case I_ADD : //0 
			#if debug
				printf("run : ADD\n");
			#endif
				stack[sp-1] += stack[sp];
				sp--;
				pc ++;
				break;
				
			case I_MULT : //1
			#if debug
				printf("run : MULT\n");
			#endif
				stack[sp-1] *= stack[sp];
				sp--;
				pc++;
				break;
			
			case I_PUSH : // 101
			#if debug
				printf("run : PUSH %d\n", variable[code[pc+1]]);
			#endif
				stack[++sp] = variable[code[pc+1]]; // si a est à l'adresse 32 du tableau variable -> 0:101 1:32
				pc += 2;
				break;
				
			case I_POP : // 102
			
				//sp--;
				variable[code[pc+1]] = stack[sp];
				#if debug
				printf("run : POP %d\n", variable[code[pc+1]]);
			#endif
				pc +=2;
				
			
			break; 
				
			case I_EQ : //12
			#if debug
				printf("run : EQ\n");
			#endif
				
				if (stack[sp-1] == stack[sp]) 
				{
					stack[sp-1] = 1;
				}
				else 
				{
					stack[sp] = 0;
				}
				sp--;
				pc ++;
				break;
				
			case I_JF : //200
			//#if debug
				//printf("run : JF\n");
			//#endif
				
						if (stack[sp] == 0)
							{
								
									printf("run : JF\n");
								
								pc = code[pc+1];
								break;
							}
						else
							{
								
									printf("run : JF mais pas faux\n");
								
								pc += 2;
								break;
							}
						
				
			case I_J : //201
			#if debug
				printf("run : J\n");
			#endif
				pc = code[pc+1];
					break;
				
			case I_DIV : //202
			#if debug
				printf("run : MULT\n");
			#endif
				stack[sp-1] /= stack[sp];
				sp--;
				pc++;
				break;
			
			case I_NEG : //203
			#if debug
				printf("run : NEG\n");
			#endif
				stack[sp] = -stack[sp];
				pc++;
				break;
			
			case I_AND : //300
			#if debug
				printf("run : AND\n");
			#endif
				sp--;
				stack[sp] = stack[sp] && stack[sp+1];
				pc++;
				break;
			
			case I_OR : //301
			#if debug
				printf("run : OR\n");
			#endif
				sp--;
				stack[sp] = stack[sp] || stack[sp+1];
				pc++;
				break;
			
			case I_NOT : //204
			#if debug
				printf("run : NOT\n");
			#endif
				
				stack[sp] = !stack[sp];
				pc++;
				break;
				
			case I_LS : //205
			#if debug
				printf("run : LS\n");
			#endif
				if(stack[sp-1] < stack[sp]) stack[sp] = 1;
				else stack[sp] = 0;
				pc++;
				break;
			
			case I_GT : //206
			#if debug
				printf("run : GT\n");
			#endif
				if(stack[sp-1] > stack[sp]) stack[sp] = 1;
				else stack[sp] = 0;
				pc++;
				break;
		}
	}
}

   /*******************************************/
  /**********Lecture du fichier .bin**********/
 /********et rempli le tableau code[]********/
/*******************************************/
void readBin(FILE* bytecode2){
	
	int nbre_instruction;
	int no_instruction, instruction;
	int i;
	char deux_points;
	
	if (bytecode2 == NULL){	
		printf("Erreur ouverture fichier\n");
	}
	else if (bytecode2 != NULL){
		
		fscanf(bytecode2, "%d", &nbre_instruction); //lecture du nombre d'instruction
		#if debug
			printf("nbre d'instruction : %d\n", nbre_instruction);
		#endif
		for (i = 0; i < nbre_instruction; i++){ // lecture de chaque autre ligne
			fscanf(bytecode2, "%d", &no_instruction); //lecture du n° d'instruction
			if (no_instruction != i) printf("Erreur bytecode\n"); // le nombre lu n'est pas le n° d'instruction
			fscanf(bytecode2, "%c", &deux_points); // lecture des deux points séparant le n° et l'instruction
			fscanf(bytecode2, "%d", &instruction); // lecture de l'instruction
			code[i] = instruction; // remplissage du tableau code[]
			#if debug
				printf("readbin : instruction[%d] code[%d]\n", no_instruction, instruction);
			#endif
		}
	}
	fclose(bytecode2);
}

int main(int argc, char **argv)
{
	
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
		printf("Error opening read file %s\n",argv[1]);
		
	readBin(fin);
	run();
	//printf("stack[0] = %d\n", stack[0]);
	
	for (i = 0; i<20; i++){
		printf("variable[%d] = %d\n",i, variable[i]);
	}
	return 0;
}
