

#include "stm32f0xx.h"   /* defintion des registre de stm32f0xxx : CMSIS */

/*-------------------------------------------------------------------------------
  CONSTANTES ET MACROS: TYPEDEF et DEFINE
-------------------------------------------------------------------------------*/
#define BaseDeTemps          1145

/*-------------------------------------------------------------------------------
 DECLARATIONS DES VARIABLE GLOBALES 
-------------------------------------------------------------------------------*/
volatile unsigned int MarcheArretClignotementLedVerte=1;
volatile unsigned int CompteurPressionBouton;
int k = 0;

/*------------------------------------------------------------------------------
  FUNCTIONS PROTOTYPES
------------------------------------------------------------------------------*/

void Config_PA8_Mode_OutputPWM_TIM1_CH1(void);
void initPattePC13_BoutonPoussoirBleu_Interruption(void); //PC8 //PC6 //PC5 //PC4
void initPattePB3_BPHASE(void);
void AttenteActiveSansParametre(unsigned int DureeEnMilliSeconde);


/*===============================================================================
FONCTION:     main() : Fonction principale indispensable en C 
                       Point entree de application: appel des autres fonctions 
                       sauf routines interruptions (déclenchées par le matériel)
===============================================================================*/
int main (void)
{
   
   /* == Arrivé ICI le MCU est initialise
		 Avec les parametre par défaut définis dans le fichier 
		 rest configurer : frequence de travail defini 
		 dans le system_stm32f0xx_SYSCLK_48MHz_GeneAvecRC_Int_8MHz.c	
	*/
	/*---------------------------------------------------------------------------
	  Initialisez les variables
	---------------------------------------------------------------------------*/

	 int i, j;

	
	/*---------------------------------------------------------------------------
	  Initialisez le matériel : périphériques... 
	---------------------------------------------------------------------------*/

	 Config_PA8_Mode_OutputPWM_TIM1_CH1();	
	 initPattePC13_BoutonPoussoirBleu_Interruption();
	 initPattePB3_BPHASE();
	 initPattePC13_BoutonPoussoirBleu_Interruption();
	
    // Demarrage du Timer TIM1 en dernier
    TIM1->CR1 |=(1<<0); 
		
  	while(1)   // Boucle principale ou infinie
   	{
   		// rien a faire tant que l'on souhaite pas
   		// changer le rapport cyclique
			
			if ( k == 0)
			{
			
			for ( i=0 ; i<99 ; i++)
			{
				
							for (j=0 ; j<100000 ; j++)
							{
								TIM1->CCR1 = i;
							}
			}
			
			}
			
			if (k == 1)
			{
				TIM1->CCR1 = 0;
			}
			
  	}
   // Fin : Le CPU n'arrivera jamais ici
}
// FIN FONCTION MAIN


/*********************************************************************************
  FUNCTION:     EXTI4_15_IRQHandler(void)
   DESCRIPTION:  Routine d'interruption : Attention fonction déclenchée matériellement
                 si changement d'état ou de niveau sur les pattes Numero 4  à 15.
                 Ici on utilise la patte PC13
                 A chaque qu'il y a un front montant sur la patte PC13 
                 cette fonction est exécutée
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: configurer er Activer la source d'interruption EXTI13 (patte PC13)
***********************************************************************************/

void EXTI4_15_IRQHandler(void)
{
/*	if(EXTI->PR&(1<<13))                 // Test du drapeau bit b13 (PR13) du registre EXTI_PR de demande interruption
	{
				// Si on arrive ici c'est que c'est bien PC13 qui demande interruption
		EXTI->PR|=(1<<13);                // il faut acquiter la demande : on ecrit '1' pour effacer le drapeau !.
		
		if ( k == 0 )
		{
			k = 1;
		}
		
		if ( k == 1 )
		{
			k = 0;
		}
		
	}*/
	
	  
	if(EXTI->PR&(1<<13))                 // Test du drapeau bit b13 (PR13) du registre EXTI_PR de demande interruption
	{
		// Si on arrive ici c'est que c'est bien PC13 qui demande interruption
		EXTI->PR|=(1<<13);                // il faut acquiter la demande : on ecrit '1' pour effacer le drapeau !. 
		GPIOB->ODR ^= (1<<3); // Changer etat de la LED verte
	}
    
}

/*===============================================================================
  FUNCTION:     void initPattePC13_BoutonPoussoirBleu_Interruption(void)
  DESCRIPTION:  Configuration de la patte PC13 (PORT C, GPIOC) en mode entrée simple
				+ activation demande interruption si front descendant
				+ démasquage de la demande au niveau du NVIC pour que ce CPU soit sensible
				  a la demande
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: Lire ce code avec le transparent de cours correspondant
===============================================================================*/
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

/*===============================================================================
  FUNCTION:     void initPattePA5_LedVerte(void)
  DESCRIPTION:  Configuration de la patte PA5 (PORT A, GPIOA) en mode sortie
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/

void initPattePB3_BPHASE(void)
{
   RCC->AHBENR |=(1<<18);     // Activation horloge du GPIOA
   GPIOB->MODER &=~(1<<7);   // choix mode General Purpose Output bit b11 à '0'
   GPIOB->MODER |=(1<<6);    // choix mode General Purpose Output bit b10 à '1'
   GPIOB->OTYPER &=~(1<<3);   // choix techno de sortie Push-Pull : bit b5 à '0'
   GPIOB->PUPDR &=~(1<<7);   // desactivation resistance de tirage: bit b11 à '0'
   GPIOB->PUPDR &=~(1<<6);   // desactivation resistance de tirage: bit b10 à '0'
   GPIOB->OSPEEDR&=~(1<<7);  // bit b11 à '0'
   GPIOB->OSPEEDR&=~(1<<6);  // bit b10 à '0'
}


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
//	TIM1->CCR1 = 50;

}


/*===============================================================================
  FUNCTION:     AttenteActiveSansParametre(void)
  DESCRIPTION:  On fait compter le CPU du MCU dans le vide! pour attendre
  PARAMETERS:   rien
  RETURNS:   	rien   
  REQUIREMENTS: Ajuster la valeur max du compteur en fonction de la frequence du CPU
===============================================================================*/

void AttenteActiveSansParametre(unsigned int DureeEnMilliSeconde)
{
 // Faire attendre le CPU : Attente active car il comptera dans le vide
        unsigned int compteurUniteTemps;
        unsigned int compteurNombreUniteTemps;
   
        for (compteurNombreUniteTemps=0; compteurNombreUniteTemps<DureeEnMilliSeconde; compteurNombreUniteTemps++)
        {
          // boucle d'attente vide pour faire attendre le CPU 
                for (compteurUniteTemps=0; compteurUniteTemps<BaseDeTemps; compteurUniteTemps++)
                {
                    // boucle d'attente vide pour faire attendre le CPU            
            
                }
            
        }   
}




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
void Config_PA9_Mode_OutputPWM_TIM1_CH2(void)
{
	
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
	GPIOA->MODER |=(1<<19); 
	GPIOA->MODER &=~(1<<18);
	
	// 2.3 Choix de la fonction AF2 pour PA9
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
	GPIOA->OSPEEDR&=~(1<<19);
	GPIOA->OSPEEDR&=~(1<<18);
	

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
	TIM1->ARR =12;  
	
	// 5. Rapport cyclique de 25% : division de la ARR par 4
//	TIM1->CCR1 = 50;

}





