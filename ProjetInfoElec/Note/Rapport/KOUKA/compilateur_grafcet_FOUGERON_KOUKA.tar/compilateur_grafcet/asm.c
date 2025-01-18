#include <stdio.h>
#include <stdlib.h>
#include "vm_codops.h"
#include <string.h>
#define MAX_IDENTS_SIZE 100
#define MAX_LABELS_SIZE 100

int cptInstr=0;
int currentInst=0;
int line=0;

void addInstructionName(char* name,int OP_CODE,int type,char* format,int nbops);
void printdico();
void liberer_dico();
void parseAsm(FILE *fin);


struct instructionName {
//char name[50];
char *name;
// Le nom de l'instruction
int OP_CODE;
// son codop, extrait de vm_codops.h
int type;
// son type
char *format;
// son format
int nbops;
// le nombre d'operandes de l'inst
} tabInstructionName[MAX_IDENTS_SIZE];


struct label {
	char*label[20];
	int addr;
} tabLabels[MAX_LABELS_SIZE];
int currentLabel;

void addlabel(char*labelName, int addr){
	tabLabels[currentInst].addr=line;
	currentInst++;
}


		




 


	
int main(int argc,char**argv){
	//ouverture du fichier
	//FILE *fichier = fopen("grafcet_interpreteur.asm","r");

	printf("\nConstruction de dictionnaire\n");

	//Instuction de type 0

	addInstructionName("add", I_ADD, 0, "", 0);
	//addInstructionName("sub", I_SUB, 0, "", 0); Connais pas les valeurs
	addInstructionName("mult", I_MULT, 0, "", 0);
	//addInstructionName("div", I_DIV, 0, "", 0); Connais pas les valeurs
	//addInstructionName("neg", I_NEG, 0, "", 0);
	//addInstructionName("and", I_AND, 0, "", 0);
	//addInstructionName("or", I_OR, 0, "", 0);
	//addInstructionName("not", I_NOT, 0, "", 0);
	//addInstructionName("eq", I_EQ, 0, "", 0);
	//addInstructionName("ls", I_LS, 0, "", 0);
	//addInstructionName("gt", I_GT, 0, "", 0);
	addInstructionName("halt", I_HALT, 0, "", 0);
	
	//Instruction de type 1

	addInstructionName("push", I_PUSH, 1, "%s %d", 1);
	addInstructionName("pop", I_POP, 1, "%s %d", 1);
	addInstructionName("pushi", I_PUSHI, 1, "%s %d", 1);	


	// Instruction de type 3

	addInstructionName("jp", I_J, 3, "%s %s", 1);
	addInstructionName("jf", I_JF, 3, "%s %s", 1);
	//cptInstr =0;
	printdico();

	liberer_dico();
	//parseAsm(grafcet_interpreteur);
	return 0;	
}


void addInstructionName(char* name,int OP_CODE,int type,char* format,int nbops){
	
	
	//printf("\n on ajoute un nom");
	tabInstructionName[cptInstr].name = malloc(sizeof(char)*strlen(name));
	strcpy(tabInstructionName[cptInstr].name, name);
	
	//printf("\n on ajoute lopcode");
	tabInstructionName[cptInstr].OP_CODE=OP_CODE;
	

	//printf("on va ajouter le type");
	tabInstructionName[cptInstr].type= type;

	//printf("on va ajouter l format");
	tabInstructionName[cptInstr].format= malloc(sizeof(int)*strlen(format));
	strcpy(tabInstructionName[cptInstr].format,format);

	//printf("on a ajouter le nbops");
	tabInstructionName[cptInstr].nbops= nbops;
	
	
	cptInstr++;

 }


 void printdico(){
	int i=0; 
	for (i=0;i<cptInstr;i++){
		printf("\n%s", tabInstructionName[i].name);
		printf("\t%d", tabInstructionName[i].OP_CODE);
		printf("\t%d",tabInstructionName[i].type);
		printf("\t%s", tabInstructionName[i].format);
		printf("\t%d",tabInstructionName[i].nbops);
	 }
 }


 void liberer_dico(){
	int i = 0;
	for(i=0;i<cptInstr;i++){
		free(tabInstructionName[cptInstr].name);
		free(tabInstructionName[cptInstr].format);
	}
	printf("\nLe dictionnaire est libéré\n ");
 }


/*void parseAsm(FILE *fin){
	
	char line[100];//declaration du tab
	fgets (line,100,fin);//lit les caract du fichier et les range dans line
	
	while (line != END){
		if(line==:){
			
			addlabel();
		}
		else if (line==#){
			
			printf("commentaire");
		}
		else{
			
			decodeInstruction(line);
		}	
	}
}*/	



	
	 
