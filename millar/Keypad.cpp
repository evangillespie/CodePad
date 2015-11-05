#include "Arduino.h"
#include "Keypad.h"


/*
	Constructor. Generic. Boring
*/
Keypad::Keypad() {}


/*
	check the keypad status
	called every main loop
*/
void Keypad::update() {
	Serial.println("keypad!");
}