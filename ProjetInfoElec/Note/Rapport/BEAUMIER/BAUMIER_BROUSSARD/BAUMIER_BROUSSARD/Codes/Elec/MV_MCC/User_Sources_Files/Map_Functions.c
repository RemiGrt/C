//#############################################################
// Auteur : Thomas Broussard
// Date : 19/06/17
// Titre : Liaison_Serie.c
//------------------------------------------------------------
// Description  :
//	Contient les fonctions de gérer les Entrées/Sorties du microcontrôleur
//	pour le projet d'électronique
//#############################################################

// Librairies du MCC
#include "stm32f0xx.h"  

// Librairies du pc
#include <stdio.h>
#include "string.h"

// Librairies locales
#include "InitPins.h" 
#include "ADC.h"
#include "Mapping.h"
#include "TIMER.h"
#include "DigitalGPIO.h"

/*########################################
					DEFINITION DES STRUCTURES
########################################*/

typedef struct
{
	int Pin;
	char Port[2];
} Map;


Map Map_Entrees[SIZE_IN];

Map Map_Sorties[SIZE_OUT];

Map Map_Timer_PWM[SIZE_PWM];
Map Map_Sorties_PWM[SIZE_PWM];

Map Map_Entrees_ADC[SIZE_ADC];

/*################################################################################################################################################################
																															DEFINITION DES FONCTIONS GENERALES
################################################################################################################################################################*/
/*===============================================================================
FONCTION:     RAZ_Tableau_int()
Met à zéro un ensemble de cases contenues dans un tableau d'entiers
===============================================================================*/
void RAZ_Tableau_int(int * Tab, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		Tab[i] = 0;
	}
}

/*===============================================================================
FONCTION:     Write_Data_Decalage()
Copie les informations d'un tableau Src vers un tableau Dest, avec un decalage lors de la copie, selon le pas donné
===============================================================================*/
void Write_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
{
	int i,j;
	j = Debut_Dest;
	for (i = 0; i < Taille_Src; i++)
	{
		Tab_Dest[j] = Tab_Src[i];
		j+= Pas;
	}
}

/*===============================================================================
FONCTION:     Read_Data_Decalage()
Copie les informations d'un tableau Src vers un tableau Dest, avec un decalage lors de la copie, selon le pas donné
===============================================================================*/
void Read_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
{
	int i,j;
	j = Debut_Dest;
	for (i = 0; i < Taille_Src; i++)
	{
		Tab_Dest[i] = Tab_Src[j];
		j+= Pas;
	}
}


/*################################################################################################################################################################
																															DEFINITION DES FONCTIONS D'ENTREES NUMERIQUES
################################################################################################################################################################*/
/*===============================================================================
FONCTION:     Define_Mapping_Entrees_GPIO()
Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectés aux entrées numériques
===============================================================================*/
void Define_Mapping_Entrees_GPIO(void)
{
	Map_Entrees[0].Pin = IN0_Pin;			strcpy(Map_Entrees[0].Port, IN0_Port);	
	Map_Entrees[1].Pin = IN1_Pin;			strcpy(Map_Entrees[1].Port, IN1_Port);	
	Map_Entrees[2].Pin = IN2_Pin;			strcpy(Map_Entrees[2].Port, IN2_Port);	
	Map_Entrees[3].Pin = IN3_Pin;			strcpy(Map_Entrees[3].Port, IN3_Port);	
	Map_Entrees[4].Pin = IN4_Pin;			strcpy(Map_Entrees[4].Port, IN4_Port);	
	Map_Entrees[5].Pin = IN5_Pin;			strcpy(Map_Entrees[5].Port, IN5_Port);	
	Map_Entrees[6].Pin = IN6_Pin;			strcpy(Map_Entrees[6].Port, IN6_Port);	
	Map_Entrees[7].Pin = IN7_Pin;			strcpy(Map_Entrees[7].Port, IN7_Port);	
	Map_Entrees[8].Pin = IN8_Pin;			strcpy(Map_Entrees[8].Port, IN8_Port);	
	Map_Entrees[9].Pin = IN9_Pin;			strcpy(Map_Entrees[9].Port, IN9_Port);	
	Map_Entrees[10].Pin = IN10_Pin;		strcpy(Map_Entrees[10].Port, IN10_Port);	
	Map_Entrees[11].Pin = IN11_Pin;		strcpy(Map_Entrees[11].Port, IN11_Port);	
	Map_Entrees[12].Pin = IN12_Pin;		strcpy(Map_Entrees[12].Port, IN12_Port);	
	Map_Entrees[13].Pin = IN13_Pin;		strcpy(Map_Entrees[13].Port, IN13_Port);	
	Map_Entrees[14].Pin = IN14_Pin;		strcpy(Map_Entrees[14].Port, IN14_Port);	
	Map_Entrees[15].Pin = IN15_Pin;		strcpy(Map_Entrees[15].Port, IN15_Port);	
}

