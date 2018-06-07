#include "Door.h"
#include <iostream>

Door::Door(iDoor& door, iValve& valve, iLock& lock)
	: door(door),
	  valve(valve),
	  lock(lock)
{

}


std::string Door::GetDoorStatus(char message[])
{
	return door.GetDoorStWatus(message);
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

bool Door::SetLockStatus(char message[])
{
	return lock.SetLockStatus(message);
}

