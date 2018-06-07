#include "Sluice.h"
#include <iostream>
#include <cstddef>

Sluice::Sluice(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight)
	: door(door)
	, waterSensor(waterSensor)
	, trafficLight(trafficLight)
	, schutState(new SchutState(door, waterSensor, trafficLight))
{
	IdleEntryActions();
}

Sluice::~Sluice()
{

}
void Sluice::HandleEvent(Events ev) {
	switch (CurrentMainState) {
		case Idle:
			CurrentMainState = HandleStateIdle(ev);
			break;
		case Schutten:
			CurrentMainState = HandleStateSchutten(ev);
		case Emergency:
			CurrentMainState = HandleStateEmergency(ev);

		default:
			std::cerr << "ERROR: illegal/unhandled running state with number: " << CurrentMainState;
			break;


	};
}

	State Sluice::HandleStateIdle(Events ev) {
		State nextState = Idle;

		switch (ev) {
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

	State Sluice::HandleStateEmergency(Events ev) {
		State nextState = Emergency;

		switch (ev) {
			case EV_RESUME:
				break; //was return 0;

			default:
				break;

		}
		return nextState;
	}

	State Sluice::HandleStateSchutten(Events ev) {
		State nextState = Schutten;

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
				schutState->HandleEvent(nextState, ev);
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

	void Sluice::IdleEntryActions() {
		//do nothing. This exists for possible expansions to the system.
	}
	void Sluice::IdleExitActions() {


	}

	void Sluice::SchuttenEntryActions() {
		//do nothing. This exists for possible expansions to the system.
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

