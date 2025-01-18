
#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include "vm_codops.h"
#include <stdio.h>
#include <stdlib.h>

#include "initpc.h"

/*===============================================================================
  FUNCTION:     void initPattePC5(void) LED4
  DESCRIPTION:  Configuration de la patte PC5 (PORT C, GPIOC) en mode entrée
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initPattePC5(void)
{
   RCC->AHBENR |=(1UL<<19);     // Activation horloge du GPIOC
   GPIOC->MODER &=~(1UL<<27);   // choix mode General Purpose Output bit b1 à '0'
   GPIOC->MODER &=~(1UL<<26);    // choix mode General Purpose Output bit b0 à '0'
   GPIOC->OTYPER &=~(1UL<<5);   // choix techno de sortie Push-Pull : bit b6 à '0'
   GPIOC->PUPDR &=~(1UL<<27);   // desactivation resistance de tirage: bit b1 à '0'
   GPIOC->PUPDR &=~(1UL<<27);   // desactivation resistance de tirage: bit b0 à '0'
   GPIOC->OSPEEDR&=~(1UL<<27);  // bit b11 à '0'
	 GPIOC->OSPEEDR|=(1UL<<26);  // bit b10 à '0'
}
/*===============================================================================
  FUNCTION:     void initPattePC6(void) LED4
  DESCRIPTION:  Configuration de la patte PC6 (PORT C, GPIOC) en mode entrée
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initPattePC6(void)
{
   RCC->AHBENR |=(1UL<<19);     // Activation horloge du GPIOC
   GPIOC->MODER &=~(1UL<<27);   // choix mode General Purpose Output bit b1 à '0'
   GPIOC->MODER &=~(1UL<<26);    // choix mode General Purpose Output bit b0 à '0'
   GPIOC->OTYPER &=~(1UL<<6);   // choix techno de sortie Push-Pull : bit b6 à '0'
   GPIOC->PUPDR &=~(1UL<<27);   // desactivation resistance de tirage: bit b1 à '0'
   GPIOC->PUPDR &=~(1UL<<26);   // desactivation resistance de tirage: bit b0 à '0'
   GPIOC->OSPEEDR&=~(1UL<<27);  // bit b11 à '0'
   GPIOC->OSPEEDR|=(1UL<<26);  // bit b10 à '0'
}
/*===============================================================================
  FUNCTION:     void initPattePC8(void) LED2
  DESCRIPTION:  Configuration de la patte PC8 (PORT C, GPIOC) en mode entrée
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initPattePC8(void)
{
   RCC->AHBENR |=(1UL<<19);     // Activation horloge du GPIOC
   GPIOC->MODER &=~(1UL<<27);   // choix mode General Purpose Output bit b3 à '0'
   GPIOC->MODER &=~(1UL<<26);    // choix mode General Purpose Output bit b2 à '1'
   GPIOC->OTYPER &=~(1UL<<8);   // choix techno de sortie Push-Pull : bit b8 à '0'
   GPIOC->PUPDR &=~(1UL<<27);   // desactivation resistance de tirage: bit b3 à '0'
   GPIOC->PUPDR &=~(1UL<<26);   // desactivation resistance de tirage: bit b2 à '0'
   GPIOC->OSPEEDR&=~(1UL<<27);  // bit b3 à '0'
   GPIOC->OSPEEDR|=(1UL<<26);  // bit b2 à '0'
}
/*===============================================================================
  FUNCTION:     void initPattePC9(void) LED2
  DESCRIPTION:  Configuration de la patte PC8 (PORT C, GPIOC) en mode entrée
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
void initPattePC9(void)
{
   RCC->AHBENR |=(1UL<<19);     // Activation horloge du GPIOC
   GPIOC->MODER &=~(1UL<<27);   // choix mode General Purpose Output bit b3 à '0'
   GPIOC->MODER &=~(1UL<<26);    // choix mode General Purpose Output bit b2 à '1'
   GPIOC->OTYPER &=~(1UL<<9);   // choix techno de sortie Push-Pull : bit b8 à '0'
   GPIOC->PUPDR &=~(1UL<<27);   // desactivation resistance de tirage: bit b3 à '0'
   GPIOC->PUPDR &=~(1UL<<26);   // desactivation resistance de tirage: bit b2 à '0'
   GPIOC->OSPEEDR&=~(1UL<<27);  // bit b3 à '0'
   GPIOC->OSPEEDR|=(1UL<<26);  // bit b2 à '0'
}

