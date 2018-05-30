#include "Valve.h"


Valve::Valve(HardwareConnection* const hardwareConnection)
{
	this->hardwareConnection = hardwareConnection;
}

std::string Valve::GetValveStatus(char message[], int size)
{
	return hardwareConnection->Transmit(message, size, 0);
}

bool Valve::SetValveStatus(char message[], int size)
{
	if ("ack" != hardwareConnection->Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}