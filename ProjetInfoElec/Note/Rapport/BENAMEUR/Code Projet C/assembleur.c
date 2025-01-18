///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///															///
///		Projet C : compilateur d'un grafcet									///
///															///
///		Fichier pour generer un assembleur									///
///															///
///		prend en parametre un fichier d'entree .asm et un fichier de sortie .bin 				///
///		L'assembleur permet de passer d'un fichier ASM a un fichier binaire					///
///	Groupe : SITTHIVONGS - BISSAUGE EI2I3 HF									///
///															///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembleur.h"
/*
	Fonction main 
	Gere la presence des deux fichiers necessaires
	Realisation d'un dictionnaire listant les instructions connues avec leur nom, leur valeur decimal, et leur type (utile lors du parseASM)
	Initialise les variables utilises pour l'assembleur
	Appelle les 3 fonctions principales de l'assembleur
		- ParseASM
		- ResolveEtiquette
		- WriteBinCode


*/
int main(int argc, char** argv)
{
	if ( argc != 3)
	{
		printf("Wrong use of the programm, there are to 2 arguments : input file.asm and output file.bin \n");
		return 0;
	}
	
	t_instruction tabInstructions[20];
	AddCodOp(tabInstructions, 0, "I_ADD", 1, 0);
	AddCodOp(tabInstructions, 1, "I_MULT", 3, 0);
	AddCodOp(tabInstructions, 2, "I_AND", 8, 0);
	AddCodOp(tabInstructions, 3, "I_OR", 9, 0);
	AddCodOp(tabInstructions, 4, "I_NOT", 10, 0);
	AddCodOp(tabInstructions, 5, "I_EQ", 11, 0);
	AddCodOp(tabInstructions, 6, "I_LS", 12, 0);
	AddCodOp(tabInstructions, 7, "I_GT", 13, 0);
	AddCodOp(tabInstructions, 8, "I_PUSHI", 100, 1);
	AddCodOp(tabInstructions, 9, "I_PUSH", 101, 1);
	AddCodOp(tabInstructions, 10, "I_POP", 102, 1);
	AddCodOp(tabInstructions, 11, "I_JP", 200, 3);
	AddCodOp(tabInstructions, 12, "I_JF", 201, 3);
	AddCodOp(tabInstructions, 13, "I_HALT", 400, 0);
//	printf("fin des init des instructions \n");
	
	int code[15000];

	
	FILE* fichierSortie = fopen(argv[2],"w+b");
	if(fichierSortie == NULL)
	{
		printf("Erreur dans l'ouverture du fichier de sortie \n");
		return 0;
	}
	FILE* fichierEntree = fopen(argv[1], "r");
	if(fichierEntree == NULL)
	{
		printf("Erreur dans l'ouverture du fichier d'entree \n");
		return 0;
	}
	
	t_etiquette tabEtiquette[500];	
	t_reference tabReference[500];
	
	t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference = (t_nbInstructionEtiquetteReference*) malloc(sizeof(t_nbInstructionEtiquetteReference));
	// structure pour connaitre le nombre d'étiquettes, de references et d'instructions		(malloc necessaire pour avoir le bon espace memoire)
	nbInstructionEtiquetteReference->nbReference = 0;
	nbInstructionEtiquetteReference->nbEtiquette = 0;
	nbInstructionEtiquetteReference->nbInstruction = 0;
	
	
	ParseASM(fichierEntree, tabInstructions, tabEtiquette, tabReference, code, nbInstructionEtiquetteReference);
	
	ResolveEtiquette(code, tabEtiquette, tabReference, nbInstructionEtiquetteReference);
	
	WriteBinCode(code, fichierSortie, nbInstructionEtiquetteReference);
	
	return 0;
}

// on set un dictionnaire de toutes les instruments possibles dans un tableau rangé suivant un type et les instructions possibles qui suivent
void AddCodOp(t_instruction* tabInstructions, int instructionIndex, char* name, int codop, int type)
{
	strcpy((tabInstructions + instructionIndex)->name, name);
	
	(tabInstructions + instructionIndex)->codop = codop;
	
	(tabInstructions + instructionIndex)->type = type;	
}

