#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the pause state. called ever iteration of the main loop
*/
void PauseState::update() {
	// @TODO: move the servo back and forth
	//Evan, can you add the clock servo sweeping here
	//servo 14 sweeps between SERVO_14_POSITION_A and SERVO_14_POSITION_B at SERVO_14_SPEED
	
	//g_servo_manager.move_servo(14, SERVO_14_POSITION_A, SERVO_14_SPEED);
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
