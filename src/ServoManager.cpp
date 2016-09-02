#include "ServoManager.h"
#include "Arduino.h"


/*
	Constructor. Generic. Boring
*/
ServoManager::ServoManager() {
	Dynamixel.begin(1000000);
}


/*
	Move a particular servo to a position at a speed

	:param servo_id: the servo to move
	:param position: the final position to move to
	:param speed: how fast to move

	:return
*/
void ServoManager::move_servo(int servo_id, int position, int speed){
	Dynamixel.moveSpeed(servo_id, position, speed);
	_target_positions[servo_id] = position;
}


/*
	check if the servo is in it's target position

	:param servo_id: which servo are we checking?

	:return: true if it's in position. fale otherwise
*/
bool ServoManager::is_servo_in_position(int servo_id){
	if (
		abs(
			Dynamixel.readPosition(servo_id) - _target_positions[servo_id]
			) <= SERVO_MAXIMUM_ERROR
		){
		return true;
	}
	return false;
}
