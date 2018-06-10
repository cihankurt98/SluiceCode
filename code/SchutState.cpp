#include "SchutState.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

SchutState::SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight)
  : door(door)
  , waterSensor(waterSensor)
  , trafficLight(trafficLight)
{

}

void SchutState::HandlePseudoState()
{
  // TODO - implement SchutState::HandlePseudoState
  LightsRightRed();
  std::string doorOpen = "doorOpen;";
  std::string doorClosed = "doorClosed;";


  //DIT KLOPT NOT NIET. DIT MOET DE CHOICE BLOCK AAN HET BEGIN VOORSTELLEN
  // check doorstatus and act accordingly to state machine
  //Zet ook alle trafficlights op rood
  char getWaterLevel[] = {"GetWaterLevel;"};
  char low[] = {"low;"};
  char high[] = {"high;"};
  if (door.GetDoorStatusRight() == doorOpen)
  {
    currentSubState = CloseRightDoor;
    CloseRightDoorEntryActions();
  }
  else if (door.GetDoorStatusLeft() == doorOpen)
  {
    currentSubState = CloseLeftDoor;
    CloseLeftDoorEntryActions();
  }

  else if (door.GetDoorStatusRight() == doorClosed && door.GetDoorStatusLeft() == doorClosed && waterSensor.GetWaterLevel(getWaterLevel) == low )
  {
    currentSubState = ElevateWaterHigh;
    ElevateWaterHighEntryActions();
  }
  else if (door.GetDoorStatusRight() == doorClosed && door.GetDoorStatusLeft() == doorClosed && waterSensor.GetWaterLevel(getWaterLevel) == high )
  {
    currentSubState = ElevateWaterLow;
    ElevateWaterLowEntryActions();
  }
}

