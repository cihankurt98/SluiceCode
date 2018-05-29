#ifndef SLUICE_H
#define SLUICE_H


#include "HardwareConnection.h"
#include "State.h"
#include "Events.h"

class Sluice {


public:
	Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight, iLock& lock);
	~Sluice();

private:
	State CurrentMainState;
	void HandleEvent(Events ev);
	State HandleStateIdle(Events ev);
	State HandleStateSchutten(Events ev);
	State HandleStateEmergency(Events ev);
	iDoor& door;
	iWaterSensor& waterSensor;
	iTrafficLight& trafficLight;
	iLock& lock;

	void IdleEntryActions();
	void IdleExitActions();
	void SchuttenEntryActions();
	void SchuttenExitActions();
	void EmergencyEntryActions();
	void EmergencyExitActions();


	Sluice(const Sluice& other): door(other.door), waterSensor(other.waterSensor), trafficLight(other.trafficLight), lock(other.lock){};
	Sluice& operator= (const Sluice&) {return *this; };
};

#endif
