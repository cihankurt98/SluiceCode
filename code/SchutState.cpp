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
  HandleElevateHighSubstates(elevateState,ev);
  OpenValve3ExitActions();
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
void SchutState::HandleElevateHighSubstates(ElevateWaterHighSubState& elevateState,Events ev)
{
  elevateState = OpenValve1;
  switch (ev)
  {
    case EV_WATERLEVEL_ABOVE_VALVE2:
      OpenValve1ExitActions();

          elevateState = OpenValve2;
          OpenValve2EntryActions();
          break;
    case EV_WATERLEVEL_ABOVE_VALVE3:
      OpenValve2ExitActions();

          elevateState = OpenValve3;
          OpenValve3EntryActions();
    default:
      break;

  }
}

void SchutState::CloseRightDoorEntryActions()
{
  //ENTRY: rightdoor.close();
  char message[] = {"SetDoorRight:close;"};
  door.SetDoorStatus(message);

  //leftdoor trafficlights red
  char tlMessage1[] = {"SetTrafficLight1Red:on;"};
  char tlMessage2[] = {"SetTrafficLight1Green:off;"};

  for (int i = 1; i < 3; i++)
  {
    tlMessage1[15] = i;
    trafficLight.SetTrafficLightStatus(tlMessage1);
    tlMessage2[15] = i;
    trafficLight.SetTrafficLightStatus(tlMessage2);
  }

  
}
void SchutState::CloseRightDoorExitActions()
{
  //nothing
}
void SchutState::CloseLeftDoorEntryActions()
{
  //ENTRY: leftdoor.close;
  char message[] = {}
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
void SchutState::OpenValve1EntryActions()
{
  //do nothing
}
void SchutState::OpenValve1ExitActions()
{
  //do nothing
}
void SchutState::OpenValve2EntryActions()
{
  //open middle valve
}
void SchutState::OpenValve2ExitActions()
{
  //do nothing
}
void SchutState::OpenValve3EntryActions()
{
  //open highest valve
}
void SchutState::OpenValve3ExitActions()
{
  //do nothing
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
