/****************
  Arduino Keypad Project for Chris Millar. Title to be Determined
****************/

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>

#include "StateMachine.h"
#include "Passcode.h"
#include "Pins.h"

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
	
	randomSeed(analogRead(UNCONNECTED_PIN));	// make sure this is always reading an unconnected pin

	state_machine.begin(0);
}

void loop() {
	state_machine.update();
	delay(50);
}
