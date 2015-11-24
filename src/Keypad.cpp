#include "Arduino.h"
#include "Keypad.h"
#include "Config.h"

int incoming_byte;
int incoming_int;

unsigned long keypad_timeout = KEYPAD_TIMEOUT_SECS * 1000;

/*
	Constructor. Generic. Boring
*/
Keypad::Keypad() {
	reset();
}


/*
	check the keypad status
	called every main loop
*/
void Keypad::update() {
	
	_update_status();

	//check for incoming digits
	if (Serial.available() > 0) {
        incoming_byte = Serial.read();
        incoming_int = _convert_byte_to_int(incoming_byte);
        if (incoming_int != -1) {
	        _add_digit_to_received(incoming_int);
	    }
    }
}


/*
	check conditions and update the status

	possible statuses are:
	0 - waiting for data
	1 - code entered and complete
	2 - timeout
*/
void Keypad::_update_status() {

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
}


/*
	convert the encoded information into an integer
	return -1 if error

	:param encoded_int: the encoded version of the int
*/
int Keypad::_convert_byte_to_int(int encoded_int) {
	// XXX: this really only works for serial and ascii encoding

	if (encoded_int >= 48 && encoded_int <= 57) {
		return encoded_int - 48;
	} else {
		return -1;
	}
}


/*
	store a digit received in the local array
	If too many digits get entered, we use the newest set

	:param inc_digit: the incoming digit
*/
void Keypad::_add_digit_to_received(int inc_digit) {
	for (int i = 0; i < CODE_LENGTH-1; i++){
		_entered_values[i] = _entered_values[i+1];
	}
	_entered_values[CODE_LENGTH-1] = inc_digit;
}