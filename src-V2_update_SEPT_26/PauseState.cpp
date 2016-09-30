#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"
#include "Pins.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the pause state. called ever iteration of the main loop
*/
void PauseState::update() {
	// everything is still working
	if (_system_state == 1){
		_update_clock_sweep();
		_update_tuba_sounds();
		_update_landscape_tube();
		_update_pizza_oven();

		if (_is_pir_triggered() == false){
			_system_state = 0;
			_turn_system_off();
			_next_update_time = 0;
		}
	} else {
		if (_is_pir_triggered() == true){
			if (_next_update_time == 0){
				_next_update_time = millis() + random(5000, 15000);
			} else {
				if (millis() >= _next_update_time){
					_turn_system_on();
					_next_update_time = 0;
					_system_state = 1;
				}
			}
		}
	}
}


/*
	turn everything off when the PIR turns off
*/
void PauseState::_turn_system_off(){
	Serial.println("everything turns off!");

	//Turn LEDs off
	digitalWrite(LED_1_PIN, LOW);
	digitalWrite(LED_2_PIN, LOW);
	digitalWrite(LED_3_PIN, LOW);
	digitalWrite(LED_4_PIN, LOW);
	digitalWrite(LED_5_PIN, LOW);
	digitalWrite(LED_6_PIN, LOW);
	digitalWrite(LED_7_PIN, LOW);
	digitalWrite(LED_8_PIN, LOW);
	digitalWrite(LED_9_PIN, LOW);
	digitalWrite(LED_10_PIN, LOW);
	digitalWrite(LED_11_PIN, LOW);
	digitalWrite(LED_12_PIN, LOW);

	digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);
	digitalWrite(LANDSCAPE_TUBE_MOTOR_PIN, LOW);
	
	//Always ON panel 3 LEDs
	digitalWrite(16, LOW);
	//Always ON 12V strips in panel 3
	digitalWrite(17, LOW);

	//Red Pulley LED - pin 23 (quad shifter)
	g_shifter_quad.setPin(23, LOW);

	//Always ON panel 1 LEDs – pin 26 (quad shifter)
	g_shifter_quad.setPin(26, LOW);

	//Pizza oven exterior LEDs - pin 28 (quad shifter)
	g_shifter_quad.setPin(28, LOW);

	//Clock number LEDs 
	g_shifter_quad.setPin(13,LOW);  //clock number LED 0
	g_shifter_quad.setPin(14,LOW);  //clock number LED 1
	g_shifter_quad.setPin(15,LOW);  //clock number LED 2
	g_shifter_quad.setPin(16,LOW);  //clock number LED 3
	g_shifter_quad.setPin(17,LOW);  //clock number LED 4
	g_shifter_quad.setPin(18,LOW);  //clock number LED 5
	g_shifter_quad.setPin(19,LOW);  //clock number LED 6
	g_shifter_quad.setPin(20,LOW);  //clock number LED 7
	g_shifter_quad.setPin(21,LOW);  //clock number LED 8
	g_shifter_quad.setPin(22,LOW);  //clock number LED 9

	g_shifter_quad.write();

	Display::turn_neopixles_on_or_off(false);

}


