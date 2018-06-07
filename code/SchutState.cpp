#include "SchutState.h"
#include <iostream>

SchutState::SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight)
: door(door)
, waterSensor(waterSensor)
, trafficLight(trafficLight)
{

}

void SchutState::HandlePseudoState()
{
	// TODO - implement SchutState::HandlePseudoState





  //DIT KLOPT NOT NIET. DIT MOET DE CHOICE BLOCK AAN HET BEGIN VOORSTELLEN
  // check doorstatus and act accordingly to state machine
  currentSubState = CloseRightDoor;
  CloseRightDoorEntryActions();
}

void SchutState::HandleEvent(State& superState, ElevateWaterHighSubState& elevateState, Events ev)
{
  switch (currentSubState) {
    case CloseRightDoor:
      currentSubState = HandleCloseRightDoor(ev);
      break;
    case CloseLeftDoor:
      currentSubState = HandleCloseLeftDoor(ev);
    case ElevateWaterHigh:
      currentSubState = HandleElevateWaterHigh(elevateState,ev);
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
SubState SchutState::HandleElevateWaterHigh(ElevateWaterHighSubState& elevateState,Events ev)
{
  SubState nextSubState = ElevateWaterHigh;
switch (ev)
{
  case EV_WATER_HIGH:
    ElevateWaterHighExitActions();
    elevateState = OpenValve1;

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
  //ENTRY: rightdoor.close();

  //leftdoor trafficlights red
}
void SchutState::CloseRightDoorExitActions()
{
  //nothing
}
void SchutState::CloseLeftDoorEntryActions()
{
  //ENTRY: leftdoor.close;
  //leftdoor trafficlights red
}
void SchutState::CloseLeftDoorExitActions()
{
  //nothing
}
void SchutState::ElevateWaterHighEntryActions()
{
  //ENTRY: lowest valve open

}
void SchutState::ElevateWaterHighExitActions()
{
  //EXIT: close all valves
}
void SchutState::ElevateWaterLowEntryActions()
{
  //ENTRY: open lowest valve
}
void SchutState::ElevateWaterLowExitActions()
{
  //EXIT: close lowest valve
}
void SchutState::OpenLeftDoorEntryActions()
{
  //Leftdoor.open
}
void SchutState::OpenLeftDoorExitActions()
{
  //leftdoor trafficlights green
}
void SchutState::OpenRightDoorEntryActions()
{
  //Rightdoor.open
}
void SchutState::OpenRightDoorExitActions()
{
  //rightdoor trafficlights green
}
