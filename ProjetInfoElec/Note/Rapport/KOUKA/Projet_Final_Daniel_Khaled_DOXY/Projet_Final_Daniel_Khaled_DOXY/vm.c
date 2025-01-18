
# include <stdio.h>
# include "vm_codops.h"

int pc = 0; // indice du tableau
int sp = -1; // indice de la pile D'executon
int code[100];
int stack[100];
int var = -1;
int variable[100];

void readCreateBinASM( char *filename)
{
	char line[100];
	int nbInst;
	int i;
	int co; //equivalent pc
//	int va;
	int v; //equivalent DEFINE 
	FILE *f = fopen(filename,"r");
	fgets(line, 100,f);
	sscanf(line, "%d", &nbInst);
	for(i = 0; i<nbInst; i++)
	{
		fscanf(f, "%d:%d", &co, &v);
		code[co] = v;
	}
}

void run()
{
	while(code[pc] != I_HALT)
	{
		//Debug
		printf("%d %d\n", pc, sp);
		
		switch(code[pc])
		{
			
			case I_PUSHI : sp = sp+1 ;			   
						   stack[sp] = code[pc+1] ; 
						   pc = pc+2;
			break;
			
            case I_PUSH : sp++ ; 
						  stack[sp] = variable[code[pc+1]] ;  
						  pc = pc + 2;    
            break;        

			case I_EQ : if(stack[sp-1]==stack[sp])
						{
							stack[sp-1]=1;
						}
						else
						{
							stack[sp-1]=0;
						}
						sp--;
						pc++;
			break;

			case I_JF : if (stack [sp] == 0)
						{    
							pc = code[pc+1];
						}
						sp = sp -1;
			break;
            
            case I_POP : var++ ; 
						 variable[code[pc+1]]=stack[sp] ;
						 sp--;
						 pc = pc+2;
            break;
						
			case I_J :  pc = code[pc+1];
					//	pc++;
			break;
			
			case I_MULT : stack[sp-1] = stack [sp-1]*stack[sp] ; 
						  sp = sp-1 ; 
						  pc = pc+1;
			break;
			
			case I_ADD :  stack[sp-1] = stack [sp-1]+stack[sp] ; 
						  sp  = sp-1; 
						  pc = pc+1;
			break;
			
			case I_SUB :  stack[sp-1] = stack [sp-1]-stack[sp] ; 
						  sp  = sp-1; 
						  pc = pc+1;
			break;
			
			case I_AND : stack[sp-1] = stack[sp-1] && stack[sp];
				         sp--;
			break;
				
			case I_OR : stack[sp-1] = stack[sp-1] || stack[sp];
				        sp --;
			break;
				
			case I_LS : if(stack[sp-1] < stack[sp]) 
						{
						stack[sp-1]=1;
						}
						else 
						{
						stack[sp-1]=0;
						}
						sp--;
						pc++;
			break;
			
			case I_GT : if(stack[sp-1] > stack[sp]) 
						{
						stack[sp-1]=1;
						}
						else 
						{
						stack[sp-1]=0;
						}
						sp--;
						pc++;
			break;
			
			case I_NOT :  stack[sp] = !(stack[sp]);
				          pc ++;
			break;
				
			case I_INC :  stack[sp-1] = stack [sp-1]+1 ; 
						  sp  = sp-1; 
						  pc = pc+1;
			break;
			
			case I_DEC :  stack[sp-1] = stack [sp-1]-1 ; 
						  sp  = sp-1; 
						  pc = pc+1;
			break;
		}
	}
}

int main(int argc, char **argv)
{
	
//remplacé par readBin
//	code[0] = I_PUSHI;
//	code[1] = 1;
//	code[2] = I_PUSHI;
//	code[3] = 2;
//	code[4] = I_PUSHI;
//	code[5] = 3;
//	code[6] = I_MULT;
//	code[7] = I_ADD;
//	code[8] = I_HALT;

	readCreateBinASM(argv[1]); // ./VM nomDuFichier.bin
	run();
	//printf("%d \n", stack[0]);
	return 0;
}

/*********************************************************
 * 
 * V1 avant tout c'est faux!!!!
int main()
{
int i;
int code[9];

code[0] = I_PUSHI;
code[1] = 1;
code[2] = I_PUSHI;
code[3] = 2;
code[4] = I_PUSHI;
code[5] = 3;
code[6] = I_MULT;
code[7] = I_ADD;
code[8] = I_HALT;

	while( code[i] != I_HALT)
	{
		
	}

}
*********************************************************/
