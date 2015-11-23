#include "Arduino.h"
#include "SuccessState.h"

/*
	Constructor. Generic. Boring
*/
SuccessState::SuccessState() {

}

long SuccessState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		3000,	// pause before the 0th state
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
	switch(_state_num){
		case 0:
			Serial.println("Zero");
			break;
		case 1:
			Serial.println("One");
			break;
		case 2:
			Serial.println("Big Two");
			break;
		case 3:
			Serial.println("Tha Three");
			break;
		case 4:
			Serial.println("Four");
			break;
		case 5:
			Serial.println("Five");
			break;
		case 6:
			Serial.println("sixx");
			break;
		case 7:
			Serial.println("Seven");
			break;
		case 8:
			Serial.println("eight");
			break;
		case 9:
			Serial.println("Nine");
			break;
		case 10:
			Serial.println("Ten");
			break;
		case 11:
			Serial.println("Eleven");
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}