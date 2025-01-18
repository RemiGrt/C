/**
* \file 
*			InitPins.c
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Contient les fonctions permettant d'initialiser des broches du microcontroleur
* \version
*			1
* \date
*			22 fevrier 2017
* \brief
*			\bMise a jour :\n
*			Amelioration de la fonction initPatte_OUT : ajout du choix de la resistance de tirage\n
*			Refonte de l'initialisation d'une patte en mode fonction alternative
*/


#include "stm32f0xx.h"   /* definition des registre de stm32f0xxx : CMSIS */
#include "InitPins.h" // Contient les fonctions d'initialisation des pattes du microcontroleur 
#include "string.h"

/** 
 * \fn  void initPatte_OUT(unsigned int N, char* Port, char *RPull)
 * \brief 
 *			Configuration d'une patte (definie par l'utilisateur) en tant que sortie numerique
 * \param[in] 
 *			N		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			*RPull	Resistance de tirage ("Pull-up" ou "Pull-Down")
 */
void initPatte_OUT(unsigned int N, char* Port, char *RPull)
{
				if (strcmp(Port,"A") == 0)
				{
					RCC->AHBENR 	|=	(1<<17);     		// Activation horloge du GPIOA
					GPIOA->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOA->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOA->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOA->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOA->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOA->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOA->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOA->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOA->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOA->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOA->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"B") == 0)
				{
					RCC->AHBENR 	|=	(1<<18);     		// Activation horloge du GPIOB
					GPIOB->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOB->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOB->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOB->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOB->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOB->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOB->PUPDR 	|=	(1<<(N*2));  		// dResistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOB->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOB->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOB->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOB->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"C") == 0)
				{
					RCC->AHBENR 	|=	(1<<19);     		// Activation horloge du GPIOC
					GPIOC->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOC->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOC->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOC->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOC->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOC->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOC->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOC->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOC->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOC->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOC->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"D") == 0)
				{
					RCC->AHBENR 	|=	(1<<20);     		// Activation horloge du GPIOD
					GPIOD->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOD->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOD->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOD->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOD->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOD->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOD->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOD->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOD->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOD->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOD->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"E") == 0)
				{
					RCC->AHBENR 	|=	(1<<21);     		// Activation horloge du GPIOE
					GPIOE->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOE->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOE->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOE->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOE->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOE->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOE->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOE->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOE->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOE->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOE->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"F") == 0)
				{
					RCC->AHBENR 	|=	(1<<22);     		// Activation horloge du GPIOF
					GPIOF->MODER 	&=~	(1<<(N*2+1));   	// choix mode General Purpose Output bit 2N+1 a '0'
					GPIOF->MODER 	|=	(1<<(N*2));    		// choix mode General Purpose Output bit 2N a '1'
					GPIOF->OTYPER &=~	(1<<N);  			// choix techno de sortie Push-Pull : bit N a '0'
					GPIOF->OSPEEDR&=~	(1<<(N*2+1)); 		// bit 2N+1 a '0'
					GPIOF->OSPEEDR&=~	(1<<(N*2));  		// bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOF->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOF->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOF->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOF->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOF->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOF->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
}

/** 
 * \fn  void initPatte_IN(unsigned int N, char* Port, char* RPull)
 * \brief 
 *			Configuration d'une patte (definie par l'utilisateur) en tant qu'entree numerique
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Resistance de tirage
 */
