/*
	Class to control a single flashing led

	:Author: Evan Gillespie
*/

#ifndef LEDFader_h
#define LEDFader_h

#include "Arduino.h"

class LEDFader{
	public:
		LEDFader();
		void init(int, int);
		void start_fading(int, int, int);
		bool is_fading();
		void update();
	private:
		int _index;
		int _pin;
		bool _is_active;
		double _slope;
		int _value;
		int _final_value;
		unsigned long _last_update;
};

#endif