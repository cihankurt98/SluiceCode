#ifndef SchutState_H
#define SchutState_H

#include "interfaces/iDoor.h"
#include "interfaces/iWaterSensor.h"
#include "interfaces/iTrafficLight.h"
#include "Events.h"
#include "State.h"

enum SubState
{
	CloseRightDoor,
	CloseLeftDoor,
	ElevateWaterHigh,
	ElevateWaterLow,
	OpenLeftDoor,
	OpenRightDoor
};

enum ElevateWaterHighSubState
{
	OpenValve1,
	OpenValve2,
	OpenValve3
};

class SchutState
{
public:
	SchutState(iDoor* door, iWaterSensor* waterSensor, iTrafficLight* trafficLight);
  void HandlePseudoState();
  void HandleEvent(State* superState, Events ev);
  void ExitSubStateActions();

	SubState HandleCloseRightDoor(Events ev);
	SubState HandleCloseLeftDoor(Events ev);
	SubState HandleElevateWaterHigh(Events ev);
	SubState HandleElevateWaterLow(Events ev);
	SubState HandleOpenLeftDoor(Events ev);
  SubState HandleOpenRightDoor(Events ev);

private:
	SubState currentSubState;
	iDoor* door;
	iWaterSensor* waterSensor;
	iTrafficLight* trafficLight;

	void CloseRightDoorEntryActions();
	void CloseRightDoorExitActions();
	void CloseLeftDoorEntryActions();
	void CloseLeftDoorExitActions();
	void ElevateWaterHighEntryActions();
	void ElevateWaterHighExitActions();
	void ElevateWaterLowEntryActions();
	void ElevateWaterLowExitActions();
	void OpenLeftDoorEntryActions();
	void OpenLeftDoorExitActions();
	void OpenRightDoorEntryActions();
	void OpenRightDoorExitActions();

};
#endif
