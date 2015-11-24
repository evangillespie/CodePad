#include "Arduino.h"
#include "Display.h"
#include "Config.h"

/*
	Constructor. Generic. Boring
*/
Display::Display() {}


/*
	update the numbers in the display.
	This method called every time in the main loop
*/
void Display::update(Passcode passcode) {
	if (millis() >= _next_action_time){
		_display_next_digit(passcode);
	}
}


/*
	return true if the numbers are all done being shown on the display
*/
bool Display::is_complete() {
	if (_next_action >= 4){
		Serial.print("\n");

		_reset_next_action_time(0);
		_next_action = 0;
		return true;
	}
	return false;
}


/*
	reset the next action time to be the current time plus some increment

	:param increment: time from now that the next action will execute
*/
void Display::_reset_next_action_time(unsigned long increment) {
	_next_action_time = millis() + increment;
}


/*
	show the next available digit on its respective display device
*/
void Display::_display_next_digit(Passcode passcode) {

	Serial.print(passcode.get_digit(_next_action));
	Serial.print(" ");

	_reset_next_action_time(random(MIN_DISPLAY_LAG_TIME, MAX_DISPLAY_LAG_TIME+1));
	_next_action++;
}