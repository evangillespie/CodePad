/*
	Base class for a linear sequence of events with pauses between

	:Author: Evan Gillespie
*/

#ifndef Procedure_State_h
#define Procedure_State_h

#include "Arduino.h"

class ProcedureState {
public:
	ProcedureState();
	void update();
	bool is_complete();
	void reset();

protected:
	int _state_num;
	bool _is_currently_in_pause;
	long _next_update_time;
	bool _is_procedure_complete;
	int _max_state;
	int _substate;
	unsigned long _stored_time;

	void _increment_state();

private:
	virtual void _dispatcher();
	virtual long _get_pause_length(int);
	virtual int _get_max_state();
};

#endif
