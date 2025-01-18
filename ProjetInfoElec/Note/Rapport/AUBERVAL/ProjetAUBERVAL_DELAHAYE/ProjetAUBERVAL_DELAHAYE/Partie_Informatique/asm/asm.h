/*! \file asm.h
///! \author Anaïs AUBERVAL
///! \version finale
///! \date 30/06/2017
///! \brief Programme contenant les fonctions nécessaires pour asm.c
///! Principe : Remplir un tableau codeSegment pour qu'en le parcourant on n'ai qu'à écrire son contenu
///! pour générer le fichier binaire
*/

#define MAX_CODESEGMENT_SIZE 1000
#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100

int currentInst; //!< Variable globale indiquant le nombre courant de OPCODES dans codeSegment

int currentInstructionName;

#ifndef _ASM_H_
#define _ASM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm_codops.h"

#define DEBUG 0

int i=0;
///! \brief Nombre d'instructions contenu dans le tableau d'instructions
int currentInst  = 0; 
int codeSegment[100];
///! \brief Nombre de trucs dans codeSegment
int segment=0; 
///! \brief Opcode d'une instruction nouvelle (+1 à chaque fois)
int OP_CODE = 410; 
///! \brief variable servant à resolveReferences
int cpt_ref=0; 

///!\struct tabLabels 
///!\param name[20] Le nom des étiquettes 
///!\param addr Ligne dans le fichier binaire où se trouve le code de l'étiquette
///!\brief On remplit cette structure lorsqu'on rencontre un ":"
struct label {
  char name[20];
  int addr;
} tabLabels[MAX_LABELS_SIZE]; 
int currentLabel=0;

///!\struct ref
///!\param name[20] Le nom des étiquettes 
///!\param addr Ligne dans le fichier binaire où se trouve le code de l'étiquette
///!\brief On remplit le tableau tabReferences après avoir rencontré un jump et on remplit addrInCode au moment de la fonction resolveReferences 
struct ref {
  char name[20];
  int addrInCode;
} tabReferences[MAX_LABELS_SIZE]; 
int currentRef=0;

///!\struct instructionName 
///!\param name[20] Le nom des instructions
///!\param opcode Le code opératoire de l'instruction, voir fichier "vm_codops.h"
///!\param type Le type de l'instruction 0, 1, 2 ou 3 permettant de savoir si il y a des arguments et les types de ces arguments
///!\param format Le format avec lequel on est écrit l'instruction dans l'assembleur
///!\param nbops Le nombre d'argument, souvent un ou aucun.
struct instructionName 
{
	char name[20];	
	int opcode;	
	int type;	
	char format[20];	
	int nbops;	
};

struct instructionName tabInstructionNames[MAX_IDENTS_SIZE];

