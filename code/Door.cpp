#include "Door.h"
#include <iostream>

Door::Door(iDoor& door, iValve& valve)
: door(door), valve(valve)
{
}


std::string Door::GetDoorStatus(char message[])
{
	return door.GetDoorStatus(message);
}

bool Door::SetDoorStatus(char message[])
{
	return door.SetDoorStatus(message);
}

std::string Door::GetDoorValveStatus(char message[])
{
	return valve.GetValveStatus(message);
}

bool Door::SetDoorValveStatus(char message[])
{
	return valve.SetValveStatus(message);
}


