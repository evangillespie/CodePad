#include "Arduino.h"
#include "PauseState.h"
#include "Config.h"
#include "Pins.h"

/*
	boring empty constructor
*/
PauseState::PauseState(){}



/*
	update the puse state. called ever iteration of the main loop
*/
void PauseState::update() {
	// everything is still working
	if (_system_state == 1){
		_update_clock_sweep();

		if (_is_pir_triggered() == false){
			_system_state = 0;
			_turn_system_off();
		}
	} else {
		if (_is_pir_triggered() == true){
			_system_state = 1;
			_turn_system_on();
		}
	}
}


/*
	turn everything off when the PIR turns off
*/
void PauseState::_turn_system_off(){
	Serial.println("everything turns off!");

	//Turn LEDs off
	digitalWrite(LED_1_PIN, LOW);
	digitalWrite(LED_2_PIN, LOW);
	digitalWrite(LED_3_PIN, LOW);
	digitalWrite(LED_4_PIN, LOW);
	digitalWrite(LED_5_PIN, LOW);
	digitalWrite(LED_6_PIN, LOW);
	digitalWrite(LED_7_PIN, LOW);
	digitalWrite(LED_8_PIN, LOW);
	digitalWrite(LED_9_PIN, LOW);
	digitalWrite(LED_10_PIN, LOW);
	digitalWrite(LED_11_PIN, LOW);
	digitalWrite(LED_12_PIN, LOW);
	digitalWrite(LED_13_PIN, LOW);
	digitalWrite(LED_14_PIN, LOW);

	//Turn servos off, all servos should be in final position 
}


/*
	turn everything on when the PIR turns on
*/
void PauseState::_turn_system_on(){
	Serial.println("everything turns on!");


	/************************/
	//**NOTE** - This is a copy of the "StateMachine::_initialize_system_leds" in Statmachine.cpp if anything is edited here it should be edited there too
	/************************/
	
	// Set LED 14 Pin as an output
	pinMode(LED_14_PIN, OUTPUT);

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
	sweep the clock back and forth.
*/
void PauseState::_update_clock_sweep(){
	if (g_servo_manager.is_servo_in_position(14)){
		if (_clock_sweep_dir == 0){
			g_servo_manager.move_servo(14, SERVO_14_POSITION_B, SERVO_14_SPEED);
			_clock_sweep_dir = 1;
		} else {
			g_servo_manager.move_servo(14, SERVO_14_POSITION_A, SERVO_14_SPEED);
			_clock_sweep_dir = 0;
		} 
	}
}

/*
	return true if this state is done and we should move on
*/
bool PauseState::is_complete() {
	if (millis() >= _complete_time && _is_pir_triggered() == true){
		if (_system_state == 0){
			_system_state = 1;
			_turn_system_on();
		}
		return true;
	}
	return false;
}


/*
	return true if the PIR sensor has been triggered
*/
bool PauseState::_is_pir_triggered(){
	return digitalRead(PIR_INPUT);
}


/*
	start the pause
*/
void PauseState::begin() {
	_clock_sweep_dir = 0;
	_system_state = 1;
	_complete_time = millis() + random(MIN_PAUSE_TIME_BETWEEN_RUNS, MAX_PAUSE_TIME_BETWEEN_RUNS + 1);
}