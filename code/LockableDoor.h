#ifndef LOCKABLEDOOR_H
#define LOCKABLEDOOR_H

#include "interfaces/iLock.h"
#include "Door.h"

class LockableDoor : public Door
{
public:
	LockableDoor(HardwareConnection& hardwareConnection, iValve& valve);

	//iLock
	std::string GetLockStatus(char message[]);
	bool SetLockStatus(char message[]);
};
#endif