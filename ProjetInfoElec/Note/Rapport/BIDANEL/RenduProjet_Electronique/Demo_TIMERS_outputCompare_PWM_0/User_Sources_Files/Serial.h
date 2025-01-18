/*------------------------------------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Used to communicat with your computer using USART2
 * Date: 		7/14/15
 * Author:	Christopher Jordan - Denny
 *------------------------------------------------------------------------------------------------------
 * Note(s):	SER_PutChar are used to redefine printf function
 *----------------------------------------------------------------------------------------------------*/

#ifndef SERIAL_H
#define SERIAL_H

extern void configUsart2SansInterruption (unsigned int baudRate);

extern char usart2EnvoiCaractere(char monCaractere);
extern int uart2VerifSiCaractere(void);
extern unsigned char uart2RecevoirCaractere(void);

#endif
