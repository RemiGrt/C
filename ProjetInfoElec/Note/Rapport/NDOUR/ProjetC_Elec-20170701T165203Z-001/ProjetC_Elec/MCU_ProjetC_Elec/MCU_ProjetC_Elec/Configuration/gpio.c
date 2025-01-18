#include <stdlib.h>
#include <stdio.h>


void initPattes(void)
{
   RCC->AHBENR |=(1<<17);     // Activation horloge du GPIOA
	RCC->AHBENR |=(1<<18);     // Activation horloge du GPIOB
   GPIOA->MODER &=~((1<<1)|(1<<3)|(1<<5)|(1<<7)|(1<<9)|(1<<11)|(1<<13)|(1<<15)); 
   GPIOA->MODER |=((1<<0)|(1<<2)|(1<<4)|(1<<6)|(1<<8)|(1<<10)|(1<<12)|(1<<14));   // choix mode General Purpose Output bitS pairs à '0' et bits impairs à 1
   GPIOB->MODER &=~((1<<17)|(1<<19)|(1<<21)|(1<<23)|(1<<25)|(1<<27)|(1<<29)|(1<<31)); 
   GPIOB->MODER |=((1<<16)|(1<<18)|(1<<20)|(1<<22)|(1<<24)|(1<<26)|(1<<28)|(1<<30)); 
	 GPIOA->OTYPER &= 0x0000;   // choix techno de sortie Push-Pull : bits b0 à b15 à '0'GPIOBGPIOB->OTYPER &= 0x0000;
	 GPIOA->PUPDR &= 0x00000000;   // desactivation resistance de tirage: bits b0 à b31 à '0'
   GPIOA->OSPEEDR &= 0x00000000;   // bits b0 à b31 à '0'
}
