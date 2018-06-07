#include "WaterSensor.h"


WaterSensor::WaterSensor(iWaterSensor& waterSensor)
: waterSensor(waterSensor)
{
	//helemaal niks
}

std::string WaterSensor::GetWaterLevel()
{
	char message[] = {"GetWaterLevel;"};
	return waterSensor.GetWaterLevel(message);
}