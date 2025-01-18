/*
 Definition du mapping utilisé pour gérer les broches pour le GRAFCET
*/	
			
#ifndef __MAPPING_H__			
#define __MAPPING_H__			
			
/*! taille maximum acceptée pour les tableaux fixes */
#define SIZE_BIN 1000

// Définition du nombre de pattes attribuées
// Nombre d'entrées GPIO
#define SIZE_IN 16
// Nombre de sorties GPIO
#define SIZE_OUT 16
// Nombre d'entrées ADC
#define SIZE_ADC 3
// Nombre de sorties PWM
#define SIZE_PWM 3

/*########################################
							Entrées GPIO
########################################*/
#define	IN0_Port		"B"
#define	IN0_Pin			0

#define	IN1_Port		"B"
#define	IN1_Pin			1

#define	IN2_Port		"B"
#define	IN2_Pin			2

#define	IN3_Port		"B"
#define	IN3_Pin			3

#define	IN4_Port		"B"
#define	IN4_Pin			4

#define	IN5_Port		"B"
#define	IN5_Pin			5

#define	IN6_Port		"B"
#define	IN6_Pin			6

#define	IN7_Port		"B"
#define	IN7_Pin			7

#define	IN8_Port		"B"
#define	IN8_Pin			8

#define	IN9_Port		"B"
#define	IN9_Pin			9

#define	IN10_Port		"B"
#define	IN10_Pin		10

#define	IN11_Port		"B"
#define	IN11_Pin		11

#define	IN12_Port		"B"
#define	IN12_Pin		12

#define	IN13_Port		"B"
#define	IN13_Pin		13

#define	IN14_Port		"B"
#define	IN14_Pin		14

#define	IN15_Port		"B"
#define	IN15_Pin		15

/*########################################
							Sorties GPIO 
########################################*/

#define	OUT0_Port		"C"
#define	OUT0_Pin			0

#define	OUT1_Port		"C"
#define	OUT1_Pin			1

#define	OUT2_Port		"C"
#define	OUT2_Pin			2

#define	OUT3_Port		"C"
#define	OUT3_Pin			3

#define	OUT4_Port		"C"
#define	OUT4_Pin			4

#define	OUT5_Port		"C"
#define	OUT5_Pin			5

#define	OUT6_Port		"C"
#define	OUT6_Pin			6

#define	OUT7_Port		"C"
#define	OUT7_Pin			7

#define	OUT8_Port		"C"
#define	OUT8_Pin			8

#define	OUT9_Port		"C"
#define	OUT9_Pin			9

#define	OUT10_Port	"C"
#define	OUT10_Pin			10

#define	OUT11_Port	"C"
#define	OUT11_Pin			11

#define	OUT12_Port	"C"
#define	OUT12_Pin			12

#define	OUT13_Port	"C"
#define	OUT13_Pin			13

#define	OUT14_Port	"C"
#define	OUT14_Pin			14

#define	OUT15_Port	"C"
#define	OUT15_Pin			15


/*########################################
							Entrées ADC
########################################*/
#define	ADC0_Port	"A"	
#define	ADC0_Pin	4	
			
#define	ADC1_Port	"A"	
#define	ADC1_Pin	5

#define	ADC2_Port	"A"	
#define	ADC2_Pin	6	


/*########################################
							Sorties PWM
########################################*/


#define	PWM0_Port	"A"	
#define	PWM0_Pin	9
			
#define	PWM1_Port	"A"	
#define	PWM1_Pin	10	

#define	PWM2_Port	"A"	
#define	PWM2_Pin	11	

/*########################################
					TIMER
########################################*/
#define	TIM1_Port		"A"	
#define	TIM1_Pin		8
			
#define	TIM2_Port		"A"	
#define	TIM2_Pin		1	

#define	TIM14_Port	"A"	
#define	TIM14_Pin		7	

/*########################################
					COMMUNICATION SERIE
########################################*/
#define	Rx_Port	"A"	
#define	Rx_Pin	2	
			
#define	Tx_Port	"A"	
#define	Tx_Pin	3	


#endif			
