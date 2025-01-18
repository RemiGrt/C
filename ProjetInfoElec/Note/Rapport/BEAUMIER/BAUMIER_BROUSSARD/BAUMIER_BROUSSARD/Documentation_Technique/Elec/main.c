/**
* \file 
*			main.c
* \author 
*			Thomas Broussard
* \date 
*			19 juin 2017
* \brief  
*			Contient le code pour lancer la VM sur le microcontroleur
*/
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */

// Librairies du pc
#include "Instructions.h"
#include "debug.h"
#include <assert.h>
#include <stdio.h>
#include "string.h"

// Librairies du µC
#include "DigitalGPIO.h"
#include "initPins.h"
#include "UART.h"

#include "Mapping.h"
#include "Map_Functions.h"

#include "Liaison_Serie.h"
#include "VM_MCC.h"


/*-------------------------------------------------------------------------------
  STRUCTURES
-------------------------------------------------------------------------------*/

// ENTREES GPIO
typedef struct
{
		int Valeur			[SIZE_IN];	// Indique la valeur logique actuelle de l'entree ('1' ou '0')
		int Rising_Edge	[SIZE_IN]; 	// Indique si le dernier front observe est un front montant 		(1 = oui / 0 = non)
		int Falling_Edge[SIZE_IN]; 	// Indique si le dernier front observe est un front descendant 	(1 = oui / 0 = non)
}Struct_IN;
Struct_IN GPIO_Input;
int Valeur_Precedentes_Entrees_GPIO[SIZE_IN]; // Tableau contenant les valeurs precedentes des entrees (utile pour la detection des fronts)

// SORTIES GPIO
typedef struct
{
		int Valeur				[SIZE_OUT];		// Indique la valeur logique actuelle de la sortie ('1' ou '0')
}Struct_OUT;
Struct_OUT GPIO_Output;


// ENTREES ADC
typedef struct
{
	int Valeur	[SIZE_ADC]; 	// Valeur lue sur l'ADC, en fin de conversion
	int Etat		[SIZE_ADC];		// Indique si l'entree ADC est activee ou non
}Struct_ADC;
Struct_ADC ADC_Input;
int Buffer_ADC[SIZE_ADC]; // Permet de conserver les valeurs obtenues via l'interruption ADC

// SORTIES PWM
typedef struct
{
	int Frequence	[SIZE_PWM];	// Frequence du signal PWM
	int Duty_Cycle[SIZE_PWM]; // Rapport cyclique ( en %) du signal PWM
	int Etat			[SIZE_PWM]; // Indique si la sortie PWM est activee ou non
}Struct_PWM;
Struct_PWM PWM_Output;

/*-------------------------------------------------------------------------------
 DECLARATIONS DES FONCTIONS LOCALES
-------------------------------------------------------------------------------*/
/** \fn void RAZ_ALL(void)
 * \brief 
 * 			Remet a zero l'ensemble des variables globales du programme
 */
void RAZ_ALL(void);
	
/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
/*! Flag indiquant si on peut charger un programme ou non sur la carte */
int Reception_Programme = 2;

// Definition des variables globales
/*! Program Counter : Compteur permettant de changer d'instruction a executer */
int PC = 0; 		
/*! Stack Pointer : Indique le nombre d'elements contenus dans la pile */
int SP = -1; 
	
/*! Tableau d'entier dans lequel nous allons stocker le code a executer, recu par le fichier .o rentre en parametre de la fonction Run_VM */
int Code[SIZE_BIN];		
/*! Pile d'execution permettant d'effectuer les operations indiquees par le tableau Code[] */
int Stack[SIZE_BIN];
/*! Tableau de variable permettant de stocker une ou plusieurs valeur(s) */ 	
int Variable[SIZE_BIN];	

	
volatile int Select_Channel = 4;


/** \fn int main (void)
 * \brief 
 * 			Point entree de application: appel des autres fonctions sauf routines interruptions (declenchees par le materiel)
 */
