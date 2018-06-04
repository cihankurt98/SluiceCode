#include "SchutState.h"
#include <iostream>

SchutState::SchutState(iDoor* door, iWaterSensor* waterSensor, iTrafficLight* trafficLight)
{
	// TODO - implement SchutState::SchutState
  this->door = door;
  this->waterSensor = waterSensor;
  this->trafficLight = trafficLight;
}

void SchutState::HandlePseudoState()
{
	// TODO - implement SchutState::HandlePseudoState
  InitialStateTransitionActions();

  currentSubState = CloseRightDoor;
  CloseRightDoorEntryActions();
}

void SchutState::HandleEvent(State* superState, Events* ev)
{
	if (superState == NULL || ev == NULL)
	{
		std::cout << "kanker zooi" << std::endl;
	}
	else
	{
		std::cout << "yeuy niet null" << std::endl;
	}

  switch (currentSubState) {
    case CloseRightDoor:
      currentSubState = HandleOpenRightDoor(ev);
      break;
    case CloseLeftDoor:
      currentSubState = HandleOpenLeftDoor(ev);
    case ElevateWaterHigh:
      currentSubState = HandleElevateWaterHigh(ev);


  }

}

void SchutState::ExitActions()
{
	// TODO - implement SchutState::ExitActions
}
