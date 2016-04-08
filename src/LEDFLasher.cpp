#include "LEDFlasher.h"
#include "Arduino.h"


/*
	Constuctor
*/
LEDFlasher::LEDFlasher() {
	_pin = 0;
	_index = 0;
	_is_active = false;
	_period = 0;
}


/*

	initiate a flasher with it's critical parameters

	:param index: which led is this?
	:param pin: which pin is this ped connected to?
*/
void LEDFlasher::init(int index, int pin) {
	_pin = pin;
	_index = index;
	pinMode(_pin, OUTPUT);
}


/*
	start one of the leds flashing

	:param led_index: which led are we going to start flashing?
	this is the led number as given in the project description, not the pin number
	:param freq: the frequency to flash at, in hz
*/
void LEDFlasher::turn_on(double freq){
	_period = 1.0/freq;
	_is_active = true;
	_last_update = millis();
}


/*
	stop one of the flashing leds from flashing any more. Turn it off

	:param led_index: which led do i turn off? Same index as in start_flasher
*/
void LEDFlasher::turn_off(){
	_is_active = false;
	digitalWrite(_pin, LOW);
}


/*
	update each flasher. TO be called in the loop
*/
void LEDFlasher::update(){
	if (_is_active == true){
		if (millis() >= (_last_update + (unsigned long)(_period * 1000 / 2)) ) {
			digitalWrite(_pin, !digitalRead(_pin));
			_last_update = millis();
		}
	}
}