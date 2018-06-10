#include "Sluice.h"

#include <iostream>
#include <cstddef>


Sluice::Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight, iEventGenerator& eventGen)
	: currentMainState(Idle)
    , door(door)
	, waterSensor(waterSensor)
	, trafficLight(trafficLight)
	, eventGen(eventGen)
	, schutState(new SchutState(door, waterSensor, trafficLight))
{
	IdleEntryActions();
}

Sluice::~Sluice()
{

}


bool Sluice::Run()
{
	Event ev;
	ev = eventGen.GetEvent();
	std::cout << "Run sluice.cpp ev: " << ev << std::endl;
	HandleEvent(ev);
	return ev != NoEventOccured;
}

void Sluice::HandleEvent(Event ev) {
	switch (currentMainState) {
		case Idle:
			currentMainState = HandleStateIdle(ev);
			break;
		case Schutten:
			currentMainState = HandleStateSchutten(ev);
			break;
		case Emergency:
		std::cout << "Current mainstate is emergency " << std::endl;
			currentMainState = HandleStateEmergency(ev);
			break;
		default:
			std::cerr << "Sluice handle event error mainstate: " << currentMainState << std::endl;
			break;


	};
}

	State Sluice::HandleStateIdle(Event ev)
	{
		State nextState = Idle;
		char msgDoorLeft[] = {"GetDoorLeft;"};
		char msgDoorRight[]= {"GetDoorRight;"};
		char msgTrafficLightGreen[] = {"SetTrafficLight1Green:on;"};
		char msgTrafficLightRed[] = {"SetTrafficLight1Red:off;"};
		std::string doorOpen = "doorOpen;";

		switch (ev) {
			case EV_SCHUTSTART:
				IdleExitActions();
				std::cout << "EV SCHUTSTART" << std::endl;
				nextState = Schutten;
				SchuttenEntryActions();
            case EV_BTNINVARENPRESSED:
				//CHECK WHICH DOOR IS OPEN
				//SET LIGHT 1 OR 4 ON GREEN
            	if(door.GetDoorStatus(msgDoorLeft) == doorOpen)
				{
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
				//else if not allowed. Compiler message: msgDoorRight not used.
				if (door.GetDoorStatus(msgDoorRight) == doorOpen)
				{
					msgTrafficLightGreen[15] = '4';
					msgTrafficLightRed[15] = '4';
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
                break;
            case EV_BTNUITVARENPRESSED:
                //CHECK WHICH DOOR IS OPEN
                //SET LIGHT 2 OR 3 OR GREEN
				if(door.GetDoorStatus(msgDoorLeft) == doorOpen)
				{
					msgTrafficLightGreen[15] = '2';
					msgTrafficLightRed[15] = '2';
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
				//else if not allowed. Compiler message: msgDoorRight not used.
				if (door.GetDoorStatus(msgDoorRight) == doorOpen)
				{
					msgTrafficLightGreen[15] = '3';
					msgTrafficLightRed[15] = '3';
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
                break;

			default:
				//ignored event, nothing to do here.
				// Don't do anything when another event is called.
				break;
		}
		return nextState;
	}

	State Sluice::HandleStateEmergency(Event ev)
	{
		State nextState = Emergency;

		switch (ev) {
			case EV_RESUME:
				break; //was return 0;

			default:
				break;

		}
		return nextState;
	}

	State Sluice::HandleStateSchutten(Event ev) {
		State nextState = Schutten;
		ElevateWaterHighSubState elevateState;

		switch (ev) {
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

				//Schutten substates below
			default:
				schutState->HandleEvent(nextState,elevateState, ev);
				if (nextState != Schutten) {
					SchuttenExitActions();
					switch (nextState) {
						case EV_EMERGENCY:
							nextState = Emergency;
							EmergencyEntryActions();
							break;
						default:
							std::cerr << "ERROR: unhandled state with number: " << nextState;
							break;
					}
				}

				break;

		}
		return nextState;
	}

//PRIVATE METHODS BELOW

	void Sluice::IdleEntryActions()
	{
		//do nothing. This exists for possible expansions to the system.
		std::cout << "Idle entry actions doet niks" << std::endl;
	}
	void Sluice::IdleExitActions()
	{


	}

	void Sluice::SchuttenEntryActions()
	{
		std::cout << "Ik zit in schuttenentryactions" << std::endl;
		schutState->HandlePseudoState();
	}
	void Sluice::SchuttenExitActions() {
		//do nothing. This exists for possible expansions to the system.
	}
	void Sluice::EmergencyEntryActions() {
		//TODO: SET ALL LIGHTS ON RED.
		//HALT DOOR MOVEMENT
		//CHECK DOOR STATUS
		//CLOSE VALVES IF DOORS ARE CLOSED
		//OTHERWISE DO NOTHING AND WAIT FOR RESUME EVENT

	}
	void Sluice::EmergencyExitActions() {
		//do nothing. This exists for possible expansions to the system.
	}

