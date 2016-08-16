#include "Arduino.h"
#include "Pins.h"
#include "FailState.h"
#include "Keypad.h"

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
		2000, 	// 4 - Pause 14
		0 		// 5 - no pause
	};
		
	return _pause_lengths[index];
}

int FailState::_get_max_state() {
	return 5;
}


void FailState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Fail: Zero");
			// badpin sound
			g_sound_manager.play_sound(9);

			// clear bargraph
			Keypad::clear_bargraph();

			// 4-digit display off
			Keypad::clear_4_digit();

			// Turn off Keypad clr and ok leds
			digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
			digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

			// ControlPanel led off
			digitalWrite(KEYPAD_NUMBERS_LED, LOW);
			
			// turn off all pindigit leds
			Keypad::turn_off_right_wrong_leds();

			// timer sound off
			g_sound_manager.stop_sound(4);
			g_sound_manager.stop_sound(5);

			_increment_state();
			break;

		case 1:
			Serial.println("Fail: One");

			// Servo 6 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(6, 500, 100);

			// Turn off Bricklamp led
			// g_led_flash_manager.stop_flasher(*)	waiting on pin assignment

			// Keypad Green LED fades down over 3s
			g_led_fade_manager.fade(11, 3000, 255, 0);
			
			// Keypad buttons fade down over 3s
			g_led_fade_manager.fade(5, 3000, 255, 0);
			g_led_fade_manager.fade(6, 3000, 255, 0);
			g_led_fade_manager.fade(7, 3000, 255, 0);

			_increment_state();
			break;
		case 2:
			Serial.println("Fail: Two");

			// Keypad yellow leds fade down over 5s
			g_led_fade_manager.fade(1, 5000, 255, 0);
	
			//Servo 5 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(5, 0, 100);

			//Brick warning finger flashes @ 5hz. blick warning sound triggers on high
			g_led_flash_manager.start_flasher_with_sound(3, 5, 3);

			_increment_state();
			break;
		case 3:
			Serial.println("Fail: Three");

			// Servo 1 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(1, 500, 60);

			// Servo 2 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(2, 500, 60);

			// Servo 3 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(3, 1000, 71);

			// Servo 4 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(4, 540, 71);

			// Keypad door sound
			g_sound_manager.play_sound(1);

			_increment_state();
			break;
		case 4:
			Serial.println("Fail: Four");
			
			//turn off brick warning led
			g_led_flash_manager.stop_flasher(3);
			
			// turn off timer led
			// g_led_flash_manager.stop_flasher(*); wating on pin assignment

			// Servo 8 moves
			//servo index, final pos, speed
			g_servo_manager.move_servo(8, 0, 100);

			// wait until servo 8 stops moving
			//TODO wait for servo 8


			_increment_state();
			_substate = 0;
			break;
		case 5:
			if (_substate == 0){
				Serial.println("Fail: Five");
				
				// move servo 7
				//servo index, final pos, speed
				g_servo_manager.move_servo(7, 0, 100);

				_stored_time = millis();
				for (int i=0; i < 4; i++){
					_times[i] = _stored_time + (unsigned long)random(1000, 15000);
					_elements_turned_off[i] = false;
				}
				_substate++;
			} else if (_substate == 1){
				for (int i=0; i < 4; i++){
					if (_elements_turned_off[i] == false){
						if (millis() >= _times[i]){
							switch (i){
								case 0:
									// turn off nixie tube 1
									break;
								case 1:
									// turn off nixie tube 2
									break;
								case 2:
									// turn off led matrix
									break;
								case 3:
									// turn off clock led
									break;
							}
							_elements_turned_off[i] = true;
						}
					}
				}
				
				// return to avoid _increment_state() if any of the elemts hasnt been set
				for (int i=0; i < 4; i++){
					if (_elements_turned_off[i] == false){
						return;
					}
				}
				_substate++;

			} else {
				_increment_state();
			}

			break;
		default:
			Serial.println("You're in a weird state, brah");
	}
}