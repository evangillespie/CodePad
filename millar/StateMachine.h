/*
	Passcode.h - Library for handling the overall state machine
	controls program flow and dispatches to other objects

	:Author: Evan Gillespie
*/

#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"

class StateMachine
{
	public:
		StateMachine(int state);
		void advance_state();

	private:
		int _state;

};

#endif