void initPatte_IN(unsigned int N, char* Port, char* RPull)
{
				if (strcmp(Port,"A") == 0)
				{
					RCC->AHBENR 	|=	(1<<17);     	// Activation horloge du GPIOA
					GPIOA->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOA->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOA->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOA->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOA->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOA->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOA->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOA->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"B") == 0)
				{
					RCC->AHBENR 	|=	(1<<18);     	// Activation horloge du GPIOB
					GPIOB->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOB->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOB->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOB->PUPDR 	|=	(1<<(N*2));  		// dResistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOB->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOB->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOB->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOB->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"C") == 0)
				{
					RCC->AHBENR 	|=	(1<<19);     	// Activation horloge du GPIOC
					GPIOC->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOC->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOC->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOC->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOC->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOC->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOC->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOC->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"D") == 0)
				{
					RCC->AHBENR 	|=	(1<<20);     	// Activation horloge du GPIOD
					GPIOD->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOD->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOD->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOD->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOD->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOD->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOD->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOD->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"E") == 0)
				{
					RCC->AHBENR 	|=	(1<<21);     	// Activation horloge du GPIOE
					GPIOE->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOE->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOE->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOE->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOE->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOE->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOE->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOE->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				else if (strcmp(Port,"F") == 0)
				{
					RCC->AHBENR 	|=	(1<<22);     	// Activation horloge du GPIOF
					GPIOF->MODER 	&=~	(1<<(N*2+1));   // choix mode General Purpose Output bit 2N+1	a '0'
					GPIOF->MODER 	&=~	(1<<(N*2));    	// choix mode General Purpose Output bit 2N a '0'
					if(strcmp(RPull,"Pull-Up") == 0)
					{
									GPIOF->PUPDR 	&=~	(1<<(N*2+1));   	// Resistance de tirage Pull-Up : bit 2N+1 a '0'
									GPIOF->PUPDR 	|=	(1<<(N*2));  		// Resistance de tirage Pull-Up : bit 2N a '1'
					}
					else if(strcmp(RPull,"Pull-Down") == 0)
					{
									GPIOF->PUPDR 	|=	(1<<(N*2+1));   	// Resistance de tirage Pull-Down : bit 2N+1 a '1'
									GPIOF->PUPDR 	&=~	(1<<(N*2));  		// Resistance de tirage Pull-Down : bit 2N a '0'
					}
					else
					{
									GPIOF->PUPDR 	&=~	(1<<(N*2+1));   	// desactivation resistance de tirage: bit 2N+1 a '0'
									GPIOF->PUPDR 	&=~	(1<<(N*2));  		// desactivation resistance de tirage: bit 2N a '0'
					}
				}
				
}

/** 
 * \fn  void initPatte_IN_Interruption(unsigned int N,char* Port,char* RPull, char* Front)
 * \brief 
 *			Configuration d'une patte (definie par l'utilisateur) en tant qu'entree numerique AVEC INTERRUPTION
 * \param[in] 
 *			N		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Resistance de tirage ("Pull-up" ou "Pull-Down")
 * \param[in] 
 *			Front	Choix du front d'interruption ("Montant" ou "Descendant")
 */
void initPatte_IN_Interruption(unsigned int N,char* Port,char* RPull, char* Front)
{	
					// Initialisation de la patte en mode Entree
					initPatte_IN(N,Port,RPull);
	
					// Initialisation de l'interruption
					// Activation horloge du peripherique :System configuration controller (SYSCFG) 
					RCC->APB2ENR|=(1<<0);	
	
					// Connexion au controleur d’interruption externe (EXTI).
					Select_EXTICR(N,Port);
	
					// Activation de l'interruption
					EXTI->IMR|=(1<<N);
	
					// Choix du front d'activation
					if (strcmp(Front,"Descendant") == 0)
					{
					EXTI->FTSR|=(1<<N); 	// Front Descendant active
					}
					else if (strcmp(Front,"Montant") == 0)
					{
						EXTI->RTSR|=(1<<N);		// Front Montant active
					}
					
					//Activer ou demasquer le vecteur d’interruption au niveau du NVIC en fonction du numero de la patte
					if ( N <= 1) // Pin 0 ou 1
					{
						NVIC_EnableIRQ(EXTI0_1_IRQn);
					}
					else if ( (N == 2) || (N == 3)) // Pin 2 ou 3
					{
						NVIC_EnableIRQ(EXTI2_3_IRQn);
					}
					else // Pin 4 a 15
					{
						NVIC_EnableIRQ(EXTI4_15_IRQn);
					}
}

