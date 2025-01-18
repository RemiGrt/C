/**
* \file 
*			VM_MCC.c
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Contient le code pour lancer la VM sur le microcontroleur
*/

#include "stm32f0xx.h"  
#include "string.h"
#include "Liaison_Serie.h"

// Librairies du pc
#include "Mapping.h"
#include "Instructions.h"
#include "debug.h"
#include <assert.h>
#include <stdio.h>


/** \fn void Run_VM(int *PC , int *SP , int Code[SIZE_BIN] , int Variable[SIZE_BIN] , int Stack[SIZE_BIN])
 * \brief 
 * 			Lance la machine virtuelle sur le microcontroleur \n \b Avoir defini les entrees sorties dans le fichier Mapping.h
 * \param[in] 
 *			*PC			compteur PC
 * \param[in] 
 *			*SP			compteur de pile SP
 * \param[in] 
 *			Code[SIZE_BIN]			Tableau Code
 * \param[in] 
 *			Variable[SIZE_BIN] 		Tableau Variable
 * \param[in] 
 *			Stack[SIZE_BIN] 		Tableau Stack (pile)
 */
void Run_VM(int *PC , int *SP , int Code[SIZE_BIN] , int Variable[SIZE_BIN] , int Stack[SIZE_BIN])
{	
	char Retour_Code[100];
// DECODAGE DES INSTRUCTIONS
	while( Code[*PC] != I_HALT) // On execute les instructions sequentiellement, jusqu'a tomber sur l'instruction HALT
	{	
		switch(Code[*PC])
		{	
			// Instruction Pushi
			case I_PUSHI :
							*SP = * SP + 1; // On augmente la valeur de *SP
							Stack[*SP] = Code[*PC+1]; // Affectation de la valeur du code dans la pile
							*PC += 2; // On incremente *PC de 2
					break;

			
			// Instruction ADD
			case I_ADD :
							*SP = * SP - 1; // ON decremente la valeur de *SP
							Stack[*SP] = Stack[*SP] + Stack[*SP+1]; // On additionne les deux valeurs sommets de la pile
							*PC = *PC + 1 ;// incrementation du *PC : on passe a l'instruction suivante
					break;
			
			// Instruction SUB
			case I_SUB :
							*SP = * SP - 1; // ON decremente la valeur de *SP
							Stack[*SP] = Stack[*SP] - Stack[*SP+1]; // On additionne les deux valeurs sommets de la pile
							*PC = *PC + 1 ;// incrementation du *PC : on passe a l'instruction suivante
					break;
							
			// Instruction MULT
			case I_MULT :
							*SP = * SP - 1; // ON decremente la valeur de *SP
							Stack[*SP] = Stack[*SP] * Stack[*SP+1]; // On multiplie les deux valeurs sommets de la pile
							*PC = *PC + 1 ;// incrementation du *PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								//printf("DEBUG : Instruction : MULT\n");
								//printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
							}
					break;
			
			// Instruction DIV
			case I_DIV :
							*SP = * SP - 1; // ON decremente la valeur de *SP
							assert(Stack[*SP+1] != 0);
							Stack[*SP] = Stack[*SP] / Stack[*SP+1]; // On multiplie les deux valeurs sommets de la pile
							*PC = *PC + 1 ;// incrementation du *PC : on passe a l'instruction suivante
							if(DEBUG)
							{
								//printf("DEBUG : Instruction : DIV\n");
								//printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
							}
					break;
			
			// Instruction HALT
			case I_HALT :
						//printf("DEBUG : ERREUR\n");
					break;

			// Instruction PUSH
		    	case I_PUSH :
							if (LINUX_MODE)
							{
								// Valable uniquement pour Grafcet_Safe
								switch (Code[*PC+1])
								{
										case 0 : 	
											//if (Select_In== 1){
														//printf("#############################\n");
														/*if (Variable[6] == 1) printf("Etape Actuelle : ETAPE 1\n");
														if (Variable[10] == 1) printf("Etape Actuelle : ETAPE 2\n");
														if (Variable[14] == 1) printf("Etape Actuelle : ETAPE 3\n");
														if (Variable[18] == 1) printf("Etape Actuelle : ETAPE 4\n");*/
														//printf("#############################\n");
														
														/*printf("LINUX MODE : Choisissez la valeur a appliquer pour But1\n");
														scanf("%d",&Variable[0]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour Old_But1\n");
														scanf("%d",&Variable[1]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour But2\n");
														scanf("%d",&Variable[2]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour Old_But2\n");
														scanf("%d",&Variable[3]);
														printf("LINUX MODE : Choisissez la valeur a appliquer pour An\n");
														scanf("%d",&Variable[4]);*/
														//Select_In = 0;
													//}
													break;
										default :  
													break;
								}
								*SP = * SP +  1; // on incremente la valeur de *SP
								Stack[*SP] = Variable[Code[*PC+1]]; // On prend la valeur rentree par l'utilisateur et on la met dans la Stack
							}
							if (MCC_MODE)
							{			
								*SP = * SP +  1; // on incremente la valeur de *SP
								Stack[*SP] = Variable[Code[*PC+1]]; // On prend la valeur dans le tableau Variable[N] et on la met dans la Stack
								if (DEBUG_TERMINAL)
								{
									sprintf(Retour_Code,"PUSH Variable_%d=%d\n",Code[*PC+1],Variable[Code[*PC+1]]);
									Send_Text(Retour_Code);
									Retour_Code[0] = '\0';
								}
		          }
							if(DEBUG)
							{
								//printf("DEBUG : Instruction : PUSH %d\n",Code[*PC+1]);
								//printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
		           			}
		           			*PC = * PC +  2; // On incremente *PC de 2
					break;
		        
			// Instruction POP
		    	case I_POP :
							Variable[Code[*PC+1]] = Stack[*SP]; // On stocke dans le tableau Variable la valeur de la Stack actuelle
							//if(DEBUG) printf("DEBUG : Instruction : POP %d\n",Code[*PC+1]);
							//if(DEBUG) printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
							if (DEBUG_TERMINAL)
							{
										sprintf(Retour_Code,"POP Variable_%d=%d\n",Code[*PC+1],Variable[Code[*PC+1]]);
										Send_Text(Retour_Code);
										Retour_Code[0] = '\0';
							}
							*SP = *SP - 1 ; // On decremente *SP
							*PC = * PC +  1; // On incremente *PC de 1

					break;			
					
			// Instruction EQ
				case I_EQ :     
							Stack[*SP-1] = (Stack[*SP] == Stack[*SP-1]) ? 1 : 0; // On affecte au sommet de la pile la valeur 1 si la condition Stack[*SP] == Stack[*SP-1] est vraie, 0 sinon
							*SP = *SP - 1 ; // On decremente *SP
							if(DEBUG)
							{
								//printf("DEBUG : Instruction : EQ ");
								//if (Stack[*SP] == 1) printf("DEBUG : Egalite : vraie \n");
								//if (Stack[*SP] == 0) printf("DEBUG : Egalite : fausse \n");
								//printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                            }
                            *PC = *PC + 1 ; // On incremente *PC
                    break;
                    
			// Instruction JUMP FALSE ( ne s'execute qu'après une condition)
				case I_JF : 
							// JF ne s'active que si la condition verifiee est fausse
							if(Stack[*SP]== 0)
							{
									if(DEBUG)
									{
										//printf("DEBUG : Instruction : JUMP FALSE\n");
										//printf("DEBUG : Jump a l'etape %d\n",Code[*PC+1]);
									}
									*PC = Code[*PC+1]; // JUMP : *PC prend la valeur de l'instruction suivante ( qui corre*SPond a l'etape a laquelle on veut que le programme aille)
							}
							else
							{
									*PC = * PC +  2;
							}

					break;
					
			// Instruction JUMP (inconditionnel)
				case I_J : 
							if(LINUX_MODE)
							{
								if(Code[*PC+1] == 252) 
								{
								//printf("MODE LINUX : STABILITE OK ! \n");
								//Select_In = 1;
								}
							}
							if(DEBUG)
							{
								//printf("DEBUG : Instruction : JUMP (inconditionnel)\n");
								//printf("DEBUG : Jump a l'etape %d\n",Code[*PC+1]);
							}
							*PC = Code[*PC+1]; // JUMP : *PC prend la valeur de l'instruction suivante ( qui corre*SPond a l'etape a laquelle on veut que le programme aille)
					break;
			// Instruction EQ Superieur
            case I_EQS :     
                        Stack[*SP-1] = (Stack[*SP] > Stack[*SP-1]) ? 1 : 0; // On affecte a notre booleen condition la valeur de 1 si la condition Stack[*SP] > Stack[*SP-1] est vraie, 0 sinon
                        *SP = *SP - 1 ;
                        *PC = *PC + 1 ; // On incremente *PC de 1
                        if(DEBUG)
                        {
                            //printf("DEBUG : Instruction : EQS\n");
							//if (Stack[*SP] == 1) printf("DEBUG : Egalite Sup: vraie \n");
							//if (Stack[*SP] == 0) printf("DEBUG : Egalite Sup: fausse \n");
                            //printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                        }
                    break;


            //Instruction EQI : Inferieur
            case I_EQI :     
                        Stack[*SP-1] = (Stack[*SP] < Stack[*SP-1]) ? 1 : 0; // On affecte a notre booleen condition la valeur de 1 si la condition Stack[*SP] < Stack[*SP-1] est vraie, 0 sinon
                        *SP = *SP - 1 ;
                        *PC = *PC + 1 ; // On incremente *PC de 1
                        if(DEBUG)
                        {
                            //printf("DEBUG : Instruction : EQI\n");
							//if (Stack[*SP] == 1) printf("DEBUG : Egalite Inf: vraie \n");
							//if (Stack[*SP] == 0) printf("DEBUG : Egalite Inf: fausse \n");
                            //printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                        }
                    break;	
                    
            // Instruction AND : uniquement après EQ, EQS, ou EQI
			case I_AND :
						if((Stack[*SP] == 1) && (Stack[*SP-1]) == 1)
						{
							// Si les deux valent 1 on renvoie 1
							Stack[*SP-1] = 1;
						}
						else 
						{
							// Dans les autres cas c'est 0
							Stack[*SP-1] = 0;
						}
						*SP = *SP - 1 ;
						*PC = *PC + 1 ;
						 if(DEBUG)
                        {
                           // printf("DEBUG : Instruction : AND\n");
                           // printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                        }
			break;
			
			// Instruction OR : uniquement après EQ, EQS, ou EQI
			case I_OR :
						// Si Stack[*SP] = 0 et Stack[*SP-1] = 1 ou Stack[*SP] = 1 et Stack[*SP-1] = 0
						if(Stack[*SP] != Stack[*SP-1])
						{
							// La table de verite donne 1
							Stack[*SP-1] = 1;
							*SP = *SP - 1 ;
							*PC = *PC + 1 ; // On incremente *PC de 1
						}
						// Sinon si Stack[*SP] = 0 et Stack[*SP-1] = 0
						else if((Stack[*SP] == 0) && (Stack[*SP-1]) == 0)
						{
							Stack[*SP-1] = 0;
							*SP = *SP - 1 ;
							*PC = *PC + 1 ; // On incremente *PC de 1
						}
						else if((Stack[*SP] == 1) && (Stack[*SP-1]) == 1)
						{
							Stack[*SP-1] = 1;
							*SP = *SP - 1 ;
							*PC = *PC + 1 ; // On incremente *PC de 1
						}
						if(DEBUG)
            {
							//printf("DEBUG : Instruction : OR\n");
              //printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
            }
			break;
			
			// Instruction NOT : uniquement après EQ, EQS, EQI
			case I_NOT :
						// Si Stack[*SP] = 0 
						if(Stack[*SP] == 0)
						{
							// On renvoie 1
							Stack[*SP] = 1;
						}
						// Sinon 
						else
						{
							// On renvoie 0
							Stack[*SP] = 0;
						}
						if(DEBUG)
                        {
                            //printf("DEBUG : Instruction : NOT\n");
                            //printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                        }
                        *PC = *PC + 1 ; // On incremente *PC
            break;
            
            // Instruction XOR : uniquement après EQ, EQS, EQI
			case I_XOR :
						// Si Stack[*SP] != Stack[*SP-1]
						if(Stack[*SP] != Stack[*SP-1])
						{
							// Ca renvoie 1
							Stack[*SP-1] = 1;
						}
						// Dans tous les autres cas
						else 
						{
							// Ca renvoie 0
							Stack[*SP-1] = 0;
						}
						*SP = *SP - 1 ;
						*PC = *PC + 1; // On incremente *PC de 1
						if(DEBUG)
                        {
                            //printf("DEBUG : Instruction : XOR\n");
                            //printf("DEBUG : Stack actuelle %d\n", Stack[*SP]);
                        }
            break;
			
			// Instructions non reconnue par le programme
				default :
							//if(DEBUG) printf("\nDEBUG : [ERREUR] l'instruction %d n'est pas reconnue !\n",Code[*PC]);
							*PC = *PC + 1;
					break;
		}
		if (DEBUG_TERMINAL)
		{
			sprintf(Retour_Code,"Nb_Inst=%d-Instr=%d\n",*PC,Code[*PC]);
			Send_Text(Retour_Code);
			Retour_Code[0] = '\0';
		}
	}
	
	//if(DEBUG) printf("\nDEBUG : Resultat = %d\n",Stack[0]);// Affichage du resultat contenu tout en bas de la pile
}

