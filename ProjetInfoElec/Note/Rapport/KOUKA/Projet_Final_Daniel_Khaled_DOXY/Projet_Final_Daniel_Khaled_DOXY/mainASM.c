# include <stdio.h>
# include "asm.h"
# include "vm_codops.h"


int main(int argc, char **argv)
{
	
	addInstructionName("add", I_ADD, 0, "", 0);
	addInstructionName("sub", I_SUB, 0, "", 0);
	addInstructionName("mult", I_MULT, 0, "", 0);
	addInstructionName("inc", I_INC, 0, "", 0);
	addInstructionName("dec", I_DEC, 0, "", 0);
	addInstructionName("and", I_AND, 0, "", 0);
	addInstructionName("or", I_OR, 0, "", 0);
	addInstructionName("not", I_NOT, 0, "", 0);
	addInstructionName("eq", I_EQ, 0, "", 0);
	addInstructionName("ls", I_LS, 0, "", 0);
	addInstructionName("gt", I_GT, 0, "", 0);
	addInstructionName("halt", I_HALT, 0, "", 0);
	addInstructionName("pushi", I_PUSHI, 0, "", 0);
	addInstructionName("push", I_PUSH, 0, "", 0);
	addInstructionName("pop", I_POP, 0, "", 0);
	addInstructionName("jf", I_JF, 0, "", 0);
	addInstructionName("j", I_J, 0, "", 0);
	
//	addInstructionName();
	parseAsm(argv[1]);			//addLabel				//label::label
								//decodeInstruction		//addCode
														//addReference
														//findLabel
//	resolveReferences();	//findLabel
//	printLabels();
//	dumpBinaryCode();
//	generateBinary(fout);	
	return 0;
}

