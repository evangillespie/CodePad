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
#include "Keypad.h"
#include "SuccessState.h"
#include "FailState.h"

class StateMachine
{
	public:
		StateMachine();
		void begin(int init_state);
		void increment_state();
		void set_state(int);
		void update();

	private:
		int _state;
		Passcode _passcode;
		Display _display;
		Keypad _keypad;
		SuccessState _success_state;
		FailState _fail_state;

		void _generate_passcode_and_advance();
		void _update_display_and_advance();
		void _update_keypad_and_advance();
		void _update_success_state_and_advance();
		void _update_fail_state_and_advance();
};

#endif