/*
 * joysticklib.c
 *
 * Created: 18.01.2022 11:52:54
 *  Author: Mikail, Tobias
 */ 

#include "joysticklib.h"
#include <avr/io.h>

void init_JoyADCPort()
{
	// ADC-Kanäle auf Eingang
	DDRA &= ~((1<<ADC_X_KANAL) | (1<<ADC_Y_KANAL) | (1<<ADC_Z_KANAL));
	
	// Switch (Z-Achse), pull-up aktivivieren
	PORTA |= 1<<ADC_Z_KANAL;
}

unsigned int readADC(unsigned char Kanal, unsigned int AnzahlMessungen)
{
	ADMUX = 0x00;
	ADCSRA = 0x00;
	
	// ADC-Kanal konfigurieren
	ADMUX |= (1<<REFS0) | (Kanal & 0b00000111); // Referenzspannung Vcc=5V
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1); // Wahl Takt: fADC = 187.5kHz
	
	ADCSRA |= 1<<ADEN; // ADC einschalten
	ADCSRA &= ~(1<<ADATE); // Einzelwandlung
	
	SFIOR &= ~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2)); // Freilaufbetrieb

	unsigned int z[AnzahlMessungen];
	
	// erste Wandlung verwerfen (wegen umändern des Kanals)
	ADCSRA |= 1<<ADSC;
	while(ADCSRA & (1<<ADSC)) {;}
	
	// Beginn der Auswertung
	unsigned int mittelwert = 0;
	for (unsigned int i = 0; i < AnzahlMessungen; i++)
	{
		ADCSRA |= 1<<ADSC; // Einzelwandlung starten
		while(ADCSRA & (1<<ADSC)) {;}
		z[i] = ADCW;
		mittelwert += z[i];
	}
	mittelwert = mittelwert/AnzahlMessungen;
	return mittelwert;
}

unsigned char JoyPos(unsigned char GetTasterStatus)
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	
	if (GetTasterStatus == 0x01)
	{
		z = readADC(ADC_Z_KANAL, MITTEL);
		if(z > 900)
		{
			return 0;
		}
		else
		{
			return 1;// falls gedrückt gehalten --> 1, ansonsten 0
		}
	}
	else
	{
		x = readADC(ADC_X_KANAL,MITTEL);
		y = readADC(ADC_Y_KANAL,MITTEL);
		// default (4 ... Links ... Anschlusspinsseite)
		// oben
		if (y<=YSTARTWERT-TRIGGERGRENZE)
		{
			return 1;
		} // rechts
		else if(x>=XSTARTWERT+TRIGGERGRENZE)
		{
			return 2;
		} // unten
		else if(y>=YSTARTWERT+TRIGGERGRENZE)
		{
			return 3;
		} //links
		else if(x<=XSTARTWERT-TRIGGERGRENZE)
		{
			return 4;
		} // in der Mitte
		else
		{
			return 0;
		}
	}
}
