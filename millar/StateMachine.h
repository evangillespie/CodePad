/*
	Library for handling the overall state machine
	controls program flow and dispatches to other objects

	:Author: Evan Gillespie
*/

#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"
#include "Passcode.h"
#include "Display.h"

class StateMachine
{
	public:
		StateMachine();
		void begin(int init_state);
		void increment_state();
		void update();

	private:
		int _state;
		Passcode _passcode;
		Display _display;

		void _generate_passcode_and_advance();
		void _update_display_and_advance();
};

#endif