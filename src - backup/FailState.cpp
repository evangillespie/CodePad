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
		100,	//Pause before the 0th state
		3000,	//Pause before the 1st state
		4000,	//Pause before the 2nd state
		5000,	//Pause before the 3rd state
		2000, 	//Pause before the 4th state
		0       //Pause before the 5th state
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
			//Play badpin tuba sound
			g_sound_manager.play_sound(random(300,311));
			
			//Solenoid pops TUBAMAN out of coo coo clock
			digitalWrite(TUBA_PLAYER_SOLENOID_PIN, HIGH);

			//clear bargraph
			Keypad::clear_bargraph();

			//4-digit display off
			Keypad::clear_4_digit();

			//Turn off Keypad clr and ok leds
			digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
			digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

			//ControlPanel led off
                        g_shifter_dual.setPin(9,LOW);
                        g_shifter_dual.write();
			
			//Turn off all pindigit leds
			Keypad::turn_off_right_wrong_leds();

			_increment_state();
			break;

		case 1:
			Serial.println("Fail: One");

			//Solenoid retracts TUBAMAN into coo coo clock
			digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);

			//Timer Panel Servo 6 moves to the left- position A
			g_servo_manager.move_servo(6, SERVO_6_POSITION_A, SERVO_6_SPEED);

			//Turn the Bricklight OFF
                        g_shifter_dual.setPin(8,LOW);
                        g_shifter_dual.write();

			// Keypad Green LEDs fades down
			g_led_fade_manager.fade(11, 6000, 100, 0);
			
			// Keypad buttons Blue LEDs fade down
			g_led_fade_manager.fade(2, 8000, 200, 0);

			_increment_state();
			break;
		case 2:
			Serial.println("Fail: Two");

			//Magpanel LEDs turn OFf			
			g_shifter_quad.setPin(29,LOW);
			g_shifter_quad.write();

			// Keypad yellow leds fade up
			g_led_fade_manager.fade(1, 3000, 0, 50);
	
			//Lightbrick Servo 5 moves to IN position (position A)
			g_servo_manager.move_servo(5, SERVO_5_POSITION_A, SERVO_5_SPEED);

			//Brick warning finger flashes @ 2hz. brick warning sound triggers on high
			g_led_flash_manager.start_flasher_with_sound(4, 2, 206);

                        //Timer LEDs turned OFF
                        g_shifter_dual.setPin(10,LOW);
                        g_shifter_dual.write();

			_increment_state();
			_substate = 0;
			break;
		case 3:
			Serial.println("Fail: Three");

			if (_substate == 0){
				//Keypad door right A Servo 1 moves to closed position (Position A)
				g_servo_manager.move_servo(1, SERVO_1_POSITION_A, SERVO_1_SPEED);

				//Keypad door right B Servo 2 moves to closed position (Position A)
				g_servo_manager.move_servo(2, SERVO_2_POSITION_A, SERVO_2_SPEED);

				//Keypad door left A Servo 3 moves to closed position (Position A)
				g_servo_manager.move_servo(3, SERVO_3_POSITION_A, SERVO_3_SPEED);

				//Keypad door left B Servo 4 moves to closed position (Position A)
				g_servo_manager.move_servo(4, SERVO_4_POSITION_A, SERVO_4_SPEED);

				//Miniature Keypad door servo moves to closed position (position A)
				g_servo_manager.move_servo(16, SERVO_16_POSITION_A, SERVO_16_SPEED);

				//Keypad door sound
				g_sound_manager.play_sound(202);

				_substate = 1;
			} else if (_substate == 1){
				if (
					g_servo_manager.is_servo_in_position(1) &&
					g_servo_manager.is_servo_in_position(2) &&
					g_servo_manager.is_servo_in_position(3) &&
					g_servo_manager.is_servo_in_position(4)		
				){
                                        //Turn off the Keypad MOSFET (various LEDs on Keypad)					
                                        g_led_flash_manager.stop_flasher(10);
                                        _substate = 2;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 4:
			Serial.println("Fail: Four");
			
			if (_substate == 0){
				//Stop warning finger flashing LED
				g_led_flash_manager.stop_flasher(4); 

				// Warning Bricks rotation Servo 8 rotates to closed position
				g_servo_manager.move_servo(8, SERVO_8_POSITION_A, SERVO_8_SPEED);

				//move clock servo to position A to prep for sweeping during pause state
				g_servo_manager.move_servo(14, SERVO_14_POSITION_B, SERVO_14_SPEED);

				_substate = 1;
			} else if (_substate == 1){
				// wait until servo 8 stops moving
				if (g_servo_manager.is_servo_in_position(8)) {
					_substate = 2;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;
		case 5:
			if (_substate == 0){
				Serial.println("Fail: Five");

				//Solenoid moves Warning_Bricks_Mini in
				digitalWrite(SOLENOID_2_PIN, LOW);
				
				// move Warning Bricks IN/OUT servo 7 to IN position A
				g_servo_manager.move_servo(7, SERVO_7_POSITION_A, SERVO_7_SPEED);

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
									Display::clear_nixie_tube(1);
									break;
								case 1:
									// turn off nixie tube 2
									Display::clear_nixie_tube(2);
									break;
								case 2:
									// turn off led matrix
									Display::clear_matrix();
									break;
								case 3:
									//Clock illumination LEDs fade up
									g_led_fade_manager.fade(7, 1500, 0, 50);
									
									//Green LEDs inside_clock turn off
									g_shifter_quad.setPin(25,LOW);
									g_shifter_quad.write();

									//Turn on all the clock number LEDs with a short delay in betwween for shifter to preform switching
									g_shifter_quad.setPin(13,HIGH);  //clock number LED 0
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(14,HIGH);  //clock number LED 1
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(15,HIGH);  //clock number LED 2
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(16,HIGH);  //clock number LED 3
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(17,HIGH);  //clock number LED 4
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(18,HIGH);  //clock number LED 5
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(19,HIGH);  //clock number LED 6
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(20,HIGH);  //clock number LED 7
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(21,HIGH);  //clock number LED 8
									g_shifter_quad.write();
									delay(50);
									g_shifter_quad.setPin(22,HIGH);  //clock number LED 9
									g_shifter_quad.write();
							}
							_elements_turned_off[i] = true;
						}
					}
				}
				
				//return to avoid _increment_state() if any of the elemts hasnt been set
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
