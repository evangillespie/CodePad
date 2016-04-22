
/****************
  Arduino Keypad Project for Chris Millar. Title to be Determined
****************/

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>
#include <Shifter.h>

#include "StateMachine.h"
#include "Passcode.h"
#include "Pins.h"
#include "LEDFadeManager.h"
#include "SoundManager.h"

//////////////////////////
//	global variables	//
//////////////////////////

StateMachine state_machine;
LEDFlashManager g_led_flash_manager;
LEDFadeManager g_led_fade_manager;
SoundManager g_sound_manager;

Shifter shifter(SHIFT_REGISTER_SER_IN_PIN,
				SHIFT_REGISTER_LCLOCK_PIN,
				SHIFT_REGISTER_CLOCK_PIN,
				4);

//////////////////////
//	intialization	//
//////////////////////

void setup() {
	Serial.begin(9600);
	
	randomSeed(analogRead(UNCONNECTED_PIN));	// make sure this is always reading an unconnected pin

	state_machine.begin(0);

	//prep the shift registers
	shifter.clear();
	shifter.write();
	// shifter.setPin(5, HIGH);
	// shifter.write();

}

void loop() {
	state_machine.update();
	g_led_flash_manager.update();
	g_led_fade_manager.update();
	delay(50);
}
