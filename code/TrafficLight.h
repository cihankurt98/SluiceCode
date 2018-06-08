#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "HardwareConnection.h"
#include "interfaces/iTrafficLight.h"

class TrafficLight : public iTrafficLight

{

public:
	TrafficLight(HardwareConnection& HardwareConnection);
	std::string GetTrafficLightStatus(char message[]);
	bool SetTrafficLightStatus(char message[]);

private:
	HardwareConnection& hardwareConnection;
};

#endif
