#include <stdlib.h>
#include <stdio.h>
#include "vm_codops.h"
#define DEBUG 1
 
int pc=0;//pointeur de code
int sp=-1; //pointeur de pile
int code [100]; // tableau d'entier des instructions
int stack [100]; // tableau de pile d'execution
int var [100];//tableau des variables

void run(){
	while(code[pc]!=I_HALT)
	{
		switch(code[pc])
		{
			case I_PUSHI:
				# if DEBUG
					printf("run I_PUSHI\n");
				# endif
				sp++; //pointe à la case 0 de la pile
				stack[sp]=code[pc+1]; //valeur de la case 0 = 1
				pc=pc+2;// +2 pour passer au PUSHI suivant
				printf("\nstack[sp]= %d\n",stack[sp]);
			break;
			
			
			case I_PUSH:
				# if DEBUG
					printf("run I_PUSH\n");
				# endif
				sp++; //pointe à la case 0 de la pile
				stack[sp]=var[code[pc+1]]; //affectation de la case 0 = 1
				pc=pc+2;// +2 pour passer au PUSH suivant
			break;
			case I_POP:
				# if DEBUG
					printf("run I_POP\n");
				# endif
				printf("\nvar[1]=%d\n",var[1]);  //Valeur de b avant le changement de valeur
				var[code[pc+1]]=stack[sp];//stoke la première valeur de la pile dans la variable
				printf("\nvar[1]=%d\n",var[1]); //valeur de la pile mise dans le tab de variable
				sp--; //
				pc=pc+2;
			break;
				
			case I_MULT:
				# if DEBUG
					printf("run I_MULT\n");
				# endif
				stack[sp-1]=stack[sp-1]*stack[sp];//on stocke le result de la mult dans la case inférieure de la pile
				sp--; // suppression de 2 cases pour la multiplication
				pc++; // augmentation des index d'instructions  dans le tab de code
			break;
			case I_ADD:
				# if DEBUG
					printf("run I_ADD\n");
				# endif
				stack[sp-1]=stack[sp-1]+stack[sp];//on stocke le result de l'add dans la case inférieure de la pile
				sp--; // suppression de 2 cases pour l'add, dépile
				pc++; // augmentation des index d'instructions  dans le tab de code
			break;
			
			case I_EQ:
				# if DEBUG
					printf("run I_EQ\n");
				# endif
				if(stack[sp]==stack[sp-1]){ //on compare les 2 cases
					stack[sp-1]=0;  //si vrai alors égale à 0
				}else{
					stack[sp-1]=1;//sinon égale à 1
				}
				sp--; // suppression de 2 cases pour l'add, dépile
				pc++; // augmentation des index d'instructions  dans le tab de code
				
			break;

			case I_J:
				# if DEBUG
					printf("run I_J\n");
				# endif
				pc=code[pc+1];//on va à la ligne d'instruction correspondante à pc+1
				//sp--  pas d'operation arithmétique donc pas besoin de la pile

			break;

			case I_JF:
				# if DEBUG
					printf("run I_JF\n");
				# endif
				
				if(stack[sp]==0){ //si la pile est égale à 0 alors
					pc=code[pc+1];//on saute d'une case
					
				}
				else{
					pc = pc+2;
					
				}
			break;
			
			case I_AND:
				stack[sp-1] = stack[sp-1] && stack[sp]; 
				sp--;
				
			break;
			
			case I_OR:
				stack[sp-1] = stack[sp-1] || stack[sp]; 
				sp++;
				
			break;
			
			/*case I_INF:
					if(stack[sp-1] < stack[sp]) stack[sp-1]=1;
					else stack[sp-1]=0;
					sp--;
					pc++;
			break;
			
			case I_SUP:
					if(stack[sp-1] > stack[sp]) stack[sp-1]=1;
					else stack[sp-1]=0;
					sp--;
					pc++;
			break;	*/		
					
			case I_NOT:
					stack[sp]=!stack[sp];
			break;		

			
		}

		# if DEBUG
				if(sp<0 || pc < 0 ){
printf("Erreur \n");
printf("%d,%d \n",pc,sp);

exit(1);				
}


				# endif
		
		
	}
}

void readBin (char* filename)
{
	char line[1000];//declaration du tab
	int nbinst;
	int i,co,v;
	FILE *f=fopen(filename,"r"); //ouverture du fichier en mode lecture
	fgets (line,100,f);//lit les caract du fichier et les range dans le tab
	sscanf(line,"%d",&nbinst);//lecture du chiffre de la première ligne donc 9

	for(i=0;i<nbinst;i++){
		fscanf(f,"%d:%d",&co,&v); //lecture de toutes les lignes du fichier
		code[co]=v; //stockage du premier chiffre dans co et du 2ème dans v
	}
}

int main (int argc,char**argv){

//Tableau du code

/*code[0]= I_PUSHI;
code[1]=1;
code[2]=I_PUSHI;
code[3]=2;
code[4]=I_PUSHI;
code[5]=3;
code[6]=I_MULT;
code[7]=I_ADD;
code[8]=I_HALT;*/
var[0] = 0;	//Valeur de a dans le tableau de variable => a est à l'adresse 0 dans var[]
var[1] = 3 ;	//Valeur de b dans le tableau devariable => b est à l'adresse 1 dans var[]
//readBin(argv[1]); //cette fonction effectue la même chose que ci dessus
run();
return 0;


}



