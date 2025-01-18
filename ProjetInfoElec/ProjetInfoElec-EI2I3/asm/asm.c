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

}


// Q2 : Ecrire le code 
void addInstructionName(char *instname, int opcod, int type, char *format, int nbops)
{

}


// Q3 : Ecrire le code
int findLabel(char *labelname)
{

}

// Q4 : Ecrire le code
void addLabel(char *labelname,int addr)
{

}


// Q5 : Ecrire le code
void addReference(char *labelname,int addrInCode)
{

}

// Q6 : Ecrire le code
void resolveReferences()
{

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

}

// Q9 : Ecrire des fonctions de mise au point permettant d'afficher
// les etiquettes et les references
void printLabels()
{

}

// Q10 : Completer la fonction suivante, qui permet de desassembler
// le code genere.
void dumpBinaryCode()
{

}

// Q11 : Ecrire la fonction permettant de genere le fichier langage
// machine a partir du tableau codeSegment, complet apres les
// deux passes d'assemblage
void generateBinary(FILE *fout)
{

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
