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

  currentSubState = CloseRightDoor;
  CloseRightDoorEntryActions();
}

void SchutState::HandleEvent(State* superState, Events ev)
{
	if (superState == NULL)
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
    case ElevateWaterLow:
      currentSubState = HandleElevateWaterLow(ev);
    case OpenLeftDoor:
      currentSubState = HandleOpenLeftDoor(ev);
    case OpenRightDoor:
      currentSubState = HandleOpenRightDoor(ev);

    default:
    std::cerr << "ERROR: illegal/unhandled running substate with number: " << currentSubState;
    break;


  };

}

void SchutState::ExitSubStateActions()
{
	// TODO - implement SchutState::ExitActions
}
SubState SchutState::HandleCloseRightDoor(Events ev)
{
    SubState nextSubState = CloseRightDoor;
  switch (ev)
  {
    case EV_RIGHTDOORCLOSED:
      CloseRightDoorExitActions();

      //check waterlevel to determine te elevation direction
      nextSubState = ElevateWaterLow;
      ElevateWaterLowEntryActions();
      break;
    default:
      break;
  }


  return nextSubState;

}
SubState SchutState::HandleCloseLeftDoor(Events ev)
{
  SubState nextSubState = CloseLeftDoor;
switch (ev)
{
  case EV_LEFTDOORCLOSED:
    CloseLeftDoorExitActions();

    //check waterlevel to determine te elevation direction
    nextSubState = ElevateWaterLow;
    ElevateWaterLowEntryActions();
    break;
  default:
    break;
}


return nextSubState;
}
SubState SchutState::HandleElevateWaterHigh(Events ev)
{
  SubState nextSubState = ElevateWaterHigh;
switch (ev)
{
  case EV_WATER_HIGH:
    ElevateWaterHighExitActions();

    nextSubState = OpenRightDoor;
    OpenRightDoorEntryActions();
    break;
  default:
    break;
}


return nextSubState;
}
SubState SchutState::HandleElevateWaterLow(Events ev)
{
  SubState nextSubState = ElevateWaterLow;
switch (ev)
{
  case EV_WATER_LOW:
    ElevateWaterLowExitActions();

    //check waterlevel to determine te elevation direction
    nextSubState = OpenLeftDoor;
    OpenLeftDoorEntryActions();
    break;
  default:
    break;
}


return nextSubState;
}

SubState SchutState::HandleOpenLeftDoor(Events ev)
{
  SubState nextSubState = CloseRightDoor;
switch (ev)
{
  case EV_LEFTDOOROPENED:
    CloseRightDoorExitActions();

    //check waterlevel to determine te elevation direction
    nextSubState = ElevateWaterLow;
    ElevateWaterLowEntryActions();
    break;
  default:
    break;
}


return nextSubState;
}
SubState SchutState::HandleOpenRightDoor(Events ev)
{
  SubState nextSubState = CloseRightDoor;
switch (ev)
{
  case EV_RIGHTDOORCLOSED:
    CloseRightDoorExitActions();

    //check waterlevel to determine te elevation direction
    nextSubState = ElevateWaterLow;
    ElevateWaterLowEntryActions();
    break;
  default:
    break;
}


return nextSubState;
}



//PRIVATE methods

void SchutState::CloseRightDoorEntryActions()
{

}
void SchutState::CloseRightDoorExitActions()
{

}
void SchutState::CloseLeftDoorEntryActions()
{

}
void SchutState::CloseLeftDoorExitActions()
{

}
void SchutState::ElevateWaterHighEntryActions()
{

}
void SchutState::ElevateWaterHighExitActions()
{

}
void SchutState::ElevateWaterLowEntryActions()
{

}
void SchutState::ElevateWaterLowExitActions()
{

}
void SchutState::OpenLeftDoorEntryActions()
{

}
void SchutState::OpenLeftDoorExitActions()
{

}
void SchutState::OpenRightDoorEntryActions()
{

}
void SchutState::OpenRightDoorExitActions()
{

}
