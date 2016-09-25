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
#include "Display.h"

extern ServoManager g_servo_manager;
extern LEDFlashManager g_led_flash_manager;
extern Shifter g_shifter_dual;
extern Shifter g_shifter_quad;
extern LEDFadeManager g_led_fade_manager;
extern SoundManager g_sound_manager;

class PauseState {
public:
	PauseState();
	bool is_complete();
	void update();
	void begin();
	void end();

private:
	unsigned long _complete_time;
	unsigned long _next_update_time;
	unsigned long _next_clock_time; // for the clock sweep
	int _clock_sweep_dir;
	unsigned long _next_tuba_sound_time;	// for the tuba player in the pause state
	unsigned long _tuba_sound_wait_time;
	int _tuba_sound_count;
	unsigned long _next_landscape_tube_time;
	bool _landscape_tube_active;
	unsigned long _next_pizza_oven_time;
	int _system_state;

	void _turn_system_off();
	void _turn_system_on();
	void _update_clock_sweep();
	void _update_tuba_sounds();
	void _update_landscape_tube();
	void _update_pizza_oven();
	bool _is_pir_triggered();
	unsigned long _get_next_tuba_sound_time();
	unsigned long _get_tuba_sound_length(int);
	int _get_random_tuba_sound_index();
};

#endif
