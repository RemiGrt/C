#ifndef __ASM_H__
#define __ASM_H__

void addCode(int v);
void addInstructionName(char *instname, int opcod, int ype, char *format, int nbops);
int findLabel (char *labelname);
void addLabel (char *labelname, int addr);
void addReference (char *labelname, int addrInCode);
//void resolveReferences();
void decodeInstruction (char *line);
int  parseAsm( char *f);
//void printlables ();
//void dumpBinaryCode();
//void generateBinary(FILE *fout);
 
#endif
