#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include <stdio.h>
#include "vm_codops.h"

/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/


#define MaxCode_size 1000
#define MaxStack_size 100
#define MaxVar_size 100

int code[MaxCode_size];
int stack[MaxStack_size];
int var [MaxVar_size];
int sp;
int pc;	

int main (void)
{
	
	  code[0]= I_PUSH;
	  code[1]=0;
	  code[2]=I_PUSH;
	  code[3]=1;
	  code[4]=I_AND;
	  code[5]=I_POP;
		code[6]=2;
		code[7]=I_HALT;
}
void run()
{
  while(code[pc]!=I_HALT)
	{switch(code[pc])
		{case I_PUSHI: printf("run: I_PUSHI\n");// Remplit le stack par les valeurs 0 1 2 
			stack[++sp]=code[pc+1];
 			sp++; pc=pc+2; break;
		case I_ADD: printf("run: I_ADD\n");
			stack[sp-1]=stack[sp-1]+stack[sp];
			sp++; pc++; break;
		case I_MULT: printf("run: I_MULT\n");
			stack[sp-1]=stack[sp-1]*stack[sp];
			sp--; pc++; break;
		case I_PUSH : printf("run: I_PUSH\n");// On met a dans le stack
			stack[++sp]=var[code[pc+1]];
			pc+=2; break;
		case I_EQ : printf("run: I_EQ\n");// on compare a et pushi 0
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_AND : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=1;} 
			else {
			sp--; 
			    stack[sp]=0;}
			pc++; break;
		case I_OR : printf("run: I_AND\n");// 
			if (stack[sp-1]==stack[sp])
			{	sp--; 
			    stack[sp]=0;} 
			else {
			sp--; 
			    stack[sp]=1;}
			pc++; break;
		case I_JF : printf("run: I_JF\n");
			if (stack[sp]==0){pc= code[pc+1];}  //jump
			else {pc+=2;}
			  break;
		case I_NOT : printf("run: I_NOT\n");// 
			stack[sp]=!stack[sp]; 
			pc++; break;
		case I_POP : printf("run: I_POP\n");// On affecte 1 ou 2 à b
			var[code[pc+1]]=stack[sp-1];
			pc+=2; break;
		case I_J : printf("run: I_J\n");// on écrit -1
			pc=code[pc+1];
			break;
		}
	}
}