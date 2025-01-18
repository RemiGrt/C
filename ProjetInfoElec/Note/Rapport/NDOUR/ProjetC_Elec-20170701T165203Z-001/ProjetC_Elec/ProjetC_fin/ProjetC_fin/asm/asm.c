#include <stdlib.h>
#include <stdio.h>
#include "vm_codops.h"

void parseAsm(FILE *fin);
int main(int argc, char **argv)
{
// Ouverture du fichier
FILE* fin = fopen ("grafcet.asm", "r");
	
  if ( fin == NULL)
	{ 
	  printf ("Le fichier est vide\n");
	}

// Construction du dictionnaire d'instruction

//addInstructionName(...)

// Parseur phase 1
parseAsm(fin);

// Parseur phase 2
//resolveReferences();

// Génération du code
//generateBinary(fout);
fclose(fin);
return 0;
}

void parseAsm(FILE *fin)
{  //char *labelname;
   //int addr;
   char *i;
   char str1[100];
   while( i!="end")
   {
	
	/*if (i==":")
	{ addLabel(labelname,addr);}*/
	if (i==":")
	{ str1[100]=fgets (str1,100,fin);
	  printf ("%s",str1);}	
	i++;
   }
}

/*void addLabel(char *labelname,int addr)
{
}

void decodeInstruction(char *line)
{
}

void dumpBinaryCode()
{
}
*/
