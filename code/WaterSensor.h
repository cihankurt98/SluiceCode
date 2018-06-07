#ifndef WATERSENSOR_H
#define WATERSENSOR_H

#include "HardwareConnection.h"
#include "interfaces/iWaterSensor.h"

class WaterSensor : public iWaterSensor
{
public:
	WaterSensor(HardwareConnection* const hardwareConnection);
	std::string GetWaterLevel(char message[]);

private:
	HardwareConnection* hardwareConnection;
	// private copy constructor and assignment operator to prevent making copies
	WaterSensor(const WaterSensor&) { /* do nothing */ };
	WaterSensor& operator=(const WaterSensor&) { return *this; };
};

#endif
