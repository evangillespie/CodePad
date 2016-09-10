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
	_update_clock_sweep();
}


/*
	sweep the clock back and forth.
*/
void PauseState::_update_clock_sweep(){
	if (g_servo_manager.is_servo_in_position(14)){
		if (_clock_sweep_dir == 0){
			g_servo_manager.move_servo(14, SERVO_14_POSITION_B, SERVO_14_SPEED);
			_clock_sweep_dir = 1;
		} else {
			g_servo_manager.move_servo(14, SERVO_14_POSITION_A, SERVO_14_SPEED);
			_clock_sweep_dir = 0;
		} 
	}
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
	return true if the PIR sensor has been triggered
*/
bool PauseState::is_pir_triggered(){
	// @TODO: check if it's really triggered
	// @TODO: add that random timer
	return true;
}


/*
	start the pause
*/
void PauseState::begin() {
	_clock_sweep_dir = 0;
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}