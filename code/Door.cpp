#include "Door.h"

Door::Door(HardwareConnection& hardwareConnection, iValve& valve)
	: hardwareConnection(hardwareConnection),
	  valve(valve)
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

bool Door::SetValveStatus(char message[])
{
	return valve.SetValveStatus(message);
}

std::string Door::GetValveStatus(char message[])
{
	return valve.GetValveStatus(message);
}

