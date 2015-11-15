#include "Arduino.h"
#include "FailState.h"


/*
	Constructor. Generic. Boring
*/
FailState::FailState() {}


/*
	update the FailState status
	called every main loop
*/
void FailState::update() {
	Serial.println("Fail! Do some shit.");
	
}


/*
	check if the success sequence is complete
*/
bool FailState::is_complete() {
	return true;
}