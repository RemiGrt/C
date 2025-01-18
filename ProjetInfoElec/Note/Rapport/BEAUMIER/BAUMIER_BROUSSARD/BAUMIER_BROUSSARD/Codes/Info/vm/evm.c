/**
* \file 
* 			evm.c
* \author 
* 			Jeanne Baumier & Thomas Broussard
* \date 
* 			6 février 2017
* \brief 
* 			Lis un fichier bytecode (extension \b .bin) et stocke les instructions dans le tableau \b Code[]
*/

//Librairies standards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//Librairies locales
#include "vm_codops.h"
#include "debug.h"
#include "Instructions.h"


/*! Définition de la mémoire accordée à notre machine virtuelle */
#define SIZE_BIN 1000
/*
##############################################
#####   	 Variables Globales	 	   #######
##############################################
*/
/*! Select_In permet à l'utilisateur de saisir des données en mode Linux (flag) */
int Select_In = 1;
/*! Program Counter : Compteur permettant de changer d'instruction à exécuter */
int PC = 0; 		
/*! Stack Pointer : Indique le nombre d'éléments contenus dans la pile */
int SP = -1; 
/*! Variable Pointer : Compteur permettant de changer de case dans le tableau Variable */		
int VP = 0; 		
/*! Indique si une condition est vraie ou fausse ( 1 ou 0). */
/*! Initialisé à 2 pour éviter les conflits */
int condition;		
/*! Tableau d'entier dans lequel nous allons stocker le code à éxécuter, reçu par le fichier .o rentré en paramètre de la fonction Run_VM */
int Code[SIZE_BIN];		
/*! Pile d'éxécution permettant d'effectuer les opérations indiquées par le tableau Code[] */
int Stack[SIZE_BIN];
/*! Tableau de variable permettant de stocker une ou plusieurs valeur(s) */ 	
int Variable[SIZE_BIN];	

/** \fn 
 * 		int ReadBin(char *src) 
 * \brief 
 * 		Lis un fichier bytecode (extension \b .bin) et stocke les instructions dans le tableau \b Code[]
 * \param[in] 
 * 		*src Ici, notre fichier \b .bin
 * \return 
 *			\b 1 : si les fichiers ont pu être ouverts
 * \return 
 *			\b 0 : si les fichiers n'ont pu être ouverts
 */
int ReadBin(char *src)
{
	// Ouverture du fichier en mode lecture , dont le nom a été passé en paramètre de la fonction */
	FILE * fichier = fopen(src,"r"); 
	// Variable compteur */
	int i =0;
	// Permet de stocker le nombre d'instructions 
	int Nb_Inst = 0;
	
	//Variable inutile. Elle sert simplement à éviter la lecture de certains caractère dans notre fichier */
	int none;
	//Variable inutile. Elle sert simplement à éviter la lecture de certains caractère dans notre fichier */
	char space;
	
	// Vérification de l'ouverture du fichier
	if (fichier != NULL)
	{
		if(DEBUG) printf("\nDEBUG : ouverture du fichier %s OK",src); // On indique que le fichier src s'est bien ouvert
		
		fscanf(fichier, "%d",&Nb_Inst); // Lecture du nombre d'instruction à éxécuter (1er entier contenu dans le fichier)
		if(DEBUG) printf("\nDEBUG : Nombre d'instruction = %d\n",Nb_Inst); // Affichage du nombtre d'instruction à exécuter
		
		// Remplissage du tableau d'instruction Code[] via le fichier passé en paramètre, selon le nombre d'instructions présentes
		while (i < Nb_Inst)
		{
			fscanf(fichier,"%d",&none); // On ne lit pas le chiffre en début de ligne
			fscanf(fichier,"%c",&space); // On ne lit pas le caractère ':'
			fscanf(fichier,"%c",&space); // On ne lit pas le caractère ' '
			fscanf(fichier,"%d",&Code[i]); // Récupération de l'instruction (représentée par un entier)
			i ++; // On passe à la ligne suivante
		}
		
		fclose(fichier);// fermeture du fichier en fin de lecture
		return 1; 
	}
	else
	{
		printf("ERREUR : Impossible d'ouvrir le fichier!\n");
		return 0; 
	}
}

