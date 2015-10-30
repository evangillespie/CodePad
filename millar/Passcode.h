/*
	Passcode.h - Library for dealing with the passcodes

	:Author: Evan Gillespie
*/

#ifndef Passcode_h
#define Passcode_h

#include "Arduino.h"

class Passcode
{
  public:
    Passcode();
    void generate();
    int get_passcode();
    int get_digit(int index);

  private:
    int _passcode;
};

#endif