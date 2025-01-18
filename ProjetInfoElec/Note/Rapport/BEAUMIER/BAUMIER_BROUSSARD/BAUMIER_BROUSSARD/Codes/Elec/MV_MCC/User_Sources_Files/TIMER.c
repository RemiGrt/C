/********************************************************************************
Titre : TIMER.c
Auteur : Thomas Broussard
Date : 21/02/17
--------------------------------
Description : Librairie contenant les fonctions pour effectuer des actions avec les timers
*	Initialisation d'un timer
*	Interruption sur un timer
*

Remarque : la librairie timer pourra être associée à d'autre librairie ( ADC,UART,PWM...) pour fabriquer des fonctions plus complexes.
--------------------------------
Mise à jour :  


********************************************************************************/
#include "stm32f0xx.h"   
#include "string.h"
#include "TIMER.h"


void init_TIM1_PWM(void)
{
	//Selection du mode de comptage : mode UP
	TIM1->CR1 &=~(1<<4);
	
	// Normalisation de la fréquence à 1MHz
	TIM1->PSC=(SystemCoreClock / 1000000);
	
	// Interruption
	TIM1->DIER|=(1<<0);	
}
void init_TIM2_PWM(void)
{
	//Selection du mode de comptage : mode UP
	TIM2->CR1 &=~(1<<4);
	
	// Normalisation de la fréquence à 1MHz
	TIM2->PSC=(SystemCoreClock / 1000000);

	// Interruption
	TIM2->DIER|=(1<<0);
}

void init_TIM14_PWM(void)
{
	// Normalisation de la fréquence à 1MHz
	TIM14->PSC=(SystemCoreClock / 1000000);
	
	// Interruption
	TIM14->DIER|=(1<<0);	
}