#ifndef ASSEMBLEUR_H
#define ASSEMBLEUR_H
/**
* \file asm.h
* \brief Convertit un fichier assembleur en OPcode.
*        Utilisation: asm.out file.asm file.bin
*/
#define NUM_CMD (16)/*!< Nombre d'opérations */
char *commande[100]={"add","mult","eq","es","ei","or","and","not","pushi","push","pop","jf","j","halt","pause","end"};/*!<nom des commandes*/
int numCommande[100]={0,1,12,13,14,15,16,17,100,101,102,200,201,400,401};/*!<valeur byte code*/
int argument[100]={0,0,0,0,0,0,0,0,1,1,1,2,2,0,0,-2};/*!<id argument (0=0,1=1,-1=undef,-2=end,2 char*)*/
/**
* \fn int nArg(char *mnem)
* \brief prend un mnémonique en paramettre et retourne son nombre d'arguments
* \return argument
*/
int nArg(char *mnem);
/**
* \fn int codeCommande(char *mnem)
* \brief prend un mnémonique en paramettre et retourne sa valeur OPcode
* \return numCommande
*/
int codeCommande(char *mnem);
#endif //ASSEMBLEUR_H
