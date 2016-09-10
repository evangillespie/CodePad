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
#include "ServoManager.h"
#include "Display.h"

extern LEDFlashManager g_led_flash_manager;
extern LEDFadeManager g_led_fade_manager;
extern SoundManager g_sound_manager;
extern ServoManager g_servo_manager;

class SuccessState: public ProcedureState {
public:
	SuccessState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();

	unsigned long _times[4];
	bool _elements_turned_off[4];
};

#endif