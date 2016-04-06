#include "LEDManager.h"
#include "LEDFlasher.h"
#include "Arduino.h"
#include "Config.h"


/*
	Constructor. Generic. Boring
*/
LEDManager::LEDManager() {
	for(int i=0; i < NUM_LED_FLASHERS; i++){
		_led_flashers[i].init(i, i);
	}
}


/*
	start one of the leds flashing

	:param led_index: which led are we going to start flashing?
	this is the led number as given in the project description, not the pin number
	:param freq: the frequency to flash at, in hz
*/
void LEDManager::start_flasher(int led_index, double freq){
	Serial.println("flashing...");
	_led_flashers[led_index].turn_on(freq);
}


/*
	stop one of the flashing leds from flashing any more. Turn it off

	:param led_index: which led do i turn off? Same index as in start_flasher
*/
void LEDManager::stop_flasher(int led_index){
	_led_flashers[led_index].turn_off();	
}


/*
	update each flasher. TO be called in the loop
*/
void LEDManager::update(){
	for(int i=0; i < NUM_LED_FLASHERS; i++){
		_led_flashers[i].update();
	}
}