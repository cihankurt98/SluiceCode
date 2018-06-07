#include "SchutState.h"
#include <iostream>

SchutState::SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight)
: door(door)
, waterSensor(waterSensor)
, trafficLight(trafficLight)
{
	// TODO - implement SchutState::SchutState

}

void SchutState::HandlePseudoState()
{
	// TODO - implement SchutState::HandlePseudoState
  // check doorstatus and act accordingly to state machine
  currentSubState = CloseRightDoor;
  CloseRightDoorEntryActions();
}

void SchutState::HandleEvent(State& superState, Events ev)
{
  switch (currentSubState) {
    case CloseRightDoor:
      currentSubState = HandleCloseRightDoor(ev);
      break;
    case CloseLeftDoor:
      currentSubState = HandleCloseLeftDoor(ev);
    case ElevateWaterHigh:
      currentSubState = HandleElevateWaterHigh(ev);
    case ElevateWaterLow:
      currentSubState = HandleElevateWaterLow(ev);
    case OpenLeftDoor:
      currentSubState = HandleOpenLeftDoor(superState,ev);
    case OpenRightDoor:
      currentSubState = HandleOpenRightDoor(superState,ev);

    default:
    std::cerr << "ERROR: illegal/unhandled running substate with number: " << currentSubState;
    break;


  };

}

void SchutState::ExitSubStateActions()
{
	// TODO - implement SchutState::ExitActions
  switch (currentSubState)
  {
    case CloseRightDoor:
      CloseRightDoorExitActions();
      break;
    case CloseLeftDoor:
      CloseLeftDoorExitActions();
      break;
    case ElevateWaterLow:
      ElevateWaterLowExitActions();
      break;
    case ElevateWaterHigh:
      ElevateWaterHighExitActions();
      break;
    case OpenLeftDoor:
      OpenLeftDoorExitActions();
      break;
    case OpenRightDoor:
      OpenRightDoorExitActions();
      break;

    default:
      break;
  }
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

SubState SchutState::HandleOpenLeftDoor(State& superState,Events ev)
{
  SubState nextSubState = CloseRightDoor;
switch (ev)
{
  case EV_LEFTDOOROPENED:
    OpenLeftDoorExitActions();
    superState = Idle;
    break;

  default:

    break;
}


return nextSubState;
}
SubState SchutState::HandleOpenRightDoor(State& superState,Events ev)
{
  SubState nextSubState = CloseRightDoor;
switch (ev)
{
  case EV_RIGHTDOOROPENED:
    OpenRightDoorExitActions();
    superState = Idle;
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
