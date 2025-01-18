/**
* \file 
* 				assembleur.c
* \author 
* 				Jeanne Baumier & Thomas Broussard
* \date 
* 				6 février 2017
* \brief  
* 				Regroupe les fonctions permettant de convertir un fichier assembleur .asm en un fichier .bin (utilisé dans la machine virtuelle)
* \version 
* 				2 
* \date 
* 				12/03/17
* \brief 
* 				Ajout de la conversion bin vers asm pour vérifier le bon déroulement de la conversion (voir fonction dumpBinaryCode)\n
* 				Les tableaux de structures sont à présent dynamique, ce qui rend le programme beaucoup plus flexible\n
* 				Ajout d'une fonction effaçant les espaces mémoires alloués dynamiquement\n
* 				La lecture du fichier source ligne par ligne (dans parseASM) passe à présent par une chaine de caractère Instruction de taille variable\n
* 				-> Intérêt : les fonctions prenant en paramètre la chaîne Instruction ne manipuleront plus une chaîne de taille fixe , pouvant contenir un nombre important\n
* \version 
* 				1 
* \date 
* 				11/03/17
* \brief 
* 				Ajout de la 2ème parse permettant de compléter les références indéfinies\n
* 				Régulation de l'espace mémoire alloué dynamiquement : les fuites mémoires ont été corrigées via la commande valgrind\n
* \version 
* 				0 
* \date 
* 				07/03/17
* \brief 
* 				Refonte complète du fichier Assembleur.c pour répondre aux attentes du projet
*/

//Librairies standards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
//Librairies locales
#include "asm.h"
#include "debug.h"
#include "Instructions.h"
/*
##########################################################
#####    Déclaration des variables globales 	   #######
##########################################################
*/
/*! \def Variables */
/*! Variable liée à void addLabel(char *line, int addr); */
int currentLabel = 0;
/*! Variable liée à void addLabel(char *line, int addr); */
int currentInst = 0;
/*! Variable liée à void decodeInstruction(char *line); */
int currentRef = 0;

/*! Tableau utile pour la génération des fichiers de destination */
int *codeSegment = NULL;

/*! Buffer utilisable pour créer des chaines de caractères dynamique, avec l'utilisation de fgets ou sscanf */
char buffer[TAILLE_BUFFER];

/*
##############################################
#####    Déclaration des structures 	######
##############################################
*/

/*! \struct t_label
 * \brief  Structure utilisée pour la résolution des références */
typedef struct {
	char *label;
	int addr;
}t_label;

/*! Structure globale *tabLabels */
t_label *tabLabels= NULL;
/*! Structure globale *tabReferences */
t_label *tabReferences= NULL;

// void decodeInstruction(char *line); va comparer chaque instruction trouvée à un dictionnaire d'instruction préalablement construit par le programmeur. Ce dictionnaire est en fait un tableau de structure
/*struct instructionName {
	char *name;			// Le nom de l'instruction
	int opcode;				// son codop, extrait de vm_codops.h
	int type;					// son type
	char *format;			// son format
	int nbops;				// le nb d'opérandes de l'instruction
} tabInstructionNames[MAX_IDENTS_SIZE];*/

/*
##############################################
#####    Appel des fonctions locales   #######
##############################################
*/
void AddInstruction(char* line);
void addLabel(char *line, int addr);
void dumpBinaryCode();
/*
##############################################
#####    Déclaration des fonctions 	   #######
##############################################
*/