int main (void)
{
	// Declaration variables locales 
	int Instr, Nb_Instr, Nb_Instr_MAX; // Variables utiles pour le chargement du programme dans la carte
	char Retour[SIZE_BIN]; // Variable permettant d'envoyer des caracteres par la liaison serie
	int Pos_Memory_Variable = 0;
	int i, j; // Compteurs pour les boucles
	int Nb_Val_Moyenne = 5; // Nombre de valeurs utilises pour realiser une moyenne (utile pour les mesures de l'ADC)
	
	
	// Initialisation de la COM UART
	initPatte_AF(Rx_Pin,Rx_Port,"NoPull",1);
	initPatte_AF(Tx_Pin,Tx_Port,"NoPull",1);
	
	InitUART2(9600, 8, 1, "NoParite", "RxInterrupt");
	
	// Initialisation des entrees
	Initialisation_Entrees_GPIO();
	Initialisation_Entrees_ADC();
	// Initialisation des sorties
	Initialisation_Sorties_GPIO();
	Initialisation_Sorties_PWM();
	Activer_PWM(0,10000,50);
	// Initialisation des variables
	RAZ_ALL();

	//Activer_PWM(1,10000,75);
	// Activation des interruptions
	NVIC_EnableIRQ(USART2_IRQn);
	
   while(1)   
   { 
		 /*	#################################################
						CHARGEMENT DU PROGRAMME SUR LA CARTE
		 ################################################# */
		if (Reception_Programme == 0)
		{
			// Desactivation de l'interruption pour l'UART le temps de recevoir l'integralite du programme
			NVIC_DisableIRQ(USART2_IRQn);
			
			// Reinitialisation des variables avant la reception du programme
			RAZ_ALL();
			
			// Envoi de l'acquittement indiquant l'initialisation de la communication
			Send_Text("!");
			
			// Reception du nombre d'instructions maximum contenu dans le programme
			Reception_Nb_Instr_UART2(&Nb_Instr_MAX);
			
			// Reception du programme envoye par le pc sur la liaison serie, instruction par instruction
			while (Reception_Programme == 0) 
			{
					// Reception de la trame (exemple : "10:23@")
					Reception_Programme_UART2(&Nb_Instr,&Instr);
					
					// Affectation dans le tableau Code[]
					Code[Nb_Instr] = Instr;
					
					// Envoi d'un acquittement : instruction recue
					sprintf(Retour,"%d",Code[Nb_Instr]);
					Send_Text(Retour);
					Retour[0] = '\0';
					// Verification : si l'instruction recue est 400 , alors l'analyse du programme est finie
					if (Instr == I_HALT)
					{	
						Reception_Programme = 1;
						// Reactivation de l'interruption pour l'UART
						NVIC_EnableIRQ(USART2_IRQn);
					}
			}
			Send_Text("PRGM OK");
		}

		
		// On passe a l'etape d'execution une fois que le programme a ete completement recu
		else if (Reception_Programme == 1)
		{
				/*#################################################
										LECTURE DES ENTREES GPIO
			 ################################################# */
				Pos_Memory_Variable = 0;
				// Reception de la valeur actuelle des entrees
				Lecture_Entrees_GPIO(GPIO_Input.Valeur,0,SIZE_IN);
				
				// Verification des fronts sur les entrees
				Fronts_Entrees_GPIO(GPIO_Input.Valeur, Valeur_Precedentes_Entrees_GPIO, 
														GPIO_Input.Rising_Edge, GPIO_Input.Falling_Edge, 0, SIZE_IN);
				
				// Placement des donnees dans le tableau Variable
				Write_Data_Decalage(Variable,GPIO_Input.Valeur,3,0,SIZE_IN);
				Write_Data_Decalage(Variable,GPIO_Input.Rising_Edge,3,1,SIZE_IN);
				Write_Data_Decalage(Variable,GPIO_Input.Falling_Edge,3,2,SIZE_IN);
				
				/*#################################################
												LECTURE DES ENTREES ADC
				################################################# */
				// Recuperation de l'etat des ADC dans le tableau Variable
				Pos_Memory_Variable = 3 * SIZE_IN + SIZE_OUT;
				Read_Data_Decalage(ADC_Input.Etat , Variable , 2 , Pos_Memory_Variable , SIZE_ADC);
			
				// On verifie si les ADC sont actives ou non
				for (i = 0; i < SIZE_ADC; i++)
				{
					// Si l'ADC est desactive, alors on passe sa valeur a -1
					if 			(ADC_Input.Etat[i] == 0) 
						ADC_Input.Valeur[i] = -1; 
					
					// Sinon , on effectue une scrutation pour recuperer sa valeur 
					else if (ADC_Input.Etat[i] == 1) 
						ADC_Input.Valeur[i] = Lecture_Entree_ADC(i , 5); // ( on moyenne 5 mesures pour obtenir une donnee fiable )
				}
			
				// Placement des donnees dans le tableau Variable
				Pos_Memory_Variable =  3 * SIZE_IN + SIZE_OUT + 1;
				Write_Data_Decalage(Variable , ADC_Input.Valeur , 2 , Pos_Memory_Variable , SIZE_ADC);
			
			/* #################################################
									EXECUTION DU PROGRAMME GRAFCET
				################################################# */
				// RAZ du PC 
				PC = 0;
				// Lancement de la VM pour decoder les instructions du programme
				Run_VM( &PC , &SP , Code , Variable , Stack );

				
				/* #################################################
										AFFECTATION DES SORTIES GPIO
				################################################# */		
				// Recuperation des valeurs depuis le tableau Variable
				Read_Data_Decalage(GPIO_Output.Valeur, Variable ,1 , 3 * SIZE_IN, SIZE_OUT);
				
				// Mise a jour des sorties
				Ecriture_Sorties_GPIO(GPIO_Output.Valeur , 0 , SIZE_OUT);
			
			
				/* #################################################
										AFFECTATION DES SORTIES PWM
				################################################# */	
				Pos_Memory_Variable =  3 * SIZE_IN + SIZE_OUT + 2 * SIZE_ADC;		
				
				// Recuperation de l'etat des PWM dans le tableau Variable
				Read_Data_Decalage(PWM_Output.Etat, Variable ,2 , Pos_Memory_Variable , SIZE_PWM);
			
				// Recuperation de la frequence appliquee dans le tableau Variable
				Read_Data_Decalage(PWM_Output.Frequence, Variable ,2 , Pos_Memory_Variable+1 , SIZE_PWM);
				
				// Recuperation du rapport cyclique appliquee dans le tableau Variable
				Read_Data_Decalage(PWM_Output.Duty_Cycle, Variable ,2 , Pos_Memory_Variable+2 , SIZE_PWM);
				
				// On verifie si les PWM sont actives ou non
				for (i = 0; i < SIZE_PWM; i++)
				{
					// Si le PWM est active, alors on peut le mettre en route, avec la configuration definie precedemment (Frequence et Duty Cycle)
					if (PWM_Output.Etat[i] == 1) 
					{
							Activer_PWM(i,PWM_Output.Frequence[i],PWM_Output.Duty_Cycle[i]);
					}
					// Si le PWM est desactive, alors on l'eteint
					else if (PWM_Output.Etat[i] == 0) 
					{
						/* Ajouter fonction permettant de desactiver un signal PWM */
					}
				}
						
				/* #########################################################################################
										AFFICHAGE SUR LE TERMINAL (Optionnel. Utile uniquement en debug)
				######################################################################################### */	
				if(AFFICHAGE_GPIO_TERMINAL)
				{
					// DEBUT
					sprintf(Retour,"\n\n####################################################################\n");
					Send_Text(Retour);
					Retour[0] = '\0';			
					
					// Entrees
					for (i= 0; i < SIZE_IN; i++)
					{
						sprintf(Retour,"IN [%d]  \t Val=%d \t Rise=%d \t Fall=%d\n",i,GPIO_Input.Valeur[i],GPIO_Input.Rising_Edge[i],GPIO_Input.Falling_Edge[i]);
						Send_Text(Retour);
						Retour[0] = '\0';
					}
					Send_Text("\n");
					
					//ADC
					for (i= 0; i < SIZE_ADC; i++)
					{
						sprintf(Retour,"ADC[%d]  \t Val=%d   \t Etat=%d\n",i,ADC_Input.Valeur[i],ADC_Input.Etat[i]);
						Send_Text(Retour);
						Retour[0] = '\0';
					}					
					Send_Text("\n");
					
					//Sorties
					for (i= 0; i < SIZE_OUT; i++)
					{
						sprintf(Retour,"OUT[%d]  \t Val=%d\n",i,GPIO_Output.Valeur[i]);
						Send_Text(Retour);
						Retour[0] = '\0';
					}
					
					// FIN
					sprintf(Retour,"\n####################################################################\n\n");
					Send_Text(Retour);
					Retour[0] = '\0';	
				}
		}
	}
   // Fin : Le CPU n'arrivera jamais ici
}
// FIN FONCTION MAIN


