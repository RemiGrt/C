/**
* \file 
*			Map_Functions.c
* \author 
*			Thomas Broussard
* \date 
*			19 juin 2017
* \brief  
*			Contient les fonctions de gerer les Entrees/Sorties du microcontroleur pour le projet d'electronique
*/
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

Map Map_Sorties_PWM[SIZE_PWM];
Map Map_Entrees_ADC[SIZE_ADC];

/*################################################################################################################################################################
																															DEFINITION DES FONCTIONS GENERALES
################################################################################################################################################################*/


/** 
 * \fn  void RAZ_Tableau_int(int * Tab, int Debut, int Taille)
 * \brief 
 *			Met a zero un ensemble de cases contenues dans un tableau d'entiers
 * \param[in] 
 *			Tab			Tableau a remettre a zero
 * \param[in] 
 *			Debut				Case de debut
 * \param[in] 
 *			Taille					Taille du tableau a remettre a zero
 */
void RAZ_Tableau_int(int * Tab, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		Tab[i] = 0;
	}
}

/** 
 * \fn  void Write_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
 * \brief 
 *			Copie les informations d'un tableau Src vers un tableau Dest, avec un decalage lors de la copie, selon le pas donne
 * \param[in] 
 *			Tab_Dest			Tableau de destination
 * \param[in] 
 *			Tab_Src				Tableau source
 * \param[in] 
 *			Pas					Pas choisi
 * \param[in] 
 *			Debut_Dest		Debut de la destination
 * \param[in] 
 *			Taille_Src			Taille source
 */
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

/** 
 * \fn  void Read_Data_Decalage(int * Tab_Dest, int *Tab_Src, int Pas, int Debut_Dest, int Taille_Src)
 * \brief 
 *			Lire les informations d'un tableau Src (tableau variable[]) vers un tableau Dest (tableau "trie"), avec un decalage lors de la lecture, selon le pas donne
 * \param[in] 
 *			Tab_Dest			Tableau de destination
 * \param[in] 
 *			Tab_Src				Tableau source
 * \param[in] 
 *			Pas					Pas choisi
 * \param[in] 
 *			Debut_Dest		Debut de la destination
 * \param[in] 
 *			Taille_Src			Taille source
 */
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


/** 
 * \fn  void Define_Mapping_Entrees_GPIO(void)
 * \brief 
 *			Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectes aux entrees numeriques
 */
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

/** 
 * \fn  void Initialisation_Entrees_GPIO(void)
 * \brief 
 *			Initialise l'ensemble des entrees numeriques definies
 */
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

/** 
 * \fn  void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille)
 * \brief 
 *			A partir d'un tableau d'entier, on verifie l'ensemble des entrees definies dans Map_Entrees[SIZE_IN] \n On doit egalement preciser les cases de debut et de fin du tableau
 * \param[in] 
 *			Tab					Tableau 
 * \param[in] 
 *			Debut				Case de debut
 * \param[in] 
 *			Taille					Taille
 */
void Lecture_Entrees_GPIO(int *Tab, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		Tab[i] = DigitalRead(Map_Entrees[i - Debut].Pin,Map_Entrees[i - Debut].Port);
	}
}

/** 
 * \fn  void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille)
 * \brief 
 *			Determine la valeur des fronts de chaque entree en fonction de la valeur actuelle et de la valeur precedente 
 * \param[in] 
 *			*Valeur_Actuelle			Valeur actuelle 
 * \param[in] 
 *			*Valeur_Precedente		Valeur precedente
 * \param[in] 
 *			*Front_Montant				Front_Montant
 * \param[in] 
 *			*Front_Descendant		Front_Descendant
 * \param[in] 
 *			Debut								Debut
 * \param[in] 
 *			Taille								Taille : nombre de cases a remplir pour le tableau - donc nombre d'entree pour lesquelles nous voulons relever les etats
 */
