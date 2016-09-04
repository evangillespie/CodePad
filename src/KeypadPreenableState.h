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
#include "LEDFadeManager.h"
#include "SoundManager.h"
#include "ServoManager.h"
#include <Shifter.h>

extern LEDFlashManager g_led_flash_manager;
extern LEDFadeManager g_led_fade_manager;
extern SoundManager g_sound_manager;
extern ServoManager g_servo_manager;
extern Shifter g_shifter_dual;

class KeypadPreenableState: public ProcedureState {
public:
	KeypadPreenableState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif
