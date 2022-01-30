/*
 * menulib.c
 *
 * Created: 18.01.2022 11:36:42
 *  Author: Mikail, Tobias
 */ 

#include "menulib.h"
#include "joysticklib.h"
#include "zkslibdisplay.h"
#include <stdio.h>

// ***********************START: Public Variablen (NICHT VER�NDERN)**********************
unsigned char countAuswahl = 0; // Auswahl 1,2,3, ...hochz�hlen bis maximal Auswahl
unsigned char countZeile = 0;	// auf welcher Zeile befindet sich der Cursor: z.B. LED0 oder LED1 ... hochz�hlen (0..Zeile 1, 2...Zeile 2)
unsigned char countSpalte = 0;	// ist der Cursor auf der Auswahl oder den Zust�nden
// ***********************ENDE: Public Variablen (NICHT VER�NDERN)**********************

// Display je nach Auswahlseite und Zustand aktualisieren
void refreshDisplay()
{
	display_Clear();
	for (unsigned int j = 0; j < anzahlZeilen[countAuswahl]; j++)
	{
		display_Pos(0, j);
		if(j == countZeile && countSpalte == 1)
		{
			printf("%s*%3u",listNames[countAuswahl][j], listZustaende[countAuswahl][j]);
		}
		else
		{
			printf("%s %3u",listNames[countAuswahl][j], listZustaende[countAuswahl][j]);
		}
	}
}

void changeMenu()
{
	// Zum Pr�fen ob z.B. schon einmal nach rechts navigiert wurde,
	// wenn ja, nicht mehr nach rechts navigieren und warten bis untere grenze unterschritten
	// (ungef�hr wenn Joystick in der Mitte, beim Verlassen der Trigger-Grenze)
	static unsigned char MovedLeft = 0;
	static unsigned char MovedRight = 0;
	static unsigned char MovedUp = 0;
	static unsigned char MovedDown = 0;
	static unsigned char JoyStickPressed = 0;
	
	unsigned char JoyZPos = 0; // nichtgedr�ckt (default)
	// Joystick gedr�ckt abfragen
	JoyZPos = JoyPos(0x01); // Ist Joystick gedr�ckt oder losgelassen?
	
	// allgemeine JoyStickPosition ermitteln (1 = Oben, ...)
	unsigned char joyStickPosition = 0;
	joyStickPosition = JoyPos(0x00);
	
	// Bei AuswahlMen� nach rechts o. links navigieren, wenn Joystick nicht gedr�ckt ist bzw. gedr�ckt wurde
	if(JoyZPos != 1 && JoyStickPressed == 0 && countSpalte == 0)
	{
		// Pr�fen ob schon 1 mal nach rechts und links nicht navigiert wurde
		if(MovedRight != 1 && MovedLeft != 1)
		{
			if(joyStickPosition == RECHTS && countAuswahl < ANZAHL_AUSWAHL-1)
			{
				MovedRight = 1;
				countAuswahl ++;
			}
			else if (joyStickPosition == LINKS && countAuswahl > 0)
			{
				MovedLeft = 1;
				countAuswahl --;
			}
		}
		if(joyStickPosition != RECHTS)
		{
			MovedRight = 0;
		}
		if(joyStickPosition != LINKS)
		{
			MovedLeft = 0;
		}
		refreshDisplay();
	}
	
	// Wird JoyStick gedr�ckt?
	if(JoyZPos != 0 && JoyStickPressed == 0)
	{
		JoyStickPressed = 1; // JoyStickStatus auf "wurde gedr�ckt" �ndern
	}
	
	// JoyStick wurde gedr�ckt und losgelassen --> Als gedr�ckt Werten (Anzahl der Gedr�ckten aufz�hlen)
	if(JoyZPos != 1 && JoyStickPressed == 1)
	{
		if(countSpalte < 1)
		{
			countSpalte++; // 1. mal gedr�ckt
			MovedRight = 0;
			MovedLeft = 0;
		}
		else // mehr als 1 oder zum 2. mal gedr�ckt --> countSpalte (Anzahl Dr�ckungen = 0)
		{
			// zur�ck zur Auswahl springen
			countSpalte = 0;
			countZeile = 0;
			
			// Alle andere m�glichen PositionenStatusabfragen r�cksetzen (Fehler zu vermeiden)
			MovedRight = 0;
			MovedLeft = 0;
			MovedUp = 0;
			MovedDown = 0;
		}
		JoyStickPressed = 0; // JoyStickStatus auf "nicht gedr�ckt" �ndern
	}

	// JoyStick wurde zum 1. Mal gedr�ckt bzw. eine Auswahl wurde getroffen
	if (countSpalte == 1 && JoyZPos != 1)
	{
		// Auf welcher Zeile befindet sich der Cursor ?
		if(MovedUp != 1 && MovedDown != 1)
		{
			if(joyStickPosition == OBEN && countZeile > 0)
			{
				MovedUp = 1;
				countZeile --;
			}
			else if (joyStickPosition == UNTEN && countZeile < anzahlZeilen[countAuswahl]-1)
			{
				MovedDown = 1;
				countZeile ++;
			}
		}
		if(joyStickPosition != OBEN)
		{
			MovedUp = 0;
		}
		if(joyStickPosition != UNTEN)
		{
			MovedDown = 0;
		}
		
		if(MovedRight != 1 && MovedLeft != 1)
		{
			if(joyStickPosition == RECHTS && listZustaende[countAuswahl][countZeile] < listAnzahlZustaende[countAuswahl][countZeile] - 1)
			{
				MovedRight = 1;
				listZustaende[countAuswahl][countZeile]++;
				
			}
			else if (joyStickPosition == LINKS && listZustaende[countAuswahl][countZeile] > 0)
			{
				MovedLeft = 1;
				listZustaende[countAuswahl][countZeile]--;
			}
		}
		if(joyStickPosition != RECHTS)
		{
			MovedRight = 0;
		}
		if(joyStickPosition != LINKS)
		{
			MovedLeft = 0;
		}
		refreshDisplay();
	}
}

unsigned char getZustand(unsigned char Auswahl, unsigned char Zeile)
{
	return listZustaende[Auswahl][Zeile];
}
unsigned char getZeilenAnzahl(unsigned char Auswahl)
{
	return anzahlZeilen[Auswahl];
}


