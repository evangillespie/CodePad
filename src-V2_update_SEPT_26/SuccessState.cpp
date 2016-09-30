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
		0,// Pause before the 0th state
		2000,	// Pause before the 1st state
		3000,	// Pause before the 2nd state
		4000,	// Pause before the 3rd state
		2000, 	// Pause before the 4th state
		5000,   // Pause before the 5th state
		random(15000, 40000),  // Pause before the 6th state
		random(15000, 40000), // Pause before the 7th state
		random(8000, 15000),  // Pause before the 8th state
		12000, 	// Pause before the 9th state
		3000,   // Pause before the 10th state
		4000,   // Pause before the 11th state
		2000,   // Pause before the 12th state
		1000,   // Pause before the 13th state
	};
		
	return _pause_lengths[index];
}

int SuccessState::_get_max_state() {
	return 13;
}


void SuccessState::_dispatcher() {
	switch(_state_num){
		case 0:
			Serial.println("Success- Zero");
			//Clear bargraph
			Keypad::clear_bargraph();

			_increment_state();
			break;
		case 1:
			Serial.println("Success- One");
                        //Play correct code tuba sound at random
			g_sound_manager.play_sound(random(312,319));
                        
                        //TUBAMAN pops out of coo coo clock
                        digitalWrite(TUBA_PLAYER_SOLENOID_PIN,HIGH);

			// ControlPanel led off
                        g_shifter_dual.setPin(9,LOW);
                        g_shifter_dual.write();

			// 4-digit display off
			Keypad::clear_4_digit();
			
			//pindigit leds off
			Keypad::turn_off_right_wrong_leds();

			//keypad clr and ok leds off
			digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
			digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

			_increment_state();
			break;
		case 2:
			Serial.println("Success- Two");
                        //TUBAMAN retracts into coo coo clock
                        digitalWrite(TUBA_PLAYER_SOLENOID_PIN,LOW);  
                      
			// Turn off Bricklamp LED
			g_shifter_dual.setPin(8,LOW);
                        g_shifter_dual.write();

			//get pot value
			//_substate = analogRead(ANALOG_INPUT_1) / 4; 

			//fade keypad green led down over 3s from pot position 0 - <keypadgreenpot>
			g_led_fade_manager.fade(11, 3000, _substate, 0); 

                        // Keypad buttons Blue LEDs fade down over 3s
			g_led_fade_manager.fade(2, 3000, 200, 0);

			//Power crystals fade up to brightness 200
                        g_led_fade_manager.fade(12, 5000, 0, 200);

			//Power crystal startup sound
			g_sound_manager.play_sound(213); 

			_substate = 0;
			_increment_state();
			break;
		case 3:
			Serial.println("Success- Three");
			if (_substate == 0){
				//turn off the Power to the Keypad LEDs
 				digitalWrite(LED_10_PIN,LOW);
  
				//Power crystal ambient hum sound
				g_sound_manager.play_sound(214);

				//Timer LEDs turned OFF
				g_shifter_dual.setPin(10,LOW);
				g_shifter_dual.write();

				//Timer Panel Servo 6 moves to the left- position A
			        g_servo_manager.move_servo(6, SERVO_6_POSITION_A, SERVO_6_SPEED);
				
				//Lightbrick Servo 5 moves to IN position (position A)
				g_servo_manager.move_servo(5, SERVO_5_POSITION_A, SERVO_5_SPEED);

				//Brass Cage lifts up slowly. Servos 9 and 13 move together to lift the cage
				g_servo_manager.move_servo(9, SERVO_9_POSITION_B, SERVO_9_SPEED);
				g_servo_manager.move_servo(13, SERVO_13_POSITION_B, SERVO_13_SPEED);
                                
				//Cage moving sound
				g_sound_manager.play_sound(215);

				//Red Pulley LED - pin 23 (quad shifter) OFF while cage moves
				g_shifter_quad.setPin(23, LOW);
				g_shifter_quad.write();

				//Green Pulley LED - pin 24 (quad shifter) ON while cage moves
				g_shifter_quad.setPin(24, HIGH);
				g_shifter_quad.write();
		
				_substate = 1;
			} else if (_substate == 1){
				//wait for servos to reach final pos
				if (
					g_servo_manager.is_servo_in_position(9)&&
					g_servo_manager.is_servo_in_position(13)
				){
					_substate = 2;
				}
			} else {
  				//Red Pulley LED - pin 23 (quad shifter) ON if cage is not moving
				g_shifter_quad.setPin(23, HIGH);
				g_shifter_quad.write();

				//Green Pulley LED - pin 24 (quad shifter) OFF if cage is not moving
				g_shifter_quad.setPin(24, LOW);
				g_shifter_quad.write();
  	
				//Solenoid moves brass handrail out
				digitalWrite(SOLENOID_4_PIN, HIGH);

				//stop the cage moving sound
				g_sound_manager.stop_sound(215);

				//fade power crystal LED down
				g_led_fade_manager.fade(12, 2000, 200, 5);

				_increment_state();
				_substate = 0;
			}
			break;

		case 4:
			Serial.println("Success- Four");
                if (_substate == 0){
                          
				//Solenoid moves brass stairs out                          
				digitalWrite(SOLENOID_3_PIN, HIGH);
                          
				//Cage opens up. Servos 10,11,12 move to position B in unison
                                
				//Cage top moves to open position (position B)
				g_servo_manager.move_servo(10, SERVO_10_POSITION_B, SERVO_10_SPEED);

				//Cage left moves to open position (position B)
				g_servo_manager.move_servo(11, SERVO_11_POSITION_B, SERVO_11_SPEED);

				//Cage right moves to open position (position B)
				g_servo_manager.move_servo(12, SERVO_12_POSITION_B, SERVO_12_SPEED);

				//Cage opening sound
				g_sound_manager.play_sound(216);

				_substate = 1;
				} 
				else if (_substate == 1){
				//wait for cage to open up to position B
				if (
					g_servo_manager.is_servo_in_position(10)&&
					g_servo_manager.is_servo_in_position(11)&&
					g_servo_manager.is_servo_in_position(12)
				){
					//stop the cage moving sound                                      
					g_sound_manager.stop_sound(216);					
					_substate = 2;
                                      
				}
			} else {
				_increment_state();
				_substate = 0;
			}

			break;

		case 5:
			Serial.println("Success- Five");
 			//Turn the radar control panel LEDs on 
			g_shifter_quad.setPin(27, HIGH);
			g_shifter_quad.write();
                                
			//Radar screen begins fading sequence radar (blips) 
			g_led_fade_manager.fade(5, 3500, 10, 220);
			//TODO
			//insert fading sequece here that looks like radar blips
                                
			//Play ambient radar sound
			g_sound_manager.play_sound(218);

			//Play radio chatter sound
			g_sound_manager.play_sound(219);
			_increment_state();
        		break;
        
		case 6:
			Serial.println("Success- Six");
                              
			//Turn the painting light on
			g_shifter_quad.setPin(30, HIGH);
			g_shifter_quad.write();
                                
			//Play painting light click sound
			g_sound_manager.play_sound(222);

			//Play time travel flicking sound
			g_sound_manager.play_sound(223);

			//Play ambient echo sounds
			g_sound_manager.play_sound(221);

			_increment_state();
        	        break;
        
		case 7:
			Serial.println("Success- Seven");
                                 
			//Play teleprotation sound
			g_sound_manager.play_sound(220);

			//Play portal hum sound
			g_sound_manager.play_sound(224);

			_increment_state();
          	        break;
          
		case 8:
			Serial.println("Success- Eight");
			if (_substate == 0){
				//Cage closes up. Servos 10,11,12 move to position A in unison
                                
				//Cage top moves to open position (position A)
				g_servo_manager.move_servo(10, SERVO_10_POSITION_A, SERVO_10_SPEED);

				//Cage left moves to open position (position A)
				g_servo_manager.move_servo(11, SERVO_11_POSITION_A, SERVO_11_SPEED);

				//Cage right moves to open position (position A)
				g_servo_manager.move_servo(12, SERVO_12_POSITION_A, SERVO_12_SPEED);

				//Play cage opening sound
				g_sound_manager.play_sound(216);

				_substate = 1;
				} 
				else if (_substate == 1){
				//wait for cage to close to position A
				if (
					g_servo_manager.is_servo_in_position(10)&&
					g_servo_manager.is_servo_in_position(11)&&
					g_servo_manager.is_servo_in_position(12)
				){
					//stop the cage open/close sound
					g_sound_manager.stop_sound(216);					
					_substate = 2;
				}
			} else {
				//Stop radio chatter sound
				g_sound_manager.stop_sound(219);
                                
				//Turn off Radar_control_panel LEDs
				g_shifter_quad.setPin(27, LOW);
				g_shifter_quad.write();
                                
				//Play single blip radar sound
				g_sound_manager.play_sound(217);
                                
				//Stop radar fading sequence and
				//Fade radar screen down to 10
				g_led_fade_manager.fade(5, 4000, 220, 40);
                                
				//Fade power crystals up to 200
				g_led_fade_manager.fade(12, 3000, 0, 200);
                                
				_increment_state();
				_substate = 0;
			}

			break;

		case 9:
			Serial.println("Success-Nine");

			if (_substate == 0){
				//Solenoid moves brass stairs in                          
				digitalWrite(SOLENOID_3_PIN, LOW);

				//Cage moves down slowly. Servos 9 and 13 move in unison to lower the cage 
				g_servo_manager.move_servo(9, SERVO_9_POSITION_A, SERVO_9_SPEED);
				g_servo_manager.move_servo(13, SERVO_13_POSITION_A, SERVO_13_SPEED);

				//cage moving sound
				g_sound_manager.play_sound(215);

				//Red Pulley LED - pin 23 (quad shifter) Off while cage is moving
				g_shifter_quad.setPin(23, LOW);
				g_shifter_quad.write();

				//Green Pulley LED - pin 24 (quad shifter) ON while cage is moving
				g_shifter_quad.setPin(24, HIGH);
				g_shifter_quad.write();
                                
				_substate = 1;
			} 
				else if (_substate == 1){
				//wait for cage to lower to bottom (position A)
				if (
					g_servo_manager.is_servo_in_position(9)&&
					g_servo_manager.is_servo_in_position(13)
				){
					_substate = 2;
				}
			} else {
  
  			//Red Pulley LED - pin 23 (quad shifter) ON if cage is not moving
			g_shifter_quad.setPin(23, HIGH);
			g_shifter_quad.write();

			//Green Pulley LED - pin 24 (quad shifter) off if cage is not moving
			g_shifter_quad.setPin(24, LOW);
			g_shifter_quad.write();
  
			//Stop the ambient echos
			g_sound_manager.stop_sound(221);

			//Stop the cage moving sound
			g_sound_manager.stop_sound(215);

			//Fade power crystal led down
			g_led_fade_manager.fade(12, 4000, 200, 5);

			_increment_state();
			_substate = 0;
			}

			break;

		case 10:
			Serial.println("Success-Ten");
			//Turn the painting light off
			g_shifter_quad.setPin(30, LOW);
			g_shifter_quad.write();

			//Solenoid moves brass handrail in                          
			digitalWrite(SOLENOID_4_PIN, LOW);

			// Keypad yellow leds fade up
			g_led_fade_manager.fade(1, 5000, 0, 30);

			//Brick warning finger flashes, blink warning sound triggers on high
			g_led_flash_manager.start_flasher_with_sound(4, 2, 206);

			_increment_state();
			_substate = 0;      
			break;


		case 11:      
			Serial.println("Success-Eleven");
			if (_substate == 0){
         
				// Keypad door right A Servo 1 moves to closed position (Position A)
				g_servo_manager.move_servo(1, SERVO_1_POSITION_A, SERVO_1_SPEED);

				// Keypad door right B Servo 2 moves to closed position (Position A)
				g_servo_manager.move_servo(2, SERVO_2_POSITION_A, SERVO_2_SPEED);

				// Keypad door left A Servo 3 moves to closed position (Position A)
				g_servo_manager.move_servo(3, SERVO_3_POSITION_A, SERVO_3_SPEED);

				// Keypad door left B Servo 4 moves to closed position (Position A)
				g_servo_manager.move_servo(4, SERVO_4_POSITION_A, SERVO_4_SPEED);

				// Miniature Keypad door servo moves to closed position (position A)
				g_servo_manager.move_servo(16, SERVO_16_POSITION_A, SERVO_16_SPEED);

				//Play Keypad door sound
				g_sound_manager.play_sound(202);

				_substate = 1;
			} else if (_substate == 1){
				if (
					g_servo_manager.is_servo_in_position(1)&&
					g_servo_manager.is_servo_in_position(2)&&
					g_servo_manager.is_servo_in_position(3)&&
					g_servo_manager.is_servo_in_position(4)		
				){
					_substate = 2;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;

		case 12:
			Serial.println("Success-Twelve");
			
			if (_substate == 0){
				//Stop power crystals ambient hum
				g_sound_manager.stop_sound(214);
  
				//Turn off brick finger warning led
				g_led_flash_manager.stop_flasher(4);
				
				//Warning Bricks rotation Servo 8 rotates to closed position
				g_servo_manager.move_servo(8, SERVO_8_POSITION_A, SERVO_8_SPEED);

				//move clock servo to position A to prep for sweeping during pause state
				g_servo_manager.move_servo(14, SERVO_14_POSITION_A, SERVO_14_SPEED);

				//Magpanel LEDs turn OFF			
				g_shifter_quad.setPin(29,LOW);
				g_shifter_quad.write();

				//Clock illumination LEDs fade up
				g_led_fade_manager.fade(7, 2000, 0, 70);

				_substate = 1;
			} else if (_substate == 1){
				// wait until Warning Bricks rotation servo 8 stops moving
				if (g_servo_manager.is_servo_in_position(8)){
					_substate = 2;
				}
			} else {
				_increment_state();
				_substate = 0;
			}
			break;

		case 13:
			Serial.println("Success-Thirteen");
			if (_substate == 0){
  				//Solenoid moves Warning_Bricks_Mini in
				digitalWrite (SOLENOID_2_PIN, LOW);
				
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
									//Green LEDs inside_clock turn off
									g_shifter_quad.setPin(25,LOW);
									g_shifter_quad.write();
  
  									//Turn on all the clock number LEDs with a short delay for shifter to preform switching
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
									delay(50);
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
