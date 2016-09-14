#include "Arduino.h"
#include "StateMachine.h"
#include "Config.h"
#include "LEDFlashManager.h"
#include "Pins.h"


/* STATES:
	0 - Generate code
	1 - Display code on displays
	2 - Pre-enable keypad
	3 - Wait for keypad
	4 - correct code sequence
	5 - wrong code sequence
	6 - waiting to generate code again
*/

/*
	boring empty constructor
*/
StateMachine::StateMachine(){}


/*
	start the state machine at some state

	:param state: the starting state number
*/
void StateMachine::begin(int init_state) {
	_state = init_state;

	_keypad.init();
	_display.init();

	_initialize_system_leds();
	_initialize_system_servos();
	_initialize_system_solenoids();
}


/*
	Turn off (or on) any system leds at the start of the program
*/
void StateMachine::_initialize_system_leds(){
	
	pinMode(LED_14_PIN, OUTPUT);

	/************************/
	//**NOTE** - this is copied into the pause "Turn everything on" state if anything is edited here it will need to be edited there too.
	/************************/

	//Clear the nixite tubes and matrix
	Display::clear_nixie_tube(1);
	Display::clear_nixie_tube(2);
	Display::clear_matrix();

	//12V LED strips - pin 17 (MEGA)
	digitalWrite(LED_14_PIN, HIGH);

	//Always ON panel 3 LEDs - pin 16 (MEGA)
	digitalWrite(LED_2_PIN, HIGH);

	//Red Pulley LED - pin 24 (quad shifter)
	g_shifter_quad.setPin(24, HIGH);

	//Always ON panel 1 LEDs – pin 26 (quad shifter)
	g_shifter_quad.setPin(26, HIGH);

	//Pizza oven exterior LEDs - pin 28 (quad shifter)
	g_shifter_quad.setPin(28, HIGH);

	//Magpanel LED - pin 29 (quad shifter)
	g_shifter_quad.setPin(29, HIGH);

	//Clock illumination LED - LED_7_PIN brightness of 100	This will not fade because it is not conneected to a PWM pin
	g_led_fade_manager.fade(7, 100, 0, 100);

	//Radar Screen - LED_5_PIN brightness 50 This will not fade because it is not conneected to a PWM pin
	g_led_fade_manager.fade(5, 100, 0, 50);

	//Power crystals - LED_12_PIN brightness 10 This will not fade because it is not conneected to a PWM pin
	g_led_fade_manager.fade(12, 100, 0, 10);

	//Yellow LED inside Keyapd - LED_2_PIN brightness 50 This will not fade because it is not conneected to a PWM pin
	g_led_fade_manager.fade(2, 100, 0, 50); 

	//Pizza coals inside pizza oven - LED_6_PIN brightness 100 This will not fade because it is not conneected to a PWM pin
	g_led_fade_manager.fade(6, 100, 0, 100);

	g_shifter_quad.write();

}
/*
	Set Servo start postition
*/
void StateMachine::_initialize_system_servos(){

	// move servos 8, 10, 11, 12 First
	g_servo_manager.move_servo(8,SERVO_8_POSITION_A, SERVO_8_SPEED);
	g_servo_manager.move_servo(10,SERVO_10_POSITION_A, SERVO_10_SPEED);
	g_servo_manager.move_servo(11,SERVO_11_POSITION_A, SERVO_11_SPEED);
	g_servo_manager.move_servo(12,SERVO_12_POSITION_A, SERVO_12_SPEED);

	//delay to wait for first servos to reach position this can be edited
	delay(1000);

	// Move 1,2,3,4,5,6,7,9,13,15,16 servo
	g_servo_manager.move_servo(1,SERVO_1_POSITION_A, SERVO_1_SPEED);
	g_servo_manager.move_servo(2,SERVO_2_POSITION_A, SERVO_2_SPEED);
	g_servo_manager.move_servo(3,SERVO_3_POSITION_A, SERVO_3_SPEED);
	g_servo_manager.move_servo(3,SERVO_3_POSITION_A, SERVO_3_SPEED);
	g_servo_manager.move_servo(4,SERVO_4_POSITION_A, SERVO_4_SPEED);
	g_servo_manager.move_servo(5,SERVO_5_POSITION_A, SERVO_5_SPEED);
	g_servo_manager.move_servo(6,SERVO_6_POSITION_A, SERVO_6_SPEED);
	g_servo_manager.move_servo(7,SERVO_7_POSITION_A, SERVO_7_SPEED);
	g_servo_manager.move_servo(9,SERVO_9_POSITION_A, SERVO_9_SPEED);
	g_servo_manager.move_servo(13,SERVO_13_POSITION_A, SERVO_13_SPEED);
	g_servo_manager.move_servo(15,SERVO_15_POSITION_A, SERVO_15_SPEED);
	g_servo_manager.move_servo(16,SERVO_16_POSITION_A, SERVO_16_SPEED);

}

