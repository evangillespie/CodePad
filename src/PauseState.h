/*
	Class for the pause between each iteration of the entire flow chart

	:Author: Evan Gillespie
*/

#ifndef Pause_State_h
#define Pause_State_h

#include "Arduino.h"
#include "ServoManager.h"
#include "LEDFlashManager.h"
#include "LEDFadeManager.h"
#include <Shifter.h>
#include "ServoManager.h"	

extern ServoManager g_servo_manager;
extern LEDFlashManager g_led_flash_manager;
extern Shifter g_shifter_dual;
extern Shifter g_shifter_quad;
extern LEDFadeManager g_led_fade_manager;

class PauseState {
public:
	PauseState();
	bool is_complete();
	void update();
	void begin();

private:
	unsigned long _complete_time;
	unsigned long _next_update_time;
	unsigned long _next_clock_time; // for the clock sweep
	int _clock_sweep_dir;
	int _system_state;

	void _turn_system_off();
	void _turn_system_on();
	void _update_clock_sweep();
	bool _is_pir_triggered();
};

#endif
