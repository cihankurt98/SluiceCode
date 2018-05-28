#include "Sluice.h"

Sluice::Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight,
	 iLock& lock)
	 : currentState(Idle)
	 , door(door)
	 , waterSensor(waterSensor)
	 , trafficLight(trafficLight)
	 , lock(lock)
{
	IdleEntryActions();
}

BreadBaker::~BreadBaker()
{

}

State Sluice::HandleStateIdle(Events ev)
{
	State nextState = Idle;

	switch (ev)
	{
		case EV_SCHUTSTART:
			IdleExitActions();

			nextState = Schutten;
			SchuttenEntryActions();
		default:
			//ignored event, nothing to do here.
			// Don't do anything when another event is called.
			break;
	}
	return nextState;
}

State Sluice::HandleStateEmergency(Events ev)
{
	State nextState = Emergency;

	switch (ev)
	{
		case EV_RESUME:
		return 0;

		default:
			break;

	}
	return nextState;
}
