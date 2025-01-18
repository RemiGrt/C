#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "vm_codops.h"

#define MAX_CODESEGMENT_SIZE 1000
#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100

/*! \mainpage Projet Informatique
 *
 * \date 30 Juin 2017
 *
 * 
 * \authors Bruno Martinho   &   Teddy Ferreira
 *
 * \section intro_sec Introduction
 *
 * Vous trouverez ici la documentation des fichiers sources de notre Projet Informatique
 *
 * Seuls les fichiers asm.c, graphInterpreter.c et evm.c sont commentés. Les autres fichiers n'étant pas nos réalisations.
 *
 */


/*! \page Assembleur
 *
 * \date 30 Juin 2017
 * 
 * \section intro_sec Introduction
 *
 * Ce programme permet d'assembler un fichier assembleur en bytecode
 *
 * Utilisation en console: : ./asm fichierIn.asm fichierOut.bin
 *
 * \section Compilation
 * gcc asm.c -o asm
 */

/*! \file asm.c
*/
/**
 * \fn addCode(int v)
 * \brief Permet d'ajouter une instruction dans le CodeSegment à la position indiquée par currentInst
 */
void addCode(int v)
{
        if (currentInst<MAX_CODESEGMENT_SIZE)
                codeSegment[currentInst++]=v;
}

/*! \fn addInstructionName(char*instname,int opcod,int type,char *format,int nbops)
 * \brief Permet d'ajouter une instruction à la liste des instructions.
 * Les instructions sont séparées en trois catégories selon leur type
 * Elles sont identifiées par leur nom et leur Op_Cod afin d'y faire référence
 * Le format permet d'appliquer un "masque" lors de la lecture afin d'identifier les différents arguments de l'instruction
 */
void addInstructionName(char *instname, int opcod, int type, char *format, int nbops)
{
        tabInstructionNames[currentInstructionName].name=strdup(instname);
        tabInstructionNames[currentInstructionName].opcod=opcod;
        tabInstructionNames[currentInstructionName].type=type;
        tabInstructionNames[currentInstructionName].format=strdup(format);
        tabInstructionNames[currentInstructionName].nbops=nbops;
        currentInstructionName++;
}

/*! \fn findLabel(char *labelname)
 * \brief Permet de chercher une étiquette irrésolue dans le tableau des étiquettes
 */
int findLabel(char *labelname)
{
        int i;

        for (i=0;i<currentLabel;i++)
                if (strcmp(labelname,tabLabels[i].label)==0)
                        return i;
        return -1;
}

/*! \fn addLabel(char *labelname,int addr)
 * \brief Si le label n'est pas connu, cette fonction ajoute le label et sa position au tableau des étiquettes
 */
void addLabel(char *labelname,int addr)
{
        tabLabels[currentLabel].label=strdup(labelname);
        tabLabels[currentLabel].addr=addr;
        currentLabel++;
}

/*! \fn addReference(char *labelname,int addrInCode)
 * \brief Permet d'ajouter une référence et sa position dans le tableau des références
 */
void addReference(char *labelname,int addrInCode)
{
	tabReferences[currentRef].label=strdup(labelname);
	tabReferences[currentRef].addrInCode=addrInCode;
	currentRef++;
}

/*! \fn resolveReferences()
 * \brief Permet de résoudre les références irrésolues contenues dans le tableau des références
 */
void resolveReferences()
{
        int i,fl;

        for (i=0;i<currentRef;i++)
        {
                fl=findLabel(tabReferences[i].label);
                codeSegment[tabReferences[i].addrInCode]=tabLabels[fl].addr;
        }
}
 
/*! \fn decodeInstruction(char *line)
 * \brief Permet de lire le code une première fois, en ajoutant les instructions dans le tableau Code pour lister les opérations à effectuer
 * Permet également de lister les références et étiquettes inconnues lors du premier passage
 */
