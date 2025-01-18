/********************************************************************************
|   commentaires : Illustration communication serie UART
|   auteur: Arouna DARGA
********************************************************************************/
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
		int Valeur			[SIZE_IN];	// Indique la valeur logique actuelle de l'entrée ('1' ou '0')
		int Rising_Edge	[SIZE_IN]; 	// Indique si le dernier front observé est un front montant 		(1 = oui / 0 = non)
		int Falling_Edge[SIZE_IN]; 	// Indique si le dernier front observé est un front descendant 	(1 = oui / 0 = non)
}Struct_IN;
Struct_IN GPIO_Input;
int Valeur_Precedentes_Entrees_GPIO[SIZE_IN]; // Tableau contenant les valeurs précédentes des entrées (utile pour la détection des fronts)

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
	int Etat		[SIZE_ADC];		// Indique si l'entrée ADC est activée ou non
}Struct_ADC;
Struct_ADC ADC_Input;
int Buffer_ADC[SIZE_ADC]; // Permet de conserver les valeurs obtenues via l'interruption ADC

// SORTIES PWM
typedef struct
{
	int Frequence	[SIZE_PWM];	// Fréquence du signal PWM
	int Duty_Cycle[SIZE_PWM]; // Rapport cyclique ( en %) du signal PWM
	int Etat			[SIZE_PWM]; // Indique si la sortie PWM est activée ou non
	
	int Value			[SIZE_PWM];	// Indique si la sortie PWM est à '1' ou '0'
	int Lock_State [SIZE_PWM]; //Permet de ne pas réactiver sans cesse le TIMER lorsque Etat est à 1
	volatile int Temps_Haut[SIZE_PWM];
	volatile int Temps_Bas[SIZE_PWM];

}Struct_PWM;
Struct_PWM PWM_Output;

/*-------------------------------------------------------------------------------
 DECLARATIONS DES FONCTIONS LOCALES
-------------------------------------------------------------------------------*/
void RAZ_ALL(void);
	
/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
/*! Flag indiquant si on peut charger un programme ou non sur la carte */
int Reception_Programme = 2;

// Definition des variables globales
/*! Program Counter : Compteur permettant de changer d'instruction à exécuter */
int PC = 0; 		
/*! Stack Pointer : Indique le nombre d'éléments contenus dans la pile */
int SP = -1; 
	
