#include "LEDFlashManager.h"
#include "LEDFlasher.h"
#include "Arduino.h"
#include "Config.h"
#include "Pins.h"


/*
	Constructor. Generic. Boring
*/
LEDFlashManager::LEDFlashManager() {
	for(int i=0; i < NUM_LED_FLASHERS; i++){
		_led_flashers[i].init(i+1, _get_pin_number(i+1));
	}
}


/*
	start one of the leds flashing

	:param led_index: which led are we going to start flashing?
	this is the led number as given in the project description, not the pin number
	led_index starts at 1 but the array index starts at 0, hence the -1.
	:param freq: the frequency to flash at, in hz
*/
void LEDFlashManager::start_flasher(int led_index, double freq){
	_led_flashers[led_index-1].turn_on(freq);
}


/*
	stop one of the flashing leds from flashing any more. Turn it off

	:param led_index: which led do i turn off? Same index as in start_flasher
*/
void LEDFlashManager::stop_flasher(int led_index){
	_led_flashers[led_index-1].turn_off();	
}


/*
	update each flasher. TO be called in the loop
*/
void LEDFlashManager::update(){
	for(int i=0; i < NUM_LED_FLASHERS; i++){
		_led_flashers[i].update();
	}
}


/*
	return the pin number for a given led

	:param led_index: the led index to find a pin for

	:return: digital pin number connected to that led on the arduino
*/
int LEDFlashManager::_get_pin_number(int led_index) {
	switch(led_index){
		case 1:
			return yellow_LED;
		case 2:
			return panel_3_LED;
		case 3:
			return warning_brick_LED;
		case 4:
			return warning_finger_LED;
		case 5:
			return button_3_LED;
		case 6:
			return button_2_LED;
		case 7:
			return button_1_LED;
		case 8:
			return clear_LED;
		case 9:
			return ok_LED;
		case 10:
			return keypad_LED;
		case 11:
			return green_light_keypad_LED;
		case 12:
			return power_crystal_LED;
		default:
			Serial.println("I can't find that pin, Evan");		
	}
}