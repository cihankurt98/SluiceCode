#include "LockableDoor.h"

LockableDoor::LockableDoor(HardwareConnection& hardwareConnection, iValve& valve)
	: Door(hardwareConnection, valve)
{

}
//iLock
std::string LockableDoor::GetLockStatus(char message[])
{
	int size = strlen(message);
	return hardwareConnection.Transmit(message, size, 0);
}
bool LockableDoor::SetLockStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != hardwareConnection.Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}