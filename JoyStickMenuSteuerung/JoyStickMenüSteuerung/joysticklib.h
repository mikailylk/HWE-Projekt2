/*
 * joysticklib.h
 *
 * Created: 22.01.2022 11:55:04
 *  Author: Mikail, Tobias
 */ 


#ifndef JOYSTICKLIB_H_
#define JOYSTICKLIB_H_

	// ADC Kan�le
	#define ADC_X_KANAL PA0 // X
	#define ADC_Y_KANAL PA1 // Y
	#define ADC_Z_KANAL PA2 // Z

	// Kalibrierung + Anzahl ADC-Wertungen ausw�hlen
	#define MITTEL 3			//Anzahl f�r Berechnung des Mittelwerts
	#define XSTARTWERT 505		//F�r Kalibrierung des Joysticks
	#define YSTARTWERT 498		//F�r Kalibrierung des Joysticks
	#define TRIGGERGRENZE 300	//Definiert ab welcher Neigung der Joystick reagiert
	/* 
	   Falls Eingabeparameter "GetTasterStatus" != 1 --> Gibt Joystickposition zur�ck (1 f�r OBEN, 2 f�r RECHTS, 3 f�r UNTEN, 4 f�r LINKS und 0 f�r MITTE (4 ... Links ... Anschlusspinseite)
	   Falls Eingabeparameter "GetTasterStatus" == 1 --> Gibt 0 (nicht gedr�ckt) oder 1 (gedr�ckt) zur�ck
	*/
	unsigned char JoyPos(unsigned char GetTasterStatus);
	
	/*
		Schaltet ADC-Kan�le als Eingang und aktiviert pull-up f�r "Z-Kanal" (Switch)
	*/
	void init_JoyADCPort();
#endif /* JOYSTICKLIB_H_ */