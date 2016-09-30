/*
	Class to control Dynamixel Servo Motors

	:Author: Lowell Smith
*/

#ifndef ServoManager_h
#define ServoManager_h

#include "Arduino.h"
#include <DynamixelSerial1.h>

class ServoManager{
	public:
		ServoManager();
		void move_servo(int, int, int); // servo index, final position, speed
		bool is_servo_in_position(int); // servo index

	private:
		int _target_positions[18]; // store the target positions of moving servos
		// using the id of the servos will leave element 0 unouched. Oh well.
};

#endif
