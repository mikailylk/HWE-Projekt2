/*
 * menulib.h
 *
 * Created: 18.01.2022 11:37:23
 *  Author: Mikail, Tobias
 */ 
#ifndef MENULIB_H_
#define MENULIB_H_

	// Joystick Positionen: 4 ... Links ... Anschlusspinseite bei JoyPos
	#define OBEN 1
	#define RECHTS 2
	#define UNTEN 3
	#define LINKS 4
	//											OBEN
	//											  1
	//									---------------------
	//								----* GND		J		-	
	// Anschlusspins  	LINKS   4	----* +5V		O		-	2  RECHTS
	//								----* VRX		Y		-
	//								----* VRY		S		-
	//								----* SW		Tick	-
	//									----------------------
	//											3
    //										  UNTEN
	
	// Anzahl Auswahl-Seiten
	#define ANZAHL_AUSWAHL 4 // Anzahl der Auswahlen
	#define ANZAHL_ZEILEN 2 // Maximale Zeilenzahl einer Auswahl
	
	// für Test 3 (angepasst)
	// auskommetieren für Test3
	// Anzahl Zeilen pro Auswahlseite
	#define AUSWAHL1ZEILEN 2 // Zeilenanzahl der jeweiligen Auswahl
	#define AUSWAHL2ZEILEN 2
	#define AUSWAHL3ZEILEN 2
	#define AUSWAHL4ZEILEN 2
	
	// ***********************START: Public Variablen (ZUM GEBRAUCH ANPASSEN!!!)**********************
	//Anzahl der Zeilen in der jeweiligen Auswahl (wird gebraucht, falls nicht alle Auswahlen gleich viele Zeilen haben)
	static unsigned char anzahlZeilen [ANZAHL_AUSWAHL] = {AUSWAHL1ZEILEN,AUSWAHL2ZEILEN,AUSWAHL3ZEILEN,AUSWAHL4ZEILEN};

	//Liste zum Speichern aller Zustände
	//Einstellmöglichkeiten zählen und speichern (für die Anzeige)
	static unsigned char listZustaende [ANZAHL_AUSWAHL][ANZAHL_ZEILEN] =
	{{0,0},
	{0,0},
	{0,0},
	{0,0}};
		
	//Liste zum Speichern der jeweiligen Anzahl an Zuständen
	static unsigned char listAnzahlZustaende [ANZAHL_AUSWAHL][ANZAHL_ZEILEN] =
	{{2,2},
	{2,2},
	{2,2},
	{2,2}};

	//Liste zum Speichern der Zeilennamen (für Ausgabe) (max 4 Buchstaben)
	// [AUSWAHL][ZEILEN][MaxStringLänge+1] ... hier Max String Länge: [5] da string mit escape-sequenz beendet wird
	static unsigned char listNames [ANZAHL_AUSWAHL][ANZAHL_ZEILEN][5] = {
	{"LED0", "LED1"},
	{"LED2","LED3"},
	{"LED4", "LED5"},
	{"LED6","LED7"}
	};
	// ***********************ENDE: Public Variablen (ZUM GEBRAUCH ANPASSEN!!!)************************

	/*
		// für Test 4 (angepasst)
	// Anzahl Zeilen pro Auswahlseite
	#define AUSWAHL1ZEILEN 1 // Zeilenanzahl der jeweiligen Auswahl
	#define AUSWAHL2ZEILEN 2
	#define AUSWAHL3ZEILEN 1
	#define AUSWAHL4ZEILEN 2
	
	// ***********************START: Public Variablen (ZUM GEBRAUCH ANPASSEN!!!)**********************
	//Anzahl der Zeilen in der jeweiligen Auswahl (wird gebraucht, falls nicht alle Auswahlen gleich viele Zeilen haben)
	static unsigned char anzahlZeilen [ANZAHL_AUSWAHL] = {AUSWAHL1ZEILEN,AUSWAHL2ZEILEN,AUSWAHL3ZEILEN,AUSWAHL4ZEILEN};

	//Liste zum Speichern aller Zustände
	//Einstellmöglichkeiten zählen und speichern (für die Anzeige)
	static unsigned char listZustaende [ANZAHL_AUSWAHL][ANZAHL_ZEILEN] =
	{{0},
	{0,0},
	{0},
	{0,0}};
		
	//Liste zum Speichern der jeweiligen Anzahl an Zuständen
	static unsigned char listAnzahlZustaende [ANZAHL_AUSWAHL][ANZAHL_ZEILEN] =
	{{2},
	{2,2},
	{2},
	{2,2}};

	//Liste zum Speichern der Zeilennamen (für Ausgabe) (max 4 Buchstaben)
	// [AUSWAHL][ZEILEN][MaxStringLänge+1] ... hier Max String Länge: [5] da string mit escape-sequenz beendet wird
	static unsigned char listNames [ANZAHL_AUSWAHL][ANZAHL_ZEILEN][5] = {
	{"LED1"},
	{"LED2","LED3"},
	{"LED4"},
	{"LED6","LED7"}
	};
	*/
	
	/* Funktion in der Arbeitsschleife aufrufen --> Zustände werden auf dem Display laufend aktualisiert (nach dem Aufruf ein Delay einbauen!!!) */
	void changeMenu();
	
	// gibt den Zustand an der jeweiligen Auswahl und Zeile zurück
	unsigned char getZustand(unsigned char Auswahl, unsigned char Zeile);
	
	// gibt die Zeilanzahl einer Auswahl zurück
	unsigned char getZeilenAnzahl(unsigned char Auswahl);
#endif /* MENULIB_H_ */