#include "Arduino.h"
#include "SuccessState.h"
#include "Pins.h"
#include "Keypad.h"

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

			// clear bargraph
			Keypad::clear_bargraph();

			//timersound off
			break;
		case 1:
			Serial.println("One");
			
			//goodpin sound

			//control panel leds off


			// 4-digit display off
			Keypad::clear_4_digit();
			
			//pindigit leds off

			//keypad clr and ok leds off

			break;
		case 2:
			Serial.println("Two");
			//TODO:
			//turn off bricklamp led NOTE: Brick lamp on shift registers

			//get pot value
			_substate = analogRead(ANALOG_INPUT_1) / 4; 

			//fade keypad green led down over 3s from pot position 0 - <keypadgreenpot>
			g_led_fade_manager.fade(11, 3000, _substate, 0); 


			//fade keypad button leds down over 5s"); NOTE: I dont think these pins can fade
			// Button 3 - keypadbutton's fade from max-0 over 5 seconds
			g_led_fade_manager.fade(5, 5000, 255, 0); 

			// Button 2 - keypadbutton's fade from max-0 over 5 seconds
			g_led_fade_manager.fade(6, 5000, 255, 0); 

			// Button 1 - keypadbutton's fade from max-0 over 5 seconds
			g_led_fade_manager.fade(7, 5000, 255, 0); 

			//TODO:
			//Red Crystal fades up and down at random times continuously until end of next state

			//TODO:
			//trigger power crystal sound

			break;
		case 3:
			Serial.println("Three");

			//TODO:
			//turn off timer led

			//Servo 6 moves
			//servo 5 moves
			//servos 10, 11, 12 move


			//power crystal sound off

			//turn power crystal led off
			digitalWrite(LED_12_PIN, LOW);

			break;
		case 4:
			Serial.println("Four");

			//Servo 13 moves

			//TODO EVAN: after random times, all digit displays turn off (pause23-26)

			//brick warning finger flashed @ 5hz and brick warning sound triggers when brick warning finger is high
			g_led_flash_manager.start_flasher_with_sound(3, 5.0, 1);
			
			//Servos 1, 2, 3, 4 move

			//keypad door sound triggers

			break;
		case 5:
			Serial.println("Five");

			//turn off brick warning led and sound
			g_led_flash_manager.stop_flasher(3);

			//servo 8 moves
			//servo 7 moves

			//keypad yellow leds fade up over 10s");
			g_led_fade_manager.fade(1, 10000, 0, 255);

			//3-6 minute pause

			//turn paintinglight off NOTE: no pin assinged

			//Servo 13 moves

			//Servos 10, 11, 12 move
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}