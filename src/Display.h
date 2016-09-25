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

class Display {
public:
	Display();
	void init();
	void update(Passcode);
	bool is_complete();

	static void clear_nixie_tube(int);
	static void clear_matrix();
	static void turn_neopixles_on_or_off(bool);

private:
	unsigned long _next_action_time;
	int _next_action;

	void _reset_next_action_time(unsigned long);
	void _generate_passcode_and_advance();
	void _display_next_digit(Passcode, bool);
	void _display_nixie_tube(int, int);
	void _display_led_matrix(int);
	void _display_servo(int);
};


#endif
