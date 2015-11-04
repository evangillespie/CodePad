/*
	Passcode.h - Library for handling the overall state machine
	controls program flow and dispatches to other objects

	:Author: Evan Gillespie
*/

#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"
#include "Passcode.h"

class StateMachine
{
	public:
		StateMachine();
		void begin(int init_state);
		void increment_state();
		void update();

	private:
		int _state;
		unsigned long _next_action_time;
		int _next_action;	// generic variable to store info while in a state
		Passcode _passcode;

		void _reset_next_action_time(unsigned long increment);

		void _generate_passcode_and_advance();
		void _update_display();
		void _display_next_digit();
		bool _is_display_complete();

};

#endif