#include "TrafficLight.h"

TrafficLight::TrafficLight(HardwareConnection* const hardwareConnection)
{
	this->hardwareConnection = hardwareConnection;
}

std::string TrafficLight::GetTrafficLightStatus(char message[], int size)
{
	return hardwareConnection->Transmit(message, size, 0);
}

bool TrafficLight::SetTrafficLightStatus(char message[], int size)
{
	if ("ack" != hardwareConnection->Transmit(message, size, 0))
	{

		return false;
	}
	return true;
}
