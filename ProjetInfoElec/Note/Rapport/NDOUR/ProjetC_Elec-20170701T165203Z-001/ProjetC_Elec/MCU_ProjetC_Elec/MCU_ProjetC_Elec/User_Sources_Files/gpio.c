#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */
#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"


void initPattes(void)
{
   RCC->AHBENR |=(1<<17);     // Activation horloge du GPIOA
	 RCC->AHBENR |=(1<<18);     // Activation horloge du GPIOB
   GPIOA->MODER &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<6)|(1<<9)|(1<<11)|(1<<13)|(1<<15)); // choix mode General Purpose input pour les pattes PA0 et PA1, Alternate Function pour PA2 et PA3
   GPIOA->MODER |=((1<<5)|(1<<7)|(1<<8)|(1<<10)|(1<<12)|(1<<14));   // choix mode General Purpose Output bitS pairs à '0' et bits impairs à 1
   GPIOB->MODER &=~((1<<17)|(1<<19)|(1<<21)|(1<<23)|(1<<25)|(1<<27)|(1<<29)); 
   GPIOB->MODER |=((1<<16)|(1<<18)|(1<<20)|(1<<22)|(1<<24)|(1<<26)|(1<<28)|(1<<30)); 
	 GPIOC->MODER &=~((1<<17)|(1<<19)|(1<<21)|(1<<23)|(1<<25)|(1<<27)|(1<<29)); 
   GPIOC->MODER |=((1<<16)|(1<<18)|(1<<20)|(1<<22)|(1<<24)|(1<<26)|(1<<28)|(1<<30)); 
	 
	 GPIOA->OTYPER &= 0x0000;   // choix techno de sortie Push-Pull : bits b0 à b15 à '0'GPIOBGPIOB->OTYPER &= 0x0000;
	 GPIOB->OTYPER &= 0x0000;   // choix techno de sortie Push-Pull : bits b0 à b15 à '0'GPIOBGPIOB->OTYPER &= 0x0000;
	 GPIOC->OTYPER &= 0x0000;   // choix techno de sortie Push-Pull : bits b0 à b15 à '0'GPIOBGPIOB->OTYPER &= 0x0000;
	 
	 GPIOA->PUPDR &= 0x00000000;   // desactivation resistance de tirage: bits b0 à b31 à '0'
	 GPIOB->PUPDR &= 0x00000000;   // desactivation resistance de tirage: bits b0 à b31 à '0'
	 GPIOC->PUPDR &= 0x00000000;   // desactivation resistance de tirage: bits b0 à b31 à '0'
   
	 GPIOA->OSPEEDR &= 0x00000000;   // bits b0 à b31 à '0'
	 GPIOB->OSPEEDR &= 0x00000000;   // bits b0 à b31 à '0'
	 GPIOC->OSPEEDR &= 0x00000000;   // bits b0 à b31 à '0'
}

void initPattePC13_BoutonPoussoirBleu_Interruption(void)
{
    //1. Activer horloge du GPIOx concernée : ici GPIOC
    RCC->AHBENR |=(1<<19);     // Activation horloge du GPIOC
  //2. Configurer la patte en mode INPUT 
    GPIOC->MODER &=~(1<<27);   // choix  Input mode bit b27 à '0'
    GPIOC->MODER &=~(1<<26);   // choix  Input mode bit b26 à '0'
  //3.désactiver les résistances de tirages 
    GPIOC->PUPDR &=~(1<<27);   // desactivation resistance de tirage: bit b11 à '0'
    GPIOC->PUPDR &=~(1<<26);   // desactivation resistance de tirage: bit b10 à '0'
  //4. Activer horloge du périphérique :System configuration controller (SYSCFG)  
   RCC->APB2ENR|=(1<<0);
  //5.Relier la patte à une entrée du contrôleur  d’interruption externe (EXTI). 
  // la patte PC13 a relier à l'entrée EXTI13
  // il faut ecrire "0010" sur les bites b7b6b5b4 du registre SYSCFG_EXTICR4
  // avec l'interface CMSIS, SYSCFG_EXTICR4 = SYSCFG->EXTICR[3]
    SYSCFG->EXTICR[3] &=~((1<<7)|(1<<6)|(1<<4));
	SYSCFG->EXTICR[3] |=(1<<5);
  //6. Activer l’entrée 13 du EXTI 
    EXTI->IMR|=(1<<13);
  //7. Indiquer la nature électrique du signal de déclenchement
  // Ici nous souhaitons du Front descendant car selon le schema electrique
  // de la carte si Bouton Appuyé PC13 ='0' si non '1'
    EXTI->FTSR|=(1<<13);
  //8. Activer ou démasquer le vecteur d’interruption au nviveau du NVIC: Utilisation de fonction CMSIS
  // pour que le CPU y soit sensible 
    NVIC_EnableIRQ(EXTI4_15_IRQn);
  // on peux donner une priorité à cette source d'interruption
  // on utilisera la fonction  NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
  // Comme il y a une seule demande d'interruption ce n'est pas nécessaire 
}

  