void Fronts_Entrees_GPIO(int *Valeur_Actuelle, int *Valeur_Precedente, int *Front_Montant, int *Front_Descendant, int Debut, int Taille)
{
	int i;
	for (i = Debut; i < Debut + Taille; i++)
	{
		// Cas où un front Descendant est detecte
		if (Valeur_Actuelle[i] < Valeur_Precedente[i])
		{
			Front_Descendant[i] = 1;
			Front_Montant[i] 		= 0;
		}
		// Cas où un front Montant est detecte
		else if 
		(Valeur_Actuelle[i] > Valeur_Precedente[i])
		{
			Front_Descendant[i] = 0;
			Front_Montant[i] 		= 1;		
		}
		// Si La valeur actuelle est egale a la valeur precedente, alors on passe l'ensemble des fronts a zero
		else
		{
			Front_Descendant[i] = 0;
			Front_Montant[i] 		= 0;
		}
		// Une fois le front determine, on peut sauvegarder la valeur actuelle dans le tableau des valeurs precedente, pour le prochain appel de la fonction
		Valeur_Precedente[i] = Valeur_Actuelle[i];
	}	
}
/*################################################################################################################################################################
																													DEFINITION DES FONCTIONS DE SORTIES NUMERIQUES
################################################################################################################################################################*/


/** 
 * \fn  void Define_Mapping_Sorties_GPIO(void)
 * \brief 
 *			Remplit le tableau de structure Map_Sorties[SIZE_OUT] avec l'ensemble des Ports/Pins affectes aux sorties numeriques
 */
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



/** 
 * \fn  void Initialisation_Sorties_GPIO(void)
 * \brief 
 * 		Initialise l'ensemble des sorties numeriques definies
 */
 
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



/** 
 * \fn  void Ecriture_Sorties_GPIO(int *Tab, int Debut, int Taille)
 * \brief 
 * 		A partir d'un tableau d'entier, on actualise l'ensemble des sorties definies dans Map_Sorties[SIZE_OUT] \n On doit egalement preciser la case de debut du tableau, et la taille du tableau a lire
 * \param[in] 
 *			*Tab								Tableau
 * \param[in] 
 *			Debut				Case de debut
 * \param[in]  
 *			Taille			Taille du tableau
 */
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

/** 
 * \fn  void Define_Mapping_Entrees_ADC(void)
 * \brief 
 * 		Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectes aux entrees numeriques
 */
void Define_Mapping_Entrees_ADC(void)
{
	Map_Entrees_ADC[0].Pin = ADC0_Pin;			strcpy(Map_Entrees_ADC[0].Port, ADC0_Port);	
	Map_Entrees_ADC[1].Pin = ADC1_Pin;			strcpy(Map_Entrees_ADC[1].Port, ADC1_Port);	
	Map_Entrees_ADC[2].Pin = ADC2_Pin;			strcpy(Map_Entrees_ADC[2].Port, ADC2_Port);	
}

/** 
 * \fn  void Initialisation_Entrees_ADC(int Resolution)
 * \brief 
 * 		Initialise l'ensemble des entrees ADC definies, sans les activer
 * \param[in]  
 *			Resolution			Resolution souhaitee
 */
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


/** 
 * \fn  int Lecture_Entree_ADC(int Num_ADC, int NB_Mesures)
 * \brief 
 * 		Realise une serie de mesures sur l'entree ADC selectionnee, puis rnevoie la moyenne de ces valeurs
 * \param[in]  
 *			Num_ADC			Num_ADC
 * \param[in]  
 *			NB_Mesures			NB_Mesures
 */
