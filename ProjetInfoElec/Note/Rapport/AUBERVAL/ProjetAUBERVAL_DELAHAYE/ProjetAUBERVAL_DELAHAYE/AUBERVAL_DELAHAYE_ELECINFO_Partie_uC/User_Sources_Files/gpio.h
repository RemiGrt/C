/*------------------------------------------------------------------------------
 Eleves: DELAHAYE Laurent
         GHABRO Raphael
 
 EI2I - 3
 
 Projet Microcontrôleur : Afficheur Tournant
Description : Fichier header d'initialisation des ports GIPOx
 ------------------------------------------------------------------------------*/

#ifndef __GPIO_H__
#define __GPIO_H__

/*------------------------------------------------------------------------------
 define
 ------------------------------------------------------------------------------*/
#define LED1 (1UL<<0)
#define LED2 (1UL<<1)
#define LED3 (1UL<<2)
#define LED4 (1UL<<3)
#define LED5 (1UL<<4)
#define LED6 (1UL<<5)
#define LED7 (1UL<<6)
#define LED8 (1UL<<7)

#define LED9 (1UL<<8)
#define LED10 (1UL<<9)
#define LED11 (1UL<<10)
#define LED12 (1UL<<11)
#define LED13 (1UL<<12)
#define LED14 (1UL<<13)
#define LED15 (1UL<<14)
#define LED16 (1UL<<15)


/*------------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 ------------------------------------------------------------------------------*/
void init_GPIO(GPIO_TypeDef *GPIOx, int LEDx);

#endif
