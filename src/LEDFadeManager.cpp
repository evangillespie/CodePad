#include "LEDFadeManager.h"
#include "LEDFader.h"
#include "Arduino.h"
#include "Config.h"
#include "Pins.h"


/*
	Constructor. Generic. Boring
*/
LEDFadeManager::LEDFadeManager() {
	for(int i=0; i < NUM_LED_FADERS; i++){
		_led_faders[i].init(i+1, _get_pin_number(i+1));
	}
}


/*
	start one of the leds fading up

	:param led_index: which led are we going to start Fading?
	this is the led number as given in the project description, not the pin number
	led_index starts at 1 but the array index starts at 0, hence the -1.
	:param total_time: time (in milliseconds) that the whole fading process will take
	:param init_value: the value that the led will start at
	:param final_value: the value that the led will reach after total_time
*/
void LEDFadeManager::fade(int led_index, int total_time, int init_value, int final_value){
	_led_faders[led_index-1].start_fading(total_time, init_value, final_value);
}


/*
	Return true if the led in question is still in the middle of fading

	:param led_index: which led am i checking?

	:return: true if the led is fading, false if not
*/
bool LEDFadeManager::is_fading(int led_index){
	return _led_faders[led_index-1].is_fading();
}


/*
	update each Fader. To be called in the main loop
*/
void LEDFadeManager::update(){
	for(int i=0; i < NUM_LED_FADERS; i++){
		_led_faders[i].update();
	}
}


/*
	return the pin number for a given led

	:param led_index: the led index to find a pin for

	:return: digital(pwm) pin number connected to that led on the arduino
*/
int LEDFadeManager::_get_pin_number(int led_index) {
	switch(led_index){
		//@TODO: figure these out
		case 1:
			return LED_1_PIN;
		default:
			Serial.println("I can't find that pin, Evan");		
	}
}