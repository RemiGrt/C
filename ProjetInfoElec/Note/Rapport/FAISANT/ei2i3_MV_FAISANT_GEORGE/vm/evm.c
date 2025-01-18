#include <stdio.h>
#include <stdlib.h>
#include "vm_codops.h"
/**
* @file evm.c
* @brief machine virtuelle pour pc
*/

/**
* @fn void lecture_binaire(char* fichier, int *code)
* @brief charge un fichier binaire dans la mémoire de la VM
* @param fichier nom du fichier
* @param code tableau pour stocker le byte code
*/
void lecture_binaire(char* fichier, int *code);
/**
* @fn void run()
* @brief fait tourner machine virtuelle
*/
void run();
/**
* @var pc
* @brief compteur programme
* @var sp
* @brief compteur de la pille
* @var code
* @brief tableau contenant le code
* @var stack
* @brief pille
* @var variable
* @brief tableau pour les variables
*/
int pc = 0, sp = -1;
int code[1000] = {0}, stack[100] = {0}, variable[100] = {0};

int main(int argc,char **argv)
{
   // if (argc > 1)
    {
        lecture_binaire("asm.bin"/*argv[1]*/,code);
        run();
        printf("Resultat %d\n",stack[sp]);
    }
    return 0;
}
void run()
{
    while(code[pc]!=400)
    {
		printf("pc:%d\tsp:%d\n", pc,sp);
        switch (code[pc])
        {
            case I_ADD : //add
                stack[sp-1] = stack[sp] + stack[sp-1];
                sp--;
                break;
            case I_MULT : //mult
                stack[sp-1] = stack[sp] * stack[sp-1];
                sp--;
                break;
            case I_PUSHI : //pushi
                stack[++sp] = code[++pc];
                break;
            case I_HALT : //halt
                break;
            case I_PUSH : //push
                stack[++sp] = variable[code[++pc]];
                break;
            case I_EQ : //eq
                if (stack[sp] == stack[sp-1])
                    stack[--sp] = 1;
                else
                    stack[--sp] = 0;
                break;
            case I_ES : //es
                if (stack[sp-1] > stack[sp])
                    stack[--sp] = 1;
                else
                    stack[--sp] = 0;
                break;
            case I_EI : //ei
                if (stack[sp-1] < stack[sp])
                    stack[--sp] = 1;
                else
                    stack[--sp] = 0;
                break;
            case I_OR : //or
                stack[sp-1] = stack[sp] || stack[sp-1];
                sp--;
				break;
            case I_AND : //and
                stack[sp-1] = stack[sp] && stack[sp-1];
                sp--;
				break;
            case I_NOT : //not
                stack[sp] =(stack[sp]==0);
				break;
            case I_POP : //pop
                variable[code[++pc]] = stack[sp--];
                break;
            case I_J : //jump
                pc=code[pc+1];
                continue;
                break;
            case I_JF : //jumpfalse
                if(stack[sp--]==0)
                    {
                    pc=code[pc+1];
                    continue;
                    }
                else
                    pc++;
                break;
            case I_PAUSE :
                scanf(" ");
                break;
			default:
				printf("instructiont: %d, inconnu @:\n pc=%d\n",code[pc], pc);
				return ;
			break;

        }
        pc++;
    }

}

void lecture_binaire(char* fichier, int *code)
{
    FILE *fid = fopen(fichier,"r");
    int n = 0;
    fscanf(fid,"%d",&n);
    int i;
    for(i=0;i<n;i++)
    {
        fgetc(fid); //retour ligne
        fscanf(fid,"%d",&code[i]); //sp
        fgetc(fid); //":"
        fscanf(fid,"%d",&code[i]);
    }
}


