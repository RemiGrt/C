/********************************************************************************
Titre : ADC1.c
Auteur : Thomas Broussard
Date : 21/02/17
--------------------------------
Description : Librairie contenant les fonctions pour effectuer des actions sur l'ADC1
*	Initialisation des ADC1
*	Lecture du résultat d'une conversion
*	


--------------------------------
Mise à jour :  


********************************************************************************/
#include "stm32f0xx.h"   
#include "string.h"
#include "ADC.h"

/*===============================================================================
  FUNCTION:     initADC1_SingleMode(unsigned int Pin, char* Port,unsigned int Resolution)
  DESCRIPTION:  Initialisation d'une patte en ADC1 , mode single , sans interruption
  PARAMETERS:   Numéro de la patte, Port de la patte, Résolution de la conversion
  RETURNS:   	rien   
  REQUIREMENTS: Avoir activé au moins une patte en mode analogique
===============================================================================*/
void initADC1_SingleMode(unsigned int Resolution)
{
	//Activation de l'horloge dédiée à l'ADC1
	RCC->APB2ENR |= (1<<9);
	
	// Choix de la clock ADC_CLK (Asynchrone) 
	ADC1->CFGR2 &=~ ((1<<31)|(1<<30));
	
	// Calibration de l'ADC1
	Calibration_ADC1();
	
	// Activation de l'ADC1
	Enable_ADC1();
	
	//Init_Analogic_Mode(Pin,Port);
	// Choix de la résolution : 12, 10, 8 ou 6 bits (par défaut : 12 bits)
	switch(Resolution)
	{
		case 12 :
					ADC1->CFGR1 &=~ ((1<<4)|(1<<3));
					break;
		case 10 :
					ADC1->CFGR1 &=~ (1<<4);
					ADC1->CFGR1 |=  (1<<3);
					break;
		case 8 :
					ADC1->CFGR1 |=  (1<<4);
					ADC1->CFGR1 &=~ (1<<3);
					break;
		case 6 :
					ADC1->CFGR1 |= ((1<<4)|(1<<3));
					break;
		default : 
					ADC1->CFGR1 &=~ ((1<<4)|(1<<3));
					break;
	}
	
	// Choix du mode Single : bit 13 du registre CFGR1 à '0'
	ADC1->CFGR1 &=~ (1<<13);
	
	// Durée pour effectuer une conversion (par défaut, on choisit la plus longue possible pour avoir le résultat le plus précis possible)
	ADC1->SMPR |= ((1<<2)|(1<<1)|(1<<0));
	
	// Choix de VREFint comme signal à convertir (VREFint : signal analogique arrivant sur la patte choisie)
	ADC->CCR |= (1<<22);
}

/*===============================================================================
  FUNCTION:     Start_ADC1_Conversion
  DESCRIPTION:  Réalise une conversion sur l'ADC1, sans interruption
  PARAMETERS:   Aucun
  RETURNS:   	Résultat de la conversion (en décimal)
  REQUIREMENTS: l'ADC1 doit être initialisé et activé
===============================================================================*/
int Start_ADC1_Conversion(int Channel)
{
		int Result;
		
		// Activation de l'ADC1
		Enable_ADC1();
	
		// Choix du channel à convertir
		Select_Channel_ADC(Channel);
	
		// Début de la conversion ADC1
		ADC1->CR |= ADC_CR_ADSTART; 
	
		while ((ADC1->ISR & (1<<2)) == 0) // On attend que la conversion soit terminée pour pouvoir lire le résultat
		{
		/* For robust implementation, add here time-out management */
		}
		Result =  ADC1->DR;
		//ADC1->CFGR1 ^= ADC_CFGR1_SCANDIR; /* Toggle the scan direction */
			
		// Désactivation de l'ADC1
		Disable_ADC1();
		
		return Result;
}
	

