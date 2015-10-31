/****************
  Arduino Keypad Project for Chris Millar. Title to be Determined
****************/


#include "StateMachine.h"
#include "Passcode.h"


//////////////////////////
//	global variables	//
//////////////////////////

Passcode passcode;


//////////////////////
//	intialization	//
//////////////////////

void setup() {
	Serial.begin(9600);

	// @TODO: dispatcher class to control the state machine
}

void loop() {

	delay(50);
}