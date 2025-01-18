#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "vm_codops.h"


#define TAILLE_MAX_LAB 100
#define TAILLE_MAX_ID 100
#define TAILLE_MAX_CODESEG 1000

unsigned int codeSegment[TAILLE_MAX_CODESEG];
int currentInst;

void addCode(int v)
{
        if (currentInst<TAILLE_MAX_CODESEG)
                codeSegment[currentInst++]=v;
}

struct Nom_instruction {
	char *name;			// Le nom de l'instruction
	int opcod;			// son codop donné à partir de vm_codops.h
	int type;			// son type
	char *format;			// son format
	int nbops;			// le nombre d'operandes de l'inst
} tab_nom_instruction[TAILLE_MAX_ID]; 
int instruction_actuelle;

void ajouter_instruction(char *instname, int opcod, int type, char *format, int nbops)
{
        tab_nom_instruction[instruction_actuelle].name=strdup(instname);
        tab_nom_instruction[instruction_actuelle].opcod=opcod;
        tab_nom_instruction[instruction_actuelle].type=type;
        tab_nom_instruction[instruction_actuelle].format=strdup(format);
        tab_nom_instruction[instruction_actuelle].nbops=nbops;
        instruction_actuelle++;
}

struct label {			
	char *label;
	int addr;
// Structure tres simple qui va contenir le code
// genere. La seule fonction d'acces a ce tableau est
// la fonction
/*
  void addCode(int v), qui ajoute l'instruction v
  a la position courante dans codeSegment. La position
  courante est contenue dans la variable globale currentInst,
  qui est incrementee apres ajout d'une instruction
*/

} tabLabels[TAILLE_MAX_LAB]; 
int currentLabel;

int recherche_label(char *labelname)		// Recherche label dans la table, affiche l'indice si le label est présent
{
        int i;

        for (i=0;i<currentLabel;i++)
                if (strcmp(labelname,tabLabels[i].label)==0)
                return i;
        return -1;
}

void ajouter_label(char *labelname,int addr)			// fonction qui permet d'ajouter un label
{
        tabLabels[currentLabel].label=strdup(labelname);
        tabLabels[currentLabel].addr=addr;
        currentLabel++;
}

struct ref {
	char *label;
	int addrInCode;
} tabReferences[TAILLE_MAX_LAB]; 
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
                fl=recherche_label(tabReferences[i].label);
                codeSegment[tabReferences[i].addrInCode]=tabLabels[fl].addr;
        }
}


 
void decode_Instruction(char *line) //	Cette fonction : Identifie le type de l'instruction, Fait le décodage supplémentaire, Appel addCode pour remplir 						codeSegment (tableau global unsigned int) et Ajoute des références si l'instruction décodée fait référence à une 						étiquette encore inconnue (tableau global)
{
	int i,j,l,k,pos,comp;
	char *p;
	int int_operand;
	int found=0;
	char dummy[25];
	char string_operand[256];
	char string_label[25];
	char instname[25];

	pos=0;
	l=0;
	while (!isalpha(line[pos])) 
		pos++;
	while (isalpha(line[pos]))
		instname[l++]=line[pos++];
	instname[l++]=0;

	for (i=0;i<instruction_actuelle;i++)
	{
		printf("tabname=|%s| ",tab_nom_instruction[i].name);
		comp=strcmp(instname,tab_nom_instruction[i].name);
		if (comp==0)
		{
			switch(tab_nom_instruction[i].type)
			{
				case 0:
					found=1;
					addCode(tab_nom_instruction[i].opcod);
					break;
				case 1:
					found=1;
					sscanf(line,tab_nom_instruction[i].format,dummy,&int_operand);
					addCode(tab_nom_instruction[i].opcod);
					addCode(int_operand);
					break;
				case 3:
					found=1;
					sscanf(line,tab_nom_instruction[i].format,dummy,string_label);
					addCode(tab_nom_instruction[i].opcod);
		                        int fl=recherche_label(string_label);
                        		if (fl!=-1)
                                		addCode(tabLabels[fl].addr);
                        		else
                        		{
                                		addReference(string_label,currentInst);
                                		addCode(-1);
                        		}
					break;
			}
		}
	}
	if ((i==instruction_actuelle) && (found==0))
	{
		printf("Syntax error with line %s",line);
		exit(1);
	}
}

/* Cette fonction parcourt les lignes du fichier source assembleur tant qu'elle n'a pas rencontré de ligne avec "end". Pour chaque ligne il y a 3 cas de figure: si la ligne de texte contient : il s'agit d'une étiquette, on appelle la fonction addLabel
	si on trouve #, c'est un commentaire
	sinon, il s'agit d'une instruction et on appelle la fonction decode_Instruction
*/
int parseAsm(FILE *fin)
{
	char line[100];

	fgets(line,100,fin);
	while (strstr(line,"end")==NULL)
	{
		if (line[0]=='#')
		{
		}
		else
		{
			char *p=strstr(line,":");
			if (p!=NULL)
			{
		 		*p='\0';	
				ajouter_label(line,currentInst);
			}
			else
			{
				decode_Instruction(line);
			}
		}

		fgets(line,100,fin);
	}
	return 0;
}

