/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Keypad_h
#define Keypad_h

#include "Arduino.h"
#include "Passcode.h"
#include <Adafruit_LEDBackpack.h>

class Keypad {
public:
	Keypad();
	void update(Passcode);
	int get_status();
	int get_entered_code();
	void reset();

	void init();

	void clear_bargraph();
private:
	int _entered_values[4];
	unsigned long _init_time;
	int _status;

	void _is_key_pressed();
	void _register_queued_key();
	void _update_status(Passcode);
	void _update_btns_flashing();
	int _convert_byte_to_int(int);
	void _add_digit_to_received(int);
	void _update_right_wrong_leds(Passcode);
};

#endif
