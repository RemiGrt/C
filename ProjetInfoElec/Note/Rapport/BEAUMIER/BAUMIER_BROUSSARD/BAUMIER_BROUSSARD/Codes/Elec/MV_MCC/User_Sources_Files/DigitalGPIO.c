/********************************************************************************
Titre : Gestion_GPIO.h
Auteur : Thomas Broussard
Date : 22/02/17
--------------------------------
Description : Librairie permettant de gérer les Entrées et Sorties Numériques
* Lecture d'une Entrée Numérique
* Ecriture d'une Sortie Numérique
* Inversement d'une Sortie Numérique

********************************************************************************/
#include "stm32f0xx.h" 
#include "string.h"

                 
/*===============================================================================
  FUNCTION:     DigitalWrite
  DESCRIPTION:  Force la valeur d'une Patte en Sortie Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte, Etat Logique (1 ou 0)
  RETURNS:   	rien
  REQUIREMENTS: La patte doit être initialisée en Sortie Numérique
===============================================================================*/
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

/*===============================================================================
  FUNCTION:     DigitalToggle
  DESCRIPTION:  Inverse la valeur d'une Patte en Sortie Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte
  RETURNS:   	rien
  REQUIREMENTS: La patte doit être initialisée en Sortie Numérique
===============================================================================*/
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


/*===============================================================================
  FUNCTION:     DigitalRead
  DESCRIPTION:  Lit la valeur d'une patte en mode Entrée Numérique
  PARAMETERS:   Numéro de la patte, Port de la patte
  RETURNS:   	Etat logique de la patte (1 ou 0)
  REQUIREMENTS: La patte doit être initialisée en Entrée Numérique
===============================================================================*/
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
	else
	{
			return -1;
	}
}