void Afficher_labels()	// Fonction qui permet d'affichier les différents labels 
{
	int i;

	for (i=0;i<currentLabel;i++)
		printf("%5.5d : %s\n",tabLabels[i].addr,tabLabels[i].label);
}

/* Fonction de désassamblage du code (fonction de vérification)
Elle permet de générer le code assembleur correspondant aux OP_CODE stockés dans codeSegment. Sa sortie peut être en console ou dans un fichier. */

void dumpBinaryCode()
{
	int pc=0;
	int pos;

	while (pc!=currentInst)
	{
		printf("%5.5d: ",pc);
		switch (codeSegment[pc])
		{
                        case OP_ADD:
				printf("add\n");
                                pc++ ; break;
                        case OP_SUB:
				printf("sub\n");
                                pc++ ; break;
                        case OP_MULT:
				printf("mult\n");
                                pc++ ; break;
                        case OP_DIV:
				printf("div\n");
                                pc++ ; break;
                        case OP_NEG:
				printf("neg\n");
                                pc++ ; break;
                        case OP_AND:
				printf("and\n");
                                pc++ ; break;
                        case OP_OR:
				printf("or\n");
                                pc++ ; break;
                        case OP_NOT:
				printf("not\n");
                                pc++ ; break;
                        case OP_EQ:
				printf("eq\n");
                                pc++ ; break;
                        case OP_LS:
				printf("ls\n");
                                pc++ ; break;
                        case OP_GT:
				printf("gt\n");
                                pc++ ; break;
                        case OP_PUSH:
				printf("push %d\n",codeSegment[pc+1]);
                                pc+=2; break;
                        case OP_POP:
				printf("pop %d\n",codeSegment[pc+1]);
                                pc+=2; break;
                        case OP_PUSHI:
				printf("pushi %d\n",codeSegment[pc+1]);
                                pc+=2; break;
                        case OP_JP:
				printf("jp %d\n",codeSegment[pc+1]);
                                pc+=2;
                                break;
                        case OP_JF:
				printf("jf %d\n",codeSegment[pc+1]);
                                pc+=2;
                                break;
                        case OP_HALT:
				printf("halt\n");
                                pc++; break;
			default:
				printf("Instruction inconnue :(\n");
				exit(1);
				break;
		}
	}
}

void generateBinary(FILE *fout) //Fonction qui nous permet de génerer notre fichier .bin
{
	int i;

	fprintf(fout,"%d\n",currentInst);
	for (i=0;i<currentInst;i++)
		fprintf(fout,"%d:%d\n",i,codeSegment[i]);
}

int main(int argc, char **argv)
{
	if (argc!=3)
	{
		printf("Usage : asm infile.asm outfile.bin\n");
	}
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
		printf("Error opening read file %s\n",argv[1]);

	instruction_actuelle=0;
	ajouter_instruction("add", OP_ADD, 0, "", 0);
	ajouter_instruction("sub", OP_SUB, 0, "", 0);
	ajouter_instruction("mult", OP_MULT, 0, "", 0);
	ajouter_instruction("div", OP_DIV, 0, "", 0);
	ajouter_instruction("neg", OP_NEG, 0, "", 0);
	ajouter_instruction("and", OP_AND, 0, "", 0);
	ajouter_instruction("or", OP_OR, 0, "", 0);
	ajouter_instruction("not", OP_NOT, 0, "", 0);
	ajouter_instruction("eq", OP_EQ, 0, "", 0);
	ajouter_instruction("ls", OP_LS, 0, "", 0);
	ajouter_instruction("gt", OP_GT, 0, "", 0);
	ajouter_instruction("push", OP_PUSH, 1, "%s %d", 1);
	ajouter_instruction("pushi", OP_PUSHI, 1, "%s %d", 1);
	ajouter_instruction("pop", OP_POP, 1, "%s %d", 1);
	ajouter_instruction("jp", OP_JP, 3, "%s %s", 1);
	ajouter_instruction("jf", OP_JF, 3, "%s %s", 1);
	ajouter_instruction("halt", OP_HALT, 0, "", 0);

	currentLabel=0;
	currentInst=0;
	
	printf("First assembly phase (analyze and decode instructions)..\n");
	parseAsm(fin);
	fclose(fin);
	printf("no errors\n");
	printf("Second assembly phase (resolve undefined references)..\n");
	resolveReferences();
	printf("no errors\n");
	Afficher_labels();
	printf("Dumping generated binary code (please verify)\n");
	dumpBinaryCode();
	printf("no errors\n");

	FILE *fout=fopen(argv[2],"w");
	if (fout==NULL)
		printf("Error opening write file %s\n",argv[2]);
	generateBinary(fout);
	fclose(fout);

	return 0;
}
