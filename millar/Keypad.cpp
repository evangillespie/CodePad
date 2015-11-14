#include "Arduino.h"
#include "Keypad.h"

int incoming_byte;
int incoming_int;

int code_length = 4;

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

	if (Serial.available() > 0) {
        incoming_byte = Serial.read();
        incoming_int = _convert_byte_to_int(incoming_byte);
        if (incoming_int != -1) {
	        _add_digit_to_received(incoming_int);
	    }
    }
}


/*
	return true if the keypad state is complete
*/
bool Keypad::is_complete() {
	for (int i = 0; i < code_length; i++) {
		if (_entered_values[i] == -1){
			return false;
		}
	}
	return true;
}


/*
	return the entered code as an integer
*/
int Keypad::get_entered_code(){
	int val;
	float ret = 0.0;
	for (int i = 0; i < code_length; i++){
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
	for (int i = 0; i < code_length; i++){
		_entered_values[i] = -1;
	}
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
	for (int i = 0; i < code_length-1; i++){
		_entered_values[i] = _entered_values[i+1];
	}
	_entered_values[code_length-1] = inc_digit;
}