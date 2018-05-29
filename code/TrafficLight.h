#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "iTrafficLight"

class TrafficLight : public iTrafficLight

{

public:
	TrafficLight();
	void GetTrafficLightStatus();
	void SetTrafficLightStatus();

private:
	// private copy constructor and assignment operator to prevent making copies
	TrafficLight(const TrafficLight&) { /* do nothing */ };
	TrafficLight& operator=(const TrafficLight&) { return *this; };
};

#endif
