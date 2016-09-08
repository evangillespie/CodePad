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
			//Servo 6 move from 0-500 @ speed=100
			//servo index, final pos, speed
			g_servo_manager.move_servo(6,  SERVO_6_POSITION_B, SERVO_6_SPEED);
			_increment_state();
			_substate = 0;
			break;
		case 1:
			//Servo 7 move from 0-500 @ speed=100
			//Servo "Warning Bricks IN/OUT" extends outward
			//servo index, final pos, speed
			if (_substate == 0){
				g_servo_manager.move_servo(7, SERVO_7_POSITION_B, SERVO_7_SPEED);
				_substate++;
			} else if (_substate == 1){
				//Wait for Servo 7 to reach 500
				if (g_servo_manager.is_servo_in_position(7)){
					_substate++;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 2:

			//Servo 8 move from 0-500 @ speed=100
			//Servo ""Warning Bricks rotation"  rotate to open (position B)
			//servo index, final pos, speed
			g_servo_manager.move_servo(8, SERVO_8_POSITION_B, SERVO_8_SPEED);


			// Door warning sound triggers when led is high
			g_led_flash_manager.start_flasher_with_sound(3, 4.0, 2);
			_substate = 0;
			_increment_state();
			break;
		case 3:
			if (_substate == 0){
				g_led_flash_manager.stop_flasher(3);//stop Brick warning LED from previous case
				g_led_flash_manager.start_flasher_with_sound(3, 12.0, 2);//Brick warning LED flashed @ 12 hz for 2 seconds
				_stored_time = millis();
				_substate = 1;
			} else if (_substate == 1){
				if (millis() >= (_stored_time + 2000)){
					_substate = 2;
				}
			} else if (_substate == 2){
				g_led_flash_manager.stop_flasher(3);

				// Servo Keypad door right A moves to open position (position B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(1,SERVO_1_POSITION_B, SERVO_1_SPEED);

				// Servo Keypad door right B moves to open position (position B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(2, SERVO_2_POSITION_B, SERVO_2_SPEED);
				
				// Servo Keypad door Left A moves to open position (position B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(3, SERVO_3_POSITION_B, SERVO_3_SPEED);
				
				// Servo Keypad door Left B moves to open position (position B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(4, SERVO_4_POSITION_B, SERVO_4_SPEED);
				
				// Keypad door sound triggers or possile "doorOpenSound"
				g_sound_manager.play_sound(1);
				_substate = 3;
			} else if (_substate == 3){
				// Wait for Servo 1-4 to get to final position
				if ( 
					g_servo_manager.is_servo_in_position(1) &&
					g_servo_manager.is_servo_in_position(2) &&
					g_servo_manager.is_servo_in_position(3) &&
					g_servo_manager.is_servo_in_position(4)
				){
					_substate = 4;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 4:
			if (_substate == 0){
				
				//get pot value. use _susbstate temporarily so we don't need another variable
				_substate = analogRead(ANALOG_INPUT_1) / 4; 

				// keypadgreen LEDs fade from 0 - <keypadgreenpot> value over 3 seconds
				g_led_fade_manager.fade(11, 3000, 0, _substate);

				/*REMOVED 
				// Button 3 - keypadbutton's fade from 0 - max over 3 seconds
				g_led_fade_manager.fade(5, 3000, 0, 255); 

				// Button 2 - keypadbutton's fade from 0 - max over 3 seconds
				g_led_fade_manager.fade(6, 3000, 0, 255); 

				// Button 1 - keypadbutton's fade from 0 - max over 3 seconds
				g_led_fade_manager.fade(7, 3000, 0, 255);
				*/ 

				//ADDED
				//KEYPAD_NUMBERS_LED fade 0-max over 3 seconds
				g_led_fade_manager.fade(13, 3000, 0, 255);

				
				//TimerLED no pin yet - NOTE: on Shift register
				//TODO: on dual shift register pin 10
				g_shifter_dual.setPin(10, HIGH);

				//keypadyellow LEDs fade from max - 0 over 4 seconds
				g_led_fade_manager.fade(2, 4000, 255, 0);

				//control panel leds on
				digitalWrite(KEYPAD_NUMBERS_LED, HIGH);

				//servo5 move from 0 - 500 @ speed = 100
				//servo index, final pos, speed
				g_servo_manager.move_servo(5, SERVO_5_POSITION_B, SERVO_5_SPEED);

				//g_led_flash_manager.start_flasher(*,0);// NOTE: on Shift register
				//TODO: on dual shift register pin 9, find out if HIGH, LOW or FADE?
				g_shifter_dual.setPin(9, HIGH);

				g_shifter_dual.write();
				
				_substate = 1;
			} else if (_substate == 1){
				if (g_servo_manager.is_servo_in_position(5)){
					_substate = 2;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 5:
			_increment_state();
			break;
		default:
			Serial.println("You're in a weird state, brah");
	}

	
}