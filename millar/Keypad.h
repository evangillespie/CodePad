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

private:
	int _entered_value;
};

#endif