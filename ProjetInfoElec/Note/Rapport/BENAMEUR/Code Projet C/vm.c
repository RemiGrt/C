#include <stdio.h>
#include "vm_codops.h"
/*
	Fichier VM.c
	Groupe : Sitthivongs - Bissauge
	L'executable de ce code prends un fichier en parametre :
		- un fichier d'entree contenant une liste d'instruction en code bianire avec une norme d'ecriture precise.
		La premiere ligne doit donner le nombre d'instruction totale du code
		Les lignes suivantes contiennent les instructions avec la norme suivante : [n° de l'instruction] : [instruction]
		la derniere ligne du fichier doit etre l'instruction 400, qui donne la fin du code
		(voir le fichier  fout.bin pour exemple)
	Ce code est ensuite lu par la VM afin de fournir deux tableaux de donner
		- le premier correspond a la pile, les instructions vont etre empile et depile en fonction des instructions du code
		c'est dans ce tableau que le code va etre reellemement execute
		- le deuxieme est un tableau de variable (optionnel). Dans notre cas du grafcet, on retrouve la valeur des capteurs/actionneurs/boutons/LEDs/...
*/

// prototypes
void Run();
void ReadBinary(char* file);


int pc = 0;
int sp = -1;
int pile[1000];

int code[100];

int variable[100];
 
int main(int argc, char** argv)
{
// 	code pour tester la machine virtuelle : la solution etant 7
/*	code[0] = I_PUSHI;
	code[1] = 1;
	code[2] = I_PUSHI;
	code[3] = 2;
	code[4] = I_PUSHI;
	code[5] = 3;
	code[6] = I_MULT;
	code[7] = I_ADD;
	code[8] = I_HALT;
	
	Run();
	printf("solution est : %d \n", pile[0]);
	
*/

//	code pour lire un fichier et utiliser la machine virtuelle
	if (argc == 1)
		printf("Argument is missing");

	ReadBinary(argv[1]);

	Run();

	printf("solution est : %d \n", pile[0]);

	return 0;


}

/*
	Fonction ReadBinary(char* file)
	parametre : un fichier
	
	cette fonction lit un fichier contenant toutes les instructions d'un code a executer
	Elle remplit un tableau d'entier interne a ce fichier nomme code[] qui est l'image du code qui se trouve dans le fichier d'entree. Chaque instruction lue dans le fichier d'entree est inscrite dans ce tableau.
	Le tableau code[] est ensuite lu et interprete par la fonction Run()
*/

void ReadBinary(char* file)
{

        FILE* fichier = fopen (file, "r");


        int count ;

        //fscanf(ficher, "%d", &count);
        char line[100];
        fgets(line, 100, fichier);
        sscanf(line, "%d", &count);

	printf("Nombre d'instructions total : %d \n", count);

        int i;
        int index, value;
        for(i = 0; i < count; i++)
        {
                fscanf(fichier, "%d:%d", &index, &value);
                //printf("%d \n", value);
                code[index] = value;
        }

// 	for(i=0; i<count; i++)
//		printf("commande %d : %d \n", i, code[i]);
}



/*
	Fonction Run()
	Cette fonction utilise la tableau code[] rempli par la fonction ReadBinary afin d'interpreter les instructions qui s'y trouve en remplissant 2 tableaux
		- la pile, tableau dans lequel sont stockees les constantes temporaires et les resultats d'autres instructions
		- un tableau de variable contenant la valeur des composants utilises dans le grafcet correspondant au code fourni
	Cette fonction execute le code binaire fourni sur la pile
*/
void Run()
{
	//int i;
        while(code[pc] != I_HALT)
	{
//		printf("pc : %d, sp : %d valeur pile : %d commande : %d \n", pc, sp,pile[sp], code[pc]);
                switch(code[pc])
		{
                        case I_PUSHI:
				sp++;
				pile[sp] = code[pc + 1];
				pc = pc +2;
				break;

			case I_MULT :
				pile[sp - 1 ] = pile[sp - 1] * pile[sp];
				sp --;
				pc ++;
				break;

			case I_ADD :
				pile[sp - 1 ] = pile[sp - 1] + pile[sp];
				sp --;
				pc ++;
				break;
				
		 	 case I_NOT : 
                       		if(pile[sp] == 0)
                       			pile[sp] = 1;
               			else
               				pile[sp] = 0;
               				
       				pc ++;  
       				break;
               				
			case I_AND :
				if (pile[sp] && pile[sp -1])
					pile[sp-1] = 1;
				else 
					pile[sp-1] = 0;
					
				sp --;
				pc ++;     
				break;    
				
			case I_OR :
				if (pile[sp] || pile[sp -1])
					pile[sp-1] = 1;
				else 
					pile[sp-1] = 0;
					
				sp --;
				pc ++;     
				break;

                        case I_EQ :
                                if (pile[sp - 1 ] == pile[sp])
                                        pile[sp-1] = 1;
                                else
                                        pile[sp-1] = 0;

                                sp --;
                                pc ++;
                                break;
                                
                      case I_LS :
                       		if (pile[sp - 1 ] < pile[sp])
                                        pile[sp-1] = 1;
                                else
                                        pile[sp-1] = 0;

                                sp --;
                                pc ++;
                                break;
                                
             	  	case I_LE :
                       		if (pile[sp - 1 ] <= pile[sp])
                                        pile[sp-1] = 1;
                                else
                                        pile[sp-1] = 0;

                                sp --;
                                pc ++;
                                break;
                                
                       case I_GT :
                       		if (pile[sp - 1 ] > pile[sp])
                                        pile[sp-1] = 1;
                                else
                                        pile[sp-1] = 0;

                                sp --;
                                pc ++;
                                break;
                              
			case I_GE :
                       		if (pile[sp - 1 ] >= pile[sp])
                                        pile[sp-1] = 1;
                                else
                                        pile[sp-1] = 0;

                                sp --;
                                pc ++;
                                break;
                                
                        case I_INC :
                		pile[sp] = pile[sp] + 1;
                		pc ++;
                		break;
                		
        		case I_DEC :
        			pile[sp] = pile[sp] - 1;
        			pc ++;
        			break;
    
                        case I_POP :
                                variable[code[pc + 1]] = pile[sp];
                                sp --;
                                pc = pc + 2;    
                                break;

                        case I_PUSH:
                                pile[sp+1] =  variable[code[pc+1]];
                                sp++;
                                pc = pc + 2 ;
                                break;

                        case I_JF :
                                if (pile[sp] == 0)
					pc = code[pc+1] ;
				else 
					pc = pc +2;
                                break;

                        case I_JP :
                                pc = code[pc +1];
                                break;

                        case I_JT :
                               if (pile[sp] == 1)
                                        pc = code[pc+1];
				else 
					pc = pc +2;
                               break;
                               
                }
/*		printf("etat pile \n");
		for(i=0; i<=sp; i++)
			printf("indice %d, %d \n", i, pile[i]);
*/	
	}
}

