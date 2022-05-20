/*
 * setup.h
 *
 * Created: 26.03.2015 15:14:49
 *  Author: Fabian
 */ 

#ifndef __SETUP_H__
#define __SETUP_H__

#include <avr/io.h>
//#include <avr/iotn84a.h>
#include "millis.h"
#include "adc.h"     

/*****************************************************************************
** Variablen
*****************************************************************************/
volatile unsigned long long starttime;            // Variable fuer die Startzeit des Zaehlers
volatile unsigned char reed;                      // Variable fuer den Zustand des REED Kontaktes
unsigned long messcycle;						//Variable fuer die Messzeit.

/*****************************************************************************
** Funktionen
*****************************************************************************/

// Initialisieren des Magnettesters
void setup(void);

#endif /* __SETUP_H__ */

/*
* E O F
*/