/*! Tableau d'entier dans lequel nous allons stocker le code à éxécuter, reçu par le fichier .o rentré en paramètre de la fonction Run_VM */
int Code[SIZE_BIN];	
/*
	int Code[]={
100,
0,102,79,101,79,100,0,12,200,200,101,80,102,84,101,81,102,85,101,82,
102,86,101,83,102,87,101,80,100,1,12,101,1,100,1,102,64,101,65,100,
2048,14,20,20,200,55,100,1,102,89,100,1,102,92,101,81,100,1,12,101,
1,100,1,102,64,101,65,100,2048,13,20,20,200,83,100,1,102,90,100,1,
102,93,101,82,100,1,12,101,1,100,1,102,64,101,65,100,2048,14,20,20,
200,111,100,1,102,91,100,1,102,94,101,83,100,1,12,101,1,20,200,129,
100,1,102,88,100,1,102,95,101,80,101,92,21,20,101,88,102,80,101,81,
101,93,21,20,101,89,102,81,101,82,101,94,21,20,101,90,102,82,101,83,
101,95,21,20,101,91,102,83,101,80,101,84,12,101,81,101,85,12,101,82,
101,86,12,101,83,101,87,12,20,20,20,200,198,100,1,102,79,201,4,101,
80,100,1,12,200,211,100,0,102,48,101,81,100,1,12,200,222,100,0,102,
48,101,82,100,1,12,200,233,100,0,102,48,101,83,100,1,12,200,244,100,
1,102,48,400};
*/
/*! Pile d'éxécution permettant d'effectuer les opérations indiquées par le tableau Code[] */
int Stack[SIZE_BIN];
/*! Tableau de variable permettant de stocker une ou plusieurs valeur(s) */ 	
int Variable[SIZE_BIN];	

	
volatile int Freq_Div;
volatile int Freq_Normalisee;
/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
	// Declaration variables locales 
	int Instr, Nb_Instr, Nb_Instr_MAX; // Variables utiles pour le chargement du programme dans la carte
	char Retour[SIZE_BIN]; // Variable permettant d'envoyer des caractères par la liaison série
	int Pos_Memory_Variable = 0;
	int i; // Compteurs pour les boucles
	int Nb_Val_Moyenne = 5; // Nombre de valeurs utilisés pour réaliser une moyenne (utile pour les mesures de l'ADC)

	// Initialisation des entrées
	Initialisation_Entrees_GPIO();
	Initialisation_Entrees_ADC();
	// Initialisation des sorties
	Initialisation_Sorties_GPIO();	
	Initialisation_Sorties_PWM();
	// Initialisation des variables
	RAZ_ALL();
	
	// Initialisation de la COM UART
	initPatte_AF(Rx_Pin,Rx_Port,"NoPull",1);
	initPatte_AF(Tx_Pin,Tx_Port,"NoPull",1);
	
	InitUART2(9600, 8, 1, "NoParite", "RxInterrupt");
	
	
	// Activation des interruptions
	NVIC_EnableIRQ(USART2_IRQn);
		
	// -------------------------
	// DEBUGGING
	//Variable[80] = 1;
	//Reception_Programme = 1;
	// -------------------------
   while(1)   
   { 
		 /*	#################################################
						CHARGEMENT DU PROGRAMME SUR LA CARTE
		 ################################################# */
		if (Reception_Programme == 0)
		{
			// Désactivation de l'interruption pour l'UART le temps de recevoir l'integralite du programme
			NVIC_DisableIRQ(USART2_IRQn);
			
			// Réinitialisation des variables avant la réception du programme
			RAZ_ALL();
			
			// Envoi de l'acquittement indiquant l'initialisation de la communication
			Send_Text("!");
			
			// Réception du nombre d'instructions maximum contenu dans le programme
			Reception_Nb_Instr_UART2(&Nb_Instr_MAX);
			
			// Réception du programme envoyé par le pc sur la liaison série, instruction par instruction
			while (Reception_Programme == 0) 
			{
					// Reception de la trame (exemple : "10:23@")
					Reception_Programme_UART2(&Nb_Instr,&Instr);
					
					// Affectation dans le tableau Code[]
					Code[Nb_Instr] = Instr;
					
					// Envoi d'un acquittement : instruction reçue
					sprintf(Retour,"%d",Code[Nb_Instr]);
					Send_Text(Retour);
					Retour[0] = '\0';
					// Verification : si l'instruction reçue est 400 , alors l'analyse du programme est finie
					if (Instr == I_HALT)
					{	
						Reception_Programme = 1;
						// Réactivation de l'interruption pour l'UART
						NVIC_EnableIRQ(USART2_IRQn);
					}
			}
			Send_Text("PRGM OK");
			
		}

		
		// On passe a l'etape d'execution une fois que le programme a été complètement reçu
		else if (Reception_Programme == 1)
		{
						
				/*#################################################
										LECTURE DES ENTREES GPIO
			 ################################################# */
				Pos_Memory_Variable = 0;
				// Réception de la valeur actuelle des entrées
				Lecture_Entrees_GPIO(GPIO_Input.Valeur,0,SIZE_IN);
				
				// Verification des fronts sur les entrees
				Fronts_Entrees_GPIO(GPIO_Input.Valeur, Valeur_Precedentes_Entrees_GPIO, 
														GPIO_Input.Rising_Edge, GPIO_Input.Falling_Edge, 0, SIZE_IN);
				
				// Placement des données dans le tableau Variable
				Write_Data_Decalage(Variable,GPIO_Input.Valeur,3,0,SIZE_IN);
				Write_Data_Decalage(Variable,GPIO_Input.Rising_Edge,3,1,SIZE_IN);
				Write_Data_Decalage(Variable,GPIO_Input.Falling_Edge,3,2,SIZE_IN);
				
				/*#################################################
												LECTURE DES ENTREES ADC
				################################################# */
				// Récupération de l'état des ADC dans le tableau Variable
				Pos_Memory_Variable = 3 * SIZE_IN + SIZE_OUT;
				if (ETAT_DEFAUT_ADC == 0)
					Read_Data_Decalage(ADC_Input.Etat , Variable , 2 , Pos_Memory_Variable , SIZE_ADC);
			
				// On vérifie si les ADC sont activés ou non
				for (i = 0; i < SIZE_ADC; i++)
				{
					// Si l'ADC est désactivé, alors on passe sa valeur à -1
					if 			(ADC_Input.Etat[i] == 0) 
						ADC_Input.Valeur[i] = -1; 
					
					// Sinon , on effectue une scrutation pour récupérer sa valeur 
					else if (ADC_Input.Etat[i] == 1) 
						ADC_Input.Valeur[i] = Lecture_Entree_ADC(i , Nb_Val_Moyenne); // ( on moyenne 5 mesures pour obtenir une donnée fiable )
				}
			
				// Placement des données dans le tableau Variable
				Pos_Memory_Variable =  3 * SIZE_IN + SIZE_OUT + 1;
				Write_Data_Decalage(Variable , ADC_Input.Valeur , 2 , Pos_Memory_Variable , SIZE_ADC);
			
			/* #################################################
									EXECUTION DU PROGRAMME GRAFCET
				################################################# */
				// RAZ du PC 
				PC = 0;
				// Lancement de la VM pour décoder les instructions du programme
				Run_VM( &PC , &SP , Code , Variable , Stack );

				
				/* #################################################
										AFFECTATION DES SORTIES GPIO
				################################################# */		
				// Récupération des valeurs depuis le tableau Variable
				Read_Data_Decalage(GPIO_Output.Valeur, Variable ,1 , 3 * SIZE_IN, SIZE_OUT);
				
				// Mise à jour des sorties
				Ecriture_Sorties_GPIO(GPIO_Output.Valeur , 0 , SIZE_OUT);
			
			
				/* #################################################
										AFFECTATION DES SORTIES PWM
				################################################# */	
				Pos_Memory_Variable =  3 * SIZE_IN + SIZE_OUT + 2 * SIZE_ADC;		
				
				// Récupération de l'état des PWM dans le tableau Variable
				if (ETAT_DEFAUT_PWM == 0)
					Read_Data_Decalage(PWM_Output.Etat, Variable ,3 , Pos_Memory_Variable , SIZE_PWM);
			
				// Récupération de la fréquence appliquée dans le tableau Variable
				Read_Data_Decalage(PWM_Output.Frequence, Variable ,3 , Pos_Memory_Variable+1 , SIZE_PWM);
				
				// Récupération du rapport cyclique appliquée dans le tableau Variable
				Read_Data_Decalage(PWM_Output.Duty_Cycle, Variable ,3 , Pos_Memory_Variable+2 , SIZE_PWM);
				
				// On vérifie si les PWM sont activés ou non
				for (i = 0; i < SIZE_PWM; i++)
				{
					// Configuration Fréquence et Rapport Cyclique
					PWM_Output.Temps_Haut[i] = ((1000000 / PWM_Output.Frequence[i]) * PWM_Output.Duty_Cycle[i]) /100;
					PWM_Output.Temps_Bas[i]  = ((1000000 / PWM_Output.Frequence[i]) *(100 - PWM_Output.Duty_Cycle[i])) /100;		
					
					// Si le PWM est activé, alors on peut le mettre en route, avec la configuration définie précédemment (Fréquence et Duty Cycle)
					if (PWM_Output.Etat[i] == 1 && PWM_Output.Lock_State[i] != 1) 
					{
							Activer_PWM(i);
							PWM_Output.Lock_State[i] = 1; // On empêche de réactiver le PWM inutilement
					}
					// Si le PWM est désactivé, alors on l'éteint
					else if (PWM_Output.Etat[i] == 0) 
					{
						Desactiver_PWM(i);
						PWM_Output.Lock_State[i] = 0;
					}
				}
						
				/* #########################################################################################
										AFFICHAGE SUR LE TERMINAL (Optionnel. Utile uniquement en debug)
				######################################################################################### */	
				// Affichage des états des entrées et sorties sur le terminal
				if(AFFICHAGE_GPIO_TERMINAL)
				{
					// DEBUT
					sprintf(Retour,"\n\n####################################################################\n");
					Send_Text(Retour);
					Retour[0] = '\0';			
					sprintf(Retour,"\nENTREES/SORTIES\n");
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"\n####################################################################\n\n");
					Send_Text(Retour);
					Retour[0] = '\0';				
					
					// Entrées
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
					Send_Text("\n");
					
					// PWM
					for (i= 0; i < SIZE_PWM; i++)
					{
						sprintf(Retour,"PWM[%d]  \t Freq=%d \t Duty=%d \t Etat=%d\n",i,PWM_Output.Frequence[i],PWM_Output.Duty_Cycle[i],PWM_Output.Etat[i]);
						
						Send_Text(Retour);
						Retour[0] = '\0';
					}
				}
				// Affichage au terminal des variables internes liées au grafcet 
				if(AFFICHAGE_STEP_GRAFCET)
				{
					
					sprintf(Retour,"\n####################################################################\n");
					Send_Text(Retour);
					Retour[0] = '\0';			
					sprintf(Retour,"\nGRAFCET\n");
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"\n####################################################################\n\n");
					Send_Text(Retour);
					Retour[0] = '\0';			
					
					
					// Stabilité
					sprintf(Retour,"STABLE   : %d\n",Variable[79]);
					Send_Text(Retour);
					Retour[0] = '\0';	
					//Etapes actives
					sprintf(Retour,"etape e0 : %d\n",Variable[80]);
					Send_Text(Retour);
					Retour[0] = '\0';						
					sprintf(Retour,"etape e1 : %d\n",Variable[81]);
					Send_Text(Retour);
					Retour[0] = '\0';						
					sprintf(Retour,"etape e2 : %d\n",Variable[82]);
					Send_Text(Retour);
					Retour[0] = '\0';						
					sprintf(Retour,"etape e3 : %d\n",Variable[83]);
					Send_Text(Retour);
					Retour[0] = '\0';							
					Send_Text("\n");
					
					// Etapes precedentes
					sprintf(Retour,"old e0 : %d\n",Variable[84]);
					Send_Text(Retour);
					
					Retour[0] = '\0';		
					sprintf(Retour,"old e1 : %d\n",Variable[85]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"old e2 : %d\n",Variable[86]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"old e3 : %d\n",Variable[87]);
					Send_Text(Retour);
					Retour[0] = '\0';	
					Send_Text("\n");
					
					// Appels
					sprintf(Retour,"appel e0 : %d\n",Variable[88]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"appel e1 : %d\n",Variable[89]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"appel e2 : %d\n",Variable[90]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"appel e3 : %d\n",Variable[91]);
					Send_Text(Retour);
					Retour[0] = '\0';	
					Send_Text("\n");
					
					//Reponses
					sprintf(Retour,"reponse e0 : %d\n",Variable[92]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"reponse e1 : %d\n",Variable[93]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"reponse e2 : %d\n",Variable[94]);
					Send_Text(Retour);
					Retour[0] = '\0';		
					sprintf(Retour,"reponse e3 : %d\n",Variable[95]);
					Send_Text(Retour);
					Retour[0] = '\0';	
					Send_Text("\n");	
				}
				
		}
	}
   // Fin : Le CPU n'arrivera jamais ici
}
// FIN FONCTION MAIN

