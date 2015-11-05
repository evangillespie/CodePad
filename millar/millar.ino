/****************
  Arduino Keypad Project for Chris Millar. Title to be Determined
****************/


#include "StateMachine.h"
#include "Passcode.h"


//////////////////////////
//	global variables	//
//////////////////////////

StateMachine state_machine;
Passcode passcode;


//////////////////////
//	intialization	//
//////////////////////

void setup() {
	Serial.begin(9600);
	
	randomSeed(analogRead(1));	// make sure this is always reading an unconnected pin

	state_machine.begin(0);
}

void loop() {
	state_machine.update();
	delay(50);
}