/*
	turn everything on when the PIR turns on
*/
void PauseState::_turn_system_on(){
	Serial.println("everything turns on!");


	/************************/
	//**NOTE** - This is a copy of the "StateMachine::_initialize_system_leds" in Statmachine.cpp if anything is edited here it should be edited there too
	/************************/
	
	// Set ALways ON LED on panel 3 as an output
	pinMode(16, OUTPUT);

	//Always ON panel 3 LEDs - pin 16 (MEGA)
	digitalWrite(16, HIGH);	

	// Set 12V LED strips panel 3 as an output
	pinMode(17, OUTPUT);

	//12V LED strips panel 3 - pin 17 (MEGA)
	digitalWrite(17, HIGH);

	//Red Pulley LED - pin 23 (quad shifter)
	g_shifter_quad.setPin(23, HIGH);

	//Always ON panel 1 LEDs – pin 26 (quad shifter)
	g_shifter_quad.setPin(26, HIGH);

	//Pizza oven exterior LEDs - pin 28 (quad shifter)
	g_shifter_quad.setPin(28, HIGH);

	//Clock number LEDs 
	g_shifter_quad.setPin(13,HIGH);  //clock number LED 0
	g_shifter_quad.setPin(14,HIGH);  //clock number LED 1
	g_shifter_quad.setPin(15,HIGH);  //clock number LED 2
	g_shifter_quad.setPin(16,HIGH);  //clock number LED 3
	g_shifter_quad.setPin(17,HIGH);  //clock number LED 4
	g_shifter_quad.setPin(18,HIGH);  //clock number LED 5
	g_shifter_quad.setPin(19,HIGH);  //clock number LED 6
	g_shifter_quad.setPin(20,HIGH);  //clock number LED 7
	g_shifter_quad.setPin(21,HIGH);  //clock number LED 8
	g_shifter_quad.setPin(22,HIGH);  //clock number LED 9
									
	//Clock illumination LED - LED_7_PIN brightness of 100	
	g_led_fade_manager.fade(7, 100, 0, 70);

	//Radar Screen - LED_5_PIN brightness 50 // This analog control of LED_5_PIN glitches out shiftregister.  ?
	//g_led_fade_manager.fade(5, 100, 0, 50);

	//Power crystals - LED_12_PIN brightness 10 
	g_led_fade_manager.fade(12, 100, 0, 10);

	//Yellow LED inside Keyapd - LED_2_PIN brightness 50 
	g_led_fade_manager.fade(1, 100, 0, 50); 

	//Pizza coals inside pizza oven - LED_6_PIN brightness 100 
	g_led_fade_manager.fade(6, 100, 0, 80);

	g_shifter_quad.write();

	Display::turn_neopixles_on_or_off(true);
}


/*
	sweep the clock back and forth.
*/
void PauseState::_update_clock_sweep(){
	if (millis() >= _next_clock_time){
		if (_clock_sweep_dir == 0){
			g_servo_manager.move_servo(14, SERVO_14_POSITION_B, SERVO_14_SPEED);
			_clock_sweep_dir = 1;
		} else {
			g_servo_manager.move_servo(14, SERVO_14_POSITION_A, SERVO_14_SPEED);
			_clock_sweep_dir = 0;
		}
		_next_clock_time = millis() + CLOCK_SWEEP_TIME_DELAY;
	}
}


/*
	play a bunch of tuba sounds at random and move a solenoid
*/
void PauseState::_update_tuba_sounds(){
	if (millis() > _next_tuba_sound_time){
		if (_tuba_sound_wait_time == 0){
			//trigger a sound and hit the solenoid
			digitalWrite(TUBA_PLAYER_SOLENOID_PIN, HIGH);
			int sound_index = _get_random_tuba_sound_index();
			g_sound_manager.play_sound(sound_index);
			
			//get a wait time
			_tuba_sound_wait_time = millis() + _get_tuba_sound_length(sound_index);
			if (++_tuba_sound_count > TUBA_SOUND_SOUNDS_IN_SET){
				_tuba_sound_count = 0;
			}
		} else if (millis() >= _tuba_sound_wait_time){
			digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);
			_tuba_sound_wait_time = 0;
			_next_tuba_sound_time = _get_next_tuba_sound_time();
		}
	}
}


/*
	return the time of the next tuba sound
	it might be a very soon if the sounds are playing in sequence
	or it might be long if the sounds are done for now

	:return: time of the next tuba sound
*/
unsigned long PauseState::_get_next_tuba_sound_time(){
	unsigned long additional_time;
	if (_tuba_sound_count < TUBA_SOUND_SOUNDS_IN_SET){
		additional_time = random(TUBA_SOUND_SOUND_TIME_MINIMUM, TUBA_SOUND_SOUND_TIME_MAXIMUM + 1);
	} else {
		additional_time = random(TUBA_SOUND_SET_TIME_MINIMUM, TUBA_SOUND_SET_TIME_MAXIMUM + 1);
	}

	return millis() + additional_time;
}


/*
	pick a random sound from the available tuba sounds

	:return: sound index that can be sent to the sound manager
*/
int PauseState::_get_random_tuba_sound_index(){
	// @CHRIS: SET THIS ARRAY TO CONTAIN THE SOUND INDECIES OF ALL TUBA SOUNDS
	int tuba_sounds[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
				21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
				41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
				61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
				81, 82, 83, 84, 85, 86, 87, 88, 89 ,90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
				101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
				121, 122, 123, 124, 125, 126, 127, 128, 129, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140};

	int pick = random(0, sizeof(tuba_sounds)/sizeof(int));
	return tuba_sounds[pick];
}


