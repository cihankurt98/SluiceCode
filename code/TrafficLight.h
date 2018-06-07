#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "interfaces/iTrafficLight.h"

class TrafficLight

{

public:
	TrafficLight(iTrafficLight& trafficLight);
	std::string GetTrafficLightRedStatus(char message[]);
	bool SetTrafficLightStatus(char message[]);

private:
	iTrafficLight& trafficLight;
};

#endif
