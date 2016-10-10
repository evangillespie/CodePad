/*
	Class to represent and contol the various display elements

	:Author: Evan Gillespie
*/

#ifndef Display_h
#define Display_h

#include <Shifter.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_NeoPixel.h>

#include "Arduino.h"
#include "Passcode.h"
#include "Pins.h"
#include "Servomanager.h"
#include "SoundManager.h"
#include "LEDFlashManager.h"
#include "LEDFadeManager.h"

extern Shifter g_shifter_quad;
extern ServoManager g_servo_manager;
extern LEDFlashManager g_led_flash_manager;
extern LEDFadeManager g_led_fade_manager;
extern SoundManager g_sound_manager;
extern bool g_pizza_oven_trigger;
extern bool g_pizza_sign_on;


class Display {
public:
	Display();
	void init();
	void update(Passcode);
	bool is_complete();
	void update_pizza_sign();
	void update_pizza_oven();

	static void clear_nixie_tube(int);
	static void clear_matrix();
	static void turn_neopixles_on_or_off(bool);
	static void activate_pizza_sign(bool);
	static void activate_pizza_oven_sequence();

private:
	unsigned long _next_action_time;
	int _next_action;
	unsigned long _next_pizza_sign_time;
	int _pizza_sign_state;
	unsigned long _next_pizza_oven_time;
	int _pizza_oven_state;

	void _reset_next_action_time(unsigned long);
	void _generate_passcode_and_advance();
	void _display_next_digit(Passcode, bool);
	void _display_nixie_tube(int, int);
	void _display_led_matrix(int);
	void _display_servo(int);
	void _move_pizza_sign_servo(int);
	void _trigger_pizza_lights(int);
};


#endif