// une passe pour creer un tableau avec toutes les insctructions et en supprimant les lignes de commentaire
/*
	Fonction ParseASM
	
	Cette fonction va lire chaque ligne du fichier .asm et les differencier selon 3 choix :
		- un commentaire marque par #, les commentaires ne sont pas utilises, on ne fait donc rien
		- une etiquette, marque par :, ces edrnieres sont utilisees pour les JUMP qui permettent de coder les instructions IF et les boucles WHILE (DO...WHILE)
		 dans ce cas, on note le n° de l'instruction qui suit l'etiquette
		- une instruction, on peut en diffencier 3 types :
			- type 0 : une instruction qui ne necessite pas de parametre en plus (ex : AND, OR, MULT, ADD,...)
			- type 1 : une instruction qui necessite un parametre supplementaire (ex : POP et PUSH (suivi de l'indice de la variable), PUSHI (suivi d'une constante), ...)
			- type 3 : une instruction qui necessite l'emplacement dans le code d'une etiquette (ex : JUMP, qui a pour seconde instruction l'indice de l'intruction ou doit se placer le code pointer de la VM) 
		- Pour chaque intruction on remplit un tableau d'entier code[] avec les instructions lues et les parametres s'il y en a
		 dans le cas des reference, on ne connait pas encore le parametre a inscrire dans le tableau code[] (on note pour le moment -1 à l'indice de l'intruction correspondante)
		 Pour resoudre, la valeur des JUMP, on fait appelle a la fonction ResolveEtiquette
		 
		 
	 Pour les JUMP on utlise deux structures
	 	- Une pour les références lors de l'appel du JUMP. On y stock le nom de la référence ainsi que l'indice à laquelle elle se trouve dans le code(qui correspond a celui du JUMP + 1)
	 	- Une pour les etiquettes, où l'on stock le nom de l'etiquette ainsi que l'incide de l'instruction courante
*/
void ParseASM(FILE* fichierEntree, t_instruction* tabInstructions, t_etiquette* tabEtiquette, t_reference* tabReference, int* code, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference)
{
	char line[100]; 
	int etiquetteIndex = 0;			//tableau pour stocker les lignes       
	int referenceIndex = 0;
	int instructionCourante = 0;
	char commande[10];			// pour stocker les codop de chaque lign du fichier d'entrée
	int valeur;				// pour les types 1
	char reference[100];				// pour stocker les noms des references pour les jumps
	
	int i;
	fgets(line, 100, fichierEntree);
	while( strstr(line, "END") == NULL)
	{
		//printf("ligne :%s fin \n", line);
		//printf("instrucution num :%d \n",	instructionCourante);
		
		
		if (strstr(line, "#"))				// c'est un commentaire    => rien a faire
		{	//printf("je suis un com\n");
		}
		else if(strstr(line,":"))			// c'est une reference pour un jump
		{	// il faut recuperer le nom et reference = le numéro de la commande
		
			//printf("je suis un ref \n");
			strcpy((tabEtiquette + etiquetteIndex)->name, NomEtiquette(line));
			
			
			(tabEtiquette + etiquetteIndex)->numInstruction = instructionCourante;
//			printf("l etiquette recu ds le parse %s num instruction : %d \n", NomEtiquette(line), instructionCourante);
			etiquetteIndex ++;
		}
		else						// c'est une instruction 
		{	// il faut recuperer le type et savoir combien il fait d'instructions qui suivent (pour les jp recuperer le nom et reference = -1)
			//printf("je suis une instruction \n");
			sscanf(line, "%s", commande);
			//printf(" la commande est : %s \n", commande);

			for(i=0; i <  nbInstructionType; i++)
				if(strcmp(commande, tabInstructions[i].name) == 0)
				{
					//printf("il s'agit de : %s \n",tabInstructions[i].name);
					code[instructionCourante] = tabInstructions[i].codop;
					instructionCourante ++;
					
					if(tabInstructions[i].type == 1)
					{
						sscanf(line, "%s %d", commande, &valeur);
						code[instructionCourante] = valeur;
						instructionCourante ++;
					}
					else if (tabInstructions[i].type == 3)
					{
						// il s'agit d'une reference, on remplit donc le tableau de references avec le nom lu ainsi que l'indice de la reference dans le code
						// ce dernier va utile lors de la resolution des references pour ecrire l'indice de l'etiquette a l'indice correcte de la reference 
						sscanf(line, "%s %s", commande, reference);
//						printf("la ref lu : %s et son indice : %d \n", reference, instructionCourante);
						strcpy(tabReference[referenceIndex].name, reference);
						tabReference[referenceIndex].addCode = instructionCourante;				// adresse du code correspondant a la reference du jump
						referenceIndex ++;
						
						code[instructionCourante] = -1;
						instructionCourante ++;
					}
				}
		}
		
		fgets(line, 100, fichierEntree); 		// ligne suivante
		//printf("\n ligne suivante\n\n");
	}	
	
	//printf("tout le fichier d'entree a ete lu \n");
	
	
	// structure pour redonner le nombre d'étiquette, de reference et d'instruction
	nbInstructionEtiquetteReference->nbReference = referenceIndex;
	nbInstructionEtiquetteReference->nbEtiquette = etiquetteIndex;
	nbInstructionEtiquetteReference->nbInstruction = instructionCourante;
	
//	for(i=0; i<etiquetteIndex; i++)
//		printf("indice de l'etiquette %s num %d : %d \n", tabEtiquette[i].name, i, tabEtiquette[i].numInstruction);
	
}
/*
	Fonction qui prend un parametre la ligne d'une etiquette et renvoie l'etiquette en supprimant les :
*/
char* NomEtiquette(char* etiquette)
{

	//printf("etiq en entree %s \n", etiquette);
	int i=0;
	
	while(etiquette[i] != ':')
	{
		etiquette[i] = etiquette[i];
		i ++;
	}
	etiquette[i]='\0';
	//printf("etiq en sortie %s \n", etiquette);
	return etiquette;
}

