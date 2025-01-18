/**
* \file 
*			TIMER.c
* \author 
*			Thomas Broussard
* \date 
*			21 fevrier 2017
* \brief  
*			Librairie contenant les fonctions pour effectuer des actions avec les timers\n
*			Initialisation d'un timer\n
*			Interruption sur un timer
*			\b Remarque :\n
*			La librairie timer pourra être associee à d'autre librairie ( ADC,UART,PWM...) pour fabriquer des fonctions plus complexes.
*/

#include "stm32f0xx.h"   
#include "string.h"
#include "TIMER.h"

/** 
 * \fn  void init_TIM2_PWM(void)
 * \brief 
 *			Initialisation du timer2 en mode PWM
 */
void init_TIM2_PWM(void)
{
	//Activation de l'horloge
	RCC->APB1ENR |= (1<<0); 
	//Selection du mode de comptage : mode UP
	TIM2->CR1 &=~(1<<4);
	// Normalisation de la frequence à 1MHz
	TIM2->PSC=(SystemCoreClock / 1000000);
	
	// Desactivation de l'interruption
	TIM2->DIER &=~(1<<0);
}


// si tu modifies le timer, merci d'utiliser ce genre de commentaires : 
/*
/** 
 * \fn  void initTIMER_BaseUnit(char* Timer,int Delai, char* Unite_Temps, char*Interrupt)
 * \brief 
 *			Initialisation d'un Timer choisi par l'utilisateur (TIM2 ou TIM3) en mode Time-base unit
 * \param[in] 
 *			Timer			Nom du timer à utiliser ("TIM2" ou "TIM3")
 * \param[in] 
 *			Delai			Frequence ( > 100 Hz )
 * \param[in] 
 *			Unite_Temps		Rapport Cyclique (%)
 * \param[in] 
 *			*Interrupt		Type d'interruption ("Interrupt" ou "NoInterrupt")
 */
