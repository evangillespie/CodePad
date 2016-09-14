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
		7000,	//pause before the 0th state
		5000,	//pause before the 1st state
		4000,	//pause before the 2nd state
		4000,	//pause before the 3rd state
		2000,	//pause before the 4th state
		500,	//pause before the 5th state
	};
		
	return _pause_lengths[index];
}

int KeypadPreenableState::_get_max_state() {
	return 5;
}


void KeypadPreenableState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Preenable Zero");
			//keypadyellow LEDs fade from 0 - 100 over 3 seconds
			g_led_fade_manager.fade(1, 3000, 0, 50);
			
			//pizza coals LED fades from 0-150 over 5 seconds
			g_led_fade_manager.fade(6, 5000, 0, 150);

			//Timer panel moves to right position (position B)
			g_servo_manager.move_servo(6,  SERVO_6_POSITION_B, SERVO_6_SPEED);

			_increment_state();
			_substate = 0;
			break;
		case 1:
			Serial.println("Preenable: One");
			//power crystal LED fades from 0-80 over 5 seconds
			g_led_fade_manager.fade(12, 5000, 0, 40);

			//Servo "Warning Bricks IN/OUT" extends outward
			if (_substate == 0){
				g_servo_manager.move_servo(7, SERVO_7_POSITION_B, SERVO_7_SPEED);

				//Play air release sound
				g_sound_manager.play_sound(211);

				_substate++;
			} else if (_substate == 1){
				//Wait for Servo "Warning Bricks IN/OUT" to position B
				if (g_servo_manager.is_servo_in_position(7)){
					_substate++;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 2:
                        Serial.println("Preenable: Two");
                        
                        //Solenoid moves Warning_Bricks_Mini out
			digitalWrite (SOLENOID_2_PIN, HIGH);

			//Servo ""Warning Bricks rotation"  rotate to open (position B)
			g_servo_manager.move_servo(8, SERVO_8_POSITION_B, SERVO_8_SPEED);

			//Door warning sound triggers when led is high
			g_led_flash_manager.start_flasher_with_sound(3, 1.5, 206);

			_substate = 0;
			_increment_state();
			break;
		case 3:
			//Turn on the power to the Keypad LEDs
			digitalWrite(LED_10_PIN,HIGH);

			if (_substate == 0){
				Serial.println("Preenable: Three");

				//stop Brick warning LED from previous case
				g_led_flash_manager.stop_flasher(3);  

				_stored_time = millis();
				_substate = 1;
			} else if (_substate == 1){
				if (millis() >= (_stored_time + 2000)){
					_substate = 2;
				}
			} else if (_substate == 2){

				//Servo Keypad door right A moves to open position (position B)
				g_servo_manager.move_servo(1,SERVO_1_POSITION_B, SERVO_1_SPEED);

				//Servo Keypad door right B moves to open position (position B)
				g_servo_manager.move_servo(2, SERVO_2_POSITION_B, SERVO_2_SPEED);
				
				//Servo Keypad door Left A moves to open position (position B)
				g_servo_manager.move_servo(3, SERVO_3_POSITION_B, SERVO_3_SPEED);
				
				//Servo Keypad door Left B moves to open position (position B)
				g_servo_manager.move_servo(4, SERVO_4_POSITION_B, SERVO_4_SPEED);

				//Miniature Keypad door servo moves to open position (position B)
				g_servo_manager.move_servo(16, SERVO_16_POSITION_B, SERVO_16_SPEED);
				
				//Keypad door sound triggers
				g_sound_manager.play_sound(202);
				_substate = 3;
			} else if (_substate == 3){
				//Wait for Servo 1-4 to get to final position
				if ( 
					g_servo_manager.is_servo_in_position(1) &&
					g_servo_manager.is_servo_in_position(2) &&
					g_servo_manager.is_servo_in_position(3) &&
					g_servo_manager.is_servo_in_position(4)
				){
					//Stop the DOOR LED flashing                                      
					g_led_flash_manager.stop_flasher(3);  
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

				//TimerLED ON
				g_shifter_dual.setPin(10, HIGH);
				g_shifter_dual.write();

				//keypadyellow LEDs fade from max - 0 over 4 seconds
				g_led_fade_manager.fade(1, 7000, 50, 0);

				//Bricklight moves to outer position (B)
				g_servo_manager.move_servo(5, SERVO_5_POSITION_B, SERVO_5_SPEED);
				
				_substate = 1;
			} else if (_substate == 1){
				if (g_servo_manager.is_servo_in_position(5)){
  
				//get pot value. use _susbstate temporarily so we don't need another variable
				_substate = analogRead(ANALOG_INPUT_1) / 4; 

				//Keypad Green LEDs fade from 0 - 100
				g_led_fade_manager.fade(11, 6000, 0, 100);

				//KEYPAD_NUMBERS_LED fade 0-max over 6 seconds
				g_led_fade_manager.fade(2, 6000, 0, 200);

			
				//Bricklight LED ON
				g_shifter_dual.setPin(8,HIGH);
				g_shifter_dual.write();
                                
				//Display panel LEDs ON    
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
