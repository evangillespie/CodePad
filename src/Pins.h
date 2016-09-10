/*
	IO pin assignments for the whole program

	:Author: Evan Gillespie
*/

// Any unconnected pin
#define UNCONNECTED_PIN A0


// Keypad pins
#define KEYPAD_NUMBER_1 22
#define KEYPAD_NUMBER_2 24
#define KEYPAD_NUMBER_3 26
#define KEYPAD_NUMBER_4 28
#define KEYPAD_NUMBER_5 30
#define KEYPAD_NUMBER_6 32
#define KEYPAD_NUMBER_7 34
#define KEYPAD_NUMBER_8 36
#define KEYPAD_NUMBER_9 38
#define KEYPAD_NUMBER_0 40
#define KEYPAD_NUMBER_CLR 42
#define KEYPAD_NUMBER_OK 48
#define KEYPAD_NUMBERS_LED 44
#define KEYPAD_NUMBER_CLR_LED 39
#define KEYPAD_NUMBER_OK_LED 41

#define KEYPAD_DISPLAY_WRITE_PIN A6
#define KEYPAD_DISPLAY_A1_PIN A7
#define KEYPAD_DISPLAY_A2_PIN A8
#define KEYPAD_DISPLAY_D0_PIN A11
#define KEYPAD_DISPLAY_D1_PIN A13
#define KEYPAD_DISPLAY_D2_PIN A15
#define KEYPAD_DISPLAY_D3_PIN A14
#define KEYPAD_DISPLAY_D4_PIN A12
#define KEYPAD_DISPLAY_D5_PIN A10
#define KEYPAD_DISPLAY_D6_PIN A9

// Pin offsets in the DUAL SHIFT REGISTER to control LEDs that 
// show if the keypad pressed are right or wrong
// correct pins are [correct_offset:correct_offset + 3]
#define KEYPAD_RIGHT_WRONG_LED_1_CORRECT_OFFSET 0
#define KEYPAD_RIGHT_WRONG_LED_1_INCORRECT_OFFSET 4	

// Nixie Tube Shift register
#define NIXIE_TUBE_1_PIN_OFFSET 16
#define NIXIE_TUBE_2_PIN_OFFSET 20

// LED pins
#define LED_1_PIN 2  //yellow LEDs aka keypad Yellow
#define LED_2_PIN 16 //LED Panel#3
#define LED_3_PIN 23 //Warning Brick LED
#define LED_4_PIN 25 //Warning Finger LED
#define LED_5_PIN 27 //Button 3 LED
#define LED_6_PIN 29 //Button 2 LED
#define LED_7_PIN 31 //Button 1 LED
#define LED_8_PIN 39 //CLR LED
#define LED_9_PIN 41 //OK LED
#define LED_10_PIN 43 //Keypad LED aka Keypad MOSFET aka Keypad various LED control
#define LED_11_PIN 45 //Keypad Green LED aka Green light bars
#define LED_12_PIN 46 //power crystal
#define LED_13_PIN 44 //KEYPAD_NUMBERS_LED	
#define LED_14_PIN 17 // 12V LED strips 	

// Shift register pins
#define QUAD_SHIFT_REGISTER_LCLOCK_PIN A4
#define QUAD_SHIFT_REGISTER_CLOCK_PIN A5
#define QUAD_SHIFT_REGISTER_SER_IN_PIN A3

#define DUAL_SHIFT_REGISTER_LCLOCK_PIN 47
#define DUAL_SHIFT_REGISTER_CLOCK_PIN 49
#define DUAL_SHIFT_REGISTER_SER_IN_PIN 50

// ANALOG INPUT pins
#define PIR_INPUT A0 //PIR sensor
#define ANALOG_INPUT_1 A1 //Potentiometer 1 for now is keypadGreen pot, NOTE: might change
#define ANALOG_INPUT_2 A2 //Potentiometer 2

// Solenoid Pins 

#define SOLENOID_1_PIN 7 //tuba player that pops out of coo coo clock
#define SOLENOID_2_PIN 8 //miniature version of the warning bricks
#define SOLENOID_3_PIN 9 //Brass stairs that pop up when cage lifts up
#define SOLENOID_4_PIN 10 //Brass handrail door that opens when cage lifts up
#define SOLENOID_5_PIN 11 //pizza oven door
