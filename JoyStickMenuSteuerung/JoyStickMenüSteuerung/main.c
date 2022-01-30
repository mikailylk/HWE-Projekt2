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
// auskommentieren für Test4 (nur als Demonstration, wie man einzelne Auswahlseiten --> Zeilen durchgehen kann)
// Der Benutzer kann mit Verwendung von Methoden, diese Vorhgehensweise um einiges vereinfachen!!
/*
void refreshLEDStatusTest4()
{
		// Alle Auswahlseiten durchgehen
		for (int i = 0; i<ANZAHL_AUSWAHL; i++)
		{
			// die Zeilen durchgehen (Abhängig von Auswahl --> Anzahl der Zeilen)
			for (int j = 0; j<getZeilenAnzahl(i); j++)
			{
				switch (i)
				{
					// Auswahlseite 1
					case 0:
						// Zeilen durchgehen
						switch (j)
						{
							// Zeile 1
							case 0:
							if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC1);
							else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC1;
							break;
							
							// Zeile 2 (LEER!!)
							case 1:
							// LEER, da in dieser Zeile nichts steht
							break;
						}
					break;
					
					// Auswahlseite 2
					case 1:
							// Zeilen durchgehen
							switch (j)
							{
								// Zeile 1
								case 0:
								if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC2);
								else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC2;
								break;
												
								// Zeile 2
								case 1:
								if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC3);
								else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC3;
								break;
							}
					break;
					// ...
					// Auswahlseite 3
					case 2:
							// Zeilen durchgehen
							switch (j)
							{
								// Zeile 1
								case 0:
								if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC4);
								else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC4;
								break;
											
								// Zeile 2 (LEER)
								case 1:
								// LEER, da in dieser Zeile nichts steht
								break;
							}
					break;
					
					case 3:
							// Zeilen durchgehen
							switch (j)
							{
								// Zeile 1
								case 0:
								if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC6);
								else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC6;
								break;
						
								// Zeile 2
								case 1:
								if(getZustand(i,j)==0)
								PORTC &= ~(1<<PC7);
								else if(getZustand(i,j) == 1)
								PORTC |= 1<<PC7;
								break;
							}
					break;
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