/** \fn  
 * 			void parseAsm (FILE* fichier_src)
 * \brief 
 * 			Convertis un fichier source contenant des instructions en un fichier contenant des instructions représentées par des entiers
 * \param[in] 
 * 			*fichier_src 			Fichier source
 */
 
 void parseAsm (FILE* fichier_src)
{

	char *instruction = NULL;
	
	// Allocation dynamique des tableaux
	codeSegment = malloc(sizeof(int));
	tabLabels = malloc(sizeof(t_label));
	tabReferences = malloc(sizeof(t_label));
	
	assert(tabLabels != NULL || tabReferences != NULL || codeSegment != NULL);
	
	
	// Lecture de la première ligne du fichier
	fgets(buffer, sizeof(buffer), fichier_src); 		// on sauvegarde la totalité de la ligne dans un buffer de taille fixe
	buffer[strlen(buffer)-1]='\0';  					// enlève le '\n' à la fin
	instruction=malloc((strlen(buffer)+1)*sizeof(char));// la taille de la chaîne de caractère instruction est allouée dynamiquement, en fonction du contenu du buffer
	assert(instruction != NULL); 						// une erreur à cet endroit indique que l'allocation de la mémoire a échouée
	strcpy(instruction, buffer); 						// le contenu du buffer est recopié dans la chaine de caractère instruction
	
	while (strstr(instruction,"end")== 0)
	{	
		
		// Si le caractère # est présent dans la chaîne, alors il s'agit d'un commentaire
		if ((strchr(instruction,'#') != NULL))
		{
				//On évite l'ensemble de la ligne pour continuer le programme
		}
		
		// Si la ligne contient ":" , il s'agit d'une étiquette ou d'un label
		else if ((strchr(instruction,':') != NULL))
		{
			addLabel(instruction,currentInst);
		}

		// Si il s'agit d'une instruction
		else 
		{
			AddInstruction(instruction);
		}	
		
		// suppression du contenu de la "précédente" instruction pour pouvoir en affecter un nouveau
		free (instruction);
		
		// Lecture de la ligne suivante du fichier
		fgets(buffer, sizeof(buffer), fichier_src); 		// on sauvegarde la totalité de la ligne dans un buffer de taille fixe
		buffer[strlen(buffer)-1]='\0';  					// enlève le '\n' à la fin
		instruction=malloc((strlen(buffer)+1)*sizeof(char));// la taille de la chaîne de caractère instruction est allouée dynamiquement, en fonction du contenu du buffer
		assert(instruction != NULL); 						// une erreur à cet endroit indique que l'allocation de la mémoire a échouée
		strcpy(instruction, buffer); 						// le contenu du buffer est recopié dans la chaine de caractère instruction
	}
	// Libération de l'espace mémoire alloué pour les chaînes de caractères propres à la fonction
	free(instruction);
}


/** \fn  
 * 			void resolveReferences()
 * \brief 
 * 			Permet de compléter toute les références indéfinies
 */
 
void resolveReferences()
{
	int i,j;	
	// Etude de chaque Référence une par une
	for(i = 0; i < currentRef; i++)
	{
		//Comparaison de la référence avec la liste de label
		for (j = 0; j < currentLabel; j++)
		{
			if(DEBUG) printf("Référence : %s // Label : %s\n",tabReferences[i].label,tabLabels[j].label);
			
			// Si la référence i correspond à au label j , alors on peut compléter le tableau codeSegment pour définir la référence
			if(strcmp(tabReferences[i].label,tabLabels[j].label) == 0)
			{
				codeSegment[tabReferences[i].addr] = tabLabels[j].addr; 
				if(DEBUG) printf("Référence %s définie ! \n",tabReferences[i].label);
			}
		}
		if(DEBUG) printf("\n");
	}
}

/** \fn  
 * 			void generateBinary(FILE* fichier_dest)
 * \brief 
 * 			Génère le fichier .bin grâce au tableau codeSegment, précédemment complété par les 1ère et 2ème parse
 * \param[in] 
 * 			*fichier_dest 		Fichier de destination
 */
void generateBinary(FILE* fichier_dest)
{
	int i,j;
	int N;
	// 1 : on compte le nombre d'instruction présent dans le tableau
	for (i = 0 ; i < currentInst; i++)
	{
		if (codeSegment[i] == I_HALT) N = i; // la dernière case du tableau contenant la valeur I_HALT est considéré comme étant la fin du programme
	}
	N++;
	fprintf(fichier_dest,"%d\n",N);
	// 2 : On écrit le fichier de destination
	for (j = 0 ; j < N; j++)
	{
		fprintf(fichier_dest,"%d: %d\n",j,codeSegment[j]);
	}
	
}	

/** \fn  
 * 			void generateBinary(FILE* fichier_dest)
 * \brief 
 * 			Génère le fichier .bin grâce au tableau codeSegment, précédemment complété par les 1ère et 2ème parse
 * \param[in] 
 * 			*fichier_dest 		Fichier de destination
 */
