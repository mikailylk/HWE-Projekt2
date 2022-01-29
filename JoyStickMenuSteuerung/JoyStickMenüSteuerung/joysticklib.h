/*
 * joysticklib.h
 *
 * Created: 22.01.2022 11:55:04
 *  Author: Mikail, Tobias
 */ 


#ifndef JOYSTICKLIB_H_
#define JOYSTICKLIB_H_

	// ADC Kanäle
	#define ADC_X_KANAL PA0 // X
	#define ADC_Y_KANAL PA1 // Y
	#define ADC_Z_KANAL PA2 // Z

	// Kalibrierung + Anzahl ADC-Wertungen auswählen
	#define MITTEL 3			//Anzahl für Berechnung des Mittelwerts
	#define XSTARTWERT 505		//Für Kalibrierung des Joysticks
	#define YSTARTWERT 498		//Für Kalibrierung des Joysticks
	#define TRIGGERGRENZE 300	//Definiert ab welcher Neigung der Joystick reagiert
	/* 
	   Falls Eingabeparameter "GetTasterStatus" != 1 --> Gibt Joystickposition zurück (1 für OBEN, 2 für RECHTS, 3 für UNTEN, 4 für LINKS und 0 für MITTE (4 ... Links ... Anschlusspinseite)
	   Falls Eingabeparameter "GetTasterStatus" == 1 --> Gibt 0 (nicht gedrückt) oder 1 (gedrückt) zurück
	*/
	unsigned char JoyPos(unsigned char GetTasterStatus);
	
	/*
		Schaltet ADC-Kanäle als Eingang und aktiviert pull-up für "Z-Kanal" (Switch)
	*/
	void init_JoyADCPort();
#endif /* JOYSTICKLIB_H_ */