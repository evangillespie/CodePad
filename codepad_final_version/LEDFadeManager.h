/*
	Class to control the various fading LEDs

	:Author: Evan Gillespie
*/

#ifndef LEDFadeManager_h
#define LEDFadeManager_h

#include "Arduino.h"
#include "LEDFader.h"
#include "Config.h"

class LEDFadeManager{
	public:
		LEDFadeManager();
		void fade(int, int, int, int);
		bool is_fading(int);
		void update();
	private:
		int _get_pin_number(int);
		LEDFader _led_faders[NUM_LED_FADERS];
};

#endif
