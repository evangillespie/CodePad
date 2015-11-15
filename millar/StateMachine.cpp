#include "Arduino.h"
#include "StateMachine.h"


/* STATES:
	0 - Generate code
	1 - Display code on displays
	2 - Wait for keypad
	3 - wrong code sequence
	4 - correct code sequence
*/


/*
	boring empty constructor
*/
StateMachine::StateMachine(){
}


/*
	start the state machine at some state

	:param state: the starting state number
*/
void StateMachine::begin(int init_state) {
	_state = init_state;
}


/*
	increment the state by 1
*/
void StateMachine::increment_state() {
	int max_state = 3;

	if (_state == max_state){
		_state = 0;
	} else{
		_state++;	
	}
}

/*
	Set the intenal state to a particular state

	:param new_state: the state after this is complete
*/
void StateMachine::set_state(int new_state) {
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
		default:
			break;
	}
}


///////////////////////////////////////

void StateMachine::_generate_passcode_and_advance() {
	_passcode.generate();
	increment_state();

	Serial.println(_passcode.get_passcode());
}

void StateMachine::_update_display_and_advance() {
	_display.update(_passcode);
		if(_display.is_complete() == true){
			increment_state();
			_keypad.reset();
		}
}

void StateMachine::_update_keypad_and_advance(){
	_keypad.update();

	switch(_keypad.get_status()){
		case 0:
			break;
		case 1:
			Serial.println("Keypad complete:");
			Serial.println(_keypad.get_entered_code());

			set_state(0);
			break;
		case 2:
			Serial.println("TIMEOUT");
			set_state(0);
			break;
	}
}