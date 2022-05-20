/*
 * Magnet_Tester.cpp
 *
 *  Created: 01.02.2015 10:10:50
 *  Author: Fabian
 *
 *  Magnet Tester in den Grenzmodulen.
 *  LED's (Gruen(PA1) - ok, Gelb(PA2) - Messung, Rot(PA3) - Fail,(PB2) - Unused)
 *  REED(PB2) - Magnet Sensor
 *  RLT(PB1) - Messung Start
 *  Pot(PA7) - Zeit justierung
 *
 *	Freq Mc = 1Mhz
 *
 *  ACHTUNG:
 *  Fuer die Test auf der STK600 muessen die Signale leider invertiert werden.
 *  d.h. Soll eine LED Leuchten muss der Ausgang auf 0 gesetzt werden.
 *  Der Taster ist ebenfalls mit einem Pull-Up Wiederstand ausgeruestet (active Low)
 *
 *  To Do: Achtung, nur ASCII-7 fuer den Text verwenden oder everything in english.
 *         Angewoehnen im Editor die "Tab to Space" Konversion einzuschalten, 
*          da unterschiedliche Tabweite unterschiedliche Formatierung bedeutet.
 *
 */ 

#include "setup.h"      // Alles wird über den kleinen Baum inkludiert.

/**********************************************************************************
** I N I T
**********************************************************************************/
int init(void)
{
    // Init routine, alles wird hier in der notwendigen Reihenfolge initialisert.
    
    /*
    Da alles ueber setup.h verfuegbar ist, kann hier eine zentrale stelle fuer alle init sachen sein.
    Die #ifdefs sind dann nur noch notwendig, wenn es umstaende geben kann die unvorhergesehen sind und zur
    --> compilezeit <-- nicht vorhanden sind, sonst haben die #ifdefs keine Funktion mehr.
    
    setup.h -> milis.h 
            |-> new.h -> more.h
            |-> next.h -> ...
            ->  ...
    */
    
    millis_init();      // Time Init
    ADC_INIT();			// ADC Init
    setup();            // Base Setup
    
    return 0;
}


/**********************************************************************************
** R U N
**********************************************************************************/
int main(void)
{
    // Zuerst ein Setup fahren.
    init();

	/************************************************************************/
	/* danach: Messzeit festlegen                                           */
	/************************************************************************/
	ADC_READ();	// Wert zwischen 0 und 1023
	adcval = adcval*10;
	if (adcval <= 500)
	{
		adcval = 500;
	}
	//messcycle = 1000;
	messcycle = adcval;
	//*************************************************
    // Hauptloop
    //*************************************************
    while(1)
    {
        int loop = 0;
        
        //*************************************************
        //LED's rücksetzten (STK600)
        //*************************************************
        if(starttime == 0)
        {
            starttime = millis;
            PORTA |= ((1<<PA0)|(1<<PA2)|(1<<PA1)|(1<<PA3));
        }
        
        //*************************************************
        //Kontroll blinker
        //*************************************************
        if (led >= messcycle)
        {
            PORTA ^= (1<<PA0);
            led = 0;
        }
        
        //*************************************************
        // Irrm erkennen
        //*************************************************
        if(!(PINB&(1<<PINB1)))
        {
            starttime = millis;
            PORTA &= ~(1<<PA2);             //END: PORTA |= (1<<PA2); Messung starten (Gelb on)
            PORTA |= ((1<<PA1)|(1<<PA3));   //Test LED PortA LED 2 sollte Leuchten //PA1 - Grün OFF / PA3 Rot OFF
            reed = 0;                       //Flag Reed rücksetzten
            
            //*************************************************
            // Messzyklus
            //*************************************************
            while (loop == 0)
            {
                
                //*************************************************
                // Restart Messzyklus
                //*************************************************
                if(!(PINB&(1<<PINB1)))
                {
                    //starttime = millis;
                }
                
                //*************************************************
                // Erkennung Magnet
                //*************************************************
                if(!(PINB&(1<<PINB2)))
                {
                    PORTA &= ~(1<<PA1);             //REED Erkannt Grün ON
                    reed = 1;                       //Flag Reed setzten
                }
                
                //*************************************************
                // Ende Messzyklus
                //*************************************************
                if((starttime + 5000) <= millis)        //Ende Messzyklus erkennen
                {
                    //PORTA |= (0<<PA2);                //Irrm LED off
                    if(reed == 1)
                    {
                        PORTA &= ~(1<<PA1);         //REED LED on
                        PORTA |= (1<<PA2);          //IRRM LED off
                        loop = 1;                   //while Schleife auflösen
                    }
                    else
                    {
                        PORTA &= ~(1<<PA3);         //Fail LED on (Magnet nicht erkannt)
                        PORTA |= (1<<PA2);          //IRRM LED off
                        loop = 1;                   //while Schleife auflösen
                    }
                }
            }
        }
    }
}



/*
* E O F
*/