/*===============================================================================
FONCTION:     Initialisation_Entrees_GPIO() 
Initialise l'ensemble des entrées numériques définies
===============================================================================*/
void Initialisation_Entrees_GPIO(void)
{
	int i;
	Define_Mapping_Entrees_GPIO();
	for (i = 0; i < SIZE_IN; i++)
	{
		Map_Entrees[i].Port[1] ='\0';
		initPatte_IN(Map_Entrees[i].Pin , Map_Entrees[i].Port , "Pull-Down");	
	}
}

/*===============================================================================
FONCTION:     Lecture_Entrees_GPIO() 
A partir d'un tableau d'entier, on vérifie l'ensemble des entrées définies dans Map_Entrees[SIZE_IN]
On doit également préciser les cases de début et de fin du tableau
===============================================================================*/
void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		Tab[i] = DigitalRead(Map_Entrees[i - Debut].Pin,Map_Entrees[i - Debut].Port);
	}
}

/*===============================================================================
FONCTION:     Fronts_Entrees_GPIO() 
Determine la valeur des fronts de chaque entrée en fonction de la valeur actuelle et de la valeur précédente 
===============================================================================*/
void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		// Cas où un front Descendant est détecté
		if (Valeur_Actuelle[i] < Valeur_Precedente[i])
		{
			Front_Descendant[i] = 1;
			Front_Montant[i] 		= 0;
		}
		// Cas où un front Montant est détecté
		else if 
		(Valeur_Actuelle[i] > Valeur_Precedente[i])
		{
			Front_Descendant[i] = 0;
			Front_Montant[i] 		= 1;		
		}
		// Si La valeur actuelle est égale à la valeur précédente, alors on passe l'ensemble des fronts à zéro
		else
		{
			Front_Descendant[i] = 0;
			Front_Montant[i] 		= 0;
		}
		// Une fois le front déterminé, on peut sauvegarder la valeur actuelle dans le tableau des valeurs précédente, pour le prochain appel de la fonction
		Valeur_Precedente[i] = Valeur_Actuelle[i];
	}	
}
/*################################################################################################################################################################
																													DEFINITION DES FONCTIONS DE SORTIES NUMERIQUES
################################################################################################################################################################*/

/*===============================================================================
FONCTION:     Define_Mapping_Sorties_GPIO()
Remplit le tableau de structure Map_Sorties[SIZE_OUT] avec l'ensemble des Ports/Pins affectés aux sorties numériques
===============================================================================*/
void Define_Mapping_Sorties_GPIO(void)
{
	Map_Sorties[0].Pin = OUT0_Pin;			strcpy(Map_Sorties[0].Port, OUT0_Port);	
	Map_Sorties[1].Pin = OUT1_Pin;			strcpy(Map_Sorties[1].Port, OUT1_Port);	
	Map_Sorties[2].Pin = OUT2_Pin;			strcpy(Map_Sorties[2].Port, OUT2_Port);	
	Map_Sorties[3].Pin = OUT3_Pin;			strcpy(Map_Sorties[3].Port, OUT3_Port);	
	Map_Sorties[4].Pin = OUT4_Pin;			strcpy(Map_Sorties[4].Port, OUT4_Port);	
	Map_Sorties[5].Pin = OUT5_Pin;			strcpy(Map_Sorties[5].Port, OUT5_Port);	
	Map_Sorties[6].Pin = OUT6_Pin;			strcpy(Map_Sorties[6].Port, OUT6_Port);	
	Map_Sorties[7].Pin = OUT7_Pin;			strcpy(Map_Sorties[7].Port, OUT7_Port);	
	Map_Sorties[8].Pin = OUT8_Pin;			strcpy(Map_Sorties[8].Port, OUT8_Port);	
	Map_Sorties[9].Pin = OUT9_Pin;			strcpy(Map_Sorties[9].Port, OUT9_Port);	
	Map_Sorties[10].Pin = OUT10_Pin;		strcpy(Map_Sorties[10].Port, OUT10_Port);	
	Map_Sorties[11].Pin = OUT11_Pin;		strcpy(Map_Sorties[11].Port, OUT11_Port);	
	Map_Sorties[12].Pin = OUT12_Pin;		strcpy(Map_Sorties[12].Port, OUT12_Port);	
	Map_Sorties[13].Pin = OUT13_Pin;		strcpy(Map_Sorties[13].Port, OUT13_Port);	
	Map_Sorties[14].Pin = OUT14_Pin;		strcpy(Map_Sorties[14].Port, OUT14_Port);	
	Map_Sorties[15].Pin = OUT15_Pin;		strcpy(Map_Sorties[15].Port, OUT15_Port);	
}

