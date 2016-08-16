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
			g_sound_manager.play_sound(10);

			//control panel leds off
			digitalWrite(KEYPAD_NUMBERS_LED, LOW);

			// 4-digit display off
			Keypad::clear_4_digit();
			
			//pindigit leds off
			Keypad::turn_off_right_wrong_leds();

			//keypad clr and ok leds off
			digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
			digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

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

			//trigger power crystal sound
			g_sound_manager.play_sound(11); 

			break;
		case 3:
			Serial.println("Three");

			//TODO:
			//turn off timer led

			//Servo 6 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(6, 0, 100);
			//servo 5 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(5, 0, 100);

			//servos 10, 11, 12 move
			//servo index, final pos, speed
			g_servo_manager.move_servo(10, 0, 100);
			g_servo_manager.move_servo(11, 0, 100);
			g_servo_manager.move_servo(12, 0, 100);

			//TODO wait for servos to reach final pos


			g_sound_manager.stop_sound(11);

			//turn power crystal led off
			digitalWrite(LED_12_PIN, LOW);

			break;
		case 4:
			Serial.println("Four");

			//Servo 13 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(13, 500, 100);

			//TODO EVAN: after random times, all digit displays turn off (pause23-26)

			//brick warning finger flashed @ 5hz and brick warning sound triggers when brick warning finger is high
			g_led_flash_manager.start_flasher_with_sound(3, 5.0, 3);
			
			//Servos 1, 2, 3, 4 move
			//servo index, final pos, speed
			g_servo_manager.move_servo(1, 500, 60);

			//servo index, final pos, speed
			g_servo_manager.move_servo(2, 500, 60);

			//servo index, final pos, speed
			g_servo_manager.move_servo(3, 1000, 71);

			//keypad door sound triggers
			g_sound_manager.play_sound(1);

			break;
		case 5:
			Serial.println("Five");

			//turn off brick warning led and sound
			g_led_flash_manager.stop_flasher(3);

			//servo 8 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(8, 0, 100);

			//TODO: When servo 8 reaches final pos continue

			//servo 7 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(7, 0, 100);

			//keypad yellow leds fade up over 10s");
			g_led_fade_manager.fade(1, 10000, 0, 255);

			//3-6 minute pause

			//turn paintinglight off NOTE: no pin assinged

			//Servo 13 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(13, 0, 100);
			//TODO: When Servo 13 is at final position continue

			//Servos 10, 11, 12 move
			//servo index, final pos, speed
			g_servo_manager.move_servo(10, 0, 100);
			g_servo_manager.move_servo(11, 0, 100);
			g_servo_manager.move_servo(12, 0, 100);

			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	_increment_state();
}