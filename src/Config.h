/*
	Configuration variables for the whole program

	:Author: Evan Gillespie
*/


#define DEBUG_MODE true

//Length of the passcode in digits
#define CODE_LENGTH 4


// For the random times between when chatacters are displayed
#define MIN_DISPLAY_LAG_TIME 2000
 #define MAX_DISPLAY_LAG_TIME 4000
//#define MIN_DISPLAY_LAG_TIME 100
//#define MAX_DISPLAY_LAG_TIME 500


//Time in seconds before the keypad times out
#define KEYPAD_TIMEOUT_SECS 40
#define KEYPAD_CLR_FLASH_PERIOD 250
#define KEYPAD_OK_FLASH_PERIOD 250


// THE TIME BETWEEN ITERATIONS OF THE WHOLE FLOW CHART
#define MIN_PAUSE_TIME_BETWEEN_RUNS 200000
#define MAX_PAUSE_TIME_BETWEEN_RUNS 210000


// THE NUMBER OF CONNECTED LEDS THAT CAN BE TURNED ON TO FLASH
#define NUM_LED_FLASHERS 12
#define NUM_LED_FADERS 12


// how long (in ms) between steps for fading leds
#define LED_FADE_TIME_INCREMENT 100


// delay between sweeps for the clock in the pause state
#define CLOCK_SWEEP_TIME_DELAY 48000


// Maximum positional error in servo movements to trigger the next substate
#define SERVO_MAXIMUM_ERROR 25


// Destinations for the servo motors

//Keypad door right A

//Keypad door right A closed
#define SERVO_1_POSITION_A 500
//Keypad door right A open
#define SERVO_1_POSITION_B 971

#define SERVO_1_SPEED 17

//Keypad door right B

//Keypad door right B closed
#define SERVO_2_POSITION_A 500
//Keypad door right B open
#define SERVO_2_POSITION_B 29

#define SERVO_2_SPEED 17

//Keypad door left A

//Keypad door left A closed
#define SERVO_3_POSITION_A 874
//Keypad door left A open`
#define SERVO_3_POSITION_B 339

#define SERVO_3_SPEED 20

//Keypad door left B

//Keypad door left B closed
#define SERVO_4_POSITION_A 175
//Keypad door left B open
#define SERVO_4_POSITION_B 710

#define SERVO_4_SPEED 20

// Bricklight

//Bricklight IN
#define SERVO_5_POSITION_A 215
//Bricklight OUT
#define SERVO_5_POSITION_B 820

#define SERVO_5_SPEED 90

//Timer panel

//Timer panel left
#define SERVO_6_POSITION_A 1
//Timer panel right
#define SERVO_6_POSITION_B 1000

#define SERVO_6_SPEED 30

//Warning Bricks IN/OUT

//Warning Bricks IN
#define SERVO_7_POSITION_A 160
//Warning Bricks OUT
#define SERVO_7_POSITION_B 600

#define SERVO_7_SPEED 30

//Warning Bricks rotation

//Warning Bricks rotation closed
#define SERVO_8_POSITION_A 1000
//Warning Bricks rotation open
#define SERVO_8_POSITION_B 1

#define SERVO_8_SPEED 80

//cage riser A

//cage riser A Down
#define SERVO_9_POSITION_A 767
//cage riser A Up
#define SERVO_9_POSITION_B 16

#define SERVO_9_SPEED 30

//Cage Top

//Cage Top Closed
#define SERVO_10_POSITION_A 90
//Cage Top Open
#define SERVO_10_POSITION_B 460

#define SERVO_10_SPEED 30

//Cage left

//Cage left closed
#define SERVO_11_POSITION_A 1023
//Cage left open
#define SERVO_11_POSITION_B 660

#define SERVO_11_SPEED 30

//Cage right

//Cage right closed 
#define SERVO_12_POSITION_A 680
//Cage right open
#define SERVO_12_POSITION_B 340

#define SERVO_12_SPEED 30

//cage riser B

//cage riser B Down
#define SERVO_13_POSITION_A 221
//cage riser B Up
#define SERVO_13_POSITION_B 972

#define SERVO_13_SPEED 30

//clock

//clock clockwise
#define SERVO_14_POSITION_A 50
//clock counter clockwise
#define SERVO_14_POSITION_B 950

#define SERVO_14_SPEED 10

//Streetza Pizza sign

//Streetza Pizza sign chef's mounth neutral
#define SERVO_15_POSITION_A 340
//Streetza Pizza sign chef's mouth open
#define SERVO_15_POSITION_B 550

#define SERVO_15_SPEED 15

//Miniature Keypad door

//Miniature Keypad door closed
#define SERVO_16_POSITION_A 380
//Miniature Keypad door open
#define SERVO_16_POSITION_B 590
	
#define SERVO_16_SPEED 8


// VARIABLES FOR THE TUBA SOUNDS IN THE PAUSE STATE
// minimum time between sounds in a set
#define TUBA_SOUND_SOUND_TIME_MINIMUM 1000
// maximum time between sounds in a set
#define TUBA_SOUND_SOUND_TIME_MAXIMUM 3000
// number of sounds in a set
#define TUBA_SOUND_SOUNDS_IN_SET 4
// minimum time between sets
#define TUBA_SOUND_SET_TIME_MINIMUM 180000
// maximum time between sets
#define TUBA_SOUND_SET_TIME_MAXIMUM 300000
