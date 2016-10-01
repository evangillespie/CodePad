#include "Arduino.h"
#include "StateMachine.h"
#include "Config.h"
#include "LEDFlashManager.h"
#include "Pins.h"
//#include "LEDFadeManager.h"  //added sept 11 by CM

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
	_keypad.init();
	_display.init();

	_initialize_system_solenoids();
	_initialize_system_leds();
	_initialize_system_servos();


	set_state(init_state);
}


/*
	Turn off (or on) any system leds at the start of the program
*/
void StateMachine::_initialize_system_leds(){

	/************************/
	//**NOTE** - this is copied into the pause "Turn everything on" state if anything is edited here it will need to be edited there too.
	/************************/

	//always ON LEDs panel 3 Pin 16 as an output
	pinMode(16, OUTPUT);

	//Always ON panel 3 LEDs - pin 16 (MEGA)
	digitalWrite(16, HIGH);	

	// 12V lightstrip LEDs 14 Pin as an output
	pinMode(17, OUTPUT);

	//sets landscape tube motor as output -- We'll deal with this in V2
	pinMode(3, OUTPUT);

	//Landscape tube motor off-- We'll deal with this part in V2
	digitalWrite(3, LOW);

	//12V LED strips panel 3 - pin 17 (MEGA)
	digitalWrite(17, HIGH);

	//Clock illumination LED - LED_7_PIN brightness of 80	
	analogWrite(LED_7_PIN, 80);

	//Power crystals set at brightness 10
	analogWrite(LED_12_PIN, 10);

	//Yellow keypad LEDs set at brightnes 40  //added sept 30
	analogWrite(LED_1_PIN, 40);

	// Radar LED starts at brightness 20 
	//pinMode(4, OUTPUT);
	analogWrite(LED_5_PIN, 20);   //LED_5_PIN causes glitches whe its used for analog fading.   

	//Clear the nixie tubes and matrix
	Display::clear_nixie_tube(1);
	Display::clear_nixie_tube(2);
	Display::clear_matrix();
	Display::turn_neopixles_on_or_off(true);

	//Red Pulley LED - pin 23 (quad shifter)
	g_shifter_quad.setPin(23, HIGH);
	g_shifter_quad.write();
	delay(50);

	//Always ON panel 1 LEDs – pin 26 (quad shifter)
	g_shifter_quad.setPin(26, HIGH);
	g_shifter_quad.write();
	delay(50);

	//Pizza oven exterior LEDs - pin 28 (quad shifter)
	g_shifter_quad.setPin(28, HIGH);
	g_shifter_quad.write();
	delay(50);

	//Clock number LEDs 
	g_shifter_quad.setPin(13,HIGH);  //clock number LED 0
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(14,HIGH);  //clock number LED 1
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(15,HIGH);  //clock number LED 2
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(16,HIGH);  //clock number LED 3
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(17,HIGH);  //clock number LED 4
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(18,HIGH);  //clock number LED 5
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(19,HIGH);  //clock number LED 6
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(20,HIGH);  //clock number LED 7
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(21,HIGH);  //clock number LED 8
	g_shifter_quad.write();
	delay(50);
	g_shifter_quad.setPin(22,HIGH);  //clock number LED 9
	g_shifter_quad.write();
	delay(50);

	

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
	delay(6000);

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
	pinMode(TUBA_PLAYER_SOLENOID_PIN, OUTPUT);
	pinMode(SOLENOID_2_PIN, OUTPUT);
	pinMode(SOLENOID_3_PIN, OUTPUT);
	pinMode(SOLENOID_4_PIN, OUTPUT);
	pinMode(PIZZA_OVEN_DOOR_SOLENOID_PIN, OUTPUT);

	//TUBAMAN 7 tuba player that pops out of coo coo clock
	digitalWrite(TUBA_PLAYER_SOLENOID_PIN, LOW);

	//WARNING_BRICKS_MINI 8 miniature version of the warning bricks 
	digitalWrite(SOLENOID_2_PIN, LOW);

	//STAIRS 9 Brass stairs that pop up when cage lifts up
	digitalWrite(SOLENOID_3_PIN, LOW);

	//HANDRAIL 10 Brass handrail door that opens when cage lifts up 
	digitalWrite(SOLENOID_4_PIN, LOW);

	//PIZZA_OVEN_DOOR 11 pizza oven door
	digitalWrite(PIZZA_OVEN_DOOR_SOLENOID_PIN, LOW);

}
/*
	Set the intenal state to a particular state

	:param new_state: the state after this is complete
*/
void StateMachine::set_state(int new_state) {
	switch(new_state) {
  		case 1:
			_pause_state.end();
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
	_display.update_pizza_sign();
	_display.update_pizza_oven();
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
				_keypad.turn_off_displays();
				set_state(4);
			} else {
				_keypad.turn_off_displays();
				set_state(5);
			}

			break;
		case 2:
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
