#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H


class iTrafficLight
{
public:
	virtual ~iTrafficLight() {};

	void GetTrafficLightStatus();

	void SetTrafficLightStatus();
};

#endif
