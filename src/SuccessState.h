/*
	Class for the flow once the passcode is entered correctly

	:Author: Evan Gillespie
*/

#ifndef Success_State_h
#define Success_State_h

#include "Arduino.h"
#include "ProcedureState.h"
#include "LEDFlashManager.h"
#include "LEDFadeManager.h"
#include "SoundManager.h"

extern LEDFlashManager g_led_flash_manager;
extern LEDFadeManager g_led_fade_manager;
extern SoundManager g_sound_manager;

class SuccessState: public ProcedureState {
public:
	SuccessState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif