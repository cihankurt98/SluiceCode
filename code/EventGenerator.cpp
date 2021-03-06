#include "EventGenerator.h"
#include <iostream>
#include <sstream>

EventGenerator::EventGenerator(iDoor& door, iWaterSensor& waterSensor)
:door(door),
waterSensor(waterSensor)
{
	char getWaterLevel[] = {"GetWaterLevel;"};
	prevWaterLevel = waterSensor.GetWaterLevel(getWaterLevel);
	prevRightDoorState = door.GetDoorStatusRight();
	prevLeftDoorState = door.GetDoorStatusLeft();
}


Event EventGenerator::GetEvent()
{
	Event result = NoEventOccured;

	HandlePollEvents();

	if (events.size() > 0)
	{
		result = events[0];
		events.erase(events.begin());
	}
	return result;
}

void EventGenerator::BtnStartPressed()
{
	events.push_back(EV_SCHUTSTART);
}

void EventGenerator::BtnUitvarenPressed()
{
	events.push_back(EV_BTNUITVARENPRESSED);
}

void EventGenerator::BtnInvarenPressed()
{
	events.push_back(EV_BTNINVARENPRESSED);
}

void EventGenerator::BtnAlarmPressed()
{
	events.push_back(EV_EMERGENCY);
}

void EventGenerator::BtnResetPressed()
{
	events.push_back(EV_RESUME);
}

Event EventGenerator::TranslateToEvent(std::string eventString)
{
	if (eventString == "low;")return EV_WATER_LOW;
	if (eventString == "aboveValve2;") return EV_WATERLEVEL_ABOVE_VALVE2;
	if (eventString == "aboveValve3;") return EV_WATERLEVEL_ABOVE_VALVE3;
	if (eventString == "high;") return EV_WATER_HIGH;
	if (eventString == "doorClosed;left") return EV_LEFTDOORCLOSED;
	if (eventString == "doorClosed;right") return EV_RIGHTDOORCLOSED;
	if (eventString == "doorOpen;left") return EV_LEFTDOOROPENED;
	if (eventString == "doorOpen;right") return EV_RIGHTDOOROPENED;

	return NoEventOccured;
}


void EventGenerator::HandlePollEvents()
{
	char getWaterLevel[] = {"GetWaterLevel;"};
	
	std::string currWaterLevel = waterSensor.GetWaterLevel(getWaterLevel);
	std::string currRightDoorState = door.GetDoorStatusRight();
	std::string currLeftDoorState = door.GetDoorStatusLeft();

	if (currWaterLevel != prevWaterLevel)
	{
		events.push_back((TranslateToEvent(currWaterLevel)));
		prevWaterLevel = currWaterLevel;
	}

	if (currRightDoorState != prevRightDoorState)
	{
		std::stringstream ss;
		ss << currRightDoorState << "right";
		events.push_back(TranslateToEvent(ss.str()));
		prevRightDoorState = currRightDoorState;
	}

	if (currLeftDoorState != prevLeftDoorState)
	{
		std::stringstream ss;
		ss << currLeftDoorState << "left";
		events.push_back(TranslateToEvent(ss.str()));
		prevLeftDoorState = currLeftDoorState;
	}

}