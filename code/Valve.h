#ifndef VALVE_H
#define VALVE_H

#include "iValve.h"

class Valve : public iValve
{
public:
	Valve();
	void GetValveStatus();

	void SetValveStatus();

private:
	// private copy constructor and assignment operator to prevent making copies
	Valve(const Valve&) { /* do nothing */ };
	Valve& operator=(const Valve&) { return *this; };
};
};

#endif
