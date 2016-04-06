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
#define NUM_LED_FLASHERS 3