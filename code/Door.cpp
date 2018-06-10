#include "Door.h"

Door::Door(HardwareConnection& hardwareConnection, iValve& valve)
	: hardwareConnection(hardwareConnection),
	  valve(valve)
{
}

std::string Door::GetDoorStatusLeft()
{
	char message[] = {"GetDoorLeft;"};
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

std::string Door::GetDoorStatusRight()
{
	char message[] = {"GetDoorRight;"};
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}


bool Door::SetDoorStatusLeftOpen()
{
	char message[] = {"SetDoorLeft:open;"};
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

bool Door::SetDoorStatusLeftClose()
{
	char message[] = {"SetDoorLeft:close;"};
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

bool Door::SetDoorStatusRightOpen()
{
	char message[] = {"SetDoorRight:open;"};
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

bool Door::SetDoorStatusRightClose()
{
	char message[] = {"SetDoorRight:close;"};
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

