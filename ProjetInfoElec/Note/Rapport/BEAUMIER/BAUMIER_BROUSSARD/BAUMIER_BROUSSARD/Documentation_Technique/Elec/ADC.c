/**
* \file 
*			ADC.c
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			21 février 2017
* \brief  
*			Librairie contenant les fonctions pour effectuer des actions sur l'ADC1\n
*			Initialisation des ADC1\n
*			Lecture du résultat d'une conversion
*/

#include "stm32f0xx.h"   
#include "string.h"
#include "ADC.h"

/** 
 * \fn  void initADC1_SingleMode(unsigned int Resolution)
 * \brief 
 *			Initialisation d'une patte en ADC1, mode single, sans interruption \n
 * 		\b Avoir activé au moins une patte en mode analogique
 * \param[in] 
 *			Resolution		Résolution de la conversion
 */
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

/** 
 * \fn  
 *			int Start_ADC1_Conversion(int Channel)
 * \brief 
 *			Réalise une conversion sur l'ADC1, sans interruption \n
 *			\b/!\ L'ADC1 doit être initialisé et activé \b/!\
 * \param[in] 
 *			Channel				Channel choisi
 * \return 
 *			Résultat de la conversion en décimal
 */
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
	
/** 
 * \fn  void initADC1_ContinuousMode(unsigned int Pin, char* Port,unsigned int Resolution)
 * \brief 
 *			Initialisation d'une patte en ADC1,en mode continu, avec interruption à chaque fin de conversion
 * \param[in] 
 *			Pin				Numéro de la patte
 * \param[in] 
 *			Port			Port de la patte
 * \param[in] 
 *			Resolution		Résolution de la conversion
 */
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

/** 
 * \fn  void Disable_ADC1(void)
 * \brief 
 *			Désactive l'ADC1
 */
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

/** 
 * \fn  void Enable_ADC1(void)
 * \brief 
 *			Active l'ADC1
 */
void Enable_ADC1(void)
{
	// Activation de l'ADC
	ADC1->CR |=(1<<0); 
	while ((ADC1->ISR & (1<<0)) == 0); //On attend que l'ADC soit correctement activé
}

/** 
 * \fn  void Start_ADC1(void)
 * \brief 
 *			Démarre une conversion sur l'ADC1
 */
void Start_ADC1(void)
{
	ADC1->CR |=(1<<2); //Lancement de la conversion
}

/** 
 * \fn  void Calibration_ADC1(void)
 * \brief 
 *			Permet de calibrer l'ADC1
 */
void Calibration_ADC1(void)
{
	if ((ADC1->CR & (1<<0)) != 0)
	{
		ADC1->CR &= ~(1<<0); // RAZ du bit ADEN si il est déjà à '1'
	}
	ADC1->CR |= ADC_CR_ADCAL; // Lancement de la calibration
	while ((ADC1->CR & ADC_CR_ADCAL) != 0); // On attend que la calibration soit terminée
}

/** 
 * \fn  void Select_Channel_ADC(unsigned int Channel)
 * \brief 
 *			Choix du channel à convertir
 * \param[in] 
 *			Channel			Channel choisi
 */
void Select_Channel_ADC(unsigned int Channel)
{
		// Sélection du canal de conversion en fonction de la patte
		ADC1->CHSELR = 0;// RAZ du registre
		ADC1->CHSELR |= (1<<Channel); // Ajout du channel souhaité

}
