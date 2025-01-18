/*------------------------------------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: Redirection des fonction C printf C pour utiliser USART2
 * Date: 		12/02/17
 * Author:	Arouna DARGA
 *------------------------------------------------------------------------------------------------------
 * Note(s):	Magique!
 *----------------------------------------------------------------------------------------------------*/

/*--------------------------------------Include Statements--------------------------------------------*/
#include <stdio.h>
#include <rt_misc.h>
#include "Serial.h"
/*--------------------------------------Additional Compiler Info--------------------------------------*/
#pragma import(__use_no_semihosting_swi)
/*--------------------------------------Structure Definitions-----------------------------------------*/
struct __FILE { int handle;};
FILE __stdout;
FILE __stdin;
/*--------------------------------------Functions-----------------------------------------------------*/

int fputc(int c, FILE *f){
  return (usart2EnvoiCaractere(c));
}


int fgetc(FILE *f){
  return (uart2RecevoirCaractere());
}

void _sys_exit(int return_code){
label:  goto label;  /* endless loop */
}
