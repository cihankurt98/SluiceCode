#ifndef SLUICE_H
#define SLUICE_H

#include "SchutState.h"
#include "interfaces/iEventGenerator.h"

class Sluice {


public:
	Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight,
		iEventGenerator& eventGen);
	~Sluice();

	bool Run();


private:
	State currentMainState;
	iDoor& door;
	iWaterSensor& waterSensor;
	iTrafficLight& trafficLight;
	iEventGenerator& eventGen;
	SchutState* schutState;


	void HandleEvent(Event ev);
	State HandleStateIdle(Event ev);
	State HandleStateSchutten(Event ev);
	State HandleStateEmergency(Event ev);
	void IdleEntryActions();
	void IdleExitActions();
	void SchuttenEntryActions();
	void SchuttenExitActions();
	void EmergencyEntryActions();
	void EmergencyExitActions();


};

#endif
