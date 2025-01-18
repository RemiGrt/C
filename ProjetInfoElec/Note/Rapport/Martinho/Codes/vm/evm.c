#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm_codeops.h"
#define M 1000
#define N 100

/*! \page machinevirtuelle Machine Virtuelle
 *
 * \date 30 Juin 2017
 * 
 * \section intro_sec Introduction
 *
 * Ce fichier contient la fonction run(), permettant d'éxecuter le code grafcet stocké
 */

 /*! \file evm.c
 */


int pc = 0; //Program Counter
int sp = -1; //Stack Pointer

int code[M]; // Mémoire
int stack[N]; //pile d'opération
int variable[N]={But0,But1,an0,stable,Old_But0,Old_But1,Appel_e0,Appel_e1,Appel_e2,Appel_e3,Reponse_e0,Reponse_e1,Reponse_e2,Reponse_e3,Old_e0,Old_e1,Old_e2,Old_e3,e0,e1,e2,e3,riseBut0,riseBut1}; //tableau stockant les variables

/*! \fn  run()
 * \brief La fonction run va éxecuter les fonctions conformément aux instructions ordonnées par les valeurs stockées dans le tabelau Code contenant les instructions lues du .bin
 * Ici chaque ligne du tableau Code est lue jusqu'a rencontré l'instruction de fin de lecture I_HALT
 * 		  
 */
void run()
{
	while(code[pc] != I_HALT)
	{
		switch(code[pc])
		{
			case I_PUSHi:
				stack[++sp] = code[pc+1]; 
				pc=pc+2;
				//printf("run: I_PUSHi\n");
			break;

			case I_PUSH:
				stack[++sp] = variable[code[pc+1]]; 
				pc=pc+2;
				//printf("run: I_PUSH\n");
			break;

			case I_ADD:
				stack[sp-1] = stack[sp] + stack[sp-1];
				sp--; 
				pc++;
				//printf("run: I_ADD\n");
			break;

			case I_MULT:
				stack[sp-1] = stack[sp] * stack[sp-1];
				sp--;
				pc++;
			//	printf("run: I_MULT\n");			
			break;

			case I_EQ:
				if(stack[sp]==stack[sp-1])
				{
					stack[sp-1]=1;
				}
				else
				{
					stack[sp-1]=0;
				}
				pc++;
				sp--;
				//printf("run: I_EQ\n");
			break;

			case I_POP:
				var[code[pc+1]] = stack[sp];
				sp--;
				pc = pc+2;
				break;
				//printf("run: I_POP\n");
				//printf("run: variable[%d]:%d\n", code[pc+1], variable[code[pc+1]]);				
			break;
			
			case I_EQ :
				if(stack[sp]==stack[sp-1]) stack[sp-1]=1;
				else stack[sp-1]=0;
				sp--;
				pc++;
			break;
				
			case I_J:
				pc=code[pc+1];
				//printf("run: I_J\n");
			break;		

			case I_JF:
				if(stack[sp] == 0){
					pc = code[pc+1];
					sp--;
				}
				else{
					pc = pc + 2;
					sp--;
				}
				//printf("run: I_JF\n");				
			break;

			case I_AND:
				stack[sp-1] = stack[sp-1] && stack[sp];
				sp--;
				pc++;
				//printf("run: I_AND\n");
			break;

			case I_GT:
				if(stack[sp-1] > stack[sp])
				{
					stack[sp-1]=1;
				}
				else
				{
					stack[sp-1]=0;
				}
				pc++;
				sp--;
				//printf("run: I_GT\n");
			break;

			case I_LS:
				if(stack[sp-1] < stack[sp])
				{
					stack[sp-1]=1;
				}
				else
				{
					stack[sp-1]=0;
				}
				pc++;
				sp--;
				//printf("run: I_LS\n");
			break;

			case I_NOT:
				stack[sp] = ~stack[sp];
				pc++;
				//printf("run: I_NOT\n");
			break;

			case I_OR:
				stack[sp-1] = stack[sp-1] || stack[sp];
				sp --;
				pc++;
				//printf("run: I_OR\n");
			break;
		}
	}	
}

/*! \fn  readBin(char *filename, int *code)
 * \brief La fonction readBin permet de stockées les instructions contenues dans le fichier .bin dans le tableau code pour l'éxecution future de la fonction run()
 * 		  
 */
int* readBin(char *filename, int *code)
{
	int i, j, ligne[N];
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
		printf("Numéro ligne : %d\n", ligne[j]); 
		printf("Contenu ligne : %d\n", code[j]); 
	}
	fclose(fichier);
	return code;
}

int main(int argc, char *argv[])
{
	int i;
	//int variable[]={1,4};
	readBin(argv[1]);
	run(); 
	for(i=0; i<5; i++)
	{		
		printf("variable[%d]:%d\n",i, variable[i]);
	}
	return 0;
}