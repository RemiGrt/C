#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "vm_codops.h"
#include "asm.h"

/*! \mainpage Assembleur
 *
 * \section intro_sec Introduction
 *
 * 
 * 
 * Ce programme permet d'assembler un fichier assembleur en bytecode
 * Utilisation en console: : ./asm fichierIn.asm fichierOut.bin
 *
 * \section Compilation
 * gcc asm.c -o asm
 *
 * \subsection step1 Step 1: Blabla
 *  blabla
 * etc...
 */

// Q1 : Ecrire le code
/*! \brief Complète le tableau codeSegment
 */
void addCode(int v)
{
  //printf("addCode %d (%d)\n",v,currentInst);
  if (currentInst<MAX_CODESEGMENT_SIZE)
    codeSegment[currentInst++]=v;
}


// Q2 : Ecrire le code 
void addInstructionName(char *instname, int opcod, int type, char *format, int nbops)
{
  tabInstructionNames[currentInstructionName].name=strdup(instname);
  tabInstructionNames[currentInstructionName].opcod=opcod;
  tabInstructionNames[currentInstructionName].type=type;
  tabInstructionNames[currentInstructionName].format=strdup(format);
  tabInstructionNames[currentInstructionName].nbops=nbops;
  currentInstructionName++;
}


// Q3 : Ecrire le code
int findLabel(char *labelname)
{
  int i;

  for (i=0;i<currentLabel;i++)
    if (strcmp(labelname,tabLabels[i].label)==0)
      return i;
  return -1;
}

// Q4 : Ecrire le code
void addLabel(char *labelname,int addr)
{
  tabLabels[currentLabel].label=strdup(labelname);
  tabLabels[currentLabel].addr=addr;
  currentLabel++;
}


// Q5 : Ecrire le code
void addReference(char *labelname,int addrInCode)
{
  tabReferences[currentRef].label=strdup(labelname);
  tabReferences[currentRef].addrInCode=addrInCode;
  currentRef++;
}

// Q6 : Ecrire le code
void resolveReferences()
{
  int i,fl;

  for (i=0;i<currentRef;i++)
    {
      fl=findLabel(tabReferences[i].label);
      codeSegment[tabReferences[i].addrInCode]=tabLabels[fl].addr;
    }
}

