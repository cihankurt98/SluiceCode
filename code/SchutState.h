#ifndef SchutState_H
#define SchutState_H

#include "iDoor.h"
#include "iWaterSensor.h"
#include "iTrafficLight.h"
#include "Events.h"
#include "State.h"
#include "StandardProcedureSubStates.h"
#include "ElevateWaterHighSubStates.h"

class SchutState
{
public:
	SchutState(iDoor& door, iWaterSensor& waterSensor, iTrafficLight& trafficLight);
  void HandlePseudoState();
  void HandleEvent(State superState, Events ev);
  void ExitActions();
	~SchutState();

};
#endif
