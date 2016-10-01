#include "Arduino.h"
#include "Keypad.h"
#include "Config.h"
#include "Pins.h"


int incoming_byte;
int incoming_int;
int _queued_num;
bool _is_clr_flashing;
unsigned long _last_clr_change;
bool _is_ok_flashing;
unsigned long _last_ok_change;
unsigned long _bargraph_time_step;
int _bargraph_num_lights;	//number of bargraph elements that are currently lit up
int _prev_bargraph_num_lights;

unsigned long keypad_timeout = (unsigned long)KEYPAD_TIMEOUT_SECS * (unsigned long)1000;

Adafruit_24bargraph bar = Adafruit_24bargraph();

/*
	Constructor. Generic. Boring
*/
Keypad::Keypad() {
	pinMode(KEYPAD_NUMBER_1, INPUT);
	pinMode(KEYPAD_NUMBER_2, INPUT);
	pinMode(KEYPAD_NUMBER_3, INPUT);
	pinMode(KEYPAD_NUMBER_4, INPUT);
	pinMode(KEYPAD_NUMBER_5, INPUT);
	pinMode(KEYPAD_NUMBER_6, INPUT);
	pinMode(KEYPAD_NUMBER_7, INPUT);
	pinMode(KEYPAD_NUMBER_8, INPUT);
	pinMode(KEYPAD_NUMBER_9, INPUT);
	pinMode(KEYPAD_NUMBER_0, INPUT);
	pinMode(KEYPAD_NUMBER_CLR, INPUT);
	pinMode(KEYPAD_NUMBER_OK, INPUT);
	pinMode(KEYPAD_NUMBERS_LED, OUTPUT);
	pinMode(KEYPAD_NUMBER_CLR_LED, OUTPUT);
	pinMode(KEYPAD_NUMBER_OK_LED, OUTPUT);

	pinMode(KEYPAD_DISPLAY_WRITE_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_A1_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_A2_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D0_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D1_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D2_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D3_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D4_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D5_PIN, OUTPUT);
	pinMode(KEYPAD_DISPLAY_D6_PIN, OUTPUT);

	digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
	digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);

	_bargraph_time_step = keypad_timeout / 24;
	_bargraph_num_lights = 0;
	_prev_bargraph_num_lights = 0;

	reset();
}


void Keypad::init() {
	bar.begin(0x70);
	clear_bargraph();
	_update_display();
	clear_4_digit();
}

/*
	check the keypad status
	called every main loop
*/
void Keypad::update(Passcode passcode) {
	_update_status(passcode);
	_is_key_pressed(passcode);
	_update_btns_flashing();
}


/*
	save that a key was pressed on the keypad
*/
void Keypad::_is_key_pressed(Passcode passcode){
	if (digitalRead(KEYPAD_NUMBER_1)){
		_queued_num = 1;
	}
	else if (digitalRead(KEYPAD_NUMBER_2)){
		_queued_num = 2;
	}
	else if (digitalRead(KEYPAD_NUMBER_3)){
		_queued_num = 3;
	}
	else if (digitalRead(KEYPAD_NUMBER_4)){
		_queued_num = 4;
	}
	else if (digitalRead(KEYPAD_NUMBER_5)){
		_queued_num = 5;
	}
	else if (digitalRead(KEYPAD_NUMBER_6)){
		_queued_num = 6;
	}
	else if (digitalRead(KEYPAD_NUMBER_7)){
		_queued_num = 7;
	}
	 else if (digitalRead(KEYPAD_NUMBER_8)){
	 	_queued_num = 8;
	}
	else if (digitalRead(KEYPAD_NUMBER_9)){
		_queued_num = 9;
	}
	else if (digitalRead(KEYPAD_NUMBER_0)){
		_queued_num = 0;
	}
	else if (digitalRead(KEYPAD_NUMBER_CLR)){
		_queued_num = 11;
	}
	else if (digitalRead(KEYPAD_NUMBER_OK)){
		_queued_num = 12;
	} else {
		_register_queued_key(passcode);
	}
}


