/*
	Class to control Dynamixel Servo Motors

	:Author: Lowell Smith
*/

#ifndef ServoManager_h
#define ServoManager_h

#include "Arduino.h"

class ServoManager{
	public:
		ServoManager();
		void move_servo(int, int, int); // servo index, final position, speed
		int read_servo(int); // servo index, read servo position
};

#endif