void StateMachine::_initialize_system_solenoids(){
	//Set Solenoids as outputs
	pinMode(SOLENOID_1_PIN, OUTPUT);
	pinMode(SOLENOID_2_PIN, OUTPUT);
	pinMode(SOLENOID_3_PIN, OUTPUT);
	pinMode(SOLENOID_4_PIN, OUTPUT);
	pinMode(SOLENOID_5_PIN, OUTPUT);

	//TUBAMAN 7 tuba player that pops out of coo coo clock
	digitalWrite(SOLENOID_1_PIN, LOW);

	//WARNING_BRICKS_MINI 8 miniature version of the warning bricks 
	digitalWrite(SOLENOID_2_PIN, LOW);

	//STAIRS 9 Brass stairs that pop up when cage lifts up
	digitalWrite(SOLENOID_3_PIN, LOW);

	//HANDRAIL 10 Brass handrail door that opens when cage lifts up 
	digitalWrite(SOLENOID_4_PIN, LOW);

	//PIZZA_OVEN_DOOR 11 pizza oven door
	digitalWrite(SOLENOID_5_PIN, LOW);

}
/*
	Set the intenal state to a particular state

	:param new_state: the state after this is complete
*/
void StateMachine::set_state(int new_state) {
	switch(new_state) {
		case 2:
			_keypad_preenable_state.reset();
			break;
		case 3:
			_keypad.reset();
			_keypad.clear_bargraph();
			break;
		case 4:
			_success_state.reset();
			break;
		case 5:
			_fail_state.reset();
			break;
		case 6:
			_pause_state.begin();
			break;
	}

	_state = new_state;
}


/*
	another loop has passed. update the status of the state machine
*/
void StateMachine::update() {

	switch(_state){
		case 0:
			_generate_passcode_and_advance();
			break;
		case 1:
			_update_display_and_advance();
			break;
		case 2:
			_update_keypad_preenable_and_advance();
			break;
		case 3:
			_update_keypad_and_advance();
			break;
		case 4:
			_update_success_state_and_advance();
			break;
		case 5:
			_update_fail_state_and_advance();
			break;
		case 6:
			_update_pause_state_and_advance();
			break;
	}
}


///////////////////////////////////////

/*

*/
void StateMachine::_generate_passcode_and_advance() {
	_passcode.generate();
	set_state(1);
}


/*

*/
void StateMachine::_update_display_and_advance() {
	_display.update(_passcode);
	if(_display.is_complete() == true){
		set_state(2);
	}
}


/*

*/
void StateMachine::_update_keypad_preenable_and_advance() {
	_keypad_preenable_state.update();

	if (_keypad_preenable_state.is_complete() == true){
		set_state(3);
	}
}


/*

*/
void StateMachine::_update_keypad_and_advance(){
	_keypad.update(_passcode);

	switch(_keypad.get_status()){
		case 0:
			break;
		case 1:
			if (_keypad.get_entered_code() == _passcode.get_passcode()){
				Serial.println("Code correct.");
				_keypad.turn_off_displays();
				set_state(4);
			} else {
				Serial.println("Code incorrect.");
				_keypad.turn_off_displays();
				set_state(5);
			}

			break;
		case 2:
			Serial.println("Timeout.");
			_keypad.turn_off_displays();
			set_state(5);
			break;
	}
}


/*

*/
void StateMachine::_update_success_state_and_advance(){
	_success_state.update();

	if (_success_state.is_complete() == true){
		set_state(6);
	}
}


/*

*/
void StateMachine::_update_fail_state_and_advance(){
	_fail_state.update();

	if (_fail_state.is_complete() == true){
		set_state(6);
	}
}


/*

*/
void StateMachine::_update_pause_state_and_advance(){
	_pause_state.update();

	if (_pause_state.is_complete() == true){
		set_state(0);
	}
}