/*
	register the last pressed key in now that all are released
*/
void Keypad::_register_queued_key(Passcode passcode){
	if (_queued_num >= 0){
		if (_queued_num < 10){
			_add_digit_to_received(_queued_num);
		} else {
			//clr button
			if (_queued_num == 11){
				//backspace
				for (int i = CODE_LENGTH-1; i >= 0; i--){
					if (_entered_values[i] >= 0){
						_entered_values[i] = -1;
						break;
					}
				}
			}
			// ok button
			if (_queued_num == 12){
				// if less than 4 digits are entered, ignore!
				if (_entered_values[0] != -1 &&
					_entered_values[1] != -1 &&
					_entered_values[2] != -1 &&
					_entered_values[3] != -1){
						int entered_code = get_entered_code();

						if (entered_code == passcode.get_passcode()){
								_status = 1;
						} else if (_is_code_special(entered_code)){
							_execute_special_code_sequence(entered_code);
						} else {
							_status = 1;
						}
				}
			}
		}
		_update_display();
		_update_right_wrong_leds(passcode);
		_play_right_wrong_sound(passcode, _queued_num);
		_queued_num = -1;
	}
}


/*
	update the 4 digit display based on what's in _entered_values
*/
void Keypad::_update_display(){
	for (int i=0; i<CODE_LENGTH; i++){
		_write_display_character(i, _entered_values[i]);
	}
}

/*
	write a single character to the 4-digit dot matrix display

	:param index: where do I write it? 0-3
	:param num: which number to I write? num=-1 to write blank
*/
void Keypad::_write_display_character(int index, int num){
	//only elements 0-3 change for numbers and 4 for blank
	int sequence[7] = {0, 0, 0, 0, 1, 1, 0}; // initialize to 0

	//turn write pin off while we get ready
	digitalWrite(KEYPAD_DISPLAY_WRITE_PIN, HIGH);

	//position
	index = 3 - index;	// index is reversed on the display
	digitalWrite(KEYPAD_DISPLAY_A1_PIN, index / 2);
	digitalWrite(KEYPAD_DISPLAY_A2_PIN, index % 2);
	
	//character
	if (num == -1){
		// show a dash when digit not entered yet
		sequence[0] = 1;
		sequence[1] = 0;
		sequence[2] = 1;
		sequence[3] = 1;
		sequence[4] = 0;
		sequence[5] = 1;
		sequence[6] = 0;
	} else {
  
		//convert num to binary
		for (int j=0; j < 4; j++){
			sequence[j] = num % 2;
			num = num / 2;
		}
	}

	digitalWrite(KEYPAD_DISPLAY_D0_PIN, sequence[0]);
	digitalWrite(KEYPAD_DISPLAY_D1_PIN, sequence[1]);
	digitalWrite(KEYPAD_DISPLAY_D2_PIN, sequence[2]);
	digitalWrite(KEYPAD_DISPLAY_D3_PIN, sequence[3]);
	digitalWrite(KEYPAD_DISPLAY_D4_PIN, sequence[4]);
	digitalWrite(KEYPAD_DISPLAY_D5_PIN, sequence[5]);
	digitalWrite(KEYPAD_DISPLAY_D6_PIN, sequence[6]);

	//write it
	digitalWrite(KEYPAD_DISPLAY_WRITE_PIN, LOW);
}


/*
	check conditions and update the status

	possible statuses are:
	0 - waiting for data
	1 - code entered and complete
	2 - timeout

	:param passcode: Passcode object to compare against
*/
void Keypad::_update_status(Passcode passcode) {

	//check if clr should flash
	_is_clr_flashing = false;
	for (int i=0; i<CODE_LENGTH; i++){
		if (_entered_values[i] >= 0){
			if (_entered_values[i] != passcode.get_digit(i)){
				_is_clr_flashing = true;
			}
		}
	}

	//check if ok should flash
	_is_ok_flashing = true;
	for (int i=0; i<CODE_LENGTH; i++){
		if (_entered_values[i] == -1){
			_is_ok_flashing = false;
		}
	}
	
	//update bar graph
	_bargraph_num_lights = 24 - (millis() - _init_time) / _bargraph_time_step;
	int led_color = 0;
	
	if (_bargraph_num_lights < 8){
		led_color = LED_RED;
	} else if (_bargraph_num_lights < 16){
		led_color = LED_YELLOW;
	} else {
		led_color = LED_GREEN;
	}

	//play sound for bargraph click down
	if (_prev_bargraph_num_lights != _bargraph_num_lights
			&& _prev_bargraph_num_lights != 0){
		if (led_color == LED_RED){
			g_sound_manager.play_sound(208);
		} else {
			g_sound_manager.play_sound(209);
		}
	}

	for(int b = 0; b < 24; b++){
		if (b < _bargraph_num_lights) {
			bar.setBar(b, led_color);
		} else {
			bar.setBar(b, LED_OFF);
		}
	}
	bar.writeDisplay();
	_prev_bargraph_num_lights = _bargraph_num_lights;


	//check for timeout
	if (millis() >= _init_time + keypad_timeout){
		_status = 2;
	}
}


/*
	flash the clr button if applicable
*/
void Keypad::_update_btns_flashing(){
	if (_is_clr_flashing){
		if (int(millis() - _last_clr_change) > KEYPAD_CLR_FLASH_PERIOD / 2){
			//toggle led status
			digitalWrite(KEYPAD_NUMBER_CLR_LED, !digitalRead(KEYPAD_NUMBER_CLR_LED));
			_last_clr_change = millis();
		}
	} else{
		digitalWrite(KEYPAD_NUMBER_CLR_LED, LOW);
	}

	if (_is_ok_flashing){
		if (int(millis() - _last_ok_change) > KEYPAD_OK_FLASH_PERIOD / 2){
			//toggle led status
			digitalWrite(KEYPAD_NUMBER_OK_LED, !digitalRead(KEYPAD_NUMBER_OK_LED));
			_last_ok_change = millis();
		}
	} else{
		digitalWrite(KEYPAD_NUMBER_OK_LED, LOW);
	}
}


/*
	return true if the keypad state is complete
*/
int Keypad::get_status() {
	return _status; 
}


/*
	return the entered code as an integer
*/
int Keypad::get_entered_code(){
	int val;
	float ret = 0.0;
	if (_entered_values[0] != -1 &&
			_entered_values[1] != -1 &&
			_entered_values[2] != -1 &&
			_entered_values[3] != -1){
		for (int i = 0; i < CODE_LENGTH; i++){
			if (_entered_values[i] >= 0){
				val = _entered_values[i];
			} else {
				val = 0;
			}

			ret = ret + (val * pow(10, 3-i));
		}
		return (int)lround(ret);
	} else {
		return -1;
	}
}


/*
	turn leds on or off if the user has entered correct or incorrect values

	:param passcode: Passcode object to compare against
*/
void Keypad::_update_right_wrong_leds(Passcode passcode){
	for (int i=0; i<CODE_LENGTH; i++){
		if (_entered_values[i] >= 0){
			if (_entered_values[i] == passcode.get_digit(i)){
				g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_CORRECT_OFFSET, HIGH);
				g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_INCORRECT_OFFSET, LOW);
			} else {
				g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_CORRECT_OFFSET, LOW);
				g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_INCORRECT_OFFSET, HIGH);
			}
		} else {
			g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_CORRECT_OFFSET, LOW);
			g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_INCORRECT_OFFSET, LOW);
		}
		g_shifter_dual.write();
	}
}


/*
	play a sound to indicate whether the correct digit was entered

	:param passcode: Passcode object to compare against
	:param entered_digit: the last entered digit
*/
void Keypad::_play_right_wrong_sound(Passcode passcode, int entered_digit){
	int pass_index = -1;

	if (entered_digit == 12){
		// OK
		return;
	} else if ( entered_digit == 11){
		g_sound_manager.play_sound(204);
		return;
	} else {
		for (int i=CODE_LENGTH-1; i>=0; i--){
			if (_entered_values[i] > -1){
				pass_index = i;
				break;
			}
		}
		if (pass_index > -1){
			g_sound_manager.play_sound(203);
			if (passcode.get_digit(pass_index) != entered_digit){
				g_sound_manager.play_sound(205);
			}
			return;
		}
	}
}


/*
	Turn off all right/wrong leds
*/
void Keypad::turn_off_right_wrong_leds(){
	for (int i=0; i<CODE_LENGTH; i++){
		g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_CORRECT_OFFSET, LOW);
		g_shifter_dual.setPin(i+KEYPAD_RIGHT_WRONG_LED_1_INCORRECT_OFFSET, LOW);
	}
	g_shifter_dual.write();
}


/*
	turn off all displays at the end of the keypad cycle
*/
void Keypad::turn_off_displays(){
	turn_off_right_wrong_leds();
	clear_bargraph();
	clear_4_digit();
}


/*
	reset all internal variables
*/
void Keypad::reset() {
	for (int i = 0; i < CODE_LENGTH; i++){
		_entered_values[i] = -1;
	}

	_update_display();

	_init_time = millis();
	_status = 0;
	_queued_num = -1;
	_is_clr_flashing = false;
	_last_clr_change = millis();
	_is_ok_flashing = false;
	_last_ok_change = millis();

	_bargraph_num_lights = 0;

	turn_off_right_wrong_leds();
}


/*
	store a digit received in the local array
	If too many digits get entered, we use the newest set

	:param inc_digit: the incoming digit
*/
void Keypad::_add_digit_to_received(int inc_digit) {
	for (int i = 0; i < CODE_LENGTH; i++){
		if (_entered_values[i] == -1){
			_entered_values[i] = inc_digit;
			break;
		}
	}
}


/*
	return true if a given code is one of the special codes

	:param entered_code: the code that's been entered, as a single int

	:return: true if the code is special, false otherwise
*/
bool Keypad::_is_code_special(int entered_code){
	// @CHRIS: CHANGE THIS LIST OF SPECIAL CODES
	int special_codes[] = {4827, 8110, 3827, 2864, 5348, 8433, 2317, 7467, 5792, 2438, 6161, 2654, 5340, 3427, 3714, 4953, 3687, 3555, 7552, 9893, 2038, 7112, 9661, 932, 4339, 8475, 5967};
	// ^^^

	for (int i = 0; i < sizeof(special_codes)/sizeof(int); i++){
		if (special_codes[i] == entered_code){
			return true;
		}
	}

	return false;
}


/*
	execute some particular code for each special code

	:param entered_code: the code that's been entered, as a single int
*/
void Keypad::_execute_special_code_sequence(int entered_code){
	// @CHRIS: PUT CODE HERE FOR EACH SPECIAL CODE. DONT FORGET THE 'break;'

	switch (entered_code){
		case 4827:
			//play horn
			g_sound_manager.play_sound(225);
			break;
		case 8110:
			//play wino aunt
			g_sound_manager.play_sound(256);
			break;
		case 3827:
			//play burrito splat
			g_sound_manager.play_sound(258);
			break;
		case 2864:
			//play cat barf
			g_sound_manager.play_sound(257);
			break;
		case 5348:
			//play ambient farm sound
			g_sound_manager.play_sound(236);
			break;
		case 8433:
			//play WWII jet
			g_sound_manager.play_sound(237);
			break;
		case 2317:
			//play boat horn
			g_sound_manager.play_sound(238);
			break;
		case 7467:
			//play WWII bomber
			g_sound_manager.play_sound(239);
			break;
		case 5792:
			//play random bass guitar sample
			g_sound_manager.play_sound(random(227,229));
			break;
		case 2438:
			//play pig monster squeal
			g_sound_manager.play_sound(255);
			break;
		case 6161:
			//play random ambient city drone
			g_sound_manager.play_sound(random(246,253));
			break;
		case 2654:
			//play exit announcment
			g_sound_manager.play_sound(240);
			break;
		case 5340:
			//play random rain 
			g_sound_manager.play_sound(random(233,234));
			break;
		case 3427:
			//play girl talking 
			g_sound_manager.play_sound(241);
			break;
		case 2038:
			//play sneeze splat
			g_sound_manager.play_sound(245);
			break;
		case 3687:
			//play guy in yellow monitor
			g_sound_manager.play_sound(242);
			break;
		case 7552:
			//play air conditioner
			g_sound_manager.play_sound(244);
			break;
		case 3555:
			//play antenae alien communication
			g_sound_manager.play_sound(243);
			break;
		case 9893:
			//play bell
			g_sound_manager.play_sound(259);
			break;
		case 3714:
			//play orange telephone ring
			g_sound_manager.play_sound(230);
			break;
		case 4953:
			//play telephone rotery dial
			g_sound_manager.play_sound(231);
			break;
		case 9661:
			//play "Jim" phone message
			g_sound_manager.play_sound(232);
			break;
		case 7112:
			//play pencil sharpen
			g_sound_manager.play_sound(235);
			break;
		case 932:
			g_sound_manager.play_sound(254);
			Display::activate_pizza_oven_sequence();
			break;
		case 4339:
			g_sound_manager.play_sound(254);
			Display::activate_pizza_oven_sequence();
			break;
		case 8475:
			g_sound_manager.play_sound(254);
			Display::activate_pizza_oven_sequence();
			break;
		case 5967:
			g_sound_manager.play_sound(254);
			Display::activate_pizza_oven_sequence();
			break;
	}

	// reset the keypad state back to the beginning
	reset();
}	


/*
	turn off all leds in the bargraph
*/
void Keypad::clear_bargraph(){
	for(int b = 0; b < 24; b++){
		bar.setBar(b, LED_OFF);
	}
	bar.writeDisplay();
}


/*
	clear the 4-digit display imediately
	mostly code copied from _write_display_character
*/
void Keypad::clear_4_digit(){
	int index;
	for (int i=0; i<CODE_LENGTH; i++){
		// only elements 0-3 change for numbers and 4 for blank
		int sequence[7] = {0, 0, 0, 0, 0, 1, 0}; // initialize to 0

		//turn write pin off while we get ready
		digitalWrite(KEYPAD_DISPLAY_WRITE_PIN, HIGH);

		//position
		index = 3 - i;	// index is reversed on the display
		digitalWrite(KEYPAD_DISPLAY_A1_PIN, index / 2);
		digitalWrite(KEYPAD_DISPLAY_A2_PIN, index % 2);
		

		digitalWrite(KEYPAD_DISPLAY_D0_PIN, sequence[0]);
		digitalWrite(KEYPAD_DISPLAY_D1_PIN, sequence[1]);
		digitalWrite(KEYPAD_DISPLAY_D2_PIN, sequence[2]);
		digitalWrite(KEYPAD_DISPLAY_D3_PIN, sequence[3]);
		digitalWrite(KEYPAD_DISPLAY_D4_PIN, sequence[4]);
		digitalWrite(KEYPAD_DISPLAY_D5_PIN, sequence[5]);
		digitalWrite(KEYPAD_DISPLAY_D6_PIN, sequence[6]);

		// write it
		digitalWrite(KEYPAD_DISPLAY_WRITE_PIN, LOW);
	}
}
