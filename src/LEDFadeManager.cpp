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
		case 2:
			return LED_2_PIN;
		case 3:
			return LED_3_PIN;
		case 4:
			return LED_4_PIN;
		case 5:
			return LED_5_PIN;
		case 6:
			return LED_6_PIN;
		case 7:
			return LED_7_PIN;
		case 8:
			return LED_8_PIN;
		case 9:
			return LED_9_PIN;
		case 10:
			return LED_10_PIN;
		case 11:
			return LED_11_PIN;
		case 12:
			return LED_12_PIN;
		default:
			Serial.println("I can't find that pin, Evan");		
	}
}