/*###############################################################################
																INTERRUPTIONS
###############################################################################*/

/*===============================================================================
FONCTION:     USART2_IRQHandler

Interruption sur l'USART 2
===============================================================================*/
void USART2_IRQHandler(void)
{
	if ((USART2->ISR&(1<<5)))
	{
		NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
		NVIC_DisableIRQ(TIM2_IRQn);		
		NVIC_DisableIRQ(TIM14_IRQn);
		
		// Si un caractère '?' est reçu par la liaison série, alors on indique que l'on souhaite recommencer la lecture du programme par un '!'
		if (USART2->RDR == '?')
		{	
			Reception_Programme = 0;
		}
		
		NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
		NVIC_EnableIRQ(TIM2_IRQn);		
		NVIC_EnableIRQ(TIM14_IRQn);
	}
}

/*===============================================================================
Interruption sur le Timer 1 => PWM 0
===============================================================================*/

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
	  if((TIM1->SR & (1<<0))== (1<<0)) // vérifions que c'est bien le debordement qui demande interruption
    {
			NVIC_DisableIRQ(USART2_IRQn);
			NVIC_DisableIRQ(TIM2_IRQn);
			NVIC_DisableIRQ(TIM14_IRQn);
			
			TIM1->SR &= ~(1<<0);  						// reset du drapeau de demande interruption

			if (PWM_Output.Value[0] == 1)
			{
				TIM1->ARR = PWM_Output.Temps_Haut[0] -1 ;
				PWM_Output.Value[0] = 0;
			}
			else
			{
				TIM1->ARR = PWM_Output.Temps_Bas[0] -1 ;
				PWM_Output.Value[0] = 1;
			}
			TIM1->CR1 |=(1<<0); 
			DigitalToggle(PWM0_Pin,PWM0_Port);
			
			NVIC_EnableIRQ(TIM2_IRQn);			
			NVIC_EnableIRQ(TIM14_IRQn);
			NVIC_EnableIRQ(USART2_IRQn);
    }	
}
/*===============================================================================
Interruption sur le Timer 2 => PWM 1
===============================================================================*/
void TIM2_IRQHandler (void)
{
	
  if((TIM2->SR & (1<<0))== (1<<0)) // vérifions que c'est bien le debordement qui demande interruption
    {
			NVIC_DisableIRQ(USART2_IRQn);
			NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
			NVIC_DisableIRQ(TIM14_IRQn);
			
			TIM2->SR &= ~(1<<0);  						// reset du drapeau de demande interruption
			
			if (PWM_Output.Value[1] == 1)
			{
				TIM2->ARR = PWM_Output.Temps_Haut[1] -1 ;
				PWM_Output.Value[1] = 0;
			}
			else
			{
				TIM2->ARR = PWM_Output.Temps_Bas[1] -1 ;
				PWM_Output.Value[1] = 1;
			}
			
			TIM2->CR1 |=(1<<0); 
			DigitalToggle(PWM1_Pin,PWM1_Port);
			
			NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);			
			NVIC_EnableIRQ(TIM14_IRQn);
			NVIC_EnableIRQ(USART2_IRQn);
    }
}
/*===============================================================================
Interruption sur le Timer 14 => PWM 2
===============================================================================*/

