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
		3000,	// pause before the 0th state - Pause 10
		3000,	// pause before the 1st state - Pause 11
		4000,	// 2nd - Pause 12
		5000,	// 3 - Pause 13
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
			// badpin tuba sound
			g_sound_manager.play_sound(random(300,311));

			// clear bargraph
			Keypad::clear_bargraph();

			// 4-digit display off
			Keypad::clear_4_digit();

			// Turn off Keypad clr and ok leds
			digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
			digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

			// ControlPanel led off
                        g_shifter_dual.setPin(9,LOW);
                        g_shifter_dual.write();
			
			// turn off all pindigit leds
			Keypad::turn_off_right_wrong_leds();

			// timer sound off
			g_sound_manager.stop_sound(208);
			g_sound_manager.stop_sound(209);

			_increment_state();
			break;

		case 1:
			Serial.println("Fail: One");

			// Timer Panel Servo 6 moves to the left- position A
			//servo index, final pos, speed
			g_servo_manager.move_servo(6, SERVO_6_POSITION_A, SERVO_6_SPEED);

			// Turn off Bricklamp LED
			g_shifter_dual.setPin(8,LOW);
                        g_shifter_dual.write();

			// Keypad Green LED fades down over 3s
			g_led_fade_manager.fade(11, 3000, 100, 0);
			
			// Keypad buttons Blue LEDs fade down over 3s
			g_led_fade_manager.fade(2, 3000, 200, 0);

			_increment_state();
			break;
		case 2:
			Serial.println("Fail: Two");

			// Keypad yellow leds fade up over 3s
			g_led_fade_manager.fade(1, 3000, 0, 50);
	
			//Lightbrick Servo 5 moves to IN position (position A)
			//servo index, final pos, speed
			g_servo_manager.move_servo(5, SERVO_5_POSITION_A, SERVO_5_SPEED);

			//Brick warning finger flashes @ 5hz. blick warning sound triggers on high
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
				
				//Keypad doors close
					
				// Keypad door right A Servo 1 moves to closed position (Position A)
				//servo index, final pos, speed
				g_servo_manager.move_servo(1, SERVO_1_POSITION_A, SERVO_1_SPEED);

				// Keypad door right B Servo 2 moves to closed position (Position A)
				//servo index, final pos, speed
				g_servo_manager.move_servo(2, SERVO_2_POSITION_A, SERVO_2_SPEED);

				// Keypad door left A Servo 3 moves to closed position (Position A)
				//servo index, final pos, speed
				g_servo_manager.move_servo(3, SERVO_3_POSITION_A, SERVO_3_SPEED);

				// Keypad door left B Servo 4 moves to closed position (Position A)
				//servo index, final pos, speed
				g_servo_manager.move_servo(4, SERVO_4_POSITION_A, SERVO_4_SPEED);

                                // Miniature Keypad door servo moves to closed position (position A)
				//servo index, final pos, speed
				g_servo_manager.move_servo(16, SERVO_16_POSITION_A, SERVO_16_SPEED);

				g_sound_manager.play_sound(202);   // Keypad door sound

				_substate = 1;
			} else if (_substate == 1){
				if (
					//read one of the Keypad door servos to see if its at closed position
					g_servo_manager.read_servo(4) == SERVO_4_POSITION_A		
				){
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
				//turn off brick finger warning LED
				g_led_flash_manager.stop_flasher(4);
				
				//turn off the Keypad power MOSFET
				digitalWrite(LED_10_PIN,LOW);
				
				// Warning Bricks rotation Servo 8 rotates to closed position
				//servo index, final pos, speed
				g_servo_manager.move_servo(8, SERVO_8_POSITION_A, SERVO_8_SPEED);

				_substate = 1;
			} else if (_substate == 1){
				// wait until Warning Bricks rotation servo 8 stops moving
				if (g_servo_manager.read_servo(8) == SERVO_8_POSITION_A){
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
				
				// move Warning Bricks IN/OUT servo 7 to IN position A
				//servo index, final pos, speed
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
									//Evan, can you add the code to turn these displays off?
									// turn off nixie tube 1
									break;
								case 1:
									// turn off nixie tube 2
									break;
								case 2:
									// turn off led matrix
									break;
								case 3:
									// clock illumination LEDs fade up
									g_led_fade_manager.fade(7, 5000, 0, 100);
									
									//Green_LEDs_inside_clock turn off
									g_shifter_quad.setPin(25,LOW);
                        						g_shifter_quad.write();
									
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
