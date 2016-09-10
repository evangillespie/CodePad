#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"
#include "Pins.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the puse state. called ever iteration of the main loop
*/
void PauseState::update() {
	// everything is still working
	if (_system_state == 1){
		_update_clock_sweep();

		if (_is_pir_triggered() == false){
			_system_state = 0;
			_turn_system_off();
		}
	} else {
		if (_is_pir_triggered() == true){
			_system_state = 1;
			_turn_system_on();
		}
	}
}


/*
	turn everything off when the PIR turns off
*/
void PauseState::_turn_system_off(){
	Serial.println("everything turns off!");
}


/*
	turn everything on when the PIR turns on
*/
void PauseState::_turn_system_on(){
	Serial.println("everything turns on!");
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
	if (millis() >= _complete_time && _is_pir_triggered() == true){
		if (_system_state == 0){
			_system_state = 1;
			_turn_system_on();
		}
		return true;
	}
	return false;
}


/*
	return true if the PIR sensor has been triggered
*/
bool PauseState::_is_pir_triggered(){
	return digitalRead(PIR_INPUT);
}


/*
	start the pause
*/
void PauseState::begin() {
	_clock_sweep_dir = 0;
	_system_state = 1;
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}