/** 
 * \fn  void Select_EXTICR(unsigned int N, char* Port)
 * \brief 
 *			Initialise automatiquement le registre EXTICR en indiquant la patte souhaitee
 *			\b Utiliser le mode interruption externe \b
 * \param[in] 
 *			N		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
void Select_EXTICR(unsigned int N, char* Port)
{
	int BitLSB; // Variable contenant le 1er bit du code a modifier
	int Num_Reg; // Variable contenant le numero du registre a modifier
	
	// 1- Choix du registre en fonction du N° de la patte
	//EXTIRCR[0]
	if (N<=3) 										Num_Reg = 0;
	//EXTIRCR[1]
	else if((N>= 4) && (N<= 7)) 	Num_Reg = 1;
	//EXTIRCR[2]
	else if((N>= 8) && (N<= 11)) 	Num_Reg = 2;
	//EXTIRCR[3]
	else if((N>= 12) && (N<= 15)) Num_Reg = 3;
		
	// 2- Choix du bit de poids faible pour configurer le registre en fonction du N° de la patte
	// Bits [b3 b2 b1 b0]
	if 			  ((N == 0) ||(N == 4) ||(N == 8) ||(N == 12)) BitLSB = 0;
	// Bits [b7 b6 b5 b4]
	else if   ((N == 1) ||(N == 5) ||(N == 9) ||(N == 13)) BitLSB = 4;
	// Bits [b11 b10 b9 b8]
	else	if ((N == 2) ||(N == 6) ||(N == 10) ||(N == 14)) BitLSB = 8;
	// Bits [b15 b14 b13 b12]
	else	if ((N == 3) ||(N == 7) ||(N == 11) ||(N == 15)) BitLSB = 12;

	// 3 - Choix du code en fonction du port
	// Code "0000" 
	if (strcmp(Port,"A") == 0)
	{
			SYSCFG->EXTICR[Num_Reg] &=~((1<<(BitLSB+3))|(1<<(BitLSB+2))|(1<<(BitLSB+1))|(1<<BitLSB)); // '0'	
	}
	// Code "0001"
	else if (strcmp(Port,"B") == 0)
	{
			SYSCFG->EXTICR[Num_Reg] &=~((1<<(BitLSB+3))|(1<<(BitLSB+2))|(1<<(BitLSB+1))); // '0'	
			SYSCFG->EXTICR[Num_Reg] |=(1<<BitLSB); //'1'		
	}
	// Code "0010"
	else if (strcmp(Port,"C") == 0)
	{
			SYSCFG->EXTICR[Num_Reg] &=~((1<<(BitLSB+3))|(1<<(BitLSB+2))|(1<<BitLSB)); // '0'	
			SYSCFG->EXTICR[Num_Reg] |=(1<<(BitLSB+1)); //'1'		
	}
	
}

/** 
 * \fn  void initPatte_AF(unsigned int Pin, char* Port,char* RPull, unsigned int Num_AF)
 * \brief 
 *			Initialise une patte avec la fonction alternative souhaitee
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			RPull	Resistance de tirage ("Pull-up" ou "Pull-Down")
 * \param[in] 
 *			Num_AF	Numero de la fonction alternative
 */
