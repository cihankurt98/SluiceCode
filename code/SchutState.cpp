#include "SchutState.h"

SchutState::SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight)
{
	// TODO - implement SchutState::SchutState
  this->door = door;
  this->waterSensor = waterSensor;
  this->trafficLight = trafficLight;
}

void SchutState::HandlePseudoState()
{
	// TODO - implement SchutState::HandlePseudoState
}

void SchutState::HandleEvent(State superState, Events ev)
{
	// TODO - implement SchutState::HandleEvent
  superstate = Idle;
  ev = EV_EMERGENCY;
}

void SchutState::ExitActions()
{
	// TODO - implement SchutState::ExitActions
}
