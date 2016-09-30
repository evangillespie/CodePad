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
	_sound = 0;
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
	digitalWrite(_pin, LOW);
}


/*
	start one of the leds flashing

	:param led_index: which led are we going to start flashing?
	this is the led number as given in the project description, not the pin number
	:param freq: the frequency to flash at, in hz
*/
void LEDFlasher::turn_on(double freq){
	if (freq == 0.0){
		_period = 0;
		digitalWrite(_pin, HIGH);
	} else {
		_period = 1000.0/freq;
	}
	_is_active = true;
	_last_update = millis();
}


/*
	start one of the leds flashing and a sound that plays along with each flash

	:param freq: the frequency to flash at, in hz
	:param sound_index: which sound do you want to play
*/
void LEDFlasher::turn_on_with_sound(double freq, int sound_index){
	if (freq == 0.0){
		_period = 0;
		digitalWrite(_pin, HIGH);
	} else {
		_period = 1000.0/freq;
	}
	_sound = sound_index;
	_is_active = true;
	_last_update = millis();
}


/*
	stop one of the flashing leds from flashing any more. Turn it off

	:param led_index: which led do i turn off? Same index as in start_flasher
*/
void LEDFlasher::turn_off(){
	_is_active = false;
	_sound = 0;
	digitalWrite(_pin, LOW);
}


/*
	update each flasher. TO be called in the loop
*/
void LEDFlasher::update(){

	if (_is_active == true && _period != 0){
		if (millis() >= (_last_update + (unsigned long)(_period / 2)) ) {
			digitalWrite(_pin, !digitalRead(_pin));
			if (_sound > 0 && digitalRead(_pin) == HIGH){
				g_sound_manager.play_sound(_sound);
			}
			_last_update = millis();
		}
	}
}
