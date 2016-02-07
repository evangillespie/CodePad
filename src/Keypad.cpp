#include "Arduino.h"
#include "Keypad.h"
#include "Config.h"
#include "Pins.h"

int incoming_byte;
int incoming_int;
int _queued_num;
bool _is_clr_flashing;
unsigned long _last_clr_change;

unsigned long keypad_timeout = KEYPAD_TIMEOUT_SECS * 1000;

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
	digitalWrite(keypad_number_clr_led, LOW);
	digitalWrite(keypad_number_clr_led, LOW);

	reset();
}


/*
	check the keypad status
	called every main loop
*/
void Keypad::update(Passcode passcode) {
	_update_status(passcode);
	_is_key_pressed();
	_update_clr_flashing();
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
				//do this
			}
		}
		_queued_num = -1;
	}
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

	//check if clr shoudl flash
	_is_clr_flashing = false;
	for (int i=0; i<CODE_LENGTH; i++){
		if (_entered_values[i] >= 0){
			if (_entered_values[i] != passcode.get_digit(i)){
				_is_clr_flashing = true;
			}
		}
	}

	//check for completeness
	_status = 1;
	for (int i = 0; i < CODE_LENGTH; i++) {
		if (_entered_values[i] == -1){
			_status = 0;
		}
	}

	//check for timeout
	if (millis() >= _init_time + keypad_timeout){
		_status = 2;
	}
}


/*
	flash the clr button if applicable
*/
void Keypad::_update_clr_flashing(){
	if (_is_clr_flashing){
		if (int(millis() - _last_clr_change) > KEYPAD_CLR_FLASH_PERIOD / 2){
			//togle led status
			digitalWrite(keypad_number_clr_led, !digitalRead(keypad_number_clr_led));
			_last_clr_change = millis();
		}
	} else{
		digitalWrite(keypad_number_clr_led, LOW);
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
	for (int i = 0; i < CODE_LENGTH; i++){
		if (_entered_values[i] >= 0){
			val = _entered_values[i];
		} else {
			val = 0;
		}

		ret = ret + (val * pow(10, 3-i));
	}
	return (int)lround(ret);
}


/*
	reset all internal variables
*/
void Keypad::reset() {
	for (int i = 0; i < CODE_LENGTH; i++){
		_entered_values[i] = -1;
	}

	_init_time = millis();
	_status = 0;
	_queued_num = -1;
	_is_clr_flashing = false;
	_last_clr_change = millis();
}


/*
	store a digit received in the local array
	If too many digits get entered, we use the newest set

	:param inc_digit: the incoming digit
*/
void Keypad::_add_digit_to_received(int inc_digit) {
	for (int i = 0; i < CODE_LENGTH-1; i++){
		if (_entered_values[i] == -1){
			_entered_values[i] = inc_digit;
			break;
		}
	}
	Serial.println(inc_digit);
}