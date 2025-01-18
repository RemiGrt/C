#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "vm_codops.h"

#define DEBUG 1
int pc= 0;
int sp = -1;
int code[100];
int stack[100];
int var[100];



/*int main(int argc, char **argv)
{
	
	code[0]=I_PUSHI;
	code[1]=1;
	code[2]=I_PUSHI;
	code[3]=2;
	code[4]=I_PUSHI;
	code[5]=3;
	code[6]=I_MULT;
	code[7]=I_ADD;
	code[8]=I_HALT;
	
	var[0]=2;

	
	//read_bin(argv[1]);
	//run();
	grafcet_interuption();
	return 0;
}*/

void read_bin(char* filename)
{
	int i=0;
	int v=0;
	int co=0;
	char line[100];
	int nbInstruction;
	FILE *f=fopen(filename,"r");
	fgets(line,100,f);
	sscanf(line,"%d",&nbInstruction);
  
		for(i=0;i<nbInstruction;i++)
		{
			fscanf(f, "%d:%d", &co,&v);
			code[co]=v;
		}	
}


void run()
{
	while(code[pc]!=I_HALT)
	{
		switch(code[pc])
		{
		case I_PUSHI:
			sp++; stack[sp] = code[pc+1]; pc =pc+2;
#if DEBUG
	printf("run: I_PUSHI\n");
#endif
		break;
		case I_MULT:
			stack[sp-1] = stack[sp-1]*stack[sp]; sp--; pc++;
#if DEBUG
	printf("run: I_MULT\n");
#endif
		break;
		case I_ADD:
			stack[sp-1] = stack[sp-1]+stack[sp]; sp--; pc++;
#if DEBUG
	printf("run: I_ADD\n");
#endif
		break;
		case I_PUSH:
		 stack[sp-1]=var[code[pc+1]]; pc+=2; 
#if DEBUG
	printf("run: I_PUSH\n");
#endif
		break;
		case I_EQ:
			if(stack[sp-1]==stack[sp])
			{
				stack[sp-1]=1; 
				pc++;
			}	
			else 						
			{
				stack[sp-1]=0; 
				pc++; 
			}
#if DEBUG
	printf("run: I_EQ\n");
#endif			
		break;
		case I_POP:
			var[code[pc]]=stack[sp]; pc=pc+2;
#if DEBUG
	printf("run: I_POP\n");
#endif
		break;
		case I_JF:
			if(stack[sp]==1)			
				pc++;	
			else		
			{
				pc=code[pc+1];
			}	
			
#if DEBUG
	printf("run: I_JF\n");
#endif
		break;
		case I_JP:
			pc=code[pc+1];	
#if DEBUG
	printf("run: I_J\n");
#endif
		break;
		case I_NOT:
		stack[sp]=!stack[sp];
		break;
		
		case I_AND:
		stack[sp] = stack[sp-1] && stack[sp] ;
		sp--; pc++;
		break;
	
		case I_OR:
		stack[sp] = stack[sp-1] || stack[sp] ;
		sp--; pc++;
		break;
		
		case I_LS:
		if(	stack[sp-1]<stack[sp])	
		{
 			stack[sp]=1; pc++; sp--;
		}
		else 
		{
			stack[sp]=0; pc++; sp--;
		}
		break;

		case I_GT:
		if(	stack[sp-1]>stack[sp])
		{	
 			stack[sp]=1; pc++; sp--;
 		}
		else
		{ 
			stack[sp]=0; pc++; sp--;
		}
		break;
		
	   }
#if DEBUG
	printf("run: stack: 	%d	%d	%d	%d	%d	%d\n",stack[0],stack[1],stack[2],stack[3],stack[4],stack[5]);
	printf("run: variable:  %d	%d	%d	%d	%d	%d\n",var[0],var[1],var[2],var[3],var[4],var[5]);
#endif
	}
	
}


void grafcet_interuption()
{
int stable,e1,e2,e3,e4,
	 appel_e1 =0,appel_e2=0,appel_e3=0,appel_e4=0,
	reponse_e1=0,reponse_e2=0,reponse_e3=0,reponse_e4=0,
	old_e1=0,old_e2=0,old_e3=0,old_e4=0,
	old_but1 = 0,pot=0,but1,but2,old_but2, rise_but1, rise_but2;

	
	e1=1;
	e2=0;
	e3=0;
	e4=0;
	but1=0;
	but2=0;	

	while(1)
	{
		old_but1 = but1;
		old_but2 = but2;
		printf("\n bouton1 :");
		scanf (" %d",&but1);
		printf("\n bouton2 :");
		scanf (" %d",&but2);
		printf("\n potar :");
		scanf (" %d",&pot);
		
		

		if(but1==1 && old_but1==0){
			rise_but1=1;
		}
		else if( but1==0 && old_but1==1) {
			rise_but1=0;
		}
		if(but2==1 && old_but2==0){
			rise_but2=1;
		}
		else if (but2==0 && old_but2==1){
			rise_but2=0;
		}
		
		stable=0;
		appel_e1 =0,appel_e2=0,appel_e3=0,appel_e4=0;
		reponse_e1=0,reponse_e2=0,reponse_e3=0,reponse_e4=0;
		while(stable==0)
		{
		printf("stable %d", stable);
			if (e1==1 && (rise_but1==1 && pot< 128))
			{
				appel_e2=1;
				reponse_e1=1;
				#if DEBUG
					printf("if 1");
			#endif
			}
			
			else if (e2==1 && (rise_but1==1 && pot > 128))
			{
				appel_e3=1;
				reponse_e2=1;
				#if DEBUG
					printf("if 2");
			#endif
			}
			
			else if (e3==1 && (rise_but1==1 && pot< 128))
			{
				appel_e4=1;
				reponse_e3=1;
				#if DEBUG
					printf("if 3");
			#endif
			}
			
			else if (e4==1 && rise_but2==1)
			{
				appel_e1=1;
				reponse_e4=1;
				printf("if 4");
			}
			
			old_e1=e1;
			e1=(appel_e1 || (e1 && !(reponse_e1)));
			old_e2=e2;
			e2=(appel_e2 || (e2 && !(reponse_e2)));
			old_e3=e3;
			e3=(appel_e3 || (e3 && !(reponse_e3)));
			old_e4=e4;
			e4=(appel_e4 || (e4 && !(reponse_e4)));
			
			#if DEBUG
					printf("\n e1: %d		e2: %d		e3: %d		e4: %d \n",e1,e2,e3,e4);
			#endif
			if ((e1==old_e1) && (e2==old_e2) && (e3==old_e3) && (e4==old_e4))
			{
				stable=1;
			}	
		}

	}
}



//3673618@cfatpe08:/home/sasl/encad/pecheux/EI2I/EI2I3/projet_c$ 
