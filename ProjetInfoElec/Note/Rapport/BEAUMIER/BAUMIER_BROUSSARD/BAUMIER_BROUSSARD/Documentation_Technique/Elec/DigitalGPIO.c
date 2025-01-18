/**
* \file 
*			DigitalGPIO.c
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			22 fevrier 2017
* \brief  
*			Librairie permettant de gerer les Entrees et Sorties Numeriques\n
*			Lecture d'une Entree Numerique\n
*			Ecriture d'une Sortie Numerique\n
*			Inversement d'une Sortie Numerique
*/

#include "stm32f0xx.h" 
#include "string.h"
#include "DigitalGPIO.h"

/** 
 * \fn  void DigitalWrite (unsigned int Pin, char * Port, unsigned int  Etat)
 * \brief 
 *			Force la valeur d'une Patte en Sortie Numerique \n
 *			La patte doit etre initialisee en Sortie Numerique
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \param[in] 
 *			Etat	Etat Logique ( '\b1' ou '\b0')
 */
void DigitalWrite (unsigned int Pin, char * Port, unsigned int  Etat)
{
	if (strcmp(Port,"A") == 0)
	{
		switch (Etat)
		{
			case 0 :
					GPIOA->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOA->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		}
		
	}
	else if (strcmp(Port,"B") == 0)
	{
				switch (Etat)
		{
			case 0 :
					GPIOB->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOB->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		}
	}
	else if (strcmp(Port,"C") == 0)
	{
				switch (Etat)
		{
			case 0 :
					GPIOC->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOC->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		}  
	}
	else if (strcmp(Port,"D") == 0)
	{
		switch (Etat)
		{
			case 0 :
					GPIOD->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOD->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		}  
	}		
	else if (strcmp(Port,"E") == 0)
	{
		switch (Etat)
		{
			case 0 :
					GPIOE->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOE->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		}  
	}		
	else if (strcmp(Port,"F") == 0)
	{
		switch (Etat)
		{
			case 0 :
					GPIOF->ODR 	&=~	(1<< Pin);  
					break;
			case 1 : 
					GPIOF->ODR 	|=	(1<< Pin);   
					break;
			default :
					break;
		} 
	}	
	
}

/** 
 * \fn  void DigitalToggle (unsigned int Pin, char * Port)
 * \brief 
 *			Inverse la valeur d'une Patte en Sortie Numerique \n
 *			La patte doit etre initialisee en Sortie Numerique
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 */
void DigitalToggle (unsigned int Pin, char * Port)
{
	if (strcmp(Port,"A") == 0)
	{
		GPIOA->ODR 	^=	(1<< Pin);  
	}
		
	else if (strcmp(Port,"B") == 0)
	{
		GPIOB->ODR 	^=	(1<< Pin);  
	}
	else if (strcmp(Port,"C") == 0)
	{
		GPIOC->ODR 	^=	(1<< Pin);  
	}
	else if (strcmp(Port,"D") == 0)
	{
		GPIOD->ODR 	^=	(1<< Pin);  
	}		
	else if (strcmp(Port,"E") == 0)
	{
		GPIOE->ODR 	^=	(1<< Pin);  
	}		
	else if (strcmp(Port,"F") == 0)
	{
		GPIOF->ODR 	^=	(1<< Pin);  
	}	
	
}

/** 
 * \fn  int DigitalRead (unsigned int Pin, char * Port)
 * \brief 
 *			Lit la valeur d'une patte en mode Entree Numerique
 *			\n La patte doit etre initialisee en Entree Numerique 
 * \param[in] 
 *			Pin		Numero de la patte
 * \param[in] 
 *			Port	Port de la patte
 * \return 
 *			Etat logique de la patte ('1' ou '0')
 */
int DigitalRead (unsigned int Pin, char * Port)
{
	if (strcmp(Port,"A") == 0)
	{
		if ((GPIOA->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (strcmp(Port,"B") == 0)
	{
		if ((GPIOB->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (strcmp(Port,"C") == 0)
	{
		if ((GPIOC->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (strcmp(Port,"D") == 0)
	{
		if ((GPIOD->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}		
	else if (strcmp(Port,"E") == 0)
	{
		if ((GPIOE->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}		
	else if (strcmp(Port,"F") == 0)
	{
		if ((GPIOF->IDR & (1<<Pin)) == (1<<Pin))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}	
	
}
