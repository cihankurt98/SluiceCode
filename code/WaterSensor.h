#ifndef WATERSENSOR_H
#define WATERSENSOR_H

#include "HardwareConnection.h"
#include "interfaces/iWaterSensor.h"

class WaterSensor : public iWaterSensor
{
public:
	WaterSensor(HardwareConnection& hardwareConnection);
	std::string GetWaterLevel(char message[]);

private:
	HardwareConnection& hardwareConnection;
};

#endif
