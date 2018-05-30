#include "Door.h"

Door::Door(HardwareConnection* const hardwareConnection) //not allowed to modify ptr
{
	this->hardwareConnection = hardwareConnection;
}

std::string Door::GetDoorStatus(char message[], int size)
{
	return hardwareConnection->Transmit(message, size, 0);
}

bool Door::SetDoorStatus(char message[], int size)
{
	if ("ack" != hardwareConnection->Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string Door::GetLockStatus(char message[], int size)
{
	return hardwareConnection->Transmit(message, size, 0);
}

bool Door::SetLockStatus(char message[], int size)
{
	if ("ack" != hardwareConnection->Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}
