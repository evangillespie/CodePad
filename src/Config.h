/*
	Configuration variables for the whole program

	:Author: Evan Gillespie
*/


#define DEBUG_MODE true

//Length of the passcode in digits
#define CODE_LENGTH 4


// For the random times between when chatacters are displayed
// #define MIN_DISPLAY_LAG_TIME 1000;
// #define MAX_DISPLAY_LAG_TIME 5000;
#define MIN_DISPLAY_LAG_TIME 100
#define MAX_DISPLAY_LAG_TIME 500


//Time in seconds before the keypad times out
#define KEYPAD_TIMEOUT_SECS 40
#define KEYPAD_CLR_FLASH_PERIOD 250
#define KEYPAD_OK_FLASH_PERIOD 250


// THE TIME BETWEEN ITERATIONS OF THE WHOLE FLOW CHART
#define MIN_PAUSE_TIME_BETWEEN_RUNS 10000
#define MAX_PAUSE_TIME_BETWEEN_RUNS 20000


// THE NUMBER OF CONNECTED LEDS THAT CAN BE TURNED ON TO FLASH
#define NUM_LED_FLASHERS 12
#define NUM_LED_FADERS 12


// how long (in ms) between steps for fading leds
#define LED_FADE_TIME_INCREMENT 100


// Maximum positional error in servo movements to trigger the next substate
#define SERVO_MAXIMUM_ERROR 3


// Destinations for the servo motors
#define SERVO_1_POSITION_A 100
#define SERVO_1_POSITION_B 200
#define SERVO_1_SPEED 50
#define SERVO_2_POSITION_A 100
#define SERVO_2_POSITION_B 200
#define SERVO_2_SPEED 50
#define SERVO_3_POSITION_A 100
#define SERVO_3_POSITION_B 200
#define SERVO_3_SPEED 50
#define SERVO_4_POSITION_A 100
#define SERVO_4_POSITION_B 200
#define SERVO_4_SPEED 50
#define SERVO_5_POSITION_A 100
#define SERVO_5_POSITION_B 200
#define SERVO_5_SPEED 50
#define SERVO_6_POSITION_A 100
#define SERVO_6_POSITION_B 200
#define SERVO_6_SPEED 50
#define SERVO_7_POSITION_A 100
#define SERVO_7_POSITION_B 200
#define SERVO_7_SPEED 50
#define SERVO_8_POSITION_A 100
#define SERVO_8_POSITION_B 200
#define SERVO_8_SPEED 50
#define SERVO_9_POSITION_A 100
#define SERVO_9_POSITION_B 200
#define SERVO_9_SPEED 50
#define SERVO_10_POSITION_A 100
#define SERVO_10_POSITION_B 200
#define SERVO_10_SPEED 50
#define SERVO_11_POSITION_A 100
#define SERVO_11_POSITION_B 200
#define SERVO_11_SPEED 50
#define SERVO_12_POSITION_A 100
#define SERVO_12_POSITION_B 200
#define SERVO_12_SPEED 50
#define SERVO_13_POSITION_A 100
#define SERVO_13_POSITION_B 200
#define SERVO_13_SPEED 50
#define SERVO_14_POSITION_A 100
#define SERVO_14_POSITION_B 200
#define SERVO_14_SPEED 50
#define SERVO_15_POSITION_A 100
#define SERVO_15_POSITION_B 200
#define SERVO_15_SPEED 50
#define SERVO_16_POSITION_A 100
#define SERVO_16_POSITION_B 200
#define SERVO_16_SPEED 50