///!\fn addInstructionName(char *name, int opcode, int type, char *format, int nbops)
///!\param name le nom de l'instruction que l'on ajoute à tabInstructionNames
///!\param opcode l'opcode de l'instruction à ajouter
///!\param type le type de l'instruction à ajouter
///!\param format le format de l'instruction à ajouter
///! \brief Remplissage du tableau tabInstructionNames. En remplissant chaque champ de la structure, on saura comment les 
///! chercher dans le fichier assembleur et comment les restituer dans le fichier binaire
void addInstructionName(char *name, int opcode, int type, char *format, int nbops)
{

	strcpy(tabInstructionNames[currentInst].name, name);
	tabInstructionNames[currentInst].opcode = opcode;
	tabInstructionNames[currentInst].type = type;
	strcpy(tabInstructionNames[currentInst].format , format);
	tabInstructionNames[currentInst].nbops = nbops;
	
	currentInst++;
		
		if (DEBUG){
		if (currentInst >11) {
			for (i=0; i<11;i++){
				if (DEBUG)printf("tabInstructionsNames[%d].name=%s\n",i,tabInstructionNames[i].name);
				if (DEBUG)printf("tabInstructionsNames[%d].opcode=%d\n",i,tabInstructionNames[i].opcode);
				if (DEBUG)printf("tabInstructionsNames[%d].type=%d\n",i,tabInstructionNames[i].type);
				if (DEBUG)printf("tabInstructionsNames[%d].format=%s\n",i,tabInstructionNames[i].format);
				if (DEBUG)printf("tabInstructionsNames[%d].nbops=%d\n",i,tabInstructionNames[i].nbops);
				if (DEBUG)printf("\n \n");
			}
		}
	}
}
///!\fn addLabel(char *labelname,int addr)
///!\param labelname la chaine de caractère de l'étiquette à insérer dans tabLabels
///!\param addr la ligne où on trouve le code l'étiquette dans le binaire
void addLabel(char *labelname,int addr){ 
	char s[20];
	
	sscanf(labelname,"%[^: ]",s); 
	//printf("s(labelname)=%s et addr=%d\n",s,addr); 
	strcpy(tabLabels[currentLabel].name,s);
	tabLabels[currentLabel].addr=addr;
	printf("tabLabels[%d].name=%s\ntabLabels[%d].addr=%d\n",currentLabel,tabLabels[currentLabel].name,currentLabel,tabLabels[currentLabel].addr);
	currentLabel++;
}
///!\fn addCode(struct instructionName instr,int d)
///!\param instr l'instruction à rajouter dans codeSegment 
///!\param d l'argument de l'instruction, si il n'y en a pas d=-1s
///!\brief On remplit CodeSegment selon le type de l'instructions
void addCode(struct instructionName instr,int d)
{
	//int i=segment;
	codeSegment[segment]= instr.opcode;
	if (DEBUG) printf("instr.opcode : %d et codeSegment[%d] : %d\n",instr.opcode,segment,codeSegment[segment]);
	
	if (instr.type==0){  
		if (DEBUG)printf("\nSEGMENT : %d \ncodeSegment[%d] : %d\n",segment,segment,codeSegment[segment]);
		if (instr.opcode!=I_HALT)segment++;
	}
	if (instr.type==1){// C'est à dire qu'elle a un entier comme argument
		codeSegment[++segment]=d;
		if (DEBUG)printf("\nSEGMENT: %d \ncodeSegment[%d] : %d,codeSegment[%d]=%d\n",segment,segment,codeSegment[segment],codeSegment[1+segment],segment);
		segment++;
	}
	//Apparemment segment n'a pas besoin d'être incrémenté -> FAUX
	if (instr.type==3){
		segment++; 
		codeSegment[segment]=d;
		segment++;
	}
}
///!\fn decodeInstruction(char *line)
///!\param line l'instruction qu'on a scanner, à décoder
///!\param d l'argument de l'instruction, si il n'y en a pas d=-1s
///!\brief 1. On cherche l'instruction dans le tableau d'instructions connues
///! 2. On remplit CodeSegment avec l'instruction et son argument si il y en a un
void decodeInstruction(char *line) // Changement du type que renvoie decodeInstruction
{
	int arg;
	char dummy[20];
	char etiquette[20];
	if (DEBUG)printf("line =%s\n",line);
	int i=0;

	while ((strstr(line,tabInstructionNames[i].name)==NULL) && (i<=currentInst)){
		i++;
	}
	
	if (i==currentInst){ // Alors on devrait ajouter une instruction => IMPOSSIBLE si analyse syntaxique 
		if (DEBUG)printf("Cette instruction n'existe pas : PROBLEME !\n");
	}else{
		struct instructionName instr=tabInstructionNames[i];
		if (DEBUG) printf("instr : %s codops : %d type :%d\n",instr.name,instr.opcode,instr.type);
		switch (instr.type) {
			case 0 :
				addCode(instr,-1);
				break;
			case 1 :
				sscanf(line,"%s %d",dummy,&arg);
				addCode(instr,arg);
				break;
			case 3 :
				sscanf(line,"%s %s",dummy,etiquette);
				addCode(instr,-1);
				strcpy(tabReferences[currentRef].name,etiquette);
				currentRef++;
				break;
			default :
				break;
		}
		
		if (DEBUG) printf("La fonction qu'on va ajouter dans Code Segment : %s avec comme argument :%d\n",line,arg);
	}
}
///!\fn parseAsm(char *file)
///!\param file fichier assembleur
/*! \brief Cette fonction parseAsm(FILE *file) parcourt les lignes du fichier
// source assembleur tant qu'elle n'a pas rencontre de ligne avec
// "end" a l'interieur. Pour chaque ligne il y a trois cas de figure:
// - si la ligne de texte contient un :, il s'agit d'une etiquette et
//   on la declare
// - si la ligne de texte contient un "#" : il s'agit d'un commentaire
// - sinon, il s'agit d'une instruction et on appelle decodeInstruction() 
*/
void parseAsm(char *file)
{
	char s[20];
	char s1[20];
	char dummy[20];
	int d=-1;
	//int i=0;

	FILE* f=fopen(file,"r"); //ouverture du fichier passé dans la console
	if (f==NULL){
		printf("Ouverture du fichier impossible\n");
		exit (1);
	}
	
	fgets(s,20,f);
	if (s==NULL) printf("PROBLEME !\n");
	sscanf(s,"%s %d",dummy,&d);
	printf("Scanf :%s et d=%d\n",s,d);
	
	/*if (strchr(s,'#')!=NULL){
			sscanf(s,"%[^\n]",s1);
			printf("Scanf :%s\n",s1);
		}*/

	sscanf(s,"%[^\n]",s1);
	if (s1==NULL) printf("PROBLEME !\n");
		
	while (strstr(s1,"end")==NULL) //on va parcourir le fichier jusqu'a trouver end
	{		

		if (strchr(s1,'#')!=NULL){

		}else if (strstr(s1, ":")!=NULL){ 
			addLabel(s1,segment);
			printf("CurrentLabel=%d\n",currentLabel);
			printf("s1: %s et segment : %d\n\n",s1,segment); 
		}else {
			if (DEBUG) printf("		String =%s Argument D = %d\n",s1,d);
			decodeInstruction(s1);
		}
		
	  fgets(s,20,f);
	  
	  sscanf(s,"%[^\n]",s1); ///! Gestion (suppression) des retours chariot
	}
	decodeInstruction(s); // decodeInstructions pour end
	
	fclose(f);
}