/*===============================================================================
  FUNCTION:     initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution)
  DESCRIPTION:  Initialisation d'une patte en ADC1,en mode continu, avec interruption à chaque fin de conversion
  PARAMETERS:   Numéro de la patte, Port de la patte, Résolution de la conversion
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution)
{
	/* Fonction d'interruption utilisable dans main.c : 
	void ADC1_COMP_IRQHandler(void)
	{
		// On vérifie que la demande d'interruption correspond bien à une fin de conversion (EOC)
		if(ADC1->ISR & (1<<2))
		{
			ADC1->ISR &=~(1<<2); //Acquittement de la demande d'interruption
			Result = ADC1->DR; // On enregistre le résultat de la conversion dans une variable globale
		}
	}
	*/
	
	//Activation de l'horloge dédiée à l'ADC1
	RCC->APB2ENR |= (1<<9);
	RCC->CR2 |= (1<<0);
	// On vérifie que la Clock HSI14 est prête 
	while ((RCC->CR2 & (1<<1))== 0);
	
	// Choix de la clock ADC_CLK (Asynchrone)
	ADC1->CFGR2 &=~ ((1<<31)|(1<<30));

	// Calibration de l'ADC1
	Calibration_ADC1();

	// Activation du mode Analogique sur la patte souhaitée
	if (strcmp(Port,"A") == 0)
	{
		GPIOA->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 à '1'
		GPIOA->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N à '1'
	}
	else if (strcmp(Port,"B") == 0)
	{
		GPIOB->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 à '1'
		GPIOB->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N à '1'
	}
	else if (strcmp(Port,"C") == 0)
	{
		GPIOC->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 à '1'
		GPIOC->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N à '1'
	}
	// Choix de la résolution : 12, 10, 8 ou 6 bits (par défaut : 12 bits)
	switch(Resolution)
	{
		case 12 :
					ADC1->CFGR1 &=~ ((1<<4)|(1<<3));
					break;
		case 10 :
					ADC1->CFGR1 &=~ (1<<4);
					ADC1->CFGR1 |=  (1<<3);
					break;
		case 8 :
					ADC1->CFGR1 |=  (1<<4);
					ADC1->CFGR1 &=~ (1<<3);
					break;
		case 6 :
					ADC1->CFGR1 |= ((1<<4)|(1<<3));
					break;
		default : 
					ADC1->CFGR1 &=~ ((1<<4)|(1<<3));
					break;
	}
	
	// Choix du mode Continu : bit 13 du registre CFGR1 à '1' et bit 16 à '0'
	ADC1->CFGR1 |= (1<<13);
	ADC1->CFGR1 &=~ (1<<16);
	
	// Activation auto de la conversion : on ne veut pas de trigger externe
	ADC1->CFGR1 &=~((1<<11)|(1<<10));
	
	// Sélection du canal de conversion en fonction de la patte
	ADC1->CHSELR |= (1<<Pin);
	
	// Durée pour effectuer une conversion (par défaut, on choisit la plus longue possible pour avoir le résultat le plus précis possible)
	ADC1->SMPR |= ((1<<2)|(1<<1)|(1<<0));
	
		// Choix de VREFint comme signal à convertir (VREFint : signal analogique arrivant sur la patte choisie)
	ADC->CCR |= (1<<22);

	// Activation de l'interruption "fin de conversion"
	ADC1->IER |=(1<<2);//((1<<4)|(1<<3)|(1<<2));
	
	// Activation de l'interruption sur l'ADC1
	NVIC_EnableIRQ(ADC1_COMP_IRQn);
	// Choix de la priorité pour l'interruption sur ADC1 : 0 => passe avant tout le reste
	NVIC_SetPriority(ADC1_COMP_IRQn,0);	


	// Activation de l'ADC1
	Enable_ADC1();
	
	// Lancement de la conversion
	Start_ADC1();
}

/*===============================================================================
  FUNCTION:     Disable_ADC1
  DESCRIPTION:  Désactive l'ADC1
  PARAMETERS:   rien
  RETURNS:   		rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Disable_ADC1(void)
{
	// On vérifie qu'aucune conversion n'est en cours d'exécution
	if ((ADC1->CR & (1<<2)) != 0) 
	{
		ADC1->CR |= (1<<4); // Si une conversion est en cours, on l'arrête
	}
	while ((ADC1->CR & (1<<4)) != 0); // On attend que la conversion soit correctement stoppée
	
	ADC1->CR |= (1<<1); // Désactivation de l'ADC1
	while ((ADC1->CR & (1<<0)) != 0); // On attend que l'ADC1 soit correctement désactivée
}

/*===============================================================================
  FUNCTION:     Enable_ADC1
  DESCRIPTION:  Active l'ADC1
  PARAMETERS:   rien
  RETURNS:   		rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Enable_ADC1(void)
{
	// Activation de l'ADC
	ADC1->CR |=(1<<0); 
	while ((ADC1->ISR & (1<<0)) == 0); //On attend que l'ADC soit correctement activé
}
/*===============================================================================
  FUNCTION:     Start_ADC1
  DESCRIPTION:  Démarre une conversion sur l'ADC1
  PARAMETERS:   rien
  RETURNS:   		rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Start_ADC1(void)
{
	ADC1->CR |=(1<<2); //Lancement de la conversion
}

/*===============================================================================
  FUNCTION:     Calibration_ADC1
  DESCRIPTION:  Permet de calibrer l'ADC1
  PARAMETERS:   rien
  RETURNS:   		rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Calibration_ADC1(void)
{
	if ((ADC1->CR & (1<<0)) != 0)
	{
		ADC1->CR &= ~(1<<0); // RAZ du bit ADEN si il est déjà à '1'
	}
	ADC1->CR |= ADC_CR_ADCAL; // Lancement de la calibration
	while ((ADC1->CR & ADC_CR_ADCAL) != 0); // On attend que la calibration soit terminée
}

/*===============================================================================
  FUNCTION:     Select_Channel_ADC
  DESCRIPTION:  Choix du channel à convertir
  PARAMETERS:   Pin de la patte 
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void Select_Channel_ADC(unsigned int Channel)
{
		// Sélection du canal de conversion en fonction de la patte
		ADC1->CHSELR = 0;// RAZ du registre
		ADC1->CHSELR |= (1<<Channel); // Ajout du channel souhaité

}