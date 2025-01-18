#include <stdio.h>
#include "vm_codops.h"

/*! \file evm.c
 *
 * \details 
 *
 * \section Présentation
 * 
 * Ce programme permet l'interprètation du bytecode généré par l'assembleur.
 * Son rôle est de manipuler un tableau de variable qui correspond à des entrées et des sorties du système.
 * On peut imaginer que lors de son implémentation sur un microcontroleur.
 * Une case du tableau des variable pourait correspondre à un capteur et une autre un une commande moteur.
 *
 *
 *
 * Il fonctionne en deux parties :
 * - 1ère phase: 
 *       - On parcourt le fichier afin de récupérer l'opcode.
 * - 2ème phase:
 *       - On traduit chaque instruction en manipulant une pile et en actualisant les nouvelles valeurs des variables.
 *
 * \section Compilation
 * - Utilisation en console: ./evm.o safe.bin
 * 
 * - Commande de compilation: gcc evm.c -o evm.o
 *
 * \section Liste_des_fonctions:
 *  - void run(void)
 *  - void read_bin(char *filename)
*/


int pc=0;						//program counter
int sp = -1;						//sommet de la pile					
int code[100];						//tableau du code
int stack[100];						//pile
int variable[100]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40}; //tableau de variable


/*! \brief La fonction run() est la partie principale de la machine virtuelle.
// C'est elle qui va interpréter le tableau d'instruction. Elle va donc parcourir ce tableau
// et réaliser les calculs nécessaires pour chaque instruction afin de connaître les nouvelles valeurs des variables.
*/

void run() 
{
	while(code[pc]!=I_HALT) //tant que la dernière instruction n'est pas atteinte
	{
		switch (code[pc]) //on étudie l'instruction en lecture
		{

			case I_PUSHI :	//si c'est I_PUSHI, on ajoute l'entier qui suit à la pile	
			stack[++sp]=code[pc+1];			
			pc=pc+2;
			printf("%d \n", stack[sp]);		
			break;
		
			case I_ADD : //si c'est I_ADD, on additionne les deux dernières valeurs de la pile
			stack[sp-1]=stack[sp]+stack[sp-1]; //le résultat est placé à la place de la première valeur
			sp--;
			pc++;
			printf("%d \n", stack[sp]);
			break;
		
			
			case I_SUB : //si c'est I_SUB,  on fait la différence entre les deux dernières valeurs de la pile
			stack[sp-1]=stack[sp]-stack[sp-1]; //le résultat est placé à la place de la première valeur
			sp--;
			pc++;
			printf("%d \n", stack[sp]);
			break;

			case I_NEG : //si c'est I_NEG, on inverse la valeur du nombre par exemple si on a 2 on obtiendra -2
			stack[sp]=0-stack[sp]; //on remplace cette valeur par sa nouvelle valeur dans la pile
			pc++;
			printf("%d \n", stack[sp]);
			break;


			case I_MULT : //si c'est I_MULT, on fait la multiplication entre les deux dernières valeurs de la pile
			stack[sp-1]=stack[sp]*stack[sp-1]; //le résultat est placé à la place de la première valeur
			sp--;			
			pc++;
			printf("%d \n", stack[sp]);
			break;
			



			case I_EQ: //si c'est I_EQ, on compare les deux dernières valeurs de la pile
			if (stack[sp-1]==stack[sp]) stack[sp-1]=1; //si elles sont égales on remplace leur valeur par 1
			else stack[sp-1]=0; //sinon par 0
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;
		
			case I_LS: //si c'est I_LS, on compare les deux dernières valeurs de la pile
			if (stack[sp-1]>stack[sp]) stack[sp-1]=1;  //si la dernière valeur est inférieur à la valeur précédentre on remplace leur valeur par 1
			else stack[sp-1]=0; // sinon par 0
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;

			case I_GT : //si c'est I_GT, on compare les deux dernières valeurs de la pile
			if (stack[sp-1]<stack[sp]) stack[sp-1]=1; //si la dernière valeur est supérieur à la valeur précédentre on remplace leur valeur par 1
			else stack[sp-1]=0; //sinon par 0
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;

			case I_NOT: //si c'est I_NOT, on inverse la valeur de la pile, en binaire par exemple si on a 1 on obtiendra 0
			stack[sp]=!(stack[sp]);
			pc++;	
			printf("%d \n", stack[sp]);
			break;

			case I_AND: //si c'est I_AND, on réalise un AND logique entre les deux dernières valeurs de la pile
			if (stack[sp-1]&&stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;

			case I_OR: //si c'est I_OR, on réalise un OR logique entre les deux dernières valeurs de la pile
			if (stack[sp-1]||stack[sp]) stack[sp-1]=1;
			else stack[sp-1]=0;
			sp--;
			pc++;	
			printf("%d \n", stack[sp]);
			break;



			case I_PUSH: //si c'est I_PUSH, on vient placer la variable placée à l'indice qui suit l'instruction, en haut de la pile 
			stack[++sp]=variable[code[pc+1]];
			pc=pc+2;
			printf("%d\n",stack[sp]);
			break;
			
			case I_POP: //si c'est I_POP, on vient place la valeur en haut de la pile dans le tableau des variables à l'indice qui suit l'instruction
			variable[code[pc+1]]=stack[sp];
			printf("%d \n", variable[pc+1]);			
			pc=pc+2;
			break;

			case I_J: //si c'est I_J,
			if(stack[sp] == 1) //si la valeur de la pile est 1, on passe à la ligne de code demandée
			{
				pc=code[pc+1];
			}
			else //sinon on passe à l'instruction suivante
			{
				pc+=2;
			}
			break;
			
			case I_JF: //si c'est I_JF,
			if(stack[sp] != 1) //si la valeur de la pile est 0, on passe à la ligne de code demandée
			{
				pc=code[pc+1];
			}
			else //sinon on passe à l'instruction suivante
			{
				pc+=2;
			}	 
			break;

		
		}
		
		
	}

}

/*! \brief La fonction read_bin(char *filename) va parcourir le fichier.bin
// afin d'y extraire l'opcode, qui sera ensuite interprété par la fonction run() 
*/

void read_bin(char *filename)
{
	int i ; 	
	int indice;
	int nbInst; // nb d'instructions defini a l'adresse 0 du bytecode 
	


	FILE *finput;
	finput=fopen(filename,"r"); //on ouvre le fichier.bin
	
	fscanf(finput,"%d",&nbInst); //on récupère la première valeur qui correspond au nommbre d'instructions présentes dans le fichier
	

	for(i=0; i<nbInst; i++) //on parcourt les lignes du fichier
	{	
				
		//on s'attend à avoir des lignes du type "%d : %d"
		fscanf(finput,"%d",&indice); //on récupère l'indice
		printf("%d : ",indice);
		fgetc(finput);
		fgetc(finput);
		fscanf(finput,"%d",&code[i]); //on récupère l'opcode	
		printf("%d\n",code[i]);	
		
		
	}
	
}

int main(int argc,char**argv[])
{

	read_bin(argv[1]); //appel de read_bin avec le fichier en paramètre
	run(); //appel de la fonction run()

}
