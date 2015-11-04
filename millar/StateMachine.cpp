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
	_next_action_time = millis();
	_next_action = 0;
}


/*
	increment the state by 1
*/
void StateMachine::increment_state() {
	int max_state = 1;
	if (_state == max_state){
		_state = 0;
	} else{
		_state++;	
	}

	_reset_next_action_time(0);
	_next_action = 0;
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

			_update_display();
			if(_is_display_complete() == true){
				increment_state();
			}
			break;
		default:
			break;
	}
}


///////////////////////////////////////

/*
	reset the next action time to be the current time plus some increment

	:param increment: time from now that the next action will execute
*/
void StateMachine::_reset_next_action_time(unsigned long increment) {
	_next_action_time = millis() + increment;
}


void StateMachine::_generate_passcode_and_advance() {
	_passcode.generate();
	increment_state();

	Serial.println(_passcode.get_passcode());
}

/*
	update the numbers on the displays. This runs every loop.
*/
void StateMachine::_update_display() {
	if (millis() >= _next_action_time){
		_display_next_digit();
	}
}


/*
	show the next available digit on its respective display device
*/
void StateMachine::_display_next_digit() {

	Serial.print(_passcode.get_digit(_next_action));
	Serial.print(" ");

	_reset_next_action_time(random(1000, 5001));
	_next_action++;
}


/*
	return true if the numbers are all done being shown on the display
*/
bool StateMachine::_is_display_complete() {
	if (_next_action >= 4){
		Serial.print("\n");
		return true;
	}
	return false;
}