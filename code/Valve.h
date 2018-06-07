#ifndef VALVE_H
#define VALVE_H

#include "HardwareConnection.h"
#include "interfaces/iValve.h"

class Valve : public iValve
{
public:
	Valve(HardwareConnection* const hardwareConnection);
	std::string GetValveStatus(char message[]);

	bool SetValveStatus(char message[]);

private:
	HardwareConnection* hardwareConnection;
	// private copy constructor and assignment operator to prevent making copies
	Valve(const Valve&) { /* do nothing */ };
	Valve& operator=(const Valve&) { return *this; };
};

#endif
