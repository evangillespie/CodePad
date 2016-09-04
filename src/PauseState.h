/*
	Class for the pause between each iteration of the entire flow chart

	:Author: Evan Gillespie
*/

#ifndef Pause_State_h
#define Pause_State_h

#include "Arduino.h"
#include "ServoManager.h"

class PauseState {
public:
	PauseState();
	bool is_complete();
	void update();
	void begin();

private:
	unsigned long _complete_time;

};

#endif
