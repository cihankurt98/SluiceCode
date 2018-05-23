#ifndef SLUICE_H
#define SLUICE_H

class Sluice {


public:
	Sluice(iDoor& door, i WaterSensor& waterSensor, iTrafficLight& trafficLight, iLock& lock);
	~Sluice();

private:
	State CurrentMainState;

};

#endif