/*
	get a the time it takes for a sound to play

	:param sound_index: index for the sound in question.
		this index is an index to be used by the sound manager

	:return: time (in ms) it takes for that sound to play.
*/
unsigned long PauseState::_get_tuba_sound_length(int sound_index){
	// @CHRIS: PUT THE REAL SOUND LENGTHS IN HERE
	switch (sound_index){
		case 1:
			return 7200;
		case 2:
			return 2300;
		case 3:
			return 2300;
		case 4:
			return 1800;
		case 5:
			return 1800;
		case 6:
			return 1700;
		case 7:
			return 1800;
		case 8:
			return 1800;
		case 9:
			return 2400;
		case 10:
			return 2300;
		case 11:
			return 2500;
		case 12:
			return 1700;
		case 13:
			return 1900;
		case 14:
			return 1800;
		case 15:
			return 2000;
		case 16:
			return 1700;
		case 17:
			return 1400;
		case 18:
			return 1200;
		case 19:
			return 1300;
		case 20:
			return 1900;
		case 21:
			return 1800;
		case 22:
			return 1500;
		case 23:
			return 2100;
		case 24:
			return 2000;
		case 25:
			return 1300;
		case 26:
			return 1800;
		case 27:
			return 1600;
		case 28:
			return 1700;
		case 29:
			return 1600;
		case 30:
			return 1800;
		case 31:
			return 1800;
		case 32:
			return 1800;
		case 33:
			return 1800;
		case 34:
			return 2000;
		case 35:
			return 2100;
		case 36:
			return 1800;
		case 37:
			return 2000;
		case 38:
			return 2200;
		case 39:
			return 2400;
		case 40:
			return 2400;
		case 41:
			return 2400;
		case 42:
			return 1900;
		case 43:
			return 2700;
		case 44:
			return 2400;
		case 45:
			return 3000;
		case 46:
			return 3000;
		case 47:
			return 2600;
		case 48:
			return 3300;
		case 49:
			return 3600;
		case 50:
			return 3600;
		case 51:
			return 3300;
		case 52:
			return 1900;
		case 53:
			return 1700;
		case 54:
			return 1800;
		case 55:
			return 1900;
		case 56:
			return 1500;
		case 57:
			return 1600;
		case 58:
			return 1800;
		case 59:
			return 1900;
		case 60:
			return 2000;
		case 61:
			return 2000;
		case 62:
			return 1500;
		case 63:
			return 1900;
		case 64:
			return 1800;
		case 65:
			return 2000;
		case 66:
			return 1900;
		case 67:
			return 2100;
		case 68:
			return 1900;
		case 69:
			return 1700;
		case 70:
			return 1900;
		case 71:
			return 2000;
		case 72:
			return 2100;
		case 73:
			return 2400;
		case 74:
			return 2300;
		case 75:
			return 2300;
		case 76:
			return 2100;
		case 77:
			return 2200;
		case 78:
			return 2300;
		case 79:
			return 2300;
		case 80:
			return 2100;
		case 81:
			return 2400;
		case 82:
			return 1400;
		case 83:
			return 2100;
		case 84:
			return 2400;
		case 85:
			return 2600;
		case 86:
			return 3000;
		case 87:
			return 5900;
		case 88:
			return 1800;
		case 89:
			return 2200;
		case 90:
			return 4800;
		case 91:
			return 5900;
		case 92:
			return 3000;
		case 93:
			return 3000;
		case 94:
			return 4000;
		case 95:
			return 2600;
		case 96:
			return 5300;
		case 97:
			return 3300;
		case 98:
			return 4000;
		case 99:
			return 4100;
		case 100:
			return 2400;
		case 101:
			return 3000;
		case 102:
			return 3300;
		case 103:
			return 3600;
		case 104:
			return 2700;
		case 105:
			return 2300;
		case 106:
			return 2000;
		case 107:
			return 3800;
		case 108:
			return 2100;
		case 109:
			return 1900;
		case 110:
			return 1800;
		case 111:
			return 2300;
		case 112:
			return 4300;
		case 113:
			return 2100;
		case 114:
			return 3000;
		case 115:
			return 2400;
		case 116:
			return 3700;
		case 117:
			return 3100;
		case 118:
			return 2800;
		case 119:
			return 2000;
		case 120:
			return 2700;
		case 121:
			return 2800;
		case 122:
			return 3700;
		case 123:
			return 2400;
		case 124:
			return 4800;
		case 125:
			return 5600;
		case 126:
			return 1800;
		case 127:
			return 3200;
		case 128:
			return 3800;
		case 129:
			return 11300;
		case 131:
			return 7600;
		case 132:
			return 2600;
		case 133:
			return 3500;
		case 134:
			return 2600;
		case 135:
			return 3300;
		case 136:
			return 4200;
		case 137:
			return 3600;
		case 138:
			return 4700;
		case 139:
			return 4800;
		case 140:
			return 4900;
		case 141:
			return 4200;
		case 142:
			return 4700;
		case 143:
			return 5200;
		case 144:
			return 4500;
		case 145:
			return 3200;
		case 146:
			return 3400;
		//default: //?
			//return 5000;   //?
	}
}

