#include "Arduino.h"
#include "KeypadPreenableState.h"

/*
	Constructor. Generic. Boring
*/
KeypadPreenableState::KeypadPreenableState() {

}

long KeypadPreenableState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		100,	// pause before the 0th state
		100,	// pause before the 1st state
		100,	// 2nd
		100,	// 3
	};
		
	return _pause_lengths[index];
}

int KeypadPreenableState::_get_max_state() {
	return 3;
}


void KeypadPreenableState::_dispatcher() {

	// Serial.println("Servo 6 move from 0-500 @ speed=100");
	// Serial.println("Servo 7 move from 0-500 @ speed=100");
	// Serial.println("Brick warning LED flashed @ 4 hz");
	// Serial.println("Brick warning sound triggers when led is high");
	// Serial.println("Servo 8 move from 0-500 @ speed=100");
	// Serial.println("Brick warning LED flashed @ 12 hz for 2 seconds");
	// Serial.println("Brick warning sound triggers when led is high");
	// Serial.println("Servo 1 move from 500-955 @ speed=60");
	// Serial.println("Servo 2 move from 500-45 @ speed=60");
	// Serial.println("Servo 3 move from 1000-460 @ speed=71");
	// Serial.println("Servo 4 move from 0-540 @ speed=71");
	// Serial.println("Keypad door sound triggers");
	// Serial.println("Keypad greedn leds fade from 0-<keypad green pot value> over 3 secs");
	// Serial.println("Keypad buttons fade in from 0 over 3 seconds");
	// Serial.println("Timer led is high");
	// Serial.println("Keypad yellow led fade from max ot 0 over 4 seconds");
	// Serial.println("Servo 5 move from 0-500 @ speed=100");
	// Serial.println("Brick LED goes to high");
	switch(_state_num){
		case 0:
			Serial.println("Preenable: Zero");
			break;
		case 1:
			Serial.println("Preenable: One");
			break;
		case 2:
			Serial.println("Preenable: Big Two");
			break;
		case 3:
			Serial.println("Preenable: Th-Three");
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}