void decodeInstruction(char *line)
{
	int j,k;
	int type;
	int entier;
	
	char *instruct;
	instruct = malloc(20);
	char *lab_ref;
	lab_ref = malloc(20);
	sscanf(line,"%s",instruct);
	
	printf("a : %s\n", instruct);
	for(j=0;j<i;j++)
	{
		
		if(strcmp(instruct,tabInstructionNames[j].name)==0)
		{
			type = tabInstructionNames[j].type;
			printf("type : %d\n", type);
			switch(type)
			{
				case 0:
					addCode(tabInstructionNames[j].opcode);
					addrCodeSeg++;
				break;
				
				case 1:
					sscanf(line,"%s%d",instruct,&entier);
					addCode(tabInstructionNames[j].opcode);
					addrCodeSeg++;
					addCode(entier);
					addrCodeSeg++;
				break;
				
				case 3:
					sscanf(line,"%s%s",instruct,lab_ref);
					for(k=0;k<currentLabel;k++)
					{
						if(strcmp(lab_ref,tabLabels[k].label) == 0) //si le label du jump lu est pas un existant je crée la ref
						{
							
							addCode(tabInstructionNames[j].opcode);
							addrCodeSeg++;
							addCode(tabLabels[k].addr);
							addrCodeSeg++;
							break;
						}
						else
						{
							addCode(tabInstructionNames[j].opcode;
							addrCodeSeg++; 
							
							addCode(-1);
							
							tabReferences[currentRef].label = lab_ref;
							tabReferences[currentRef].addrInCode = addrCodeSeg;
							
							addrCodeSeg++;
							currentRef++;
							break;
						}
					}
				break;
			}
		}
	}
	free(instruct);
	free(lab_ref);
}

/*! \fn parseAsm(FILE *fin)
 * \brief Lis l'intégralité du fichier d'entrée et décode les instructions lues
 * Ajoute les étiquettes au tableau des labbels
 * S'arrête lorsque l'instruction lue est I_HALT
 */
void parseAsm(FILE *fin)
{
    char line[MAX_LABELS_SIZE] = ""; // Chaîne vide de taille TAILLE_MAX
	FILE *fichier=fopen(fin, "r");
	if(fichier != NULL)
	{
		fgets(line, MAX_LABELS_SIZE, fichier);
		while(strstr(line,"end") == NULL)
		{
			if (strstr(line,":") != NULL)
			{
				addLabel(line, addrCodeSeg);
			}
			else if(strstr(line,"#") != NULL)
			{
				
			}
			else if(line == "");
 			{

			}
			else
			{
				decodeInstruction(line);
			}
		fgets(line, MAX_LABELS_SIZE, fichier);
		}
	}
}

/*! \fn printLabels()
 * \brief Permet d'afficher les références et étiquettes contenues dans le tableau au moment de l'exécution
 */
void printLabels()
{
	int i;

	for (i=0;i<currentLabel;i++)
		printf("%5.5d : %s\n",tabLabels[i].addr,tabLabels[i].label);
}

/*! \fn generateBinary(FILE *fout)
 * \brief Permet de produire le fichier .bin avec le nombre de lignes en première ligne du fichier, les lignes, 
 * instructions et variables ( Exemple des lignes -> 0:100)
 */
void generateBinary(FILE *fout)
{
	int i;

	fprintf(fout,"%d\n",currentInst);
	for (i=0;i<currentInst;i++)
		fprintf(fout,"%d:%d\n",i,codeSegment[i]);
}

/*! \fn main(int argc, char **argv)
 * \brief Fonction main
 */
int main(int argc, char **argv)
{
	if (argc!=3)
	{
		printf("Usage : asm infile.asm outfile.bin\n");
	}
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
		printf("Error opening read file %s\n",argv[1]);

	addInstructionName("add", I_ADD, 0, "", 0);
	addInstructionName("mult", I_MULT, 0, "", 0);
	addInstructionName("and", I_AND, 0, "", 0);
	addInstructionName("not", I_NOT, 0, "", 0);
	addInstructionName("or", I_OR, 0, "", 0);
	addInstructionName("eq", I_EQ, 0, "", 0);
	addInstructionName("gt", I_GT, 0, "", 0);
	addInstructionName("ls", I_LS, 0, "", 0);
	addInstructionName("pushi", I_PUSHI, 1, "%s %d", 1);
	addInstructionName("push", I_PUSH, 1, "%s %d", 1);
	addInstructionName("pop", I_POP, 1, "%s %d", 1);
	addInstructionName("jf", I_JF, 3, "%s %s", 1);
	addInstructionName("jp", I_J, 3, "%s %s", 1);
	addInstructionName("halt", I_HALT, 0, "", 0);

	parseAsm(fin);
	
	fclose(fin);
	printf("no errors\n");
	printf("Second assembly phase (resolve undefined references)..\n");
	resolveReferences();
	printf("no errors\n");
	printLabels();
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