/*
	active or deactivate the landscape tube motor at the appropriate time
*/
void PauseState::_update_landscape_tube(){
	if (_next_landscape_tube_time == 0){
		_next_landscape_tube_time = millis() + random(
			LANDSCAPE_TUBE_MIN_TIME_BEFORE_ACTIVATION,
			LANDSCAPE_TUBE_MAX_TIME_BEFORE_ACTIVATION + 1
		);
	} else if (millis() >= _next_landscape_tube_time){
		if (_landscape_tube_active == false){
			// turn it on and set a time for it to turn off
			_next_landscape_tube_time = millis() + random(
				LANDSCAPE_TUBE_MIN_ACTIVE_TIME,
				LANDSCAPE_TUBE_MAX_ACTIVE_TIME + 1
			);
			digitalWrite(LANDSCAPE_TUBE_MOTOR_PIN, HIGH);
			_landscape_tube_active = true;
		} else {
			_next_landscape_tube_time = millis() + random(
				LANDSCAPE_TUBE_MIN_TIME_BEFORE_ACTIVATION,
				LANDSCAPE_TUBE_MAX_TIME_BEFORE_ACTIVATION + 1
			);
			digitalWrite(LANDSCAPE_TUBE_MOTOR_PIN, LOW);
			_landscape_tube_active = false;
		}
	}
}


/*
	trigger the pizza oven sequence at random times
*/
void PauseState::_update_pizza_oven(){
	if (millis() >= _next_pizza_oven_time){
		Display::activate_pizza_oven_sequence();
		_next_pizza_oven_time = millis() + random(PIZZA_OVEN_PAUSE_TIME_MIN, PIZZA_OVEN_PAUSE_TIME_MAX);
	}
}



/*
	return true if this state is done and we should move on
*/
bool PauseState::is_complete() {
	if (millis() >= _complete_time && _is_pir_triggered() == true){
		if (_system_state == 0){
			_system_state = 1;
			_turn_system_on();
		}
		return true;
	}
	return false;
}


/*
	return true if the PIR sensor has been triggered
*/
bool PauseState::_is_pir_triggered(){
	return digitalRead(PIR_INPUT);
}


/*
	start the pause
*/
void PauseState::begin() {
	
	digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);
	digitalWrite(LANDSCAPE_TUBE_MOTOR_PIN, LOW);

	_clock_sweep_dir = 0;
	_next_clock_time = millis();
	_tuba_sound_count = 0;
	_next_tuba_sound_time = _get_next_tuba_sound_time();
	_tuba_sound_wait_time = 0;
	_landscape_tube_active = false;
	_next_landscape_tube_time = 0;
	_next_pizza_oven_time = millis() + random(PIZZA_OVEN_PAUSE_TIME_MIN, PIZZA_OVEN_PAUSE_TIME_MAX);
	_next_update_time = 0;
	_system_state = 1;
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}

/*
	turn everything necessary off at the end of the pause state
*/
void PauseState::end(){
	digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);
	digitalWrite(LANDSCAPE_TUBE_MOTOR_PIN, LOW);
}
