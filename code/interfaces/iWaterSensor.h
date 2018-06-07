#ifndef IWATERSENSOR_H
#define IWATERSENSOR_H

#include <string>

class iWaterSensor
{
public:
	virtual ~iWaterSensor(){};
	virtual std::string GetWaterLevel(char message[]) = 0;
};

#endif
