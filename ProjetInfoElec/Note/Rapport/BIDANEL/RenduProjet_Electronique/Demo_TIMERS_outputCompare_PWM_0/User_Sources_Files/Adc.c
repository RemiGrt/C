/*Nom : ADC.C 
	Dev : Salah-Eddine MAARIF
	Date : 26/02/2017
	Descriptif : contient les fonctions nécessaires pour le fonctionnement de l'ADC
*/
#include "stm32f0xx.h"
#include "Adc.h"

uint16_t AD_last;                         /* Dernire valeur convertie         */
//uint16_t AD_ExpliciteValue;               /*Valeur explicite de la tension mesurée*/
uint8_t  AD_done = 0;                     /* flag de la complétude de la cnv  */

/*----------------------------------------------------------------------------
  Fonction de l'init de l'ADC
 *----------------------------------------------------------------------------*/
void ADC_Init_PA6 (void) {

  RCC->APB2ENR |= ( 1UL <<  17);           /* Activer le periperal clock pour GPIOA */
  /* Configurer ADC_IN6 comme une analog input */
	GPIOA->MODER |=(1<<12);    // choix mode General Purpose Output bit b12 à '1'
	GPIOA->MODER |=(1<<13);    // choix mode General Purpose Output bit b13 à '1'

#ifndef __ADC_IRQ
  /* DMA1 Channel1 configuration ---------------------------------------------*/
  RCC->AHBENR |= ( 1UL <<  0);            /* Activer le periperal clock for DMA : bit 0 */

  DMA1_Channel1->CMAR  = (uint32_t)&AD_last;    /* Paramtrer l'adresse de la mémoire du chn1     */
  DMA1_Channel1->CPAR  = (uint32_t)&(ADC1->DR); /* set chn1 peripheral address*/
  DMA1_Channel1->CNDTR = 1;               /* transmit 1 word                  */
  DMA1_Channel1->CCR   = 0x00002522;      /* configure DMA channel            */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);     /* enable DMA1 Channel1 Interrupt   */
  DMA1_Channel1->CCR  |= (1 << 0);        /* DMA Channel 1 enable             */
#endif

  /* Configuration et l'init de l'ADC cnv                                      */
  RCC->CFGR2 = 0xC000;          					 /* ADC clk = PCLK2 / 4              */

  RCC->APB2ENR |= ( 1UL <<  9);           /* Activer periperal clock for ADC1  */

	/*Reset de la config*/
  ADC1->CFGR1    =  0;                     
                    
	/*Choix du channel*/
	ADC1->CHSELR = 0x00000002;
	
	/* Temps de conversion = (55.5 + 12.5)*CLK_ADC */
  ADC1->SMPR   = ( 5UL <<  0);            /* Le SimplingTime de la cnv : 55,5 cyc. */
	ADC1->CR    |=  (1UL << 2);             /*ADSTART : Commencer la conversion par le SW */

#ifndef __ADC_IRQ
  ADC1->CFGR1    |= ( 1UL <<  0);           /* activer le DMA mode            */
#else
	/* Activer :  intruppt on EOC, EOSEQIE et overrun  */
  ADC1->IER = ADC_IER_EOCIE | ADC_IER_EOSEQIE | ADC_IER_OVRIE;        
  NVIC_EnableIRQ(ADC1_COMP_IRQn);         /* Activer ADC Interrupt             */
	NVIC_SetPriority(ADC1_COMP_IRQn,0);     /*Parametrage de priorité */
#endif

  ADC1->CR    |= ( 1UL <<  0);               /* Activer l'ADC                      */
	
	ADC->CCR |= ADC_CCR_VREFEN;                /*Déclancher le Vref*/
	
  ADC1->CR |= ADC_CR_ADCAL;                  /* Commencer la calibration        */
  while (ADC1->CR & ADC_CR_ADCAL);           /* Attendre la fin de la calibration */
}


/*----------------------------------------------------------------------------
  Lacement de la cnv ADC
 *----------------------------------------------------------------------------*/
void ADC_StartCnv (void) {

  ADC1->CR    |=  (1UL << 2);           /* Mettre en etat ON la conversion A/D */ 
}


/*----------------------------------------------------------------------------
 L'arrêt de la cnv ADC
 *----------------------------------------------------------------------------*/
void ADC_StopCnv (void) {
	
	/* Arrêter  la conversion A/D         */
  if ((ADC1->CR & ADC_CR_ADSTART) != 0) 
	{
					ADC1->CR |= ADC_CR_ADSTP; 
	}            
}

/*----------------------------------------------------------------------------
 Vérifier si l'ADC est prêt à utiliser ou non
 *----------------------------------------------------------------------------*/
int ADC_ReadyVerif(void){
	
	if (ADC1->ISR & (1<<0))
			return 1;
	else 
			return 0;
}

/*----------------------------------------------------------------------------
  Avoir les DATA convertie
 *----------------------------------------------------------------------------*/
uint16_t ADC_GetCnv (void) {

  while (!(AD_done));                     /* Attente de la fin de la cnv      */
  AD_done = 0;

  return(AD_last);
}

/*----------------------------------------------------------------------------
Calcul explicite de la tension de l'entrée :
		Vdd = 3.3 (dans le cas idéal mais dans la réalité +-10mv, dans d'autres applications nécessitant
		beaucoup de précision le calcul du potentiel Vdd est nécessaire pour chaque instant t)
		Vchx = Vdd*ADC_data/FULL_SCALE
		
		FULL_SCALE : 2^12-1 = 4095 pour cette config (résolution 12b)  

		ratio = 3.3/4095 = 8.05 
*----------------------------------------------------------------------------*/
/*
		float TensionExpliciteValue (void){
			AD_ExpliciteValue	= ((ADC_GetCnv()*3.3)/4095);
		return AD_ExpliciteValue;
}*/



#ifndef __ADC_IRQ
/*----------------------------------------------------------------------------
  DMA IRQ: Executée si le transfet est terminé 
 *----------------------------------------------------------------------------*/
void DMA1_Channel1_IRQHandler(void) {

  if (DMA1->ISR & (1 << 1)) {            /* TCIF1 interrupt?                   */
    AD_done = 1;

    DMA1->IFCR  = (1 << 1);              /* clear TCIF interrupt              */
  }
}
#endif


#ifdef __ADC_IRQ
/*----------------------------------------------------------------------------
  A/D IRQ: Executée si A/D cnv est faite
 *----------------------------------------------------------------------------*/
void ADC1_COMP_IRQnHandler(void) {

  if (ADC1->ISR & (1 << 2)) {            /* ADC1 EOC interrupt?                */
    AD_last = ((ADC1->DR)&0x0000FFFF);   //donnée convertie : derniers 16b du register ADC1-> CR
    AD_done = 1;

    ADC1->ISR &= ~(1 << 2);              /* clear EOC interrupt                */
  }

}
#endif