void generateStruct(FILE* fichier_dest)
{
	int i,j;
	int N;
	
	fprintf(fichier_dest,"int Code[]={\n");
	// 1 : on compte le nombre d'instruction présent dans le tableau
		// 1 : on compte le nombre d'instruction présent dans le tableau
	for (i = 0 ; i < currentInst; i++)
	{
		if (codeSegment[i] == I_HALT) N = i; // la dernière case du tableau contenant la valeur I_HALT est considéré comme étant la fin du programme
	}
	N++;
	// 2 : On écrit le fichier de destination
	for (j = 0 ; j < N; j++)
	{
		fprintf(fichier_dest,"%d,",codeSegment[j]);
		if (j%20==0)
			fprintf(fichier_dest,"\n");
	}
	fprintf(fichier_dest,"};\n");	
}	
/** \fn  
 * 			void AddInstruction(char* line)
 * \brief 
 * 			Permet de décoder une instruction et remplir le tableau codeSegment avec
 * \param[in] 
 * 			*line 			Ligne à décoder (sous forme d'une chaîne de caractères regroupant l'intégralité de la ligne
 */
 void AddInstruction(char* line)
{
	void *p;
	int type = -1; // initialisé à -1 
	int OpCod = 0;
	int Parametre =0;
	char instruction[10]="NULL";
	char *Etiquette;
	// Lecture de l'instruction
	sscanf(line,"%s",instruction);	
		
	// On détermine l'instruction selon le dictionnaire suivant : 
		
	// MULT	: instruction TYPE 0	
	if(strcmp(instruction,"MULT") == 0)
	{
		OpCod = I_MULT;
		type = 0;
	}
			
	// ADD : instruction TYPE 0		
	else if(strcmp(instruction,"ADD") == 0)
	{
		OpCod = I_ADD;
		type = 0;
	}
	// SUB : instruction TYPE 0		
	else if(strcmp(instruction,"SUB") == 0)
	{
		OpCod = I_SUB;
		type = 0;
	}
	// DIV : instruction TYPE 0		
	else if(strcmp(instruction,"DIV") == 0)
	{
		OpCod = I_DIV;
		type = 0;
	}
				
	// HALT : instruction TYPE 0
	else if(strcmp(instruction,"HALT") == 0)
	{
		OpCod = I_HALT;
		type = 0;
	}		
			
	// EQ : instruction TYPE 0
	else if(strcmp(instruction,"EQ") == 0)
	{
		OpCod = I_EQ;
		type = 0;
	}
			
	// EQI : instruction TYPE 0
	else if(strcmp(instruction,"EQI") == 0)
	{
		OpCod = I_EQI;
		type = 0;
	}
			
	// EQS : instruction TYPE 0
	else if(strcmp(instruction,"EQS") == 0)
	{
		OpCod = I_EQS;
		type = 0;
	}
			
	// AND : instruction TYPE 0
	else if(strcmp(instruction,"AND") == 0)
	{
		OpCod = I_AND;
		type = 0;
	}
			
	// NOT : instruction TYPE 0
	else if(strcmp(instruction,"NOT") == 0)
	{
		OpCod = I_NOT;
		type = 0;
	}
			
	// OR : instruction TYPE 0
	else if(strcmp(instruction,"OR") == 0)
	{
		OpCod = I_OR;
		type = 0;
	}
			
	// XOR : instruction TYPE 0
	else if(strcmp(instruction,"XOR") == 0)
	{
		OpCod = I_XOR;
		type = 0;
	}
	
	// PUSHI : instruction TYPE 1
	else if(strcmp(instruction,"PUSHI") == 0)
	{
		OpCod = I_PUSHI;
		type = 1;
	}
	
	// PUSH : instruction TYPE 1
	else if(strcmp(instruction,"PUSH") == 0)
	{
		OpCod = I_PUSH;
		type = 1;
	}
			
	// POP : instruction TYPE 1
	else if(strcmp(instruction,"POP") == 0)
	{
		OpCod = I_POP;
		type = 1;
	}
		
	// JUMP : instruction TYPE 3
	else if(strcmp(instruction,"J") == 0)
	{
		OpCod = I_J;
		type = 3;
	}
		
	// JUMP FALSE : instruction TYPE 3
	else if(strcmp(instruction,"JF") == 0)
	{
		OpCod = I_JF;
		type = 3;	
	}
	
	// Conversion de l'instruction et ajout dans le tableau codeSegment, en fonction de son type
	switch (type)
	{
		// INSTRUCTIONS TYPE 0
		case 0 : 
				//Réallocation de la mémoire de codeSegment pour y stocker un entier supplémentaire
				 if ((p = realloc(codeSegment, (currentInst + 1)* sizeof(int))))
				{
					codeSegment = p;
				}
				else // si la réallocation échoue, on libère l'espace
				{
					if(DEBUG)printf("Reallocation mémoire echouée...\n");
					free (codeSegment);
				}
				codeSegment[currentInst] = OpCod;
				currentInst ++;
				break;
		
		//INSTRUCTIONS TYPE 1	
		case 1 :  
				//Réallocation de la mémoire de codeSegment pour y stocker 2 entiers supplémentaires
				 if ((p = realloc(codeSegment, (currentInst + 2)* sizeof(int))))
				{
					codeSegment = p;
				}
				else // si la réallocation échoue, on libère l'espace
				{
					if(DEBUG)printf("Reallocation mémoire echouée...\n");
					free (codeSegment);
				}		
				sscanf(line, "%s %d",instruction, &Parametre);
				codeSegment[currentInst] = OpCod;
				currentInst ++;	
				codeSegment[currentInst] = Parametre;
				currentInst ++;
				break;
		
		//INSTRUCTIONS TYPE 3
		case 3 : 
				// On affecte de la mémoire pour l'Etiquette uniquement si l'instruction est de type 3
				Etiquette = malloc(strlen(line)*sizeof(char));
				//Réallocation de la mémoire de codeSegment pour y stocker 2 entiers supplémentaires
				 if ((p = realloc(codeSegment, (currentInst + 2)* sizeof(int))))
				{
					codeSegment = p;
				}
				else // si la réallocation échoue, on libère l'espace
				{
					if(DEBUG)printf("Reallocation mémoire echouée...\n");
					free (codeSegment);
				}
				//Réallocation de la mémoire de TabReference pour y stocker une structure supplémentaire
				 if ((p = realloc(tabReferences, (currentRef + 1)* sizeof(t_label))))
				{
					tabReferences = p;
				}
				else // si la réallocation échoue, on libère l'espace
				{
					if(DEBUG)printf("Reallocation mémoire echouée...\n");
					free (tabReferences);
				}
				
				
				sscanf(line, "%s %s",instruction, Etiquette);
				codeSegment[currentInst] = OpCod;
				currentInst ++;	
				codeSegment[currentInst] = -1; // Référence indéfinie
				// Allocation dynamique pour pouvoir stocker la chaîne de caractère Etiquette dans le tableau tabReference
				tabReferences[currentRef].label = malloc((strlen(Etiquette)+1)*sizeof(char));
				
				// Sauvegarde de Etiquette dans tabReference
				strcpy(tabReferences[currentRef].label, Etiquette); 
				
				// Sauvegarde de l'adresse pointé par le label
				tabReferences[currentRef].addr = currentInst;
				
				// Incrémentation du tableau de référence
				currentRef++;
				
				// Passage à la ligne suivante
				currentInst ++;
				
				// Libération de l'espace mémoire alloué pour les chaînes de caractères propres à la fonction
				free(Etiquette);
				break;
				
		//AUTRE TYPE D'INSTRUCTIONS		
		default : 
				break;
	}	
	
}