/*! \brief La fonction decodeInstruction(char *line) est appelee par la boucle
// principale d'analyse lorsque la ligne d'assembleur lue n'est pas une
// (pas de : dans la ligne). Cette fonction fait le gros du travail
// de la passe 1, en identifiant le type de l'instruction, en faisant
// le decodage supplementaire, en appelant addCode() pour remplir codeSegment
// et en ajoutant des references si l'instruction decodee fait reference
// a une etiquette encore inconnue
*/ 
void decodeInstruction(char *line)
{
  int i,j,l,k,pos,comp;
  char *p;
  int int_operand;
  int found=0;
  char dummy[25];
  char string_operand[256];
  char string_label[25];
  char instname[25];

  // This stuff just to get the instruction name in the instname string
  pos=0;
  l=0;
  // isalpha : renvoie 1 si l'argument est alphabetic
  while (!isalpha(line[pos])) 
    pos++;
  while (isalpha(line[pos]))
    instname[l++]=line[pos++];
  instname[l++]=0;
  //printf("instname=|%s|\n",instname);

  for (i=0;i<currentInstructionName;i++)
    {
      //printf("tabname=|%s| ",tabInstructionNames[i].name);
      comp=strcmp(instname,tabInstructionNames[i].name);
      //printf("comp=|%d|\n",comp);
      if (comp==0)
        {
          switch(tabInstructionNames[i].type)
            {
              // no operands, just add the codop to the code
              // nothing to resolve
            case 0:
              found=1;
              addCode(tabInstructionNames[i].opcod);
              break;
              // one operand, of type integer
              // nothing to resolve
            case 1:
              found=1;
              sscanf(line,tabInstructionNames[i].format,dummy,&int_operand);
              addCode(tabInstructionNames[i].opcod);
              addCode(int_operand);
              break;
              // one operand, and it's a label
              // check if there is something to resolve later
            case 3:
              found=1;
              sscanf(line,tabInstructionNames[i].format,dummy,string_label);
              addCode(tabInstructionNames[i].opcod);
              int fl=findLabel(string_label);
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
  if ((i==currentInstructionName) && (found==0))
    {
      printf("Syntax error with line %s",line);
      exit(1);
    }
}

/*! \brief Cette fonction parseAsm(FILE *fin) parcourt les lignes du fichier
// source assembleur tant qu'elle n'a pas rencontre de ligne avec
// "end" a l'interieur. Pour chaque ligne il y a deux cas de figure:
// - si la ligne de texte contient un :, il s'agit d'une etiquette et
//   on la declare
// - sinon, il s'agit d'une instruction et on appelle decodeInstruction()
*/
int parseAsm(FILE *fin)
{
  char line[100];

  fgets(line,100,fin);
  while (strstr(line,"end")==NULL)
    {
      printf("%s",line);

      if (line[0]=='#')
        {
        }
      else
        {
          /* if line contains ':', it's a label, and declare it as such*/
          char *p=strstr(line,":");
          if (p!=NULL)
            {
              *p='\0';	
              //printf("addLabel %s %d\n",line,currentInst);
              addLabel(line,currentInst);
            }
          else
            {
              decodeInstruction(line);
              //printf("currentInst=%d\n",currentInst);
            }
        }

      fgets(line,100,fin);
    }
  return 0;
}

// Q9 : Ecrire des fonctions de mise au point permettant d'afficher
// les etiquettes et les references
void printLabels()
{
  int i;

  for (i=0;i<currentLabel;i++)
    printf("%5.5d : %s\n",tabLabels[i].addr,tabLabels[i].label);
}

// Q10 : Completer la fonction suivante, qui permet de desassembler
// le code genere.
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

// Q11 : Ecrire la fonction permettant de genere le fichier langage
// machine a partir du tableau codeSegment, complet apres les
// deux passes d'assemblage
void generateBinary(FILE *fout)
{
  int i;

  fprintf(fout,"%d\n",currentInst);
  for (i=0;i<currentInst;i++)
    fprintf(fout,"%d:%d\n",i,codeSegment[i]);
}

// Cadeau : On vous donne le programme principale. Je sais, je sais,
// ma bonte me perdra.
int main(int argc, char **argv)
{
  if (argc!=3)
    {
      printf("Usage : asm infile.asm outfile.bin\n");
    }
  FILE *fin=fopen(argv[1],"r");
  if (fin==NULL)
    printf("Error opening read file %s\n",argv[1]);

  currentInstructionName=0;
  addInstructionName("add", OP_ADD, 0, "", 0);
  addInstructionName("sub", OP_SUB, 0, "", 0);
  addInstructionName("mult", OP_MULT, 0, "", 0);
  addInstructionName("div", OP_DIV, 0, "", 0);
  addInstructionName("neg", OP_NEG, 0, "", 0);
  addInstructionName("and", OP_AND, 0, "", 0);
  addInstructionName("or", OP_OR, 0, "", 0);
  addInstructionName("not", OP_NOT, 0, "", 0);
  addInstructionName("eq", OP_EQ, 0, "", 0);
  addInstructionName("ls", OP_LS, 0, "", 0);
  addInstructionName("gt", OP_GT, 0, "", 0);
  addInstructionName("push", OP_PUSH, 1, "%s %d", 1);
  addInstructionName("pushi", OP_PUSHI, 1, "%s %d", 1);
  addInstructionName("pop", OP_POP, 1, "%s %d", 1);
  addInstructionName("jp", OP_JP, 3, "%s %s", 1);
  addInstructionName("jf", OP_JF, 3, "%s %s", 1);
  addInstructionName("halt", OP_HALT, 0, "", 0);

  currentLabel=0;
  currentInst=0;

  printf("First assembly phase (analyze and decode instructions)..\n");
  // Cette fonction parseAsm(FILE *fin) parcourt les lignes du fichier
  // source assembleur tant qu'elle n'a pas rencontre de ligne avec
  // "end" a l'interieur. Pour chaque ligne il y a deux cas de figure:
  // - si la ligne de texte contient un :,il s'agit d'une etiquette et
  //   on la declare, on appelle addLabel(line,currentInst);
  // si on trouve #, c'est un commentaire
  // - sinon, il s'agit d'une instruction et on appelle decodeInstruction()
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
