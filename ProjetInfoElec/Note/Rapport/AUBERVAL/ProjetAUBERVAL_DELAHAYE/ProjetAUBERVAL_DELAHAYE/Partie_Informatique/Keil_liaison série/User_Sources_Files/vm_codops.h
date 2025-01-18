/*************************************************
Fichier : VM_CODOPS.H
Date 	: 07/03/2017
Auteurs : AUBERVAL/DELAHAYE
*************************************************/

#ifndef _VM_CODOPS_H_
#define _VM_CODOPS_H_

/*******************************/
/**********Valeurs :************/
/*******************************/

#define 	I_PUSHI  	100	// instruction pushi
#define 	I_MULT  	1	// instruction mul
#define 	I_ADD   	0	// instruction add
#define		I_HALT 		400  	// instruction halt

#define 	I_PUSH  	101	// instruction push
#define 	I_POP  		102	// instruction pop  prend dans stack[sp] et met dans variable [var]
#define 	I_EQ  		202	// instruction equal
#define 	I_JF 		200	// instruction jump false
#define 	I_J  		201	// instruction jump inconditinnel

#define 	I_GT 		13 	//instruction superieur Greater Than
#define 	I_LS 		12 	//instruction inferieur Lesser than
#define 	I_AND 		8 	//instruction et

/*******************************/
/*******FONCTION_RUN:***********/
/*******************************/

//void run();
//void readBin(char *filename);


#endif