/*===============================================================================
FONCTION:     Initialisation_Sorties_GPIO() 
Initialise l'ensemble des sorties numériques définies
===============================================================================*/
void Initialisation_Sorties_GPIO(void)
{
	int i;
	Define_Mapping_Sorties_GPIO();
	for (i = 0; i < SIZE_OUT; i++)
	{
		Map_Sorties[i].Port[1] ='\0';
		initPatte_OUT(Map_Sorties[i].Pin , Map_Sorties[i].Port,"Pull-Down");
	}		
	
}

/*===============================================================================
FONCTION:     Ecriture_Sorties_GPIO() 
A partir d'un tableau d'entier, on actualise l'ensemble des sorties définies dans Map_Sorties[SIZE_OUT]
On doit également préciser la case de début du tableau, et la taille du tableau à lire
===============================================================================*/
void Ecriture_Sorties_GPIO(int *Tab, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < (Debut + Taille); i++)
	{
		DigitalWrite(Map_Sorties[i - Debut].Pin , Map_Sorties[i - Debut].Port, Tab[i]);
	}
}

/*################################################################################################################################################################
																													DEFINITION DES FONCTIONS D'ENTREES ADC
################################################################################################################################################################*/

/*===============================================================================
FONCTION:     Define_Mapping_Entrees_GPIO()
Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectés aux entrées numériques
===============================================================================*/
void Define_Mapping_Entrees_ADC(void)
{
	Map_Entrees_ADC[0].Pin = ADC0_Pin;			strcpy(Map_Entrees_ADC[0].Port, ADC0_Port);	
	Map_Entrees_ADC[1].Pin = ADC1_Pin;			strcpy(Map_Entrees_ADC[1].Port, ADC1_Port);	
	Map_Entrees_ADC[2].Pin = ADC2_Pin;			strcpy(Map_Entrees_ADC[2].Port, ADC2_Port);	
}

/*===============================================================================
FONCTION:     Initialisation_Entrees_ADC() 
Initialise l'ensemble des entrées ADC définies, sans les activer
===============================================================================*/
void Initialisation_Entrees_ADC(int Resolution)
{
	int i= 0;
	Define_Mapping_Entrees_ADC();
	
	for ( i = 0 ; i < SIZE_ADC; i++)
	{
		Map_Entrees_ADC[i].Port[1] ='\0';
		Init_Analogic_Mode(Map_Entrees_ADC[i].Pin , Map_Entrees_ADC[i].Port);
	}
	initADC1_SingleMode(Resolution);
}
/*===============================================================================
FONCTION:     Lecture_Entree_ADC() 
Réalise une série de mesures sur l'entrée ADC sélectionnée, puis rnevoie la moyenne de ces valeurs
===============================================================================*/
int Lecture_Entree_ADC(int Num_ADC, int NB_Mesures)
{
	int Mesure = 0 , Moyenne = 0;
	//int Timeout = 0, Time_Max = 100000, Flag_Timeout = 0;
	int i;
	
	// Série de mesure
	for (i = 0; i < NB_Mesures; i++)
	{
		Mesure = Start_ADC1_Conversion(Map_Entrees_ADC[Num_ADC].Pin);
		Moyenne += Mesure;
	}
	return (unsigned int)(Moyenne / NB_Mesures);
}

/*################################################################################################################################################################
																													DEFINITION DES FONCTIONS DE SORTIES PWM
################################################################################################################################################################*/

/*===============================================================================
FONCTION:     Define_Mapping_Sorties_PWM()
Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectés aux entrées numériques
===============================================================================*/
void Define_Mapping_Sorties_PWM(void)
{
	Map_Sorties_PWM[0].Pin = PWM0_Pin;			strcpy(Map_Sorties_PWM[0].Port, PWM0_Port);	
	Map_Sorties_PWM[1].Pin = PWM1_Pin;			strcpy(Map_Sorties_PWM[1].Port, PWM1_Port);	
	Map_Sorties_PWM[2].Pin = PWM2_Pin;			strcpy(Map_Sorties_PWM[2].Port, PWM2_Port);	
	
	Map_Timer_PWM[0].Pin = TIM1_Pin;			strcpy(Map_Timer_PWM[0].Port, TIM1_Port);	
	Map_Timer_PWM[1].Pin = TIM2_Pin;			strcpy(Map_Timer_PWM[1].Port, TIM2_Port);	
	Map_Timer_PWM[2].Pin = TIM14_Pin;			strcpy(Map_Timer_PWM[2].Port, TIM14_Port);	
}


