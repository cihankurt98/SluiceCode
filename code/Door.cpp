#include "Door.h"

Door::Door(HardwareConnection& hardwareConnection)
: hardwareConnection(hardwareConnection)
{
}

std::string Door::GetDoorStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

bool Door::SetDoorStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string Door::GetValveStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

bool Door::SetValveStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string Door::GetLockStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

bool Door::SetLockStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}