void initPatte_AF(unsigned int Pin, char* Port,char* RPull, unsigned int Num_AF)
{
	char Code;
	// Choix du code selon la fonction a utiliser ( AF0 par defaut )
	switch (Num_AF)
	{
		case 0 : //AF0
				Code = 0x00;
				break;
		case 1 : //AF1
				Code = 0x01;
				break;
		case 2 : //AF2
				Code = 0x02;
				break;
		case 3 : //AF3
				Code = 0x03;
				break;
		case 4 : //AF4
				Code = 0x04;
				break;
		case 5 : //AF5
				Code = 0x05;
				break;
		case 6 : //AF6
				Code = 0x06;
				break;
		case 7 : //AF7
				Code = 0x07;
				break;
		default : //AF0 (par defaut)
				Code = 0x00;
				break;
	}
	
	// CHOIX DU PORT
		if (strcmp(Port,"A") == 0)
	{
		RCC->AHBENR 	|=	(1<<17);  // Activation de l'horloge associe a GPIOA
		// Configuration de la patte
		GPIOA->MODER |= (1<<(2*Pin+1));     // choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOA->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N a '0'
		GPIOA->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit b2 a '0'
		GPIOA->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOA->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 2N a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOA->PUPDR |= (1<<(2*Pin+1)); // Pull-down : bit 2N+1 a '1'
			GPIOA->PUPDR &=~(1<<(2*Pin));  	// Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOA->PUPDR &=~(1<<(2*Pin+1)); // Pull-Up : bit 2N+1 a '0'
			GPIOA->PUPDR |= (1<<(2*Pin));  	// Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOA->PUPDR &=~(1<<(2*Pin+1)); // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOA->PUPDR &=~(1<<(2*Pin));  	// desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOA->AFR[0] |=(Code<<(4*Pin));
			GPIOA->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOA->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOA->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
	
	else if (strcmp(Port,"B") == 0)
	{
		RCC->AHBENR 	|=	(1<<18);   // Activation de l'horloge associe a GPIOB
		// Configuration de la patte
		GPIOB->MODER |= (1<<(2*Pin+1));		// choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOB->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N a '0'
		GPIOB->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit N a '0'
		GPIOB->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOB->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 	2N  a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOB->PUPDR |= (1<<(2*Pin+1)); // Pull-down : bit 2N+1 a '1'
			GPIOB->PUPDR &=~(1<<(2*Pin));   // Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOB->PUPDR &=~(1<<(2*Pin+1)); // Pull-Up : bit 2N+1 a '0'
			GPIOB->PUPDR |= (1<<(2*Pin));   // Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOB->PUPDR &=~(1<<(2*Pin+1)); // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOB->PUPDR &=~(1<<(2*Pin));   // desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOB->AFR[0] |=(Code<<(4*Pin));
			GPIOB->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOB->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOB->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
	
	else if (strcmp(Port,"C") == 0)
	{
		RCC->AHBENR 	|=	(1<<19);   // Activation de l'horloge associe a GPIOC
		// Configuration de la patte
		GPIOC->MODER |= (1<<(2*Pin+1));     // choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOC->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N   a '0'
		GPIOC->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit N a '0'
		GPIOC->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOC->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 2N 	a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOC->PUPDR |= (1<<(2*Pin+1));  // Pull-down : bit 2N+1 a '1'
			GPIOC->PUPDR &=~(1<<(2*Pin));    // Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOC->PUPDR &=~(1<<(2*Pin+1));  // Pull-Up : bit 2N+1 a '0'
			GPIOC->PUPDR |= (1<<(2*Pin));    // Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOC->PUPDR &=~(1<<(2*Pin+1));  // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOC->PUPDR &=~(1<<(2*Pin));    // desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOC->AFR[0] |=(Code<<(4*Pin));
			GPIOC->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOC->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOC->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
	else if (strcmp(Port,"D") == 0)
	{
		RCC->AHBENR 	|=	(1<<20);   // Activation de l'horloge associe a GPIOD
		// Configuration de la patte
		GPIOD->MODER |= (1<<(2*Pin+1));     // choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOD->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N   a '0'
		GPIOD->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit N a '0'
		GPIOD->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOD->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 2N 	a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOD->PUPDR |= (1<<(2*Pin+1));  // Pull-down : bit 2N+1 a '1'
			GPIOD->PUPDR &=~(1<<(2*Pin));    // Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOD->PUPDR &=~(1<<(2*Pin+1));  // Pull-Up : bit 2N+1 a '0'
			GPIOD->PUPDR |= (1<<(2*Pin));    // Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOD->PUPDR &=~(1<<(2*Pin+1));  // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOD->PUPDR &=~(1<<(2*Pin));    // desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOD->AFR[0] |=(Code<<(4*Pin));
			GPIOD->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOD->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOD->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
	else if (strcmp(Port,"E") == 0)
	{
		RCC->AHBENR 	|=	(1<<21);   // Activation de l'horloge associe a GPIOE
		// Configuration de la patte
		GPIOE->MODER |= (1<<(2*Pin+1));     // choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOE->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N   a '0'
		GPIOE->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit N a '0'
		GPIOE->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOE->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 2N 	a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOE->PUPDR |= (1<<(2*Pin+1));  // Pull-down : bit 2N+1 a '1'
			GPIOE->PUPDR &=~(1<<(2*Pin));    // Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOE->PUPDR &=~(1<<(2*Pin+1));  // Pull-Up : bit 2N+1 a '0'
			GPIOE->PUPDR |= (1<<(2*Pin));    // Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOE->PUPDR &=~(1<<(2*Pin+1));  // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOE->PUPDR &=~(1<<(2*Pin));    // desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOE->AFR[0] |=(Code<<(4*Pin));
			GPIOE->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOE->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOE->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
else if (strcmp(Port,"F") == 0)
	{
		RCC->AHBENR 	|=	(1<<22);   // Activation de l'horloge associe a GPIOF
		// Configuration de la patte
		GPIOF->MODER |= (1<<(2*Pin+1));     // choix Alternate Function pour PA2 bit 2N+1 a '1'
		GPIOF->MODER &=~(1<<(2*Pin));     	// choix Alternate Function pour PA2 bit 2N   a '0'
		GPIOF->OTYPER &=~(1<<2);    		// choix techno de sortie Push-Pull : bit N a '0'
		GPIOF->OSPEEDR&=~(1<<(2*Pin+1));    // Vitesse de rafraichissement bit 2N+1 a '0'
		GPIOF->OSPEEDR&=~(1<<(2*Pin));     	// Vitesse de rafraichissement bit 2N 	a '0'
		
		// Choix de la resistance de tirage
		if (strcmp(RPull,"Pull-Down")==0)
		{
			GPIOF->PUPDR |= (1<<(2*Pin+1));  // Pull-down : bit 2N+1 a '1'
			GPIOF->PUPDR &=~(1<<(2*Pin));    // Pull-down : bit 2N   a '0'		
		}
		else if(strcmp(RPull,"Pull-Up")==0)
		{
			GPIOF->PUPDR &=~(1<<(2*Pin+1));  // Pull-Up : bit 2N+1 a '0'
			GPIOF->PUPDR |= (1<<(2*Pin));    // Pull-Up : bit 2N   a '1'				
		}
		else
		{
			GPIOF->PUPDR &=~(1<<(2*Pin+1));  // desactivation resistance de tirage: bit 2N+1 a '0'
			GPIOF->PUPDR &=~(1<<(2*Pin));    // desactivation resistance de tirage: bit 2N   a '0'			
		}
		// Choix du registre AFR et Application du code au registre
		if (Pin <= 7) // Pattes Px0 a Px7
		{
			GPIOF->AFR[0] |=(Code<<(4*Pin));
			GPIOF->AFR[0] &=~((~(Code))<<(4*Pin));
		}
		else// Pattes Px8 a Px15
		{
			GPIOF->AFR[1] |=(Code<<(4*(Pin-8)));
			GPIOF->AFR[1] &=~((~(Code))<<(4*(Pin-8)));
		}
	}
}


/** 
 * \fn  void Init_Analogic_Mode(int Pin, char *Port)
 * \brief 
 *			Initialise une patte en mode analogique, pour les ADC/DAC
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
void Init_Analogic_Mode(int Pin, char *Port)
{
	// Activation du mode Analogique sur la patte souhaitee
	if (strcmp(Port,"A") == 0)
	{
		RCC->AHBENR 	|=	(1<<17);     			// Activation horloge du GPIOA
		GPIOA->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 a '1'
		GPIOA->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N a '1'
	}
	else if (strcmp(Port,"B") == 0)
	{
		RCC->AHBENR 	|=	(1<<18);     			// Activation horloge du GPIOB
		GPIOB->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 a '1'
		GPIOB->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N a '1'
	}
	else if (strcmp(Port,"C") == 0)
	{
		RCC->AHBENR 	|=	(1<<19);     			// Activation horloge du GPIOC
		GPIOC->MODER 	|=	(1<<(Pin*2+1));   // choix mode Analogique bit 2N+1 a '1'
		GPIOC->MODER 	|=	(1<<(Pin*2));    	// choix mode Analogique bit 2N a '1'
	}
}
