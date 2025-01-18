# include <stdio.h>
# include <stdlib.h>
# include "asm.h"
# include "string.h"

int currentLabel;
int currentInstructionNames;
int currentInst;
unsigned int codeSegment[100000];

int  parseAsm( char *f)
{
	printf("parseASM\n");
	FILE *fichier = fopen(f,"r");
	
	char line [100];
	fgets(line,100,fichier);
	while ( strstr ( line,"END")== NULL)
	{
		if ( line[0]=='#')
		{
			printf("ceci est un commentaire\n");
		}
		else
		{
			char *p=strstr(line,":");
			if(p!=NULL)
			{
				printf("ceci est une étiquette\n");
				*p='\0';
				addLabel(line,currentInst);
				
			}
			else
			{
				printf("ceci est une instruction\n");
				//decodeInstruction(line);
			}
		}
		fgets(line,100,fichier);
	}
	return 0;
}

struct instructionName{
	char name[20];
	int opcod;
	int type;
	char format[20];
	int nbops;
} tabInstructionNames[100];

void addInstructionName(char *instname, int opcod, int type, char *format, int nbops)
{
	strcpy(tabInstructionNames[currentInstructionNames].name, instname);
	tabInstructionNames[currentInstructionNames].opcod = opcod ;
	tabInstructionNames[currentInstructionNames].type = type;
	strcpy(tabInstructionNames[currentInstructionNames].format, format);
	tabInstructionNames[currentInstructionNames].nbops = nbops;
	currentInstructionNames++;
}

struct label
{
	char *label;
	int addr;
}tabLabels[1000];

void addLabel(char *labelname, int addr)
{
	tabLabels[currentLabel].label = strdup(labelname);
	tabLabels[currentLabel].addr = addr;
	currentLabel++;
}

int findLabel ( char *labelname)
{
	int i;
	
	for(i=0 ; i<currentLabel ; i++)
	{
		if(strcmp(labelname,tabLabels[i].label)==0)
		{
			return i;
		}
	}
	return -1;
}
/*

void decodeInstruction ( char *line)
{
	
}

void addCode(int v)
{
	
}

void addReference ( char *labelname, int addrInCode)
{
	
}

void resolveReferences()
{
	
}

void printlables ()
{
	
}

void dumpBinaryCode()
{
	
}

void generateBinary(FILE *fout)
{
	
}
*/
