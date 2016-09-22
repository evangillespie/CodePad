#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"
#include "Pins.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the puse state. called ever iteration of the main loop
*/
void PauseState::update() {
	// everything is still working
	if (_system_state == 1){
		_update_clock_sweep();
		_update_tuba_sounds();

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

	//Turn servos off, all servos should be in final position
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
	int tuba_sounds[] = {1, 2, 3, 4, 5, 6};

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
			return 8386;
		case 2:
			return 5513;
		case 3:
			return 3425;
		case 4:
			return 4249;
		default:
			return 5000;
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

	_clock_sweep_dir = 0;
	_next_clock_time = millis();
	_tuba_sound_count = 0;
	_next_tuba_sound_time = _get_next_tuba_sound_time();
	_tuba_sound_wait_time = 0;
	_next_update_time = 0;
	_system_state = 1;
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}
