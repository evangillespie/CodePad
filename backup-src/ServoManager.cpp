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
}


/*
	Get the position of a particular servo

	:param servo_id: the servo to check

	:return: the position of the servo
*/
int ServoManager::read_servo(int servo_id){
	return Dynamixel.readPosition(servo_id);
}