void TIM14_IRQHandler(void)
{
	  if((TIM14->SR & (1<<0))== (1<<0)) // vérifions que c'est bien le debordement qui demande interruption
    {
			NVIC_DisableIRQ(USART2_IRQn);
			NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
			NVIC_DisableIRQ(TIM2_IRQn);
			
			TIM14->SR &= ~(1<<0);  						// reset du drapeau de demande interruption

			if (PWM_Output.Value[2] == 1)
			{
				TIM14->ARR = PWM_Output.Temps_Haut[2] -1 ;
				PWM_Output.Value[2] = 0;
			}
			else
			{
				TIM14->ARR = PWM_Output.Temps_Bas[2] -1 ;
				PWM_Output.Value[2] = 1;
			}
			TIM14->CR1 |=(1<<0); 
			DigitalWrite(PWM2_Pin,PWM2_Port,1);
			
			NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);			
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_EnableIRQ(USART2_IRQn);
    }	
}


/*###############################################################################
																FONCTIONS LOCALES
###############################################################################*/

/*===============================================================================
FONCTION:     RAZ_ALL()
Remet à zéro l'ensemble des variables globales du programme
===============================================================================*/
void RAZ_ALL(void)
{
	int i;
	// Entrées
	RAZ_Tableau_int(Valeur_Precedentes_Entrees_GPIO,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Falling_Edge,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Rising_Edge,0,SIZE_IN);
	RAZ_Tableau_int(GPIO_Input.Valeur,0,SIZE_IN);
	
	//ADC
	RAZ_Tableau_int(ADC_Input.Etat,ETAT_DEFAUT_ADC,SIZE_ADC);
	RAZ_Tableau_int(ADC_Input.Valeur,0,SIZE_ADC);
	
	// Sorties
	RAZ_Tableau_int(GPIO_Output.Valeur,0,SIZE_OUT);
	
	// PWM
	RAZ_Tableau_int(PWM_Output.Etat,ETAT_DEFAUT_PWM,SIZE_PWM);
	RAZ_Tableau_int(PWM_Output.Duty_Cycle,0,SIZE_PWM);
	RAZ_Tableau_int(PWM_Output.Frequence,0,SIZE_PWM);
	
	//Tableaux Stack, Code et Variable
	//RAZ_Tableau_int(Code,0,SIZE_BIN);
	RAZ_Tableau_int(Stack,0,SIZE_BIN);
	RAZ_Tableau_int(Variable,0,SIZE_BIN);
	PC = 0;
	SP = -1; 
}