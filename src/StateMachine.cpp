#include "Arduino.h"
#include "StateMachine.h"


/* STATES:
	0 - Generate code
	1 - Display code on displays
	2 - Wait for keypad
	3 - correct code sequence
	4 - wrong code sequence
	5 - waiting to generate code again
*/


/*
	boring empty constructor
*/
StateMachine::StateMachine(){}


/*
	start the state machine at some state

	:param state: the starting state number
*/
void StateMachine::begin(int init_state) {
	_state = init_state;
}


/*
	Set the intenal state to a particular state

	:param new_state: the state after this is complete
*/
void StateMachine::set_state(int new_state) {
	switch(new_state) {
		case 2:
			_keypad.reset();
			break;
		case 3:
			_success_state.reset();
			break;
		case 4:
			_fail_state.reset();
			break;
		case 5:
			_pause_state.begin();
			break;
	}

	_state = new_state;
}


/*
	another loop has passed. update the status of the state machine
*/
void StateMachine::update() {

	switch(_state){
		case 0:
			_generate_passcode_and_advance();
			break;
		case 1:
			_update_display_and_advance();
			break;
		case 2:
			_update_keypad_and_advance();
			break;
		case 3:
			_update_success_state_and_advance();
			break;
		case 4:
			_update_fail_state_and_advance();
			break;
		case 5:
			_update_pause_state_and_advance();
			break;
		default:
			break;
	}
}


///////////////////////////////////////

/*

*/
void StateMachine::_generate_passcode_and_advance() {
	_passcode.generate();
	set_state(1);
}

void StateMachine::_update_display_and_advance() {
	_display.update(_passcode);
		if(_display.is_complete() == true){
			set_state(2);
		}
}


/*

*/
void StateMachine::_update_keypad_and_advance(){
	_keypad.update(_passcode);

	switch(_keypad.get_status()){
		case 0:
			break;
		case 1:
			if (_keypad.get_entered_code() == _passcode.get_passcode()){
				Serial.println("Code correct.");
				set_state(3);
			} else {
				Serial.println("Code incorrect.");
				set_state(4);
			}

			break;
		case 2:
			Serial.println("Timeout.");
			set_state(4);
			break;
	}
}


/*

*/
void StateMachine::_update_success_state_and_advance(){
	_success_state.update();

	if (_success_state.is_complete() == true){
		set_state(5);
	}
}


/*

*/
void StateMachine::_update_fail_state_and_advance(){
	_fail_state.update();

	if (_fail_state.is_complete() == true){
		set_state(5);
	}
}


/*

*/
void StateMachine::_update_pause_state_and_advance(){
	_pause_state.update();

	if (_pause_state.is_complete() == true){
		set_state(0);
	}
}