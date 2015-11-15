/*
	Class for the flow once the passcode is entered correctly

	:Author: Evan Gillespie
*/

#ifndef Fail_State_h
#define Fail_State_h

#include "Arduino.h"

class FailState {
public:
	FailState();
	void update();
	bool is_complete();

private:

};

#endif