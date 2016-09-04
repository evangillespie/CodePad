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
		2000,	// pause before the 1st state
		3000,	// pause before the 2nd state
		5000,	// pause before the 3rd state
		2000, 	// pause before the 4th state
                5000,   // pause before the 5th state
		random(15000,40000), 	// pause before the 6th state
                random(15000,40000), 	// pause before the 7th state
                random(8000,15000), 	// pause before the 8th state
                15000, 	// pause before the 9th state
                5000,   // pause before the 10th state
                4000,   // pause before the 11th state
                4000,   // pause before the 12th state
                4000,   // pause before the 13th state
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

			// clear bargraph
			Keypad::clear_bargraph();

			_increment_state();
			break;
		case 1:
			Serial.println("Success- One");
			g_sound_manager.play_sound(random(312,319));   //play one of the correct code tuba sounds at random
                        
                        pinMode(TUBAMAN,OUTPUT);
                        digitalWrite(TUBAMAN,HIGH);   // TUBAMAN solenoid goes HIGH

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
                        digitalWrite(TUBAMAN,LOW);  // TUBAMAN solenoid goes LOW
                      
			// Turn off Bricklamp LED
			g_shifter_dual.setPin(8,LOW);
                        g_shifter_dual.write();

			//get pot value
			_substate = analogRead(ANALOG_INPUT_1) / 4; 

			//fade keypad green led down over 3s from pot position 0 - <keypadgreenpot>
			g_led_fade_manager.fade(11, 3000, _substate, 0); 

                        // Keypad buttons Blue LEDs fade down over 3s
			g_led_fade_manager.fade(2, 3000, 200, 0);

			//Power crystals fade up to brightness 200
                        g_led_fade_manager.fade(12, 5000, 0, 200);

			//trigger power crystal startup sound
			g_sound_manager.play_sound(213); 
			_substate = 0;
			_increment_state();
			break;
		case 3:
			Serial.println("Success- Three");
			if (_substate == 0){
                                //turn off the Keypad power MOSFET
			        digitalWrite(LED_10_PIN,LOW);
  
			        g_sound_manager.play_sound(214);  //trigger power crystal ambient hum sound

				//Timer LEDs turned OFF
                                g_shifter_dual.setPin(10,LOW);
                                g_shifter_dual.write();

				// Timer Panel Servo 6 moves to the left- position A
			        //servo index, final pos, speed
			        g_servo_manager.move_servo(6, SERVO_6_POSITION_A, SERVO_6_SPEED);
				
                                //Lightbrick Servo 5 moves to IN position (position A)
			        //servo index, final pos, speed
			        g_servo_manager.move_servo(5, SERVO_5_POSITION_A, SERVO_5_SPEED);

				//Cage lifts up slowly. Servos 9 and 13 move in unison to lift the cage 
				//servo index, final pos, speed
				g_servo_manager.move_servo(9, SERVO_9_POSITION_B, SERVO_9_SPEED);
                                g_servo_manager.move_servo(13, SERVO_13_POSITION_B, SERVO_13_SPEED);
                                g_sound_manager.play_sound(215); //cage moving sound
                                
                                // TODO:  How do we do this?
                                //When servo 9 is at position 600, MAG_PANEL_LED goes LOW
                                //g_shifter_quad.setPin(29,LOW);
                                //g_shifter_quad.write();
                                
                                //When servo 9 is at position 500, HANDRAIL solenoid goes HIGH
                                //digitalWrite(HANDRAIL,HIGH)
                                
                                //When servo 9 is at position 400, STAIRS solenoid goes HIGH
                                //digitalWrite(STAIRS,HIGH)
                                

				_substate = 1;
			} 
                                else if (_substate == 1){
				//wait for cage to lift to top (position B)
				if (
					g_servo_manager.read_servo(9) == SERVO_9_POSITION_B //&&
					//g_servo_manager.read_servo(13) == SERVO_13_POSITION_B
				){
					_substate = 2;
				}
			} else {
                                g_sound_manager.stop_sound(215); //stop the cage moving sound
				// fade power crystal led down
				g_led_fade_manager.fade(12, 2000, 200, 5);
				_increment_state();
				_substate = 0;
			}

			break;
		case 4:
			Serial.println("Success- Four");
                	if (_substate == 0){
                                //Cage opens up. Servos 10,11,12 move to position B in unison
                                
                                //Cage top moves to open position (position B)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(10, SERVO_10_POSITION_B, SERVO_10_SPEED);

                                //Cage left moves to open position (position B)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(11, SERVO_11_POSITION_B, SERVO_11_SPEED);

                                //Cage right moves to open position (position B)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(12, SERVO_12_POSITION_B, SERVO_12_SPEED);

                                g_sound_manager.play_sound(216); //cage opening sound

                                _substate = 1;
                                } 
                                else if (_substate == 1){
				//wait for cage to open up to position B
				if (
					//g_servo_manager.read_servo(10) == SERVO_10_POSITION_B &&
                                        //g_servo_manager.read_servo(11) == SERVO_11_POSITION_B &&
					g_servo_manager.read_servo(12) == SERVO_12_POSITION_B
				){
					_substate = 2;
                                      
				}
			} else {
                                g_sound_manager.stop_sound(215); //stop the cage moving sound
				g_sound_manager.stop_sound(214); //stop power crystals ambient hum
				_increment_state();
				_substate = 0;
			}

			break;

                case 5:
                     Serial.println("Success- Five");
                        //turn the radar control panel LEDs on 
                        g_shifter_quad.setPin(27, HIGH);
                        g_shifter_quad.write();
                        
                        //radar screen begins fading sequence radar (blips)
                        g_led_fade_manager.fade(5, 3000, 10, 200);
                        //insert fading sequece here that looks like radar blips
                        
                        g_sound_manager.play_sound(218); //   ambient radar sound
                        g_sound_manager.play_sound(219); //   radio chatter sound.  very long wav-- turn off later
                        _increment_state();
			break;
                    
                case 6:
                      Serial.println("Success-Six");
                      
                        //Teleportation prep
                        //turn the painting light on
                        g_shifter_quad.setPin(30, HIGH);
                        g_shifter_quad.write();
                        
                        g_sound_manager.play_sound(222);  //  painting light click sound
                        g_sound_manager.play_sound(223);  //  time travel flicking sound
                        g_sound_manager.play_sound(221);  //  ambient echo sounds. This wav is long-- turn it off later
                        _increment_state();
			break;
                        
                case 7:
                       Serial.println("Success-Seven");
                      
                      //jumping through portal
                      g_sound_manager.play_sound(220); // teleprotation sound
                      g_sound_manager.play_sound(224); //portal hum sound
                      _increment_state();
			break;

                case 8:
                      Serial.println("Success-Eight");
                      //stop the sounds
                      g_sound_manager.stop_sound(221);  // ambient echos
                      //I'd like to use the trackFade funcion of the sound library.   Can you enable the track fade from the wavetrigger.h?
                      //wTrig.trackFade(221, -50, 5000, 1);
                      
                      if (_substate == 0){
                                //Cage closes up. Servos 10,11,12 move to position A in unison
                                
                                //Cage top moves to open position (position A)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(10, SERVO_10_POSITION_A, SERVO_10_SPEED);

                                //Cage left moves to open position (position A)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(11, SERVO_11_POSITION_A, SERVO_11_SPEED);

                                //Cage right moves to open position (position A)
                                //servo index, final pos, speed
				g_servo_manager.move_servo(12, SERVO_12_POSITION_A, SERVO_12_SPEED);

                                g_sound_manager.play_sound(216); //cage opening sound

                                _substate = 1;
                                } 
                                else if (_substate == 1){
				//wait for cage to close to position A
				if (
					//g_servo_manager.read_servo(10) == SERVO_10_POSITION_A &&
                                        //g_servo_manager.read_servo(11) == SERVO_11_POSITION_A &&
					g_servo_manager.read_servo(12) == SERVO_12_POSITION_A
				){
					_substate = 2;
				}
			} else {
                                g_sound_manager.stop_sound(219);  //radio chatter sound
                                
                                //Turn Radar_control_panel off
                                g_shifter_quad.setPin(27, LOW);
                                g_shifter_quad.write();
                                
                                g_sound_manager.play_sound(217); // single blip radar sound
                                
                                //stop radar fading sequence and
                                //fade radar screen down to 10
                                g_led_fade_manager.fade(5, 6000, 200, 10);
                                
                                
                                //Fade power crystals up to 200
                                g_led_fade_manager.fade(12, 3000, 0, 200);
                                g_sound_manager.play_sound(214); //play power crystals ambient hum
				_increment_state();
				_substate = 0;
			}

			break;

                case 9:
			        Serial.println("Success-Nine");
			        if (_substate == 0){

				//Cage moves down slowly. Servos 9 and 13 move in unison to lower the cage 
				//servo index, final pos, speed
				g_servo_manager.move_servo(9, SERVO_9_POSITION_A, SERVO_9_SPEED);
                                g_servo_manager.move_servo(13, SERVO_13_POSITION_A, SERVO_13_SPEED);
                                g_sound_manager.play_sound(215); //cage moving sound
                                
                                // TODO:  How do we do this?
                                //When servo 9 is at position 750, MAG_PANEL_LED goes HIGH
                                //g_shifter_quad.setPin(29,HIGH);
                                //g_shifter_quad.write();
                                
                                //When servo 9 is at position 500, STAIRS solenoid goes LOW
                                //digitalWrite(STAIRS,LOW)
                                
                                //When servo 9 is at position 600, HANDRAIL solenoid goes HIGH
                                //digitalWrite(HANDRAIL,HIGH)
                                
                                //When servo 9 is at position 200, painting LED goes LOW
                                //g_shifter_quad.setPin(30,LOW);
                                //g_shifter_quad.write();
                                
				_substate = 1;
			} 
                                else if (_substate == 1){
				//wait for cage to lower to bottom (position A)
				if (
					g_servo_manager.read_servo(9) == SERVO_9_POSITION_A //&&
					//g_servo_manager.read_servo(13) == SERVO_13_POSITION_A
				){
					_substate = 2;
				}
			} else {
				g_sound_manager.stop_sound(215); //stop the cage moving sound

				// fade power crystal led down
				g_led_fade_manager.fade(12, 4000, 200, 5);
                                g_sound_manager.stop_sound(214); //stop power crystals ambient hum
				_increment_state();
				_substate = 0;
			}

			break;

                case 10:
			Serial.println("Success-Ten");

			// Keypad yellow leds fade up over Xs
			g_led_fade_manager.fade(1, 5000, 0, 30);

			//Brick warning finger flashes, blick warning sound triggers on high
			g_led_flash_manager.start_flasher_with_sound(4, 2, 206);

			_increment_state();
			_substate = 0;      
			break;
  
                case 11:      
                             Serial.println("Success-Eleven");

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

				// Keypad door sound
				g_sound_manager.play_sound(202);

				_substate = 1;
			} else if (_substate == 1){
				if (
					//read that one of the door servos is at the closed position
					g_servo_manager.read_servo(4) == SERVO_4_POSITION_A			
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
				//turn off brick finger warning led
				g_led_flash_manager.stop_flasher(4);
				
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

                case 13:
			if (_substate == 0){
				Serial.println("Success-Thirteen");
				
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
                                                                        //Evan, can you add the code to turn Nixies and Matrix off, pls?
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
