#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "HardwareConnection.h"
#include "interfaces/iTrafficLight.h"

class TrafficLight : public iTrafficLight

{

public:
	TrafficLight(HardwareConnection* const hardwareConnection);
	std::string GetTrafficLightStatus(char message[], int size);
	bool SetTrafficLightStatus(char message[], int size);

private:
	HardwareConnection* hardwareConnection;
	// private copy constructor and assignment operator to prevent making copies
	TrafficLight(const TrafficLight&) { /* do nothing */ };
	TrafficLight& operator=(const TrafficLight&) { return *this; };
};

#endif
