/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Display_h
#define Display_h

#include <Shifter.h>

#include "Arduino.h"
#include "Passcode.h"
#include "Pins.h"

extern Shifter g_shifter;

class Display {
public:
	Display();
	void update(Passcode);
	bool is_complete();
	static void clear_nixie_tube(int);

private:
	unsigned long _next_action_time;
	int _next_action;

	void _reset_next_action_time(unsigned long);
	void _generate_passcode_and_advance();
	void _display_next_digit(Passcode, bool);
	void _display_nixie_tube(int, int);
	void _display_led_matrix(int);
	void _display_servo(int);
};


#endif