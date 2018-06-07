#ifndef WATERSENSOR_H
#define WATERSENSOR_H

#include "interfaces/iWaterSensor.h"

class WaterSensor
{
public:
	WaterSensor(iWaterSensor& waterSensor);
	std::string GetWaterLevel();

private:
	iWaterSensor& waterSensor;
};

#endif
