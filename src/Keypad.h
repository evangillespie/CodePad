/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Keypad_h
#define Keypad_h

#include "Arduino.h"

class Keypad {
public:
	Keypad();
	void update();
	int get_status();
	int get_entered_code();
	void reset();

private:
	int _entered_values[4];
	unsigned long _init_time;
	int _status;

	void _update_status();
	int _convert_byte_to_int(int);
	void _add_digit_to_received(int);
};

#endif