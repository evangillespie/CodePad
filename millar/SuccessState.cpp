#include "Arduino.h"
#include "SuccessState.h"


/*
	Constructor. Generic. Boring
*/
SuccessState::SuccessState() {}


/*
	update the SuccessState status
	called every main loop
*/
void SuccessState::update() {
	Serial.println("Success! Do some shit.");
	
}


/*
	check if the success sequence is complete
*/
bool SuccessState::is_complete() {
	return true;
}