// Check !
void generateBinaryCode(char* file)
{
	FILE *fout ;
	fout=fopen(file,"w+");
	
	if (fout==NULL){
		printf("Probleme ouverture fichier binaire : %s !\n", file);
	}
	int i=0;
	fprintf(fout,"%d\n",segment);
	
	while(codeSegment[i] != 400)
	{
		fprintf(fout,"%d:%d\n",i,codeSegment[i]);
		i++;
	}
	fprintf(fout,"%d:%d\n",i,codeSegment[i]);
	fclose (fout);
}



/*************************************************/
/*struct label 
{
	char *label;
	int addr;
} tabLabels[MAX_LABELS_SIZE];*/
/*************************************************/
/*struct ref 
{
	char *label;
	int addrInCode;

} tabReferences[MAX_LABELS_SIZE];*/


/*************************************************
*********************addLabel*********************
Appel:

	addLabel(line,currentInst);
line: ligne courante
currentInst: Variable globale indiquant la position de l’instruction
courante, incrémentée après l’ajout de chaque instruction.

Complète le tableau de structure contenant les labels (variable globale)
Fonctions utiles:
	fgets(line,100,fin);
	strstr(line,"end");
*/
/*void addLabel(char *labelname,int addr)
{
	strcpy(tabLabels[MAX_LABELS_SIZE] -> labelname, label);//remplir la structure
	
	tabLabels[MAX_LABELS_SIZE] -> addr = addr; //va prendre l'adresse situee dans le tableau tabLabs et le mettre dans addr
	
}*/
/*************************************************
*********************findLabel********************
Fonction permettant de trouver le nom du label
*/
int findLabel(int cpt)
{
	int i=0;
		if (DEBUG) printf("currentLabel=%d!\n",currentLabel);
		while(i<currentLabel){ //strcmp(tabReferences[cpt].name,tabLabels[i].name)!=0)
			if (DEBUG) printf("tabReferences[cpt].name=%s et tabLabels[i].name=%s!\n",tabReferences[cpt].name,tabLabels[i].name);
			
			if ((strcmp(tabReferences[cpt].name,tabLabels[i].name))==0){
				if (DEBUG) printf("On trouve bien la référence dans les labels\n");
				tabReferences[cpt].addrInCode=tabLabels[i].addr;
				return tabReferences[cpt].addrInCode;
			}
			i++;
		}
		printf("Reference non trouvée dans tabLabel !\n"); 
	return -1 ;
		
}

