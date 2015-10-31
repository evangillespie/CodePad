#include "Arduino.h"
#include "Passcode.h"

/*
	constructor for Passcode objects
*/
Passcode::Passcode()
{
	randomSeed(analogRead(1));	// make sure this is always reading an unconnected pin
	_passcode = 0;
	generate();
}


/*
	generate a 4 digit random number and store it
*/
void Passcode::generate()
{
	_passcode = random(0, 10000);
}


/*
	return the passcode variable
*/
int Passcode::get_passcode()
{
	return _passcode;
}


/*
	return a digit from the passcode at a particular index
	index from 0 to 3
*/
int Passcode::get_digit(int index)
{
	int num;
	num = (int) (_passcode / pow(10, 3 - index));
	return (int)num % 10;
}