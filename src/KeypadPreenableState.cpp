#include "Arduino.h"
#include "KeypadPreenableState.h"

/*
	Constructor. Generic. Boring
*/
KeypadPreenableState::KeypadPreenableState() {

}

long KeypadPreenableState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		5000,	// pause before the 0th state - Pause 4
		2000,	// pause before the 1st state 5
		2000,	// 2nd Pause 6
		2000,	// 3 Pause 7
		2000,	// 4 - Pause 8
		2000,	// 5 - Pause 9

	};
		
	return _pause_lengths[index];
}

int KeypadPreenableState::_get_max_state() {
	return 5;
}


void KeypadPreenableState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Preenable zero");
			Serial.println("Servo 6 move from 0-500 @ speed=100");
			_increment_state();
			break;
		case 1:
			Serial.println("Preenable: One");
			Serial.println("Servo 7 move from 0-500 @ speed=100");
			Serial.println("Wait for Servo 7 to reach 500");
			_increment_state();
			break;
		case 2:
			Serial.println("Preenable: Big Two");
			Serial.println("Servo 8 move from 0-500 @ speed=100");
			Serial.println("Brick warning LED flashed @ 4 hz");
			Serial.println("Brick warning sound triggers when led is high");
			_increment_state();
			break;
		case 3:
			Serial.println("Preenable: Th-Three");
			Serial.println("Brick warning LED flashed @ 12 hz for 2 seconds");
			Serial.println("Servo 1 Move from 500 - 955 @ speed=60");
			Serial.println("Servo 2 Move from 500 - 45 @ speed of 60");
			Serial.println("Servo 3 move from 1000 - 460 @ speed of 71");
			Serial.println("Servo 4 move from 0 - 540 @speed of 71");
			Serial.println("Keypad door sound triggers");
			Serial.println("Wait for Servo 1-4 to get to final position");
			_increment_state();
			break;
		case 4:
			Serial.println("Preenable: Four");
			Serial.println("keypadgreen LEDs fade from 0 - <keypadgreenpot> value over 3 seconds");
			Serial.println("keypadbuttons fade from 0 - max over 3 seconds");
			Serial.println("TimerLED = HIGH");
			Serial.println("keypadyellow LEDs fade from max - 0 over 4 seconds");
			Serial.println("servo5 move from 0 - 500 @ speed = 100");
			Serial.println("Wait for servo5 to reach 500");
			Serial.println("bricklightLED = HIGH");
			_increment_state();
			break;
		case 5:
			_increment_state();
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	
}