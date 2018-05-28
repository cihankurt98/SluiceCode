#ifndef SLUICE_H
#define SLUICE_H

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
	iWaterSensor& waterSensor;
	iTrafficLight& trafficLight;
	iDoor& door;
	iLock& lock;

	void IdleEntryActions();
	void IdleExitActions();
	void SchuttenEntryActions();
	void SchuttenExitActions();
	void EmergencyEntryActions();
	void EmergencyExitActions();


	Sluice(const Sluice& other): door(other.door), lock(other.lock), waterSensor(other.waterSensor);
	Sluice& operator= (const Sluice&) {return *this; };
};

#endif
