/*
	Class to control the various flashing LEDs

	:Author: Evan Gillespie
*/

#ifndef LEDManager_h
#define LEDManager_h

#include "Arduino.h"
#include "LEDFlasher.h"
#include "Config.h"

class LEDManager{
	public:
		LEDManager();
		void start_flasher(int, double);
		void stop_flasher(int);
		void update();
	private:
		LEDFlasher _led_flashers[NUM_LED_FLASHERS];
};

#endif