/*	
	Fonction ResolveEtiquette
	
	Cette fonction va lire une seconde fois le fichier d'entree afin de lier chaque JUMP avec l'indice du code de l'étiquette
	
	On utilise donc le tableau des references et celui des etiquettes, en comparant, pour chaque indice, le nom
	Des lors que le nom correspond, on peut extraire l'indice de l'etiquette dans le code pour l'ecrire dans le tableau code[] à l'indice correspondant a la reference 
*/

void ResolveEtiquette(int* code,  t_etiquette* tabEtiquette, t_reference* tabReference, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference)
{
	int nbReference = nbInstructionEtiquetteReference->nbReference;
	int nbEtiquette = nbInstructionEtiquetteReference->nbEtiquette;
	int flagReferenceTrouvee = 0;
	
	int i,j; 

//	for(i = 0; i < nbEtiquette; i++) 
//		printf("indice de l'etiquette %s num %d : %d \n", tabEtiquette[i].name, i, tabEtiquette[i].numInstruction);
	
//	printf("\ndebut resolve \n\n");
	
	for(i = 0; i < nbReference; i++)
	{
///		printf("nom de la ref  %s num %d : %d \n", tabReference[i].name, i, tabReference[i].addCode);
		j = 0;
		do
		{
			if(strcmp(tabReference[i].name, tabEtiquette[j].name) ==0 )
			{
				code[tabReference[i].addCode] = tabEtiquette[j].numInstruction;
//				printf("indice de l'etiquette %s num %d : %d \n", tabEtiquette[j].name, j, tabEtiquette[j].numInstruction);
				flagReferenceTrouvee = 1;
			}	
			j++;
		}while(flagReferenceTrouvee == 0 && j < nbEtiquette);
		
		if (flagReferenceTrouvee == 0)
			printf("Il y a eu une erreur sur une reference \n");
			
		flagReferenceTrouvee = 0;
	}
}
/*
	fonction WriteBinCode
	
	cette fonction ecrit le tableau code[] dans le fichier de sortie, ce fichier est ensuite envoye vers la VM
	la syntaxe pour l'ecriture du tableau est importante :
		- Sur la premiere ligne du fichier, on y inscrit le nombre totale d'instruction dans le code binaire qui suit
		- Sur les lignes suivantes, on y inscrit les instructions du code avec la syntaxe suivante: [n° de l'intruction]:[instruction]
		- Sur la derniere ligne l'instruction doit etre 400, qui est l'instruction de fin de fichier
*/

void WriteBinCode(int* code, FILE* fichierSortie, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference)
{
	int nbInstruction = nbInstructionEtiquetteReference->nbInstruction;
//	printf("nm instruction totale %d \n",nbInstruction+1);
	int i;
	
	fprintf(fichierSortie,"%d\n", nbInstruction+1);
	for (i = 0; i < nbInstruction; i++)
	{
	//	printf("%d \n", code[i]);
		fprintf(fichierSortie,"%d:%d\n", i, code[i]);
	}

	fprintf(fichierSortie, "%d:400", i);
}









