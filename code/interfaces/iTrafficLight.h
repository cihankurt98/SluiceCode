#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

#include <string>

class iTrafficLight
{
public:
	virtual ~iTrafficLight() {};

	virtual std::string GetTrafficLightStatus(char message[]) = 0;

	virtual bool SetTrafficLightStatus(char message[]) = 0;
};

#endif
