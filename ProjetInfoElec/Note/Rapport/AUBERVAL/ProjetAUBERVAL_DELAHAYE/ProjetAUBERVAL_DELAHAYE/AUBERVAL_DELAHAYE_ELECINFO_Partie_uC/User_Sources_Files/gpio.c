/*------------------------------------------------------------------------------
 Eleves: 	DELAHAYE Laurent
					GHABRO Raphael
 
 EI2I - 3
 
 Projet Microcontrôleur : Afficheur Tournant
 Description : Fichier d'initialisation des ports GIPOx
 ------------------------------------------------------------------------------*/

#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include "gpio.h"
#include <stdio.h>


void init_GPIO(GPIO_TypeDef *GPIOx, int LEDx)
{
	int i=0;
	int tab[256];
	
    if(GPIOx == GPIOA)
        RCC->AHBENR |=(1<<17);              // Activation horloge du GPIOA
    else if (GPIOx == GPIOB)
        RCC->AHBENR |=(1<<18);              // Activation horloge du GPIOB
    else if (GPIOx == GPIOC)
        RCC->AHBENR |=(1<<19);              // Activation horloge du GPIOC
		
		//LEDx = tab;
		
		for(i=0;i<=LEDx;i++)
		{   
			GPIOx->MODER &=~(1<<(1+2*i));    // choix mode General Purpose Output bit 1+2*LEDx ‡ '0'
			GPIOx->MODER |=(1<<(2*i));       // choix mode General Purpose Output bit 2*LEDx ‡ '0'
			GPIOx->OTYPER &=~(1<<i);         // choix techno de sortie Push-Pull : bit LEDx ‡ '0'
			GPIOx->PUPDR &=~(1<<(1+2*i));    // desactivation resistance de tirage: bit 1+2*LEDx ‡ '0'
			GPIOx->PUPDR &=~(1<<(2*i));      // desactivation resistance de tirage: bit 2*LEDx ‡ '0'
			GPIOx->OSPEEDR&=~(1<<(1+2*i));   // bit 1+2*LEDx ‡ '0'
			GPIOx->OSPEEDR&=~(1<<(2*i));     // bit 2*LEDx ‡ '0'
		}   
		
    GPIOx->ODR = 0x00000000;                          // led initialisé en mode off
}


    