/*===============================================================================
FONCTION:     Activer_PWM() 
Active l'interruption lié au signal PWM souhaité, en modifiant sa fréquence et son rapport cyclique
===============================================================================*/
void Activer_PWM(int Num_PWM) // Activation du signal PWM (0, 1 ou 2) sélectionné en mode interruption
{
	
	switch (Num_PWM)
	{
		// PWM 0
		case 0 : 
						
						//Activation de l'horloge
						RCC->APB2ENR |= (1<<11); 
						init_TIM1_PWM();
						// Init de la fin de comptage 
						TIM1->ARR = 1000; 
						// Activation de l'interruption
						NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
						// Activation du TIMER
						TIM1->CR1 |=(1<<0); 
		break;
		
		// PWM 1
		case 1 : 
						//Activation de l'horloge
						RCC->APB1ENR |= (1<<0); 
						init_TIM2_PWM();
						// Init de la fin de comptage 
						TIM2->ARR = 1000; 
						// Activation de l'interruption
						NVIC_EnableIRQ(TIM2_IRQn);
						// Activation du TIMER
						TIM2->CR1 |=(1<<0); 
		break;
		
		// PWM 2
		case 2 : 
						//Activation de l'horloge
						RCC->APB1ENR |= (1<<8); 
						init_TIM14_PWM();
						// Init de la fin de comptage 
						TIM14->ARR = 1000; 
						// Activation de l'interruption
						NVIC_EnableIRQ(TIM14_IRQn);
						// Activation du TIMER
						TIM14->CR1 |=(1<<0); 
		break;

		// Erreur
		default : break;
	}
}

/*===============================================================================
FONCTION:     Desactiver_PWM() 
Désactive le signal PWM en question
===============================================================================*/
void Desactiver_PWM(int Num_PWM) 
{
	switch (Num_PWM)
	{
		// PWM 0
		case 0 : 
						TIM1->CR1 &= ~(1<<0); // désactivation du timer
						RCC->APB1ENR &= ~(1<<0); 	// désactivation de l'horloge du timer 2
						NVIC_DisableIRQ(TIM1_CC_IRQn);// désactivation de l'interruption
		break;
		
		// PWM 1
		case 1 : 
						TIM2->CR1 &= ~(1<<0); // désactivation du timer
						RCC->APB2ENR &= ~(1<<11);  // désactivation de l'horloge du timer 1
						NVIC_DisableIRQ(TIM2_IRQn);// désactivation de l'interruption
		break;
		
		// PWM 2
		case 2 : 
						TIM14->CR1 &= ~(1<<0); // désactivation du timer
						RCC->APB1ENR &= ~(1<<8); // désactivation de l'horloge du timer 14
						NVIC_DisableIRQ(TIM14_IRQn); // désactivation de l'interruption
		break;
		
		// Erreur
		default : break;
	}
}

/*===============================================================================
FONCTION:     Initialisation_Sorties_PWM() 
Initialise l'ensemble des timer et des entrées PWM
===============================================================================*/
void Initialisation_Sorties_PWM(void)
{
	Define_Mapping_Sorties_PWM();

	// TIMER 1
	initPatte_OUT(Map_Sorties_PWM[0].Pin,Map_Sorties_PWM[0].Port,"Pull-Down");
	initPatte_AF(Map_Timer_PWM[0].Pin,Map_Timer_PWM[0].Port,"noPull",2);
	//init_TIM1_PWM();
	//Desactiver_PWM(0);
	
	// TIMER 2 
	initPatte_OUT(Map_Sorties_PWM[1].Pin,Map_Sorties_PWM[1].Port,"Pull-Down");
	initPatte_AF(Map_Timer_PWM[1].Pin,Map_Timer_PWM[1].Port,"noPull",2);
	//init_TIM2_PWM();
	//Desactiver_PWM(1);
	
	// TIMER 14
	initPatte_OUT(Map_Sorties_PWM[2].Pin,Map_Sorties_PWM[2].Port,"Pull-Down");
	initPatte_AF(Map_Timer_PWM[2].Pin,Map_Timer_PWM[2].Port,"noPull",4);
	//init_TIM14_PWM();
	//Desactiver_PWM(2);
}

