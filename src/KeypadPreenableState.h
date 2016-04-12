/*
	Class for the flow after the passcode is displayed and before the
		keypad is enabled

	:Author: Evan Gillespie
*/

#ifndef Keypad_Preenable_State_h
#define Keypad_Preenable_State_h

#include "Arduino.h"
#include "ProcedureState.h"
#include "LEDManager.h"

extern LEDManager g_led_manager;

class KeypadPreenableState: public ProcedureState {
public:
	KeypadPreenableState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif