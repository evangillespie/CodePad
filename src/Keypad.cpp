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

unsigned long keypad_timeout = (unsigned long)KEYPAD_TIMEOUT_SECS * (unsigned long)1000;

Adafruit_24bargraph bar = Adafruit_24bargraph();

/*
	Constructor. Generic. Boring
*/
Keypad::Keypad() {
	pinMode(keypad_number_1, INPUT);
	pinMode(keypad_number_2, INPUT);
	pinMode(keypad_number_3, INPUT);
	pinMode(keypad_number_4, INPUT);
	pinMode(keypad_number_5, INPUT);
	pinMode(keypad_number_6, INPUT);
	pinMode(keypad_number_7, INPUT);
	pinMode(keypad_number_8, INPUT);
	pinMode(keypad_number_9, INPUT);
	pinMode(keypad_number_0, INPUT);
	pinMode(keypad_number_clr, INPUT);
	pinMode(keypad_number_ok, INPUT);
	pinMode(keypad_number_clr_led, OUTPUT);
	pinMode(keypad_number_ok_led, OUTPUT);

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

	digitalWrite(keypad_number_clr_led, LOW);
	digitalWrite(keypad_number_clr_led, LOW);

	_bargraph_time_step = keypad_timeout / 24;
	_bargraph_num_lights = 0;

	reset();
}


void Keypad::init() {
	bar.begin(0x70);
	clear_bargraph();
	_update_display();
}

/*
	check the keypad status
	called every main loop
*/
void Keypad::update(Passcode passcode) {
	_update_status(passcode);
	_is_key_pressed();
	_update_btns_flashing();
}


/*
	save that a key was pressed on the keypad
*/
void Keypad::_is_key_pressed(){
	if (digitalRead(keypad_number_1))
		_queued_num = 1;
	else if (digitalRead(keypad_number_2))
		_queued_num = 2;
	else if (digitalRead(keypad_number_3))
		_queued_num = 3;
	else if (digitalRead(keypad_number_4))
		_queued_num = 4;
	else if (digitalRead(keypad_number_5))
		_queued_num = 5;
	else if (digitalRead(keypad_number_6))
		_queued_num = 6;
	else if (digitalRead(keypad_number_7))
		_queued_num = 7;
	else if (digitalRead(keypad_number_8))
		_queued_num = 8;
	else if (digitalRead(keypad_number_9))
		_queued_num = 9;
	else if (digitalRead(keypad_number_0))
		_queued_num = 0;
	else if (digitalRead(keypad_number_clr))
		_queued_num = 11;
	else if (digitalRead(keypad_number_ok))
		_queued_num = 12;
	else
		_register_queued_key();
}


/*
	register the last pressed key in now that all are released
*/
void Keypad::_register_queued_key(){
	if (_queued_num >= 0){
		if (_queued_num < 10){
			_add_digit_to_received(_queued_num);
		} else {
			//clr button
			if (_queued_num == 11){
				//backspace
				for (int i = CODE_LENGTH-1; i > 0; i--){
					if (_entered_values[i] >= 0){
						_entered_values[i] = -1;
						break;
					}
				}
			}
			// ok button
			if (_queued_num == 12){
				// once the okay button is pressed, code is locked in.
				_status = 1;
			}
		}
		_update_display();
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
	:param num: which number to I write? write blank if -1
*/
void Keypad::_write_display_character(int index, int num){
	// only elements 0-3 change for numbers and 4 for blank
	int sequence[7] = {0, 0, 0, 0, 1, 1, 0}; // initialize to 0

	//turn write pin off while we get ready
	digitalWrite(KEYPAD_DISPLAY_WRITE_PIN, HIGH);

	//posistion
	digitalWrite(KEYPAD_DISPLAY_A1_PIN, index / 2);
	digitalWrite(KEYPAD_DISPLAY_A2_PIN, index % 2);
	
	// character
	if (num == -1){
		sequence[4] = 0;
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

	// write it
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

	// check if ok should flash
	_is_ok_flashing = true;
	for (int i=0; i<CODE_LENGTH; i++){
		if (_entered_values[i] == -1){
			_is_ok_flashing = false;
		}
	}

	_update_right_wrong_leds(passcode);

	
	//update bar graph
	_bargraph_num_lights = (millis() - _init_time) / _bargraph_time_step;
	for(int b = 0; b < _bargraph_num_lights; b++){
		if (b < 8){
			bar.setBar(b, LED_GREEN);
		} else if (b < 16) {
			bar.setBar(b, LED_YELLOW);
		} else {
			bar.setBar(b, LED_RED);
		}
	}
	bar.writeDisplay();


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
			//togle led status
			digitalWrite(keypad_number_clr_led, !digitalRead(keypad_number_clr_led));
			_last_clr_change = millis();
		}
	} else{
		digitalWrite(keypad_number_clr_led, LOW);
	}

	if (_is_ok_flashing){
		if (int(millis() - _last_ok_change) > KEYPAD_OK_FLASH_PERIOD / 2){
			//togle led status
			digitalWrite(keypad_number_ok_led, !digitalRead(keypad_number_ok_led));
			_last_ok_change = millis();
		}
	} else{
		digitalWrite(keypad_number_ok_led, LOW);
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
	if (_status == 1){
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
*/
void Keypad::_update_right_wrong_leds(Passcode passcode){
	// @TODO: make this work once hardware is ready
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
	turn off all leds in the bargraph
*/
void Keypad::clear_bargraph(){
	for(int b = 0; b < 24; b++){
		bar.setBar(b, LED_OFF);
	}
	bar.writeDisplay();
}
