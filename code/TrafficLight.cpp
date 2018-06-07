#include "TrafficLight.h"

TrafficLight::TrafficLight(iTrafficLight& trafficLight)
:trafficLight(trafficLight)
{
	//helemaal niks
}

std::string TrafficLight::GetTrafficLightRedStatus(char message[])
{
	return trafficLight.GetTrafficLightStatus(message);
}

bool TrafficLight::SetTrafficLightStatus(char message[])
{
	return trafficLight.SetTrafficLightStatus(message);
}