/** \fn  
 * 			void addLabel(char *line, int addr)
 * \brief 
 * 			Complète le tableau de structures contenant les labels (variable globale)
 * \param[in] 
 * 			*line 		Ligne courante
 * \param[in] 
 * 			addr 		Adresse de la ligne courante
 */
 void addLabel(char *line, int addr)
{
	void *p;
	char Vide;
	char *Nom_Etiquette = malloc(strlen(line)*sizeof(char));
	
	//Réallocation de la mémoire pour stocker un élément supplémentaire à chaque passage dans la fonction
	 if ((p = realloc(tabLabels, (currentLabel + 1)* sizeof(t_label))))
	{
		tabLabels = p;
    }
	else // si la réallocation échoue, on libère l'espace
	{
		if(DEBUG)printf("Reallocation mémoire echouée...\n");
		free (tabLabels);
    }

	sscanf(line,"%s %c",Nom_Etiquette, &Vide); // extraction du nom de l'étiquette : on évite le caractère ':'
	
	// Allocation dynamique pour pouvoir stocker la chaîne de caractère line dans le tableau tabLabels
	tabLabels[currentLabel].label = malloc((strlen(Nom_Etiquette)+1)*sizeof(char));
	
	// Sauvegarde de line dans tabLabels
	strcpy(tabLabels[currentLabel].label, Nom_Etiquette); 
		
	// Sauvegarde de l'adresse pointé par le label
	tabLabels[currentLabel].addr = addr ;
			
	// Incrémentation du tableau de label
	currentLabel++;
	
	// Libération de l'espace mémoire alloué pour les chaînes de caractères propres à la fonction
	free(Nom_Etiquette);
}

