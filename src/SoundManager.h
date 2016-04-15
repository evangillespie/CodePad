/*
	Class to control a single flashing led

	:Author: Evan Gillespie
*/

#ifndef SoundManager_h
#define SoundManager_h

#include "Arduino.h"

class SoundManager{
	public:
		SoundManager();
		void play_sound(int);
	private:
		//none yet
};

#endif