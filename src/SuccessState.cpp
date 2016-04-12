#include "Arduino.h"
#include "SuccessState.h"

/*
	Constructor. Generic. Boring
*/
SuccessState::SuccessState() {

}

long SuccessState::_get_pause_length(int index) {
	long _pause_lengths[] = {
		0,	// pause before the 0th state
		1000,	// pause before the 1st state - Pause 19
		1000,	// 2nd - Pause 20
		1000,	// 3 - Pause 21
		1000, 	// 4 - Pause 22
		1000 	// 5 - Pause 28
	};
		
	return _pause_lengths[index];
}

int SuccessState::_get_max_state() {
	return 5;
}


void SuccessState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Zero");
			Serial.println("bargraph off");
			Serial.println("timersound off");
			break;
		case 1:
			Serial.println("One");
			Serial.println("goodpin sound");
			Serial.println("control panel leds off");
			Serial.println("4-digit display off");
			Serial.println("pindigit leds off");
			Serial.println("keypad clr and ok leds off");
			break;
		case 2:
			Serial.println("Big Two");
			Serial.println("turn off bricklamp led");
			Serial.println("fade keypad greed led down over 3s");
			Serial.println("fade keypad button leds down over 5s");
			Serial.println("red crystal fades down");
			Serial.println("trigger power crystal sound");
			break;
		case 3:
			Serial.println("Tha Three");
			Serial.println("turn off timer led");
			Serial.println("Servo 6 moves");
			Serial.println("servo 5 moves");
			Serial.println("servos 10, 11, 12 move");
			Serial.println("power crystal sound off");
			Serial.println("turn power crystal led off");
			break;
		case 4:
			Serial.println("Four");
			Serial.println("Servo 13 moves");
			Serial.println("after random times, all digit displays turn off");
			Serial.println("brick warning finger flashed @ 5hz");
			Serial.println("brick warning sound triggers when brick warning finger is high");
			Serial.println("Servos 1, 2, 3, 4 move");
			Serial.println("keypad door sound triggers");
			break;
		case 5:
			Serial.println("Five");
			Serial.println("turn off brick warning led");
			Serial.println("servo 8 moves");
			Serial.println("servo 7 moves");
			Serial.println("keypad yellow leds fade up over 10s");
			Serial.println("3-6 minute pause");
			Serial.println("turn paintinglight off");
			Serial.println("Servo 13 moves");
			Serial.println("Servos 10, 11, 12 move");
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}