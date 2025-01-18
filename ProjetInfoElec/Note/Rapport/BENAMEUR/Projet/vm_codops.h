#ifndef _VM_CODOPS_h_
#define _VM_CODOPS_h_

#define I_ADD 1
#define I_SUB 2
#define I_MULT 3
#define I_AND 8
#define I_OR 9
#define I_NOT 10
#define I_EQ 11
#define I_LS 12
#define I_GT 13
#define I_INC 14
#define I_DEC 15
#define I_LE 16
#define I_GE 17
#define I_PUSHI 100
#define I_PUSH 101
#define I_POP 102
#define I_JP 200
#define I_JF 201
#define I_JT 202
#define I_HALT 400

/*
typedef struct s_element
{
        int index;
        char* reference;
        struct s_element* next;
}t_reference;

typedef struct s_element
{
        int index;
        char* etiquette;
        struct s_element* next;
}t_etiquette;

typedef struct 
{
        t_reference reference_debut;
        t_reference reference_courant;
        t_etiquette etiquette_debut;
        t_etiquette etiquette_courant;
}
*/
#endif
