#include <Shifter.h>

#include "Arduino.h"
#include "Display.h"
#include "Config.h"
#include "Pins.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(
	LANDSCAPE_TUBE_NUM_NEOPIXELS,
	LANDSCAPE_NEOPIXELS_PIN,
	NEO_GRB + NEO_KHZ800
);


/*
	Constructor. Generic. Boring
*/
Display::Display(){}


/*
	initialize anything for the display object
*/
void Display::init(){
	matrix.begin(0x71);
	neopixels.begin();

	_next_pizza_sign_time = millis(); // will start motion right away
	_pizza_sign_state = 0;
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
			_display_led_matrix(dig);

			//Play a random dipslay sound
			g_sound_manager.play_sound(random(260,287));

			//Radar LED fades up to 30
			//g_led_fade_manager.fade(5, 5000, 0, 100);

			break;
		case 1:
			_display_nixie_tube(0, dig);

			//Play a random dipslay sound
			g_sound_manager.play_sound(random(260,287));
			break;
		case 2:
			_display_servo(dig);

			//Play a random dipslay sound
			g_sound_manager.play_sound(random(260,287));
                        
			//Clock illumination LEDs fade down
			g_led_fade_manager.fade(7, 5000, 70, 0);
									
			//Green LEDs inside_clock turn ON
			g_shifter_quad.setPin(25,HIGH);
			g_shifter_quad.write();
			
			//Turn Off all the clock number LEDs
			g_shifter_quad.setPin(13, LOW);  //clock number LED 0
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(14, LOW);  //clock number LED 1
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(15, LOW);  //clock number LED 2
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(16, LOW);  //clock number LED 3
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(17, LOW);  //clock number LED 4
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(18, LOW);  //clock number LED 5
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(19, LOW);  //clock number LED 6
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(20, LOW);  //clock number LED 7
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(21, LOW);  //clock number LED 8
			g_shifter_quad.write();
			delay(50);
			g_shifter_quad.setPin(22, LOW);  //clock number LED 9
			g_shifter_quad.write();
			delay(50);

			//TODO
			//Turn ON the clock number LED that matches code digit
			//g_shifter_quad.setPin(codedigit,HIGH);

			break;
		case 3:
			_display_nixie_tube(1, dig);

			//Play a random dipslay sound
			g_sound_manager.play_sound(random(260,287));

			delay(500);

			//Magpanel LEDs turn ON			
			g_shifter_quad.setPin(29,HIGH);
			g_shifter_quad.write();

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

	:param tube_index: which nixie tube are we looking at here? 0 or 1?
*/
void Display::clear_nixie_tube(int tube_index){
	int offset;
	switch(tube_index){
		case 1:
			offset = NIXIE_TUBE_1_PIN_OFFSET;
			break;
		case 2:
			offset = NIXIE_TUBE_2_PIN_OFFSET;
			break;
		default:
			Serial.println("Wrong nixie index");
	}

	for (int i=0; i < 4; i++){
		g_shifter_quad.setPin(i+offset, HIGH);
	}
	g_shifter_quad.write();
}

/*
	Clear the matrix display
*/
void Display::clear_matrix(){
	matrix.clear();
	matrix.writeDisplay();
}

/*
	display a particular number on the led matrix

	:param display_digit: the number to show on the led matrix
*/
void Display::_display_led_matrix(int display_digit){

	matrix.setCursor(2, 1);   //Centre number in display
	matrix.setTextSize(1);    //Size 1 == 8 pixels high

	matrix.print((display_digit));

	matrix.writeDisplay();
}


/*
	display a particular number on the display servo
	just one servo is the display servo and that's what we're dealing with here

	:param display_digit: the number to display with the servo
*/
void Display::_display_servo(int display_digit){
	
	switch(display_digit){

		case 0:
			g_servo_manager.move_servo(14, 435, 50);
			break;
		case 1:
			g_servo_manager.move_servo(14, 500, 50);
			break;
		case 2:
			g_servo_manager.move_servo(14, 590, 50);
			break;
		case 3:
			g_servo_manager.move_servo(14, 680, 50);
			break;
		case 4:
			g_servo_manager.move_servo(14, 760, 50);
			break;
		case 5:
			g_servo_manager.move_servo(14, 835, 50);
			break;
		case 6:
			g_servo_manager.move_servo(14, 100, 50);
			break;
		case 7:
			g_servo_manager.move_servo(14, 185, 50);
			break;
		case 8:
			g_servo_manager.move_servo(14, 265, 50);
			break;
		case 9:
			g_servo_manager.move_servo(14, 350, 50);
			break;
	}
}


/*
	turn the neopixel set on or off.
	Not really a part of the display, but where else do I put it?

	:param new_state: true if turning on, false if turning off
*/
void Display::turn_neopixles_on_or_off(bool new_state){
	if (new_state){
		for (int i=0; i < LANDSCAPE_TUBE_NUM_NEOPIXELS; i++){
			neopixels.setPixelColor(i, neopixels.Color(100, 100, 60)); // Moderately bright green color.
		}
		neopixels.setPixelColor(9, neopixels.Color(150, 0, 0));
		neopixels.setPixelColor(6, neopixels.Color(0, 0, 220));
		neopixels.show();
	} else {
		for (int i=0; i < LANDSCAPE_TUBE_NUM_NEOPIXELS; i++){
			neopixels.setPixelColor(i, neopixels.Color(0, 0, 0));
		}
		neopixels.show();
	}
}


/*
	Update the movement of the pizza sign servos
	This isn't really the display, but it isn't really something else either.
*/
void Display::update_pizza_sign(){
	/*
		_pizza_sign_state_values:
		0 - neutral state (position a)
		1 - open
		2 - closed
		3 - 17 - chewing. odds are open positions, evens are closed
	*/
	if (millis() >= _next_pizza_sign_time){
		//increment the state and set a new time
		_pizza_sign_state++;
		if (_pizza_sign_state > 17)
			_pizza_sign_state = 0;

		_move_pizza_sign_servo(_pizza_sign_state);
		unsigned long incremental_time;
		switch(_pizza_sign_state){
			case 0:
				incremental_time = random(19000, 40000);
				break;
			case 1:
				incremental_time = 6000;
				break;
			case 2:
				incremental_time = 4000;
				break;
			default:
				incremental_time = random(150, 400);
				break;
		}
		_next_pizza_sign_time = millis() + incremental_time;
	}
}


/*
	move the pizza sign servo to a new state
	the speed and position are calculated within this function from the state

	:param new_state: State to move to. States are listed in update_pizza_sign()
*/
void Display::_move_pizza_sign_servo(int new_state){
	int pos;
	int speed;

	switch(new_state){
		case 0:
			pos = SERVO_15_POSITION_A;
			speed = SERVO_15_SPEED;
			break;
		case 1:
			pos = 550;
			speed = 20;
			break;
		case 2:
			pos = 340;
			speed = 25;
			break;
		default:
			if (new_state % 2 == 0){
				pos = random(335, 360);
			} else {
				pos = random(310, 335);
			}
			speed = random(40, 90);
			break;
	}
	g_servo_manager.move_servo(15, pos, speed);
}
