#include "TrafficLight.h"

TrafficLight::TrafficLight(HardwareConnection& hardwareConnection)
: hardwareConnection(hardwareConnection)
{
}

std::string TrafficLight::GetTrafficLightStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

bool TrafficLight::SetTrafficLightStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{

		return false;
	}
	return true;
}
