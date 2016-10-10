#include "Arduino.h"
#include "ProcedureState.h"


/*
	Constructor. Generic. Boring
*/
ProcedureState::ProcedureState() {
	reset();
}


/*
	update the ProcedureState status
	called every main loop
*/
void ProcedureState::update() {
	if (_is_currently_in_pause == true) {
		if (_next_update_time < 0){
			_next_update_time = millis() + _get_pause_length(_state_num);
		}

		if (millis() >= _next_update_time){
			_next_update_time = -1;
			_is_currently_in_pause = false;
		}
	} else {
		_dispatcher();
	}
}


/*
	reset all the internal variables
*/
void ProcedureState::reset() {
	_is_procedure_complete = false;

	_state_num = 0;

	_is_currently_in_pause = true;
	_next_update_time = -1;
}


/*
	OVERRIDE IN SUBCLASS
	Dispatch to another function based on the current state
*/
void ProcedureState::_dispatcher() {
}


/*
	check if the success sequence is complete
*/
bool ProcedureState::is_complete() {
	return _is_procedure_complete;
}


/*
	OVERRIDE IN SUBCLASS
	return the length of a pause at index in milliseconds

	:param index: return the length of the pause BEFORE this action

	:return: length of the pause in milliseconds
*/
long ProcedureState::_get_pause_length(int index) {
	return 0;
}

/*
	OVERRIDE IN SUBCLASS
	return the index of the highest attainable class (0 indexed)
*/
int ProcedureState::_get_max_state() {
	return 1;
}

/*
	Increment the state of this success procedure by one
*/
void ProcedureState::_increment_state(){
	if (_state_num == _get_max_state()){
		_state_num = 0;
		_is_procedure_complete = true;
	} else {
		_state_num++;
	}

	_is_currently_in_pause = true;
}
