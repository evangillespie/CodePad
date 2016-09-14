/*
	Class to control a single flashing led

	:Author: Evan Gillespie
*/

#ifndef SoundManager_h
#define SoundManager_h

#include "Arduino.h"
#include <wavTrigger.h>

class SoundManager{
	public:
		SoundManager();
		void play_sound(int);
		void stop_sound(int);
	private:
		wavTrigger _wTrig;
};

#endif