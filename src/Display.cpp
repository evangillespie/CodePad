#include <Shifter.h>

#include "Arduino.h"
#include "Display.h"
#include "Config.h"
#include "Pins.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

/*
	Constructor. Generic. Boring
*/
Display::Display(){}


/*
	initialize anything for the display object
*/
void Display::init(){
	matrix.begin(0x71);
}


/*
	update the numbers in the display.
	This method called every time in the main loop
*/
void Display::update(Passcode passcode) {
	if (millis() >= _next_action_time){
		_display_next_digit(passcode, DEBUG_MODE);
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
void Display::_display_next_digit(Passcode passcode, bool serial_display=false) {
	int dig = passcode.get_digit(_next_action);
	if (serial_display == true ){
		Serial.print(dig);
		Serial.print(" \n");
	}
	switch(_next_action){
		case 0:
			//fallthrough
			// case 0 and 1 use nixie tubes
		case 1:
			_display_nixie_tube(_next_action, dig);
			break;
		case 2:
			_display_led_matrix(dig);
			break;
		case 3:
			_display_servo(dig);
			break;
	}

	_reset_next_action_time(random(MIN_DISPLAY_LAG_TIME, MAX_DISPLAY_LAG_TIME+1));
	_next_action++;
}


/*
	Show a number on a particular nixie tube

	:param tube_index: which nixe tube are we looking at here? 0 or 1?
	:param display_digit: the digit to display on that nixie tube
*/
void Display::_display_nixie_tube(int tube_index, int display_digit){
	bool sequence[4];
	int offset;
	switch(tube_index){
		case 0:
			offset = NIXIE_TUBE_1_PIN_OFFSET;
			break;
		case 1:
			offset = NIXIE_TUBE_2_PIN_OFFSET;
			break;
	}

	// convert display_digit to binary
	for (int i=0; i < 4; i++){
		sequence[i] = display_digit % 2;
		display_digit = display_digit / 2;
	}

	for (int i=0; i < 4; i++){
		g_shifter_quad.setPin(i+offset, sequence[i]);
	}
	g_shifter_quad.write();
}


/*
	Clear a particular nixie tube

	:param tube_index: which nixe tube are we looking at here? 0 or 1?
*/
void Display::clear_nixie_tube(int tube_index){
	int offset;
	switch(tube_index){
		case 0:
			offset = NIXIE_TUBE_1_PIN_OFFSET;
			break;
		case 1:
			offset = NIXIE_TUBE_2_PIN_OFFSET;
			break;
	}

	for (int i=0; i < 4; i++){
		g_shifter_quad.setPin(i+offset, HIGH);
	}
	g_shifter_quad.write();
}


/*
	display a particular number on the led matrix

	:param display_digit: the number to show on the led matrix
*/
void Display::_display_led_matrix(int display_digit){
	// @TODO: this needs to be tested with hardware

	matrix.setCursor(1, 0);   // start at top left, with one pixel of spacing
	matrix.setTextSize(1);    // size 1 == 8 pixels high

	matrix.print(char(display_digit));

	matrix.writeDisplay();
}


/*
	display a particular number on the display servo
	just one servo is the display servo and that's what we're dealing with here

	:param display_digit: the number to display with the servo
*/
void Display::_display_servo(int display_digit){
	// @TODO: put the real positions in here for each number when you have them
	// @TODO: put the real servo id in each of these move_servo commands
	// @TODO: put the real speed in each of these move_servo commands
	switch(display_digit){
		case 0:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 1:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 2:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 3:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 4:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 5:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 6:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 7:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 8:
			g_servo_manager.move_servo(1, 100, 100);
			break;
		case 9:
			g_servo_manager.move_servo(1, 100, 100);
			break;
	}
}