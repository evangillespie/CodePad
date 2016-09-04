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
		8000,	// pause before the 0th state - Pause 4
		5000,	// pause before the 1st state 5
		4000,	// 2nd Pause 6
		4000,	// 3 Pause 7
		4000,	// 4 - Pause 8
		4000,	// 5 - Pause 9

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
			//Timer panel moves to right position (position B)
                        //servo index, final pos, speed
			g_servo_manager.move_servo(6,  SERVO_6_POSITION_B, SERVO_6_SPEED);
			_increment_state();
			_substate = 0;
			break;
		case 1:
			Serial.println("Preenable: One");
			//Servo "Warning Bricks IN/OUT" extends outward
			//servo index, final pos, speed
			if (_substate == 0){
				g_servo_manager.move_servo(7, SERVO_7_POSITION_B, SERVO_7_SPEED);
				g_sound_manager.play_sound(211);  //play air release sound
				_substate++;
			} else if (_substate == 1){
				//Wait for Servo "Warning Bricks IN/OUT" to reach outer postition
				if (g_servo_manager.read_servo(7) == SERVO_7_POSITION_B){
					_substate++;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 2:
			Serial.println("Preenable: Two");

			//Servo ""Warning Bricks rotation"  rotate to open (position B)
			//servo index, final pos, speed
			g_servo_manager.move_servo(8, SERVO_8_POSITION_B, SERVO_8_SPEED);

			// Door warning sound triggers when led is high
			g_led_flash_manager.start_flasher_with_sound(3, 1.5, 206);
			_substate = 0;
			_increment_state();
			break;
		case 3:
			//The power to the Keypad must be turned on here
			digitalWrite(LED_10_PIN,HIGH);
			if (_substate == 0){
				Serial.println("Preenable: Three");
				g_led_flash_manager.stop_flasher(3);//stop Brick warning LED from previous case
				g_led_flash_manager.start_flasher_with_sound(3, 5.0, 206);//Brick warning LED flashed @ 12 hz for 2 seconds
				_stored_time = millis();
				_substate = 1;
			} else if (_substate == 1){
				if (millis() >= (_stored_time + 2000)){
					_substate = 2;
				}
			} else if (_substate == 2){
				g_led_flash_manager.stop_flasher(3);
				
				//The Keypad doors open

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
				
				// Miniature Keypad door servo moves to open position (position B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(16, SERVO_16_POSITION_B, SERVO_16_SPEED);
				
				g_sound_manager.play_sound(202);    // Keypad door sound triggers
				_substate = 3;
			} else if (_substate == 3){
				// Wait for Servo 1-4 to get to final position
				if ( 
					//Read one of the Keypad door servos to see if it's at closed position
					g_servo_manager.read_servo(4) == SERVO_4_POSITION_B
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
				Serial.println("Preenable: Four");
				
				//get pot value. use _susbstate temporarily so we don't need another variable
				_substate = analogRead(ANALOG_INPUT_1) / 4; 

				// keypadgreen LEDs fade from 0 - <keypadgreenpot> value over 4 seconds
				g_led_fade_manager.fade(11, 4000, 0, _substate);
//
				//Keypad's blue LED number keys fade up 
				//KEYPAD_NUMBERS_LED fade 0-200 over 3 seconds
				g_led_fade_manager.fade(2, 3000, 0, 200);

				//TimerLED ON
				g_shifter_dual.setPin(10, HIGH);
				g_shifter_dual.write();

				//keypadyellow LEDs fade from 100 - 0 over 3 seconds
				g_led_fade_manager.fade(1, 3000, 100, 0);

				//Bricklight moves to outer position (B)
				//servo index, final pos, speed
				g_servo_manager.move_servo(5, SERVO_5_POSITION_B, SERVO_5_SPEED);
				
				_substate = 1;
			} else if (_substate == 1){
					//when Bricklight servo is out, turn on the Bricklight and timer LEDs
				if (g_servo_manager.read_servo(5) == SERVO_5_POSITION_B){
					g_shifter_dual.setPin(8,HIGH);
                                	g_shifter_dual.setPin(9,HIGH);
                                	g_shifter_dual.write();
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
