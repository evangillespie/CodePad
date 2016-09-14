/*
	Class to control the various flashing LEDs

	:Author: Evan Gillespie
*/

#ifndef LEDFlashManager_h
#define LEDFlashManager_h

#include "Arduino.h"
#include "LEDFlasher.h"
#include "Config.h"

class LEDFlashManager{
	public:
		LEDFlashManager();
		void start_flasher(int, double);
		void start_flasher_with_sound(int, double, int);
		void stop_flasher(int);
		void update();
	private:
		int _get_pin_number(int);
		LEDFlasher _led_flashers[NUM_LED_FLASHERS];
};

#endif