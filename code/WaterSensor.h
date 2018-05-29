#ifndef WATERSENSOR_H
#define WATERSENSOR_H

#include "interfaces/iWaterSensor.h"

class WaterSensor : public iWaterSensor
{
public:
	WaterSensor();


	void GetWaterLevel();

private:
	// private copy constructor and assignment operator to prevent making copies
	WaterSensor(const WaterSensor&) { /* do nothing */ };
	WaterSensor& operator=(const WaterSensor&) { return *this; };
};

#endif
