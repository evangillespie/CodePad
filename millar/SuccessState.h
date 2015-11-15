/*
	Class for the flow once the passcode is entered correctly

	:Author: Evan Gillespie
*/

#ifndef Success_State_h
#define Success_State_h

#include "Arduino.h"

class SuccessState {
public:
	SuccessState();
	void update();
	bool is_complete();

private:

};

#endif