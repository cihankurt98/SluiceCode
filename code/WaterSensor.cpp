#include "WaterSensor.h"


WaterSensor::WaterSensor(HardwareConnection* const hardwareConnection)
{
	this->hardwareConnection = hardwareConnection;
}

std::string WaterSensor::GetWaterLevel(char message[])
{
	int size = strlen(message);
	return hardwareConnection->Transmit(message, size, 0);
}
