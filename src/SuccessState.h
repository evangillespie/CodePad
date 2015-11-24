/*
	Class for the flow once the passcode is entered correctly

	:Author: Evan Gillespie
*/

#ifndef Success_State_h
#define Success_State_h

#include "Arduino.h"
#include "ProcedureState.h"

class SuccessState: public ProcedureState {
public:
	SuccessState();

private:
	void _dispatcher();
	long _get_pause_length(int);
	int _get_max_state();
};

#endif