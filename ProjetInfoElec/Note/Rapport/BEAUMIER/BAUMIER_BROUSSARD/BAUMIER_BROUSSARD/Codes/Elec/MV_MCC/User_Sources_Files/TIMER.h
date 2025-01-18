//#############################################################
// Auteur : Thomas Broussard
// Date : 10/02/17
// Titre : Init.pins.h
//------------------------------------------------------------
// Description  :
//	Contient les fonctions du fichier TIMER.h
//	
//
//
//
//
//#############################################################

#ifndef __TIMER_H__
#define __TIMER_H__

/*===============================================================================
  FUNCTION:     init_TIMx_PWM
  DESCRIPTION:  Initialisation d'un Timer choisi par l'utilisateur en mode Time-base unit avec interruption
  PARAMETERS:   
  RETURNS:   	rien   
  REQUIREMENTS: rien 
===============================================================================*/
extern void init_TIM1_PWM(void);
extern void init_TIM2_PWM(void);
extern void init_TIM14_PWM(void);

#endif

