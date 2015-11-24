/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Passcode.h"

class Display {
public:
	Display();
	void update(Passcode);
	bool is_complete();

private:
	unsigned long _next_action_time;
	int _next_action;

	void _reset_next_action_time(unsigned long);
	void _generate_passcode_and_advance();
	void _display_next_digit(Passcode);
};


#endif