int Lecture_Entree_ADC(int Num_ADC, int NB_Mesures)
{
	int Mesure = 0 , Moyenne = 0;
	//int Timeout = 0, Time_Max = 100000, Flag_Timeout = 0;
	int i;
	
	// Serie de mesure
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


/** 
 * \fn  void Define_Mapping_Sorties_PWM(void)
 * \brief 
 * 		Remplit le tableau de structure Map_Entrees[SIZE_IN] avec l'ensemble des Ports/Pins affectes aux entrees numeriques
 */
void Define_Mapping_Sorties_PWM(void)
{
	Map_Sorties_PWM[0].Pin = PWM0_Pin;			strcpy(Map_Sorties_PWM[0].Port, PWM0_Port);	
	Map_Sorties_PWM[1].Pin = PWM1_Pin;			strcpy(Map_Sorties_PWM[1].Port, PWM1_Port);	
	Map_Sorties_PWM[2].Pin = PWM2_Pin;			strcpy(Map_Sorties_PWM[2].Port, PWM2_Port);	
}

/** 
 * \fn  void Activer_PWM(int Num_PWM, int Frequence, int Duty_Cycle)
 * \brief 
 * 		Active l'interruption lie au signal PWM souhaite, en modifiant sa frequence et son rapport cyclique
 * \param[in]  
 *			Num_PWM			PWM pour lequel on souhaite activer l'interruption
 * \param[in]  
 *			Frequence			Frequence du PWM
 * \param[in]  
 *			Duty_Cycle			Rapport cyclique du PWM
 */
void Activer_PWM(int Num_PWM, int Frequence, int Duty_Cycle) // Activation du signal PWM (0, 1 ou 2) selectionne en mode interruption
{
	int Freq_Div = (1000000 / Frequence );
	int Periode = ((Freq_Div -1) *Duty_Cycle) /100;
	
	switch (Num_PWM)
	{
		// PWM 0
		case 0 : 
						// Configuration de la frequence 
						TIM2->ARR = Freq_Div - 1; 
		
						// Configuration du rapport cyclique
						TIM2->CCR2 = Periode ;
		
						// Activation du TIMER
						TIM2->CR1 |=(1<<0); 
		
						// Activation de l'interruption
					//	NVIC_EnableIRQ(TIM2_IRQn);
		break;
		/*
		// PWM 1
		case 1 : 
						// Configuration de la frequence 
						TIM3->PSC=(SystemCoreClock / 1000000);
						TIM3->ARR = Freq_Div - 1; 
						// Configuration du rapport cyclique
						TIM3->CCR1 = Periode ;
						NVIC_EnableIRQ(TIM3_IRQn);
		break;
		
		// PWM 2
		case 2 : 
						// Configuration de la frequence 
						TIM15->PSC=(SystemCoreClock / 1000000);
						TIM15->ARR = Freq_Div - 1; 
						// Configuration du rapport cyclique
						TIM15->CCR1 = Periode ;
						NVIC_EnableIRQ(TIM15_IRQn);
		break;
		*/
		// Erreur
		default : break;
	}
}


/** 
 * \fn  void Initialisation_Sorties_PWM(void)
 * \brief 
 * 		Initialise l'ensemble des timer et des entrees PWM
 */
void Initialisation_Sorties_PWM(void)
{
	int i = 0;
	
	Define_Mapping_Sorties_PWM();
	
	// Initialisation des pattes alternatives
	initPatte_AF(Map_Sorties_PWM[0].Pin,Map_Sorties_PWM[0].Port,"noPull",2);
	
	init_TIM2_PWM();
	
	//initPatte_AF(Map_Sorties_PWM[1].Pin,Map_Sorties_PWM[1].Port,"noPull",4);
	//initPatte_AF(Map_Sorties_PWM[2].Pin,Map_Sorties_PWM[0].Port,"noPull",2);
	
	// Initialisation des timers en mode interruption
	
	//init_TIM3_PWM_Interrupt();
	//init_TIM15_PWM_Interrupt();
	
}


/** 
 * \fn  void Desactiver_PWM(int Num_PWM) 
 * \brief 
 * 		Desactive le signal PWM en question
 * \param[in]  
 *			Num_PWM			Numero du PWM que l'on souhaite desactiver
 */
void Desactiver_PWM(int Num_PWM) 
{
	switch (Num_PWM)
	{
		// PWM 0
		case 0 : 
						RCC->APB1ENR &= ~(1<<0); 	// desactivation de l'horloge du timer 2
						NVIC_DisableIRQ(TIM2_IRQn);
		break;
		
		// PWM 1
		case 1 : 
						RCC->APB1ENR &= ~(1<<1);  // desactivation de l'horloge du timer 3
						NVIC_DisableIRQ(TIM3_IRQn);
		break;
		
		// PWM 2
		case 2 : 
						RCC->APB2ENR &= ~(1<<16); // desactivation de l'horloge du timer 15 
						NVIC_DisableIRQ(TIM15_IRQn);
		break;
		
		// Erreur
		default : break;
	}
}



