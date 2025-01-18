/**
* \file debug.h
* \author Jeanne Baumier & Thomas Broussard
* \date 6 fevrier 2017
* \brief Librairie dediee a la declaration d'une variable DEBUG pour activer/desactiver le mode DEBUG 
* ainsi qu'une variable LINUX_MODE pour activer/desactiver le mode LINUX et enfin MCC_MODE pour activer/desactiver le mode MCC
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*! Variable de DEBUG : */
/*! \b 0 : DEBUG desactive */
/*! \b 1 : DEBUG active */
#define DEBUG 0

/*! Variable de LINUX_MODE : */
/*! \b 0 : LINUX_MODE desactive */
/*! \b 1 : LINUX_MODE active */
#define LINUX_MODE 0 

/*! Variable de MCC_MODE : */
/*! \b 0 : MCC_MODE desactive */
/*! \b 1 : MCC_MODE active */
#define MCC_MODE 1

/*! Variable de DEBUG_TERMINAL : */
/*! \b 0 : DEBUG_TERMINAL desactive */
/*! \b 1 : DEBUG_TERMINAL active */
#define DEBUG_TERMINAL 0

/*! Variable de AFFICHAGE_GPIO_TERMINAL : */
/*! \b 0 : AFFICHAGE_GPIO_TERMINAL desactive */
/*! \b 1 : AFFICHAGE_GPIO_TERMINAL active */
#define AFFICHAGE_GPIO_TERMINAL 1

#endif
