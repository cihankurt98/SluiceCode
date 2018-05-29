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

Sluice::~Sluice()
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

State Sluice::HandleStateSchutten(Events ev)
{
	State nextState = Schutten;

	switch (ev)
	{
		//handle on Schutten level
		case EV_RIGHTDOOROPENED:
			SchuttenExitActions();

			nextState = Idle;
			IdleEntryActions();
			break;

		case EV_LEFTDOOROPENED:
			SchuttenExitActions();

			nextState = Idle;
			break;
		case EV_EMERGENCY:
			SchuttenExitActions();

			nextState = Emergency;
			EmergencyEntryActions();

		default:
			break;

	}
}

//PRIVATE METHODS BELOW

void Sluice::IdleEntryActions()
{
	//do nothing. This exists for possible expansions to the system.
}
void Sluice::IdleExitActions()
{
	//TODO: CHECK BOTH DOOR STATUS AND CLOSE THEM IF THEY ARE OPENED
}
void Sluice::SchuttenEntryActions()
{
	//do nothing. This exists for possible expansions to the system.
}
void Sluice::SchuttenExitActions()
{
	//do nothing. This exists for possible expansions to the system.
}
void Sluice::EmergencyEntryActions()
{
	//TODO: SET ALL LIGHTS ON RED.
	//HALT DOOR MOVEMENT
	//CHECK DOOR STATUS
	//CLOSE VALVES IF DOORS ARE CLOSED
	//OTHERWISE DO NOTHING AND WAIT FOR RESUME EVENT

}
void Sluice::EmergencyExitActions()
{
	//do nothing. This exists for possible expansions to the system.
}
