#include "Arduino.h"
#include "KeypadPreenableState.h"
#include "Pins.h"

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
			// g_sound_manager.play_sound(1);
			Serial.println("Preenable zero");
			//Servo 6 move from 0-500 @ speed=100
			//servo index, final pos, speed
			g_servo_manager.move_servo(6, 500, 100);
			_increment_state();
			break;
		case 1:
			Serial.println("Preenable: One");
			//Servo 7 move from 0-500 @ speed=100
			//servo index, final pos, speed
			g_servo_manager.move_servo(7, 500, 100);

			//TODO:
			//Wait for Servo 7 to reach 500
			//servo index, final pos, speed
			g_servo_manager.read_servo(7);

			_increment_state();
			break;
		case 2:
			Serial.println("Preenable: Big Two");

			//Servo 8 move from 0-500 @ speed=100
			//servo index, final pos, speed
			g_servo_manager.move_servo(8, 500, 100);


			// Door warning sound triggers when led is high
			g_led_flash_manager.start_flasher_with_sound(3, 4.0, 2);
			_substate = 0;
			_increment_state();
			break;
		case 3:
			if (_substate == 0){
				Serial.println("Preenable: Th-Three");
				g_led_flash_manager.stop_flasher(3);//stop Brick warning LED from previous case
				g_led_flash_manager.start_flasher_with_sound(3, 12.0, 2);//Brick warning LED flashed @ 12 hz for 2 seconds
				_stored_time = millis();
				_substate = 1;
			} else if (_substate == 1){
				if (millis() >= (_stored_time + 2000)){
					_substate = 2;
				}
			} else {
				g_led_flash_manager.stop_flasher(3);

				// Servo 1 Move from 500 - 955 @ speed=60
				//servo index, final pos, speed
				g_servo_manager.move_servo(1, 955, 60);

				//TODO: get direction
				// Servo 2 Move from 500 - 45 @ speed of 60
				//servo index, final pos, speed
				g_servo_manager.move_servo(2, 45, 60);
				
				// Servo 3 move from 1000 - 460 @ speed of 71
				//servo index, final pos, speed
				g_servo_manager.move_servo(3, 460, 71);
				
				// Servo 4 move from 0 - 540 @speed of 71
				//servo index, final pos, speed
				g_servo_manager.move_servo(4, 540, 71);
				
				// Keypad door sound triggers or possile "doorOpenSound"
				g_sound_manager.play_sound(1);

				//TODO:
				// Wait for Servo 1-4 to get to final position
				g_servo_manager.read_servo(1);
				g_servo_manager.read_servo(2);
				g_servo_manager.read_servo(3);
				g_servo_manager.read_servo(4);

				_increment_state();
			}
			break;
		case 4:
			Serial.println("Preenable: Four");
			
			//get pot value
			_substate = analogRead(ANALOG_INPUT_1) / 4; 

			// keypadgreen LEDs fade from 0 - <keypadgreenpot> value over 3 seconds
			g_led_fade_manager.fade(11, 3000, 0, _substate);

			// Button 3 - keypadbutton's fade from 0 - max over 3 seconds
			g_led_fade_manager.fade(5, 3000, 0, 255); 

			// Button 2 - keypadbutton's fade from 0 - max over 3 seconds
			g_led_fade_manager.fade(6, 3000, 0, 255); 

			// Button 1 - keypadbutton's fade from 0 - max over 3 seconds
			g_led_fade_manager.fade(7, 3000, 0, 255); 

			//TimerLED no pin yet - NOTE: on Shift register

			//keypadyellow LEDs fade from max - 0 over 4 seconds
			g_led_fade_manager.fade(2, 4000, 255, 0);

			//control panel leds on
			digitalWrite(KEYPAD_NUMBERS_LED, HIGH);

			//servo5 move from 0 - 500 @ speed = 100
			//servo index, final pos, speed
			g_servo_manager.move_servo(5, 500, 100);

			//Wait for servo5 to reach 500
			g_servo_manager.read_servo(5);

			//g_led_flash_manager.start_flasher(*,0);// NOTE: on Shift register
			
			_increment_state();
			break;
		case 5:
			_increment_state();
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	
}