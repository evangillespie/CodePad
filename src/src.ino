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
#include "LEDFadeManager.h"

//////////////////////////
//	global variables	//
//////////////////////////

StateMachine state_machine;
LEDFlashManager g_led_flash_manager;
LEDFadeManager g_led_fade_manager;

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
	g_led_flash_manager.update();
	g_led_fade_manager.update();
	delay(50);
}