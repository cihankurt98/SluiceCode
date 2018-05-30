#ifndef DOOR_H
#define DOOR_H

#include "HardwareConnection.h"
#include "interfaces/iDoor.h"
#include "Valve.h"
#include "interfaces/iLock.h"

class Door : public iDoor, public iValve, public iLock

{
public:
	Door(HardwareConnection* const hardwareConnection);
	~Door();
	std::string GetDoorStatus(char message[], int size);

	bool SetDoorStatus(char message[], int size);

	std::string GetLockStatus(char message[], int size);

	bool SetLockStatus(char message[], int size);
private:
	HardwareConnection* hardwareConnection;
	// private copy constructor and assignment operator to prevent making copies
	Door(const Door&) { /* do nothing */ };
	Door& operator=(const Door&) { return *this; };
};

#endif