void SchutState::HandleEvent(State& superState, ElevateWaterHighSubState& elevateState, Event ev)
{
  switch (currentSubState) {
  case CloseRightDoor:
    currentSubState = HandleCloseRightDoor(ev);
    break;
  case CloseLeftDoor:
    currentSubState = HandleCloseLeftDoor(ev);
    break;
  case ElevateWaterHigh:
    currentSubState = HandleElevateWaterHigh(elevateState, ev);
    break;
  case ElevateWaterLow:
    currentSubState = HandleElevateWaterLow(ev);
    break;
  case OpenLeftDoor:
    currentSubState = HandleOpenLeftDoor(superState, ev);
    break;
  case OpenRightDoor:
    currentSubState = HandleOpenRightDoor(superState, ev);
    break;

  default:
    std::cerr << "Schutstate handle event error mainstate:  " << currentSubState << std::endl;
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
SubState SchutState::HandleCloseRightDoor(Event ev)
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

SubState SchutState::HandleCloseLeftDoor(Event ev)
{
  SubState nextSubState = CloseLeftDoor;
  switch (ev)
  {
  case EV_LEFTDOORCLOSED:
    CloseLeftDoorExitActions();

    //check waterlevel to determine te elevation direction
    nextSubState = ElevateWaterHigh;
    ElevateWaterHighEntryActions();
    break;
  default:
    break;
  }
  return nextSubState;
}

SubState SchutState::HandleElevateWaterHigh(ElevateWaterHighSubState& elevateState, Event ev)
{
  SubState nextSubState = ElevateWaterHigh;
  HandleElevateHighSubstates(elevateState, ev);
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
SubState SchutState::HandleElevateWaterLow(Event ev)
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

SubState SchutState::HandleOpenLeftDoor(State& superState, Event ev)
{
  SubState nextSubState = OpenLeftDoor;
  switch (ev)
  {
  case EV_LEFTDOOROPENED:
    superState = Idle;
    OpenLeftDoorExitActions();
    break;

  default:

    break;
  }
  return nextSubState;
}
SubState SchutState::HandleOpenRightDoor(State& superState, Event ev)
{
  SubState nextSubState = OpenRightDoor;
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
void SchutState::HandleElevateHighSubstates(ElevateWaterHighSubState& elevateState, Event ev)
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
  door.SetDoorStatusRightClose();
  //leftdoor trafficlights red
    LightsLeftRed();
}

void SchutState::CloseRightDoorExitActions(){}

void SchutState::CloseLeftDoorEntryActions()
{
  //ENTRY: leftdoor.close;
  door.SetDoorStatusLeftClose();

  //leftdoor trafficlights red
  LightsLeftRed();
}
void SchutState::CloseLeftDoorExitActions(){}

void SchutState::ElevateWaterHighEntryActions()
{
  //ENTRY: lowest valve open
  char message[] = {"SetDoorRightValve1:open;"};
  door.SetValveStatus(message);
}

void SchutState::OpenValve1EntryActions(){}
void SchutState::OpenValve1ExitActions(){}
void SchutState::OpenValve2EntryActions()
{
  //open middle valve
  char message[] = {"SetDoorRightValve2:open;"};
  door.SetValveStatus(message);
}

void SchutState::OpenValve2ExitActions(){}
void SchutState::OpenValve3EntryActions()
{
  //open highest valve
  char message[] = {"SetDoorRightValve3:open;"};
  door.SetValveStatus(message);
}
void SchutState::OpenValve3ExitActions(){}

void SchutState::ElevateWaterHighExitActions()
{
  char messageValve1[] = {"SetDoorRightValve1:close;"};
  char messageValve2[] = {"SetDoorRightValve2:close;"};
  char messageValve3[] = {"SetDoorRightValve3:close;"};
  door.SetValveStatus(messageValve1);
  door.SetValveStatus(messageValve2);
  door.SetValveStatus(messageValve3);
}
void SchutState::ElevateWaterLowEntryActions()
{
  //ENTRY: open lowest valve
  char message[] = {"SetDoorLeftValve1:open;"};
  door.SetValveStatus(message);
}
void SchutState::ElevateWaterLowExitActions()
{
  //EXIT: close lowest valve
  char message[] = {"SetDoorLeftValve1:close;"};
  door.SetValveStatus(message);
}
void SchutState::OpenLeftDoorEntryActions()
{
  //Leftdoor.open
  door.SetDoorStatusLeftOpen();
}

void SchutState::OpenLeftDoorExitActions()
{
  //leftdoor trafficlights green
  char tlMessageRed[] = {"SetTrafficLight1Red:off;"};
  char tlMessageGreen[] = {"SetTrafficLight1Green:on;"};
  char tlMessageRed2[] = {"SetTrafficLight2Red:off;"};
  char tlMessageGreen2[] = {"SetTrafficLight2Green:on;"};


  trafficLight.SetTrafficLightStatus(tlMessageRed);
  trafficLight.SetTrafficLightStatus(tlMessageRed2);
  trafficLight.SetTrafficLightStatus(tlMessageGreen);
  trafficLight.SetTrafficLightStatus(tlMessageGreen2);
}
void SchutState::OpenRightDoorEntryActions()
{
  //Rightdoor.open
  door.SetDoorStatusRightOpen();
}
void SchutState::OpenRightDoorExitActions()
{
  //rightdoor trafficlights green
  char tlMessageRed[] = {"SetTrafficLight3Red:off;"};
  char tlMessageRed2[] = {"SetTrafficLight4Red:off;"};
  char tlMessageGreen[] = {"SetTrafficLight3Green:on;"};
  char tlMessageGreen2[] = {"SetTrafficLight4Green:on;"};

  trafficLight.SetTrafficLightStatus(tlMessageRed);
  trafficLight.SetTrafficLightStatus(tlMessageRed2);
  trafficLight.SetTrafficLightStatus(tlMessageGreen);
  trafficLight.SetTrafficLightStatus(tlMessageGreen2);

}
void SchutState::LightsLeftRed()
{
  char tlMessageRed[] = {"SetTrafficLight1Red:on;"};
  char tlMessageRed2[] = {"SetTrafficLight2Red:on;"};
  char tlMessageGreen[] = {"SetTrafficLight1Green:off;"};
  char tlMessageGreen2[] = {"SetTrafficLight2Green:off;"};

  trafficLight.SetTrafficLightStatus(tlMessageRed);
  trafficLight.SetTrafficLightStatus(tlMessageRed2);
  trafficLight.SetTrafficLightStatus(tlMessageGreen);
  trafficLight.SetTrafficLightStatus(tlMessageGreen2);
}

void SchutState::LightsRightRed()
{
  char tlMessageRed[] = {"SetTrafficLight3Red:on;"};
  char tlMessageRed2[] = {"SetTrafficLight4Red:on;"};
  char tlMessageGreen[] = {"SetTrafficLight3Green:off;"};
  char tlMessageGreen2[] = {"SetTrafficLight4Green:off;"};

  trafficLight.SetTrafficLightStatus(tlMessageRed);
  trafficLight.SetTrafficLightStatus(tlMessageRed2);
  trafficLight.SetTrafficLightStatus(tlMessageGreen);
  trafficLight.SetTrafficLightStatus(tlMessageGreen2);
}

void SchutState::Resume()
{
  switch(currentSubState)
  {
    case CloseRightDoor:
    CloseRightDoorEntryActions();
    break;
    case CloseLeftDoor:
    CloseLeftDoorEntryActions();
    break;
    case ElevateWaterHigh:
    ElevateWaterHighEntryActions();
    break;
    case ElevateWaterLow:
    ElevateWaterLowEntryActions();
    case OpenLeftDoor:
    OpenLeftDoorEntryActions();
    break;
    case OpenRightDoor:
    OpenRightDoorEntryActions();
    break;
    default:
    break;
  };
}