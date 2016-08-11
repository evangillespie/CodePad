/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Keypad_h
#define Keypad_h

#include <Shifter.h>

#include "Arduino.h"
#include "Passcode.h"
#include "SoundManager.h"
#include <Adafruit_LEDBackpack.h>

extern Shifter g_shifter_dual;
extern SoundManager g_sound_manager;

class Keypad {
public:
	Keypad();
	void update(Passcode);
	int get_status();
	int get_entered_code();
	void reset();
	void turn_off_displays();

	void init();

	static void clear_bargraph();
	static void clear_4_digit();
	static void turn_off_right_wrong_leds();
private:
	int _entered_values[4];
	unsigned long _init_time;
	int _status;

	void _is_key_pressed(Passcode);
	void _register_queued_key(Passcode);
	void _update_display();
	void _update_right_wrong_leds();
	void _write_display_character(int, int);
	void _update_status(Passcode);
	void _update_btns_flashing();
	int _convert_byte_to_int(int);
	void _add_digit_to_received(int);
	void _update_right_wrong_leds(Passcode);
};

#endif
