/*
	IO pin assignments for the whole program

	:Author: Evan Gillespie
*/

// Any unconnected pin
#define UNCONNECTED_PIN 1


// Keypad pins
#define keypad_number_1 22
#define keypad_number_2 24
#define keypad_number_3 26
#define keypad_number_4 28
#define keypad_number_5 30
#define keypad_number_6 32
#define keypad_number_7 34
#define keypad_number_8 36
#define keypad_number_9 38
#define keypad_number_0 40
#define keypad_number_clr 42
#define keypad_number_ok 48
#define keypad_number_clr_led 39
#define keypad_number_ok_led 41

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

	// ANALOG INPUT pins
#define ANALOG_INPUT_0 A0 //PIR sensor
#define ANALOG_INPUT_1 A1 //Potentiometer 1 for now is keypadGreen pot, NOTE: might change
#define ANALOG_INPUT_2 A2 //Potentiometer 2