void resolveReferences()
{
	int i=0;
	while( codeSegment[i] != 400)
	{
		if (codeSegment[i] == -1) 	//Si l'indice de code segment renvoie -1, 
				//alors il faudra mettre ce qu'a trouve findLabel dans codeSegment[i]
		{
			printf("cpt_ref=%d\n",cpt_ref);
			codeSegment[i] = findLabel(cpt_ref);
			cpt_ref++;
		}
		i++;
	}
}

// Checked !
void dumpBinaryCode(char *fout)
{
	int i=0;
	int j=0;
	FILE *fp;

	fp = fopen(fout,"rw");
	while( codeSegment[i] != 400)
	{
		
fscanf(fp,"%d",&codeSegment[i]);
		if(codeSegment[i]==0)
		{
			fprintf(fp,"add %d \n",codeSegment[i++]);
		}
		if(codeSegment[i]==1)
		{
			fprintf(fp,"mult %d \n",codeSegment[i++]);
		}
		if(codeSegment[i]==8)
		{
			fprintf(fp,"and %d \n",codeSegment[i++]);
		}
		if(codeSegment[i]==12)
		{
			fprintf(fp,"ls %d \n",codeSegment[i++]);
		}

		if(codeSegment[i]==13)
		{
			fprintf(fp,"gt %d \n",codeSegment[i++]);
		}
		if(codeSegment[i]==100)
		{
			fprintf(fp,"pushi %d \n",codeSegment[i++]); //va prendre le label situee dans le tableau tabLabs 
		}
		if(codeSegment[i]==101)
		{
			fprintf(fp,"push %d \n",codeSegment[i++]);
		}

		if(codeSegment[i]==102)
		{
			fprintf(fp,"pop %d \n",codeSegment[i++]);
		}
		if(codeSegment[i]==202)
		{
			fprintf(fp,"eq %d \n",codeSegment[i++]);
		}
		
		
/****************************************************************
Si code segment vaut 200 (donc jump false) 
	tant que l'adresse de tabref est different de 13, on incrmente j
	si addr de tabref =13 on ecrit "jf label"  
******************************************************************/
		if(codeSegment[i]==200)
		{
			while (tabReferences[j].addrInCode!=codeSegment[i++] && j<MAX_LABELS_SIZE)
			{
				j++;
			}
			if (tabReferences[j].addrInCode==codeSegment[i++])
			{
				fprintf(fp,"jf %s \n",tabReferences[i].name); 
			}
			j=0;
		}
/****************************************************************
Si code segment vaut 201 (donc jump) 
	tant que l'adresse de tabref est different de 17, on incrmente j
	si addr de tabref =17 on ecrit "j label"  
*****************************************************************/
		if(codeSegment[i]==201)
		{
			while (tabReferences[j].addrInCode!=codeSegment[i++] && j<MAX_LABELS_SIZE)
			{
				j++;
			}
			if (tabReferences[j].addrInCode==codeSegment[i++])
			{
				fprintf(fp,"jp %s \n",tabReferences[i].name); 
			}
			j=0;
		}

		
	i++;
	}
	if(codeSegment[i]==400)
	{
		fprintf(fp,"halt \n");
	}
	fclose(fp);
}
#endif

