/*

 * adc.c
 *
 * Created: 17.05.2015 10:10:56
 *  Author: Fabian
 */ 

#include "adc.h"

/************************************************************************/
/* ADC Initialisieren                                                   */
/************************************************************************/
void ADC_INIT(void)
{
	uint16_t adcval = 0;
	// die Versorgungsspannung AVcc als Referenz waehlen:
	ADMUX &= ~((1<<REFS0)|(1<<REFS1));
	// Bit ADFR ("free running") in ADCSRA steht beim Einschalten
	// schon auf 0, also single conversion
	ADCSRA = (1<<ADPS2); // | (1<<ADPS0);     // Frequenzvorteiler
	ADCSRA |= (1<<ADEN);                  // ADC aktivieren
 
	/* nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
     also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" */
 
	ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
	while (ADCSRA & (1<<ADSC) ) 
	{ 
		        // auf Abschluss der Konvertierung warten
	}
	/* ADCW muss einmal gelesen werden, sonst wird Ergebnis der nächsten
     Wandlung nicht übernommen. */
	(void) ADCW;
}


/************************************************************************/
/* ADC Einzelmessung                                                    */
/************************************************************************/
void ADC_READ(void)
{
	// Kanal waehlen, ohne andere Bits zu beeinflußen
	ADMUX |= ((1<<MUX0)|(1<<MUX1)|(1<<MUX2));	//Kanal 7 festlegen.
	ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
	while (ADCSRA & (1<<ADSC) ) 
	{
		   // auf Abschluss der Konvertierung warten
	}
	adcval = ADCW;
	return;                    // ADC auslesen und zurückgeben
}
