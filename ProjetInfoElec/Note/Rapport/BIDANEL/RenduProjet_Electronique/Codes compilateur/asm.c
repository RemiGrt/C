/********************************************************************************
|   Nom fichier : asm.c
|   auteurs: BIDANEL Matthieu FRIAA Chiheb
|   
|   Descriptions : Assembleur
|   
|   Commentaires : Permet de générer un code binaire lisible par la machine virtuelle à partir d'un grafcet
|
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_codops.h"

#define DEBUG 0

#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 1000

#define MAX_CODE_SIZE 1000

int code[100]; //Tableau contenant le code à traiter
int i;
char string[50]; //tableau contenant ce qu'on lit
int line;
int row = 1;
int currentLabel; //incrementer le compteur de label
int currentInst = 0;
int currentInstrName = 0;

void addlabel(char* labelName, int addr);
void pars(char* FileName);
void debugAddLabel(void);
void decodeInstruction(char* string);

//Permet d'ajouter du code au tableau "code"
void addCode(int v)
{
        if (currentInst<MAX_CODE_SIZE)
                code[currentInst++]=v;
}


//Fonction pour lire le fichier asm
//3 types à differencier : commentaires / instructions / étiquettes (toto)
void pars(char* FileName)
{

	FILE* file = fopen(FileName, "r");
	
	line = 0;

	while(strstr(string, "END") == NULL)
	{

		#if DEBUG
		printf("\nNouvelle itération while()"); 
		#endif


		fgets(string, 20, file);

		#if DEBUG
		printf("\nString : %s", string);
		#endif

		if(strstr(string, ":") != NULL)
		{
			#if DEBUG
			printf("Numero ligne : %d\n", line);
			#endif

			addlabel(string, line);

			#if DEBUG
			printf("Etiquette\n");
			printf("\ncurrentInst : %d", currentInst);
			#endif

		}
		else if(strstr(string, "#") != NULL)
		{
			#if DEBUG
			printf("Commentaire\n");
			#endif
		}
		else
		{
			#if DEBUG
			printf("Instruction\n");
			#endif
			decodeInstruction(string);
			row++;
		}

		line++; 

	}
	#if DEBUG
	printf("\n");
	#endif
	
	fclose(file);
}

//On défini la structure d'un label
struct label{
	char label[20];
	int addr;
}tabLabels[MAX_LABELS_SIZE]; 

//Ajoute les labels au tableau "tabLabels"
void addlabel(char* labelName, int addr)
{
	strcpy(tabLabels[currentInst].label, labelName);
	tabLabels[currentInst].addr = line;
	currentInst++;

}

//Permet de vérifier la fonction précédente
void debugAddLabel(void)
{
	int k;
	for(k=0; k<currentInst; k++)
	{
		printf("\nEtiquette n°%d => %s / Adresse : %d\n", k, tabLabels[k].label, tabLabels[k].addr);
	}
}

//Cette partie a pour but de résoudre les références de chaque label
//Cette partie a été empruntée à M.Pecheux mais ne semble pas compatible avec notre programme
//////////////
int findLabel(char *labelname)
{
        int i;

        for (i=0;i<currentLabel;i++)
                if (strcmp(labelname,tabLabels[i].label)==0)
                        return i;
        return -1;
}


struct ref {
	char *label;
	int addrInCode;
} tabReferences[MAX_LABELS_SIZE]; 
int currentRef;

void addReference(char *labelname,int addrInCode)
{
	tabReferences[currentRef].label=strdup(labelname);
	tabReferences[currentRef].addrInCode=addrInCode;
	currentRef++;
}

void resolveReferences()
{
        int i,fl;

        for (i=0;i<currentRef;i++)
        {
                fl=findLabel(tabReferences[i].label);
                code[tabReferences[i].addrInCode]=tabLabels[fl].addr;
        }
}
//////////////

//On défini une structure pour les instructions
struct instructionName{
	char name[20]; //Le nom de l'instruction
	int opcod; //Son codop, extrait de vm_codops.h
	int type; //Son type
	char format[20]; //Son format
	int nbops; //Le nombre d'operandes de l'inst
}tabInstructionNames[MAX_IDENTS_SIZE];

//Permet d'ajouter une instruction à la bibliothèque des instructions
void addInstructionName(char *name, int opcod, int type, char *format, int nbops){
	strcpy(tabInstructionNames[currentInstrName].name, name);
	tabInstructionNames[currentInstrName].opcod = opcod;
	tabInstructionNames[currentInstrName].type = type;
	strcpy(tabInstructionNames[currentInstrName].format, format);
	tabInstructionNames[currentInstrName].nbops = nbops;
	currentInstrName++;
}
 
 //Debug la fonction précédente
void debugAddInstructionName(void)
{
	int l;
	for(l=0; l<currentInstrName; l++)
	{
		printf("\nLigne : %d / Instruction : %s / Opcod : %d / Type : %d / Format : %s / nbops : %d \n", l, tabInstructionNames[l].name, tabInstructionNames[l].opcod, tabInstructionNames[l].type, tabInstructionNames[l].format, tabInstructionNames[l].nbops);
	}
}	

//Permet de décoder une instruction, cad de trouver le code correspondant
void decodeInstruction(char* string){
	int m;
	int int_operand;
	char dummy[25];
	char string_label[25];
	for (m=0;m<currentInstrName; m++)
	{
		printf("%s", string);
		if (!(strstr(string, tabInstructionNames[m].name) == NULL))
		{
			switch (tabInstructionNames[m].type)
			{
				case 0 :
					addCode(tabInstructionNames[m].opcod);
					return;
				break;
				case 1 :
					sscanf(string, tabInstructionNames[m].format, dummy, &int_operand);
					addCode(tabInstructionNames[m].opcod);
					row++;
					addCode(int_operand);
					return;
				break;
				case 3 :
					sscanf(string, tabInstructionNames[m].format, dummy, string_label);
					addCode(tabInstructionNames[m].opcod);
					row++;
					int fl=findLabel(string_label);
					if(fl!=-1)
						addCode(tabLabels[fl].addr);
					else
					{
						addReference(string_label,currentInst);
						addCode(-1);
					}
					return;
				break;
			}
		}
	}
	
}


//Permet de génerer le fichier binaire une fois toutes les instructions et les labels résolus
void generateBinary(FILE *fout)
{
	int i;

	fprintf(fout,"%d\n",currentInst);
	for (i=0;i<currentInst;i++)
		fprintf(fout,"%d:%d\n",i,code[i]);
}





int main(int argc, char** argv){

	addInstructionName("ADD", I_ADD, 0, "", 0);
	addInstructionName("MULT", I_MULT, 0, "", 0);
	addInstructionName("PUSHI", I_PUSHI, 1, "%s %d", 1);
	addInstructionName("HALT", I_HALT, 0, "", 0);
	addInstructionName("PUSH", I_PUSH, 1, "%s %d", 1);
	addInstructionName("POP", I_POP, 1, "%s %d", 1);
	addInstructionName("EQ", I_EQ, 0, "", 0);
	addInstructionName("JF", I_JF, 3, "%s %s", 1);
	addInstructionName("J", I_J, 3, "%s %s", 1);
	addInstructionName("AND", I_AND, 0, "", 0);
	addInstructionName("OR", I_OR, 0, "", 0);
	addInstructionName("LS", I_LS, 0, "", 0);
	addInstructionName("GT", I_GT, 0, "", 0);
	addInstructionName("NOT", I_NOT, 0, "", 0);
	#if DEBUG
	debugAddInstructionName();
	#endif
	
	pars(argv[1]);

	resolveReferences();
	
	FILE* fichierbin = fopen("fichier.bin", "w");

	generateBinary(fichierbin);

	fclose(fichierbin);
	
	
	#if DEBUG
	debugAddLabel();
	#endif


	return 0;

}