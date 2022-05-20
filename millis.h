/*
 * millis.h
 * uC: ATtiny84A 
 * Created: 26.03.2015 17:49:15
 *  Author: Fabian
 *
 * Beschreibung:
 * Erzeugung eines ms-Zählers, startend mit dem uC für diverse Verzögerungen
 */ 

#ifndef __MILLIS_H__
#define __MILLIS_H__


#include <avr/interrupt.h>
#include <stdio.h>

/*****************************************************************************
** Variablen
*****************************************************************************/
volatile unsigned long long millis;             // Milisekunden
volatile unsigned long led;                     // LED Status

/*****************************************************************************
** Funktionen
*****************************************************************************/
// Initialisierung und startet den Timer
void millis_init(void);


#endif /* __MILLIS_H__ */

/*
* E O F
*/
