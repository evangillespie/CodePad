
/****************
  Arduino Keypad Project for Chris Millar. Title to be Determined
****************/

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>
#include <Shifter.h>
#include <wavTrigger.h>
#include <DynamixelSerial1.h>
#include <Adafruit_NeoPixel.h>

#include "StateMachine.h"
#include "Passcode.h"
#include "Pins.h"
#include "LEDFadeManager.h"
#include "SoundManager.h"
#include "ServoManager.h"  

//////////////////////////
//	global variables	//
//////////////////////////

StateMachine state_machine;
LEDFlashManager g_led_flash_manager;
LEDFadeManager g_led_fade_manager;
SoundManager g_sound_manager;
ServoManager g_servo_manager;
bool g_pizza_oven_trigger;
bool g_pizza_sign_on;

Shifter g_shifter_quad(QUAD_SHIFT_REGISTER_SER_IN_PIN,
				QUAD_SHIFT_REGISTER_LCLOCK_PIN,
				QUAD_SHIFT_REGISTER_CLOCK_PIN,
				4);
Shifter g_shifter_dual(DUAL_SHIFT_REGISTER_SER_IN_PIN,
				DUAL_SHIFT_REGISTER_LCLOCK_PIN,
				DUAL_SHIFT_REGISTER_CLOCK_PIN,
				2);

//////////////////////
//	intialization	//
//////////////////////

int counter = 0;

void setup() {
	Serial.begin(9600);
	while (!Serial); // while the serial stream is not open, do nothing
	delay(100);

	randomSeed(analogRead(UNCONNECTED_PIN));	// make sure this is always reading an unconnected pin

	//prep the shift registers
	g_shifter_quad.clear();
	g_shifter_quad.write();
	g_shifter_dual.clear();
	g_shifter_dual.write();

	state_machine.begin(0);
}

void loop() {
	state_machine.update();
	g_led_flash_manager.update();
	g_led_fade_manager.update();
	delay(50);
	if (++counter > 1000){
		Serial.println("---");
		Serial.println(freeRam());
		Serial.println("---");
		counter = 0;
	}
}

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}