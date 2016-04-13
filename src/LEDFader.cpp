#include "LEDFader.h"
#include "Arduino.h"
#include "Config.h"


/*
	Constuctor
*/
LEDFader::LEDFader() {
	_pin = 0;
	_index = 0;
	_is_active = false;
	_value = 0;
}


/*

	initiate a Fader with it's critical parameters

	:param index: which led is this?
	:param pin: which pin is this ped connected to?
*/
void LEDFader::init(int index, int pin) {
	_pin = pin;
	_index = index;
	pinMode(_pin, OUTPUT);
}


/*
	start an led fading up (increasing in value)

	:param total_time: the total time that the fading will take
	:param init_vale: the value to start the pin at
	:param final_value: the final value that the led will reach after total_time
*/
void LEDFader::start_fading(int total_time, int init_value, int final_value){
	_is_active = true;
	_value = init_value;
	_final_value = final_value;
	_slope = (double)(final_value - init_value) / (double)total_time;
	_last_update = millis();
	analogWrite(_pin, _value);
}


/*
	update each Fader. TO be called in the loop
*/
void LEDFader::update(){
	if (_is_active == true){
		if (millis() >= _last_update + LED_FADE_TIME_INCREMENT) {
			_value = _value	+ (int)((double)LED_FADE_TIME_INCREMENT * _slope);
			if (_slope > 0 && _value > _final_value){
				_is_active = false;
				_value = _final_value;
			} else if (_slope < 0 && _value < _final_value){
				_is_active = false;
				_value = _final_value;
			}
			_last_update = millis();
		analogWrite(_pin, _value);
		}
	}
}