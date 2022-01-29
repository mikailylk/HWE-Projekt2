/*
 * JoyStickMenüSteuerung.c
 *
 * Created: 18.01.2022 10:04:38
 * Author : Mikail, Tobias
 */ 

// **********************START: Bibliotheken*******************************
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "zkslibdisplay.h"
#include "joysticklib.h"
#include "menulib.h"

// **********************ENDE: Bibliotheken*******************************


// Test-Programm für Ansteuerung aller LEDs (Test 3)
// auskommetieren für Test3
void refreshLEDStatusTest3()
{
	unsigned char ledcount = 0;
	for (int i = 0; i<ANZAHL_AUSWAHL; i++)
	{
		for (int j = 0; j<getZeilenAnzahl(i); j++)
		{
			if(getZustand(i,j) == 0)
			{
				PORTC &= ~(1<<ledcount);
			}
			else if (getZustand(i, j) == 1)
			{
				PORTC |= (1<<ledcount);
			}
			ledcount++;
		}
	}
}


// Test-Programm für Ansteuerung der LEDs, außer LED0 und LED5 (Test 4)
// auskommetieren für Test4
/*
void refreshLEDStatusTest4()
{
		unsigned char ledcount = 0;
		for (int i = 0; i<ANZAHL_AUSWAHL; i++)
		{
			for (int j = 0; j<getZeilenAnzahl(i); j++)
			{
				switch (i)
				{
					case 0:
					ledcount = 1;
					break;
					
					case 2:
					ledcount = 4;
					break;
					
					case 3:
					if(j==0)
					{
						ledcount = 6;
					}
					else
					{
						ledcount++;
					}
					break;
					
					default:
					ledcount++;
					break;
				}
				if(getZustand(i,j) == 0)
				{
					PORTC &= ~(1<<ledcount);
				}
				else if (getZustand(i, j) == 1)
				{
					PORTC |= (1<<ledcount);
				}
			}
		}
}
*/
// Test-Programm für Ansteuerung aller LEDs
int main(void)
{	
	display_Init();
	init_JoyADCPort();
	
	DDRC=0xFF;
	PORTC=0x00;
	
    while (1) 
    {
		changeMenu();
		refreshLEDStatusTest3(); // auskommetieren für Test3
		//refreshLEDStatusTest4(); // auskommetieren für Test4
		_delay_ms(20); // 50Hz aktualisierungsrate
    } 
}