/** \fn  
 * 			void dumpBinaryCode(char* filename)
 * \brief 
 * 			Créé un fichier de debug permettant de vérifier que la source a été correctement convertie
 * \param[in] 
 * 			*filename 		Fichier source
 */
void dumpBinaryCode(char* filename)
{
	int i,j,k;
	int p = 0;
	int M;
	int flag_label;
	
	//Création d'un fichier portant le même nom que le fichier passé en paramètre, en rajoutant le suffixe "Dump_"
	char *fichier = malloc((strlen("Dump_")+strlen(filename)+1)*sizeof(char));
	strcpy(fichier,"Dump_");
	strcat(fichier,filename);
	
	FILE * nvledest = fopen(fichier,"w"); // Ouverture du fichier de destination en mode écriture
	free(fichier);
	
	// 1 : on compte le nombre d'instruction présent dans le tableau
	for (k = 0 ; k < currentInst; k++)
	{
		if (codeSegment[k] == I_HALT)
		{
			 M = k; // la dernière case du tableau contenant la valeur I_HALT est considéré comme étant la fin du programme
		}
	}
	
	// 2 : On écrit le fichier de destination
	while( p <= M )
	{
		// On vérifie si la ligne suivante est affectée à un label ou non
		for(j = 0; j < currentLabel; j++)
		{	
			if((tabLabels[j].addr) == p) 
			{				
				fprintf(nvledest, "%s :\n",tabLabels[j].label);
			}
		}
		
		if(DEBUG) printf("DEBUG : Code[%d] = %d\n", p, codeSegment[p]);
		switch(codeSegment[p])
			{
				
				// ADD
				case I_ADD :
					fprintf(nvledest, "\tADD\n");
				break;
				
				// MULT
				case I_MULT :
					fprintf(nvledest, "\tMULT\n");
				break;
				
				// SUB
				case I_SUB :
					fprintf(nvledest, "\tSUB\n");
				break;
				
				// DIV
				case I_DIV :
					fprintf(nvledest, "\tDIV\n");
				break;
				
				// EQ
				case I_EQ :
					fprintf(nvledest, "\tEQ\n");
				break;
				
				// EQS
				case I_EQS :
					fprintf(nvledest, "\tEQS\n");
				break;
				
				// EQI
				case I_EQI :
					fprintf(nvledest, "\tEQI\n");
				break; 
				
				// AND
				case I_AND :
					fprintf(nvledest, "\tAND\n");
				break;
				
				// NOT
				case I_NOT :
					fprintf(nvledest, "\tNOT\n");
				break;
				
				// OR
				case I_OR :
					fprintf(nvledest, "\tOR\n");
				break;
				
				// XOR
				case I_XOR :
					fprintf(nvledest, "\tXOR\n");
				break;
				
				// PUSHI
				case I_PUSHI :
					fprintf(nvledest, "\tPUSHI %d\n", codeSegment[p+1]);
					p++;
				break;
				
				// PUSH
				case I_PUSH :
					fprintf(nvledest, "\tPUSH %d\n", codeSegment[p+1]);
					p++;
				break;
				
				// POP
				case I_POP :
					fprintf(nvledest, "\tPOP %d\n", codeSegment[p+1]);
					p++;
				break;
				
				// JF
				case I_JF :
					flag_label = 1;
					if(DEBUG) printf("DEBUG : conversion de l'instruction JF. Recherche du label correspondant:\n");
					for(i = 0; i < currentLabel; i++)
					{	
						if((tabLabels[i].addr == codeSegment[p+1]) && flag_label == 1)
						{
							if(DEBUG) printf("DEBUG : label : %d // code : %d\n",tabLabels[i].addr,codeSegment[p+1]);
							fprintf(nvledest, "\tJF %d (%s)\n", codeSegment[p+1],tabLabels[i].label);
							flag_label = 0; // on met le flag à zéro pour éviter les doublons de labels lors de l'écriture du fichier
						}
					}
					p++;
				break;
				
				// J
				case I_J :
					flag_label = 1;
					if(DEBUG) printf("DEBUG : conversion de l'instruction J. Recherche du label correspondant:\n");
					for(i = 0; i < currentLabel; i++)
					{	
						if((tabLabels[i].addr == codeSegment[p+1]) && flag_label == 1)
						{
							if(DEBUG) printf("DEBUG : label : %d // code : %d\n",tabLabels[i].addr,codeSegment[p+1]);
							fprintf(nvledest, "\tJ %d (%s)\n", codeSegment[p+1],tabLabels[i].label);
							flag_label = 0; // on met le flag à zéro pour éviter les doublons de labels lors de l'écriture du fichier
						}
					}
					p++;
				break;
				
				// HALT 
				case I_HALT :
					fprintf(nvledest, "\tHALT\n");
				break;
			}
		p++;
	}
	fprintf(nvledest, "\tend");
	fclose(nvledest);
}

