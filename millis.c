/*
 * millis.c
 *
 * Created: 26.03.2015 18:31:24
 *  Author: Fabian
 */ 

#include "millis.h"

/*****************************************************************************
** Initialisierung und startet den Timer
*****************************************************************************/
void millis_init(void)
{
    //Timer Konfiguration
    TCCR0A = (1<<WGM01);    //CTC - Modus
    TCCR0B |= (1<<CS01);    //Prescaler 8
    OCR0A = 125-1;

    //Overflow interrupt
    TIMSK0 |= ((1<<TOIE0) | (1<<OCIE0A));   //Timer Overflow aktiviert & CTC aktiviert

    //Global Interrupts erlauben
    sei();
	
	millis = 0;
	led = 0;
}

/*****************************************************************************
** Interrupts
*****************************************************************************/


ISR (TIM0_COMPA_vect) //Timer Overflow Timer 1
{
    /* Interrupt Aktion alle
    (1000000/8)/124 Hz =  1,024 ms  
    */
	//PORTA ^= (1<<PA0);
    millis++;
    led++;
}


/*
* E O F
*/
