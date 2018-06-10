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


void Sluice::Run()
{
	Event ev;
	while (true)
	{
	ev = eventGen.GetEvent();
	HandleEvent(ev);
	}
}

void Sluice::HandleEvent(Event ev)
{
	switch (currentMainState)
	{
		case Idle:
		currentMainState = HandleStateIdle(ev);
			break;
		case Schutten:
		std::cout << "Schutten" << std::endl;
		currentMainState = HandleStateSchutten(ev);
			break;
		case Emergency:
		std::cout << "Emergency" << std::endl;
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
		char msgTrafficLightGreen[] = {"SetTrafficLight1Green:on;"};
		char msgTrafficLightRed[] = {"SetTrafficLight1Red:off;"};
		std::string doorOpen = "doorOpen;";
		switch (ev) {
			case EV_SCHUTSTART:
				IdleExitActions();
				nextState = Schutten;
				SchuttenEntryActions();
				break;
            case EV_BTNINVARENPRESSED:
				//CHECK WHICH DOOR IS OPEN
				//SET LIGHT 1 OR 4 ON GREEN
            SetAllLightsRed();
            	if(door.GetDoorStatusLeft() == doorOpen)
				{
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
				//else if not allowed. Compiler message: msgDoorRight not used.
				if (door.GetDoorStatusRight() == doorOpen)
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
            SetAllLightsRed();
				if(door.GetDoorStatusLeft() == doorOpen)
				{
					msgTrafficLightGreen[15] = '2';
					msgTrafficLightRed[15] = '2';
					trafficLight.SetTrafficLightStatus(msgTrafficLightRed);
					trafficLight.SetTrafficLightStatus(msgTrafficLightGreen);
				}
				//else if not allowed. Compiler message: msgDoorRight not used.
				if (door.GetDoorStatusRight() == doorOpen)
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
			std::cout << "resume pressed ev case" << std::endl; 
			nextState = Schutten;
			schutState->Resume();
				break;

			default:
				break;

		}
		return nextState;
	}

	State Sluice::HandleStateSchutten(Event ev)
	{
		State nextState = Schutten;
		ElevateWaterHighSubState elevateState;

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
			EmergencyEntryActions();
			nextState = Emergency;
			break;
				//Schutten substates below
			default:
 				schutState->HandleEvent(nextState,elevateState, ev);
				if (nextState != Schutten)
				{
					SchuttenExitActions();
				}
				break;
		}
		return nextState;
	}


//PRIVATE METHODS BELOW

	void Sluice::IdleEntryActions(){}
	void Sluice::IdleExitActions(){}

	void Sluice::SchuttenEntryActions()
	{
		schutState->HandlePseudoState();
	}
	void Sluice::SchuttenExitActions() {
		//do nothing. This exists for possible expansions to the system.
	}
	void Sluice::EmergencyEntryActions() {
		//TODO: SET ALL LIGHTS ON RED.
		//HALT DOOR MOVEMENT
		//CLOSE VALVES 
		SetAllLightsRed();
		HaltAllDoors();
	}
	void Sluice::EmergencyExitActions() {
		//do nothing. This exists for possible expansions to the system.
	}

	void Sluice::SetAllLightsRed()
	{

		char msgTL1GreenOff[] = {"SetTrafficLight1Green:off;"};
		char msgTL2GreenOff[] = {"SetTrafficLight2Green:off;"};
		char msgTL3GreenOff[] = {"SetTrafficLight3Green:off;"};
		char msgTL4GreenOff[] = {"SetTrafficLight4Green:off;"};

		trafficLight.SetTrafficLightStatus(msgTL1GreenOff);
		trafficLight.SetTrafficLightStatus(msgTL2GreenOff);
		trafficLight.SetTrafficLightStatus(msgTL3GreenOff);
		trafficLight.SetTrafficLightStatus(msgTL4GreenOff);
		
		char msgTL1RedOn[] = {"SetTrafficLight1Red:on;"};
		char msgTL2RedOn[] = {"SetTrafficLight2Red:on;"};
		char msgTL3RedOn[] = {"SetTrafficLight3Red:on;"};
		char msgTL4RedOn[] = {"SetTrafficLight4Red:on;"};

		trafficLight.SetTrafficLightStatus(msgTL1RedOn);
		trafficLight.SetTrafficLightStatus(msgTL2RedOn);
		trafficLight.SetTrafficLightStatus(msgTL3RedOn);
		trafficLight.SetTrafficLightStatus(msgTL4RedOn);
	}

	void Sluice::HaltAllDoors()
	{

		door.SetDoorStatusLeftClose();
		door.SetDoorStatusRightClose();

		char msgDoorLeftCloseValve1[] = {"SetDoorLeftValve1:close;"};
		door.SetValveStatus(msgDoorLeftCloseValve1);
		// valve 2 and 3 never open up on the left side.
		char msgDoorRightCloseValve1[] = {"SetDoorRightValve1:close;"};
		char msgDoorRightCloseValve2[] = {"SetDoorRightValve2:close;"};
		char msgDoorRightCloseValve3[] = {"SetDoorRightValve3:close;"};
		door.SetValveStatus(msgDoorRightCloseValve1);
		door.SetValveStatus(msgDoorRightCloseValve2);
		door.SetValveStatus(msgDoorRightCloseValve3);

	}