/** \fn  
 * 			void Clean_Memory()
 * \brief 
 * 			Supprime les espaces mémoires alloués dynamiquement dans le programme
 */
void Clean_Memory()
{
		int i,j;
		// Suppression des espaces mémoires dédiés aux chaînes de caractères dans les tableaux de structures
		for (i = 0; i < currentRef; i++)
		{
			free(tabReferences[i].label);
		
		}
		for (j = 0; j < currentLabel; j++)
		{
			free(tabLabels[j].label);
			
		}
		// Suppression des espaces mémoires dédiés aux tableaux dynamiques
		free(tabReferences);
		free(tabLabels);
		free(codeSegment);
}


int main(int argc,char*argv[])
{
	printf("##############################################################################\n");
	printf(" Programme réalise par Jeanne Baumier et Thomas Broussard - ei2i3 - année 2017\n");
	printf("##############################################################################\n\n");
	
	// Vérification des arguments passés en paramètre de l'exécutable
	if(argc != 4)
	{
		printf ("ERREUR : Nombre de parametres insuffisants ! \n");
		printf ("Commande : ./Assembleur <fichier source> <fichier destination> \n");
		return EXIT_FAILURE;
	}
	else
	{	
		char* filename_src = argv[1];
		char* filename_dest = argv[2];
		char* filename_c = argv[3];
		FILE* fin = fopen(filename_src,"r");
		
		// Vérification de l'ouverture du fichier source
		if (fin!= NULL)
		{
			// Parseur phase 1
			parseAsm(fin);
			// fermeture du fichier source
			fclose(fin);
			
			// Parseur phase 2
			resolveReferences();
			
			// Fichier de debug
			dumpBinaryCode(filename_src);	
			
			// Génération du code
			FILE* fout = fopen(filename_dest,"w");
			generateBinary(fout);
			
			// fermeture du fichier destination
			fclose(fout);

			// Génération du code
			fout = fopen(filename_c,"w");
			if(DEBUG) generateStruct(fout);
			
			// fermeture du fichier destination
			fclose(fout);

			// Suppression des espaces mémoires alloués dynamiquement
			Clean_Memory();
			
			return EXIT_SUCCESS;
		}
		else
		{
				printf("ERREUR : Impossible d'ouvrir le fichier %s  !\n",argv[1]);
				return EXIT_FAILURE;
		}
	}
}
