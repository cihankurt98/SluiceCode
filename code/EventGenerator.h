#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include "Event.h"
#include "interfaces/iEventGenerator.h"
#include "interfaces/iUserInterface.h"
#include "interfaces/iDoor.h"
#include "interfaces/iWaterSensor.h"


#include <vector>

class EventGenerator: public iEventGenerator, public iUserInterface
{
public: 
	EventGenerator(iDoor& door, iWaterSensor& waterSensor);

	//interface EventGenerator
	Event GetEvent();

	//interface UserActions
	void BtnStartPressed();
	void BtnUitvarenPressed();
	void BtnInvarenPressed();
	void BtnAlarmPressed();
	void BtnResetPressed();
private:
	std::vector<Event> events;
	iDoor& door;
	iWaterSensor& waterSensor;
	std::string prevWaterLevel;
	std::string prevRightDoorState;
	std::string prevLeftDoorState;
	void HandlePollEvents();
	Event TranslateToEvent(std::string eventString);

};
#endif