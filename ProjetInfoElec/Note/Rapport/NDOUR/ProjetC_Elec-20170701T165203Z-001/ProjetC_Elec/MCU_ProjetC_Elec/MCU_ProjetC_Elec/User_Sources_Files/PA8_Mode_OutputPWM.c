#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */


/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);  

/*===============================================================================
  FUNCTION:     void Config_PA8_Mode_OutputPWM_TIM1_CH1(void)
  DESCRIPTION:  Configuration de la patte PA8 en mode output PWM du TIM1 CH1
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: Toujours activer horloge du peripherique (ici GPIOA) en premier 
  				Le TIMER TIM1 est dit Advanced TIMER : 
  				Sa configuration est diffirente des autres TIMERS
  				Utiliser la fonction Config_TIM1_TimeBaseUnitMode_SansInterrupt()
===============================================================================*/
void Config_PA8_Mode_OutputPWM_TIM1_CH1(void)
{
/* Les étapes à suivre pour configurer et utiliser ce mode sont:
	1. Activer les horloges des périphériques concernées:
		Ici 2 périphériques sont concernées:
		-GPIOx : utiliser pour configurer la/les pattes
		-TIMx : c'est le Timer TIMx 
	2. Configurer la ou les Pattes: car ici notre signal d'entrée sera connecté sur une patte
		pour ça il faut :
		2.1 identifier la ou les pattes 
			car toute les pattes ne sont pas connectées aux timers.
			Par exemple à la page 40 du datasheet on note que 
			PA8 est relié a TIM1_CH1 : AF2
			Chaque patte est reliée est a un registre TIMx_CCRy dédié  ou canal: 
			TIMx_CH2->TIMx_CCR1, TIMx_CH2->TIMx_CCR2, TIMx_CH3->TIMx_CCR3, TIMx_CH4->TIMx_CCR4
		2.2 Utiliser le registre GPIOx_MODER pour choisir Alternate Function 
		2.3 Choisir la Fonction (AF0 ou AF1 ou AF2 selon 2.1) 
			Pour connaitre quel AF il faut regarder à la page 40 à 42 du datasheet du stm32f0xx 
			par ex. pour TIM1_CH2 : c'est AF2 pour la patte PA0, PA15... 
			utiliser les registre 
			GPIO alternate function high register (GPIOx_AFRL ou GPIOx->AFR[0] en Langage C) : pour les pattes allant de 0 à 7
			GPIO alternate function high register (GPIOx_AFRH ou GPIOx->AFR[1] en Langage C) : pour les pattes allant de 8 à 15
			voir à la page 140 du reference manual pour les bits et les valeurs correspondantes à écrire

		2.4 choisir Push-pull pour la sortie : car c'est le MCU qui va imposé la tension
			Registre GPIO port output type register (GPIOx_OTYPER)(x = A..I/J/K)

		2.5 Choisir la vitesse de rafraisissement
			registre GPIO port output speed register (GPIOx_OSPEEDR)
			Bits 2y+1:2y OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	
	3. configurer le canal de sortie du  TIMER
		3.1 choisir le mode output compare pour le cannal choisi
			registre : TIMx capture/compare mode register 1 (TIMx_CCMR1)  pour le channel 1
		3.2 Choisir le type de signal que l'on souhaite générer sur la patte (channel)
		3.3 Definir l'état initial de la sortie
		3.4 deactiver ou activer le preload (prechargement automatique)
			
	4. Activer le channel

	5. Initialiser le Rapport Cyclique 
	   Dependent de la valeur du registre TIMx_ARR
	
	
*/
	
	// 1. Activer les horloges des périphériques concernées
	// 1.1 APB peripheral clock enable register 2 (RCC_APB2ENR)
	// Bit b11 TIM1EN: TIM1 timer clock enable
		// 0: TIM1 clock disabled
		// 1: TIM1 clock enabled
	RCC->APB2ENR |= (1<<11);

	//  1.2 Horloge du GPIOA
	// registre AHB peripheral clock enable register  (RCC_AHBENR)
	// bit b17 GPIOAEN '1'
	RCC->AHBENR |= (1<<17) ;
	
	// 2. Configurer la ou les Pattes
	// 2.1 identifier la ou les pattes 
	// Nous utiliserons la patte PA8 car TIM1_CH1 est connecté via AF2
	// 2.2 Choix de Alternate Function pour la patte PA8
	// registre GPIOA_MODER 
	// bits b17b16 à "10"
	GPIOA->MODER |=(1<<17); 
	GPIOA->MODER &=~(1<<16);
	
	// 2.3 Choix de la fonction AF2 pour PA8
	// registre alternate function high register (GPIOx_AFRH) 
	// bits b3b2b1b0 à "0010" 
 	GPIOA->AFR[1] &=~((1UL<<3)|(1<<2)|(1<<0));  // bits b3b2b0 à "000"
	GPIOA->AFR[1] |=(1<<1); 

	// 2.4 choisir Push-pull pour la sortie 
	// registre Registre GPIO port output type register (GPIOx_OTYPER)
	// bit b8 à '0' : Push-pull
	GPIOA->OTYPER&=~(1<<8);
	GPIOA->OTYPER&=~(1<<9);
	
	// 2.5 Choisir la vitesse de rafraisissement
	// registre GPIO port output speed register (GPIOx_OSPEEDR)
	// Bits 2y+1:2y OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	// bits b17b16 à "00" : very low-speed
	GPIOA->OSPEEDR&=~(1<<17);
	GPIOA->OSPEEDR&=~(1<<16);
	

	/* 3. configurer le canal de sortie du  TIMER
		3.1 choix du mode output pour TIM1_CH1--> IC1 is mapped on TI1
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		Bits 1:0 CC1S: Capture/Compare 1 selection
			00: CC1 channel is configured as output
			01: CC1 channel is configured as input, IC1 is mapped on TI1
			10: CC1 channel is configured as input, IC1 is mapped on TI2
			11: CC1 channel is configured as input, IC1 is mapped on TRC. 
	*/
	TIM1->CCMR1 &=~(1<<1); 
	TIM1->CCMR1 &=~(1<<0);
	
	/* 3. configurer le canal de sortie du  TIMER
		3.2 choix du mode PWM mode 1
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		bits b6b5b4 OC1M[2:0]: OC1M: Output Compare 1 mode : "110": PWM Mode 1
	*/	
	TIM1->CCMR1 |=(1<<6);
	TIM1->CCMR1 |=(1<<5);
	TIM1->CCMR1 &=~(1<<4);
	
	/* 3. configurer le canal de sortie du  TIMER
		3.3 Activer le preload (prechargement automatique)
		TIM1 capture/compare mode register 1 (TIM1_CCMR1)
		Bit b3 OC1PE:Output compare 1 preload enable
		    0: Preload register on TIMx_CCR2 disabled. TIMx_CCR2 can be written at anytime, the
			1: Preload register on TIMx_CCR2 enabled. Read/Write operations access the preload
    */
	TIM1->CCMR1|=(1<<3);


	/* 3. configurer le canal de sortie du  TIMER
		3.4 Definir l'état initial de la sortie : ici HIGH
		registre TIM1  capture/compare enable register (TIM1_CCER and TIM1_CCER)
		Bit b1 CC1P: Capture/Compare 1 output polarity
		0: OC1 active high
		1: OC1 active low

    */
	TIM1->CCER &=~(1<<1);
	
	
	/* 4. activation du mode compare
	   4.1 activation des sorties : Cas particulier du TIMER TIM1 
	    registre : TIM1 break and dead-time register (TIM1_BDTR)
		Bit 15 MOE: Main output enable
		This bit is cleared asynchronously by hardware as soon as the break input is active. It is set by
		software or automatically depending on the AOE bit. It is acting only on the channels which are
		configured in output.
		0: OC and OCN outputs are disabled or forced to idle state.
		1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in
		TIMx_CCER register).
	*/
	TIM1->BDTR |=(1<<15);

	/* 4. activation du mode compare
	   4.2 registre : TIMx capture/compare enable register (TIMx_CCER)
		bit b0 CC1E: Capture/Compare 1 output enable. refer to CC1E description
		0 Output Disabled (OCx=0, OCx_EN=0)
		1 OCx=OCxREF + Polarity, OCx_EN=1
	*/

	TIM1->CCER |= (1<<0);
   // 5. Configurer le Timing 
	// 5.1. Selection du mode de comptage du TIM1 
	// registre : TIMx control register 1 (TIMx_CR1)
	// Bit 4 DIR: Direction
	// 0: Counter used as upcounter
	// 1: Counter used as downcounter
	// Bit b4 à '0'
	TIM1->CR1 &=~(1<<4);
	
	// 5.2 Definition de la période ou fréquence du comptage 
	// Dans cet exemple nous souhaitons que le Timer compte 
	// le plus rapidement possible
	// divisons la frequence du timer par 48: soit TIM_PSC=47
	// ainsi frequenceTIMx_CLK=48x10^6/(47+1) =1 MHz 
	TIM1->PSC=47;

	// Nous souhaitons une periode de 10 kHz
	TIM1->ARR =99;  
	
	// 5. Rapport cyclique de 25% : division de la ARR par 4
	TIM1->CCR1 =50;

}

