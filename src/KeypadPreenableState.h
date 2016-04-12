/*
	Class for the flow after the passcode is displayed and before the
		keypad is enabled

	:Author: Evan Gillespie
*/

#ifndef Keypad_Preenable_State_h
#define Keypad_Preenable_State_h

#include "Arduino.h"
#include "ProcedureState.h"
#include "LEDFlashManager.h"

extern LEDFlashManager g_led_flash_manager;

class KeypadPreenableState: public ProcedureState {
public:
	KeypadPreenableState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif