/*
	Class for the flow once the passcode is entered correctly

	:Author: Evan Gillespie
*/

#ifndef Fail_State_h
#define Fail_State_h

#include "Arduino.h"
#include "ProcedureState.h"
#include "LEDManager.h"

extern LEDManager g_led_manager;

class FailState: public ProcedureState {
public:
	FailState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif