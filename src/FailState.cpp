#include "Arduino.h"
#include "FailState.h"

/*
	Constructor. Generic. Boring
*/
FailState::FailState() {

}

long FailState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		1000,	// pause before the 0th state - Pause 10
		1000,	// pause before the 1st state - Pause 11
		2000,	// 2nd - Pause 12
		2000,	// 3 - Pause 13
		2000 	// 4 - Pause 14
	};
		
	return _pause_lengths[index];
}

int FailState::_get_max_state() {
	return 4;
}


void FailState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Fail: Zero");
			Serial.println("badpin sound");
			Serial.println("bargraph off");
			Serial.println("ControlPanel led off");
			Serial.println("4-digit display off");
			Serial.println("turn off all pindigit leds");
			Serial.println("Turn off Keypad clr and ok leds");
			break;
		case 1:
			Serial.println("Fail: One");
			Serial.println("Servo 6 moves");
			Serial.println("Turn off Bricklamp led");
			Serial.println("Keypad Green LED fades down over 3s");
			Serial.println("Keypad buttons fade down over 3s");
			break;
		case 2:
			Serial.println("Fail: Big Two");
			Serial.println("Keypad yellow leds fade down over 5 s");
			Serial.println("Servo 5 moves");
			Serial.println("Brick warning finger flashes @ 5hz");
			Serial.println("Brick warning finger sound triggers when led is on");
			break;
		case 3:
			Serial.println("Fail: Tha Three");
			Serial.println("Servo 1 moves");
			Serial.println("Servo 2 moves");
			Serial.println("Servo 3 moves");
			Serial.println("Servo 4 moves");
			Serial.println("Keypad door sound");
			break;
		case 4:
			Serial.println("Fail: Four");
			Serial.println("turn off brick warning led");
			Serial.println("turn off timer led");
			Serial.println("Servo 8 moves");
			Serial.println("display elements turn off at random times");
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}