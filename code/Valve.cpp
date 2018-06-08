#include "Valve.h"

Valve::Valve(HardwareConnection& hardwareConnection)
: hardwareConnection(hardwareConnection)
{
}

std::string Valve::GetValveStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}

bool Valve::SetValveStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}