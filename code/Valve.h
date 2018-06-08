#ifndef VALVE_H
#define VALVE_H

#include "HardwareConnection.h"
#include "interfaces/iValve.h"

class Valve : public iValve
{
public:
	Valve(HardwareConnection& hardwareConnection);
	std::string GetValveStatus(char message[]);

	bool SetValveStatus(char message[]);

private:
	HardwareConnection& hardwareConnection;
};

#endif
