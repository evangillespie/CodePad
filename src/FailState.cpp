#include "Arduino.h"
#include "FailState.h"

/*
	Constructor. Generic. Boring
*/
FailState::FailState() {

}

long FailState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		3000,	// pause before the 0th state
		200,	// pause before the 1st state
		300,	// 2nd
		100,	// 3
		200, 	// 4
		300, 	// 5
		100, 	// 6
		200, 	// 7
		300, 	// 8
		100 	// 9
	};
		
	return _pause_lengths[index];
}

int FailState::_get_max_state() {
	return 9;
}


void FailState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Fail: Zero");
			break;
		case 1:
			Serial.println("Fail: One");
			break;
		case 2:
			Serial.println("Fail: Big Two");
			break;
		case 3:
			Serial.println("Fail: Tha Three");
			break;
		case 4:
			Serial.println("Fail: Four");
			break;
		case 5:
			Serial.println("Fail: Five");
			break;
		case 6:
			Serial.println("Fail: sixx");
			break;
		case 7:
			Serial.println("Fail: Seven");
			break;
		case 8:
			Serial.println("Fail: eight");
			break;
		case 9:
			Serial.println("Fail: Nine");
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}