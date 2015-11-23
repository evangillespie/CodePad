#include "Arduino.h"
#include "SuccessState.h"

/*
	Constructor. Generic. Boring
*/
SuccessState::SuccessState() {

}

long SuccessState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		1000,	// pause before the 0th state
		2000,	// pause before the 1st state
		3000,	// 2nd
		1000,	// 3
		2000, 	// 4
		3000, 	// 5
		1000, 	// 6
		2000, 	// 7
		3000, 	// 8
		1000, 	// 9
		2000, 	// 10
		3000, 	// 11
	};
		
	return _pause_lengths[index];
}

int SuccessState::_get_max_state() {
	return 11;
}


void SuccessState::_dispatcher() {
	Serial.println("Action");
	_increment_state();
}