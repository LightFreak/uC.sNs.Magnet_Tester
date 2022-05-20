/*
 * setup.c
 *
 * Created: 26.03.2015 18:36:45
 *  Author: Fabian
 */ 

#include "setup.h"

/*****************************************************************************
** Initialisieren des Magnettesters
*****************************************************************************/
void setup(void)
{
    
/*    #ifdef __MILLIS_H__
        millis_init();
    #endif // __MILLIS_H__*/
    
    //Output's definieren
    DDRA |= ((1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA0)); //LED's aktivieren.
    //DDRB |= (1<<PB2);

    //Input's konfigurieren
    DDRB |= ((0<<PB2)|(0<<PB1));    //PIN B.0 & Pin B.1 als Eingang
    PORTB |= ((1<<PB2)|(1<<PB1));   //Pin B.0 & B.1 Pull-Up's setzten
	
	starttime = 0;
	reed = 0;

    //TO DO: Poti konfigurieren mit ADC
}

/*
* E O F
*/
