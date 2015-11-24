#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the puse state. called ever iteration of the main loop
*/
void PauseState::update() {
	// @TODO: move the servo back and forth
}


/*
	return true if this state is done and we should move on
*/
bool PauseState::is_complete() {
	if (millis() >= _complete_time){
		return true;
	}
	return false;
}


/*
	start the pause
*/
void PauseState::begin() {
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}