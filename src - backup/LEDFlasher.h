/*
	Class to control a single flashing led

	:Author: Evan Gillespie
*/

#ifndef LEDFlasher_h
#define LEDFlasher_h

#include "Arduino.h"
#include "SoundManager.h"

extern SoundManager g_sound_manager;

class LEDFlasher{
	public:
		LEDFlasher();
		void init(int, int);
		void turn_on(double);
		void turn_on_with_sound(double, int);
		void turn_off();
		void update();
	private:
		int _index;
		int _pin;
		bool _is_active;
		long _period;
		unsigned long _last_update;
		int _sound;
};

#endif
