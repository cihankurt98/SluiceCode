#ifndef SLUICE_H
#define SLUICE_H



#include "State.h"
#include "Events.h"
#include "interfaces/iDoor.h"
#include "interfaces/iWaterSensor.h"
#include "interfaces/iTrafficLight.h"
#include "SchutState.h"


class Sluice {


public:
	Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight);
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
	SchutState* schutState;

	void IdleEntryActions();
	void IdleExitActions();
	void SchuttenEntryActions();
	void SchuttenExitActions();
	void EmergencyEntryActions();
	void EmergencyExitActions();


	//Sluice(const Sluice& other): door(other.door), waterSensor(other.waterSensor), trafficLight(other.trafficLight), lock(other.lock){};
	Sluice& operator= (const Sluice&) {return *this; };
};

#endif
