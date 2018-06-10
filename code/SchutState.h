#ifndef SchutState_H
#define SchutState_H

#include "interfaces/iDoor.h"
#include "interfaces/iWaterSensor.h"
#include "interfaces/iTrafficLight.h"
#include "Event.h"
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
	SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight);
  void HandlePseudoState();
  void HandleEvent(State& superState, ElevateWaterHighSubState& elevateState, Event ev);
  void ExitSubStateActions();

	SubState HandleCloseRightDoor(Event ev);
	SubState HandleCloseLeftDoor(Event ev);
	SubState HandleElevateWaterHigh(ElevateWaterHighSubState& elevateState,Event ev);
	SubState HandleElevateWaterLow(Event ev);
	SubState HandleOpenLeftDoor(State& superState,Event ev);
  	SubState HandleOpenRightDoor(State& superState,Event ev);

private:
	SubState currentSubState;
	ElevateWaterHighSubState elevateState;
	iDoor& door;
	iWaterSensor& waterSensor;
	iTrafficLight& trafficLight;
	void HandleElevateHighSubstates(ElevateWaterHighSubState& elevateState,Event ev);

	void CloseRightDoorEntryActions();
	void CloseRightDoorExitActions();
	void CloseLeftDoorEntryActions();
	void CloseLeftDoorExitActions();
	void ElevateWaterHighEntryActions();
	void OpenValve1EntryActions();
	void OpenValve1ExitActions();
	void OpenValve2EntryActions();
	void OpenValve2ExitActions();
	void OpenValve3EntryActions();
	void OpenValve3ExitActions();
	void ElevateWaterHighExitActions();
	void ElevateWaterLowEntryActions();
	void ElevateWaterLowExitActions();
	void OpenLeftDoorEntryActions();
	void OpenLeftDoorExitActions();
	void OpenRightDoorEntryActions();
	void OpenRightDoorExitActions();

	void LightsLeftRed();
	void LightsRightRed();

};
#endif