/** \fn 
 * 		void Run_VM()
 * \brief 
 * 		Lis le tableau \b Code[] afin d'effectuer les opérations dans la pile d'exécution \b Stack[]
 */
void Run_VM()
{
if (LINUX_MODE)
{
		Variable[6] = 1	;
		Variable[10] = 0;
		Variable[14] = 0;
		Variable[18] = 0;
}
	
// DECODAGE DES INSTRUCTIONS
	while( Code[PC] != I_HALT) // On exécute les instructions séquentiellement, jusqu'à tomber sur l'instruction HALT
	{	
		switch(Code[PC])
		{	
			// Instruction Pushi
			case I_PUSHI :
							SP ++; // On augmente la valeur de SP
							Stack[SP] = Code[PC+1]; // Affectation de la valeur du code dans la pile
							PC += 2; // On incrémente PC de 2
							if(DEBUG)
							{
								printf("DEBUG : Instruction : PUSHI\n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							}
					break;

			
			// Instruction ADD
			case I_ADD :
							SP --; // ON décrémente la valeur de SP
							Stack[SP] = Stack[SP] + Stack[SP+1]; // On additionne les deux valeurs sommets de la pile
							PC++;// incrémentation du PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								printf("DEBUG : Instruction : ADD\n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							}
					break;
			
			// Instruction SUB
			case I_SUB :
							SP --; // ON décrémente la valeur de SP
							Stack[SP] = Stack[SP] - Stack[SP+1]; // On additionne les deux valeurs sommets de la pile
							PC++;// incrémentation du PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								printf("DEBUG : Instruction : SUB\n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							}
					break;
							
			// Instruction MULT
			case I_MULT :
							SP --; // ON décrémente la valeur de SP
							Stack[SP] = Stack[SP] * Stack[SP+1]; // On multiplie les deux valeurs sommets de la pile
							PC++;// incrémentation du PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								printf("DEBUG : Instruction : MULT\n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							}
					break;
			
			// Instruction DIV
			case I_DIV :
							SP --; // ON décrémente la valeur de SP
							assert(Stack[SP+1] != 0);
							Stack[SP] = Stack[SP] / Stack[SP+1]; // On multiplie les deux valeurs sommets de la pile
							PC++;// incrémentation du PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								printf("DEBUG : Instruction : DIV\n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							}
					break;
			
			// Instruction HALT
			case I_HALT :
						printf("DEBUG : ERREUR\n");
					break;

			// Instruction PUSH
		    	case I_PUSH :
							if (LINUX_MODE)
							{
								// Valable uniquement pour Grafcet_Safe
								switch (Code[PC+1])
								{
										case 0 : 	if (Select_In== 1)
													{
														printf("#############################\n");
														if (Variable[6] == 1) printf("Etape Actuelle : ETAPE 1\n");
														if (Variable[10] == 1) printf("Etape Actuelle : ETAPE 2\n");
														if (Variable[14] == 1) printf("Etape Actuelle : ETAPE 3\n");
														if (Variable[18] == 1) printf("Etape Actuelle : ETAPE 4\n");
														printf("#############################\n");
														
														printf("LINUX MODE : Choisissez la valeur a appliquer pour But1\n");
														scanf("%d",&Variable[0]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour Old_But1\n");
														scanf("%d",&Variable[1]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour But2\n");
														scanf("%d",&Variable[2]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour Old_But2\n");
														scanf("%d",&Variable[3]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour An\n");
														scanf("%d",&Variable[4]);
														Select_In = 0;
													}
													break;
										default :  
													break;
								}
								SP ++; // on incrémente la valeur de SP
								Stack[SP] = Variable[Code[PC+1]]; // On prend la valeur rentrée par l'utilisateur et on la met dans la Stack
							}
							if (MCC_MODE)
							{
								SP ++; // on incrémente la valeur de SP
								Stack[SP] = Variable[Code[PC+1]]; // On prend la valeur dans le tableau Variable[N] et on la met dans la Stack
		              		}
							if(DEBUG)
							{
								printf("DEBUG : Instruction : PUSH %d\n",Code[PC+1]);
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
		           			}
		           			PC += 2; // On incrémente PC de 2
					break;
		        
			// Instruction POP
		    	case I_POP :
							Variable[Code[PC+1]] = Stack[SP]; // On stocke dans le tableau Variable la valeur de la Stack actuelle
							if(DEBUG) printf("DEBUG : Instruction : POP %d\n",Code[PC+1]);
							if(DEBUG) printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
							SP--; // On décrémente SP
							PC += 2; // On incrémente PC de 2
					break;			
					
			// Instruction EQ
				case I_EQ :     
							Stack[SP-1] = (Stack[SP] == Stack[SP-1]) ? 1 : 0; // On affecte au sommet de la pile la valeur 1 si la condition Stack[SP] == Stack[SP-1] est vraie, 0 sinon
							SP--; // On décrémente SP
							if(DEBUG)
							{
								printf("DEBUG : Instruction : EQ ");
								if (Stack[SP] == 1) printf("DEBUG : Egalité : vraie \n");
								if (Stack[SP] == 0) printf("DEBUG : Egalité : fausse \n");
								printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                            }
                            PC++; // On incrémente PC
                    break;
                    
			// Instruction JUMP FALSE ( ne s'exécute qu'après une condition)
				case I_JF : 
							// JF ne s'active que si la condition vérifiée est fausse
							if(Stack[SP]== 0)
							{
									if(DEBUG)
									{
										printf("DEBUG : Instruction : JUMP FALSE\n");
										printf("DEBUG : Jump à l'étape %d\n",Code[PC+1]);
									}
									PC = Code[PC+1]; // JUMP : PC prend la valeur de l'instruction suivante ( qui correspond à l'étape à laquelle on veut que le programme aille)
							}
							else
							{
									PC += 2;
							}

					break;
					
			// Instruction JUMP (inconditionnel)
				case I_J : 
							if(LINUX_MODE)
							{
								if(Code[PC+1] == 252) 
								{
								printf("MODE LINUX : STABILITE OK ! \n");
								Select_In = 1;
								}
							}
							if(DEBUG)
							{
								printf("DEBUG : Instruction : JUMP (inconditionnel)\n");
								printf("DEBUG : Jump à l'étape %d\n",Code[PC+1]);
							}
							PC = Code[PC+1]; // JUMP : PC prend la valeur de l'instruction suivante ( qui correspond à l'étape à laquelle on veut que le programme aille)
					break;
			// Instruction EQ Supérieur
            case I_EQS :     
                        Stack[SP-1] = (Stack[SP] > Stack[SP-1]) ? 1 : 0; // On affecte à notre booléen condition la valeur de 1 si la condition Stack[SP] > Stack[SP-1] est vraie, 0 sinon
                        SP--;
                        PC++; // On incrémente PC de 1
                        if(DEBUG)
                        {
                            printf("DEBUG : Instruction : EQS\n");
							if (Stack[SP] == 1) printf("DEBUG : Egalité Sup: vraie \n");
							if (Stack[SP] == 0) printf("DEBUG : Egalité Sup: fausse \n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
                    break;


            //Instruction EQI : Inférieur
            case I_EQI :     
                        Stack[SP-1] = (Stack[SP] < Stack[SP-1]) ? 1 : 0; // On affecte à notre booléen condition la valeur de 1 si la condition Stack[SP] < Stack[SP-1] est vraie, 0 sinon
                        SP--;
                        PC++; // On incrémente PC de 1
                        if(DEBUG)
                        {
                            printf("DEBUG : Instruction : EQI\n");
							if (Stack[SP] == 1) printf("DEBUG : Egalité Inf: vraie \n");
							if (Stack[SP] == 0) printf("DEBUG : Egalité Inf: fausse \n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
                    break;	
                    
            // Instruction AND : uniquement après EQ, EQS, ou EQI
			case I_AND :
						if((Stack[SP] == 1) && (Stack[SP-1]) == 1)
						{
							// Si les deux valent 1 on renvoie 1
							Stack[SP-1] = 1;
						}
						else 
						{
							// Dans les autres cas c'est 0
							Stack[SP-1] = 0;
						}
						SP--;
						PC++;
						 if(DEBUG)
                        {
                            printf("DEBUG : Instruction : AND\n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
			break;
			
			// Instruction OR : uniquement après EQ, EQS, ou EQI
			case I_OR :
						// Si Stack[SP] = 0 et Stack[SP-1] = 1 ou Stack[SP] = 1 et Stack[SP-1] = 0
						if(Stack[SP] != Stack[SP-1])
						{
							// La table de vérité donne 1
							Stack[SP-1] = 1;
							SP--;
							PC++; // On incrémente PC de 1
						}
						// Sinon si Stack[SP] = 0 et Stack[SP-1] = 0
						else if((Stack[SP] == 0) && (Stack[SP-1]) == 0)
						{
							Stack[SP-1] = 0;
							SP--;
							PC++; // On incrémente PC de 1
						}
						else if((Stack[SP] == 1) && (Stack[SP-1]) == 1)
						{
							Stack[SP-1] = 1;
							SP--;
							PC++; // On incrémente PC de 1
						}
						if(DEBUG)
                        {
                            printf("DEBUG : Instruction : OR\n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
			break;
			
			// Instruction NOT : uniquement après EQ, EQS, EQI
			case I_NOT :
						// Si Stack[SP] = 0 
						if(Stack[SP] == 0)
						{
							// On renvoie 1
							Stack[SP] = 1;
						}
						// Sinon 
						else
						{
							// On renvoie 0
							Stack[SP] = 0;
						}
						if(DEBUG)
                        {
                            printf("DEBUG : Instruction : NOT\n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
                        PC++; // On incrémente PC
            break;
            
            // Instruction XOR : uniquement après EQ, EQS, EQI
			case I_XOR :
						// Si Stack[SP] != Stack[SP-1]
						if(Stack[SP] != Stack[SP-1])
						{
							// Ca renvoie 1
							Stack[SP-1] = 1;
						}
						// Dans tous les autres cas
						else 
						{
							// Ca renvoie 0
							Stack[SP-1] = 0;
						}
						SP--;
						PC++; // On incrémente PC de 1
						if(DEBUG)
                        {
                            printf("DEBUG : Instruction : XOR\n");
                            printf("DEBUG : Stack actuelle %d\n", Stack[SP]);
                        }
            break;
			
			// Instructions non reconnue par le programme
				default :
							if(DEBUG) printf("\nDEBUG : [ERREUR] l'instruction %d n'est pas reconnue !\n",Code[PC]);
							PC++;
					break;
		}
	}
	
	if(DEBUG) printf("\nDEBUG : Resultat = %d\n",Stack[0]);// Affichage du résultat contenu tout en bas de la pile
}

/** \fn 
 * 		int main(int argc,char*argv[])
 * \brief 
 * 		Lis un fichier bytecode (exemple : fichier.bin) et stocke les instructions dans le tableau \b Code[]
 * \param[in] 
 * 		argc 		Nombre d'arguments saisis (incluant le nom de l'exécutable)
 * \param[in] 
 * 		argv[] 		Ici, argv[1] : fichier.bin 
 * \return 
 *			\b 0 - Arrêt normal du programme
 * \return 
 *			\b EXIT_FAILURE si le nombre de paramètres est insuffisant
 */
 
int main(int argc,char*argv[])
{	
	printf("Programme réalisé par Jeanne Baumier et Thomas Broussard - ei2i3 - année 2017\n");
	int Check = 0; // variable permettant de vérifier si le fichier a été correctement ouvert ou non
	if(argc != 2)
	{
		printf ("ERREUR : Nombre de parametres insuffisants \n");
		return EXIT_FAILURE;
	}
	else
	{
			// Lecture du fichier passé en argument 
			Check = ReadBin(argv[1]);
			// Lancement de la machine Virtuelle uniquement si le fichier a pu être lu correctement
			if (Check == 1)
			{
				Run_VM();
				return EXIT_SUCCESS;
			}
			else
			{
				return EXIT_FAILURE;
			}
			
	}
}
