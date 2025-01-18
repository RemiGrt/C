#ifndef _ex3_ // Si la constante _ex3_ n'est pas déjà définie alors:
#define _ex3_ // définir la constante _ex3_

// Definition d'un type enuméré dont le nom est t_cond.
// Les valeures d'une variable de type t_cond sont définies entre accolades
// La première (EQ) vaudra par défaut 0, la suivante 1, la deuxieme 2...
typedef enum{
  EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL, NV
}t_cond

// Comme précédement.
// Definition d'un type enuméré dont le nom est t_opcode.
// Les valeures d'une variable de type t_opcode sont définies entre accolades
// La première (AND) vaudra par défaut 0, la suivante 1, la deuxieme 2...
typedef enum{
  AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, MVN
}t_opcode

// Définition d'une structure champs de bits pour un registre 
// 32 bits
typedef struct
{
  unsigned int Rm  : 4; // Bits de 0 (LSB) à 3
  signed int Shift : 8; // Bits de 4 à 11
  unsigned int Rd  : 4; // Bits de 12 à 15
  unsigned int Rn  : 4; // Bits de 16 à 19
  unsigned int S   : 1; // Bit 20
  t_opCode OpCode  : 4; // Bits 21 à 24 (de type t_opCode, voir plus haut)
  unsigned int I   : 1; // Bit 25
  unsigned int     : 2; // Bits 26 à 27 (Inaccessible)
  t_cond Cond      : 4; // Bits 28 à 31 (de type t_cond, voir plus haut)
} t_instruction;

#endif // Fin de ifndef _ex3_