/*###############################################################################
																FONCTIONS LOCALES
###############################################################################*/

/** \fn void RAZ_ALL(void)
 * \brief 
 * 			Remet a zero l'ensemble des variables globales du programme
 */
void RAZ_ALL(void)
{
	// Entrees
	RAZ_Tableau_int(Valeur_Precedentes_Entrees_GPIO,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Falling_Edge,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Rising_Edge,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Valeur,0,SIZE_IN);
	
	RAZ_Tableau_int(ADC_Input.Etat,0,SIZE_ADC);
	RAZ_Tableau_int(ADC_Input.Valeur,0,SIZE_ADC);
	
	// Sorties
	RAZ_Tableau_int(GPIO_Output.Valeur,0,SIZE_OUT);
	
	RAZ_Tableau_int(PWM_Output.Duty_Cycle,0,SIZE_PWM);
	RAZ_Tableau_int(PWM_Output.Etat,0,SIZE_PWM);
	RAZ_Tableau_int(PWM_Output.Frequence,0,SIZE_PWM);
	
	// Traitement de fichier
	RAZ_Tableau_int(Code,0,SIZE_BIN);
	RAZ_Tableau_int(Stack,0,SIZE_BIN);
	RAZ_Tableau_int(Variable,0,SIZE_BIN);
	PC = 0;
	SP = -1; 
}


/*###############################################################################
																INTERRUPTIONS
###############################################################################*/

/** \fn void USART2_IRQHandler(void)
 * \brief 
 * 			Interruption sur l'USART 2
 */
void USART2_IRQHandler(void)
{
	if ((USART2->ISR&(1<<5)))
	{		
		// Si un caractere '?' est recu par la liaison serie, alors on indique que l'on souhaite recommencer la lecture du programme par un '!'
		if (USART2->RDR == '?')
		{	
			Reception_Programme = 0;
		}
	}
}

/** \fn void TIM2_IRQHandler (void)
 * \brief 
 * 			Interruption sur le Timer => PWM0
 */
void TIM2_IRQHandler (void)
{
   if((TIM2->SR & (1<<0))== (1<<0)) // verifions que c'est bien le debordement qui demande interruption
    {
			TIM2->SR &= ~(1<<0);  						// reset du drapeau de demande interruption
    }
}


/*===============================================================================
Interruption sur le Timer => PWM1
===============================================================================*/

/*===============================================================================
Interruption sur le Timer => PWM2
===============================================================================*/
