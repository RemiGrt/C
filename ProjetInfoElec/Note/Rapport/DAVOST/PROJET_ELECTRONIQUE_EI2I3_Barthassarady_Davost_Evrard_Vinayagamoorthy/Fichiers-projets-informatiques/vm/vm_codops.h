/**
 * @author Ghislain DAVOST & Ludovic EVRARD
 * @brief TP8 
 * @date 7/02/2017	
 */

#ifndef VM_CODOPS
#define VM_CODOPS


#define I_ADD 	1
#define I_SUB 	2
#define I_MULT 	3

#define I_AND	8
#define I_OR	9
#define I_NOT	10
#define I_EQ	11
#define I_LS	12
#define I_GT	13

#define I_INC	14
#define I_DEC	15

#define I_PUSH 	100
#define I_PUSHI 101
#define I_POP 	102 

#define I_JP 	200
#define I_JF 	201

#define I_HALT 	403

#define I_END 	1000

void read_bin(char* filename);
void run();
void ars( int nb_X);
void grafcet_interuption();
#endif 
