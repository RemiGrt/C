/**
* \file debug.h
* \author Jeanne Baumier & Thomas Broussard
* \date 6 février 2017
* \brief Librairie dédiée à la déclaration d'une variable DEBUG pour activer/désactiver le mode DEBUG 
* ainsi qu'une variable LINUX_MODE pour activer/désactiver le mode LINUX et enfin MCC_MODE pour activer/desactiver le mode MCC
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*! Variable de DEBUG : */
/*! \b 0 : DEBUG désactivé */
/*! \b 1 : DEBUG activé */
#define DEBUG 0

/*! Variable de LINUX_MODE : */
/*! \b 0 : LINUX_MODE désactivé */
/*! \b 1 : LINUX_MODE activé */
#define LINUX_MODE 0 

/*! Variable de MCC_MODE : */
/*! \b 0 : MCC_MODE désactivé */
/*! \b 1 : MCC_MODE activé */
#define MCC_MODE 1
#define DEBUG_TERMINAL 0

#define AFFICHAGE_GPIO_TERMINAL 0
#define AFFICHAGE_STEP_GRAFCET 0


#define ETAT_DEFAUT_ADC	0
#define ETAT_DEFAUT_PWM 0

#endif
