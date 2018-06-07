#ifndef DOOR_H
#define DOOR_H

#include "HardwareConnection.h"
#include "interfaces/iDoor.h"
#include "interfaces/iValve.h"
#include "interfaces/iLock.h"

class Door : public iDoor, public iValve, public iLock

{
public:
	//
	Door(HardwareConnection* const hardwareConnection);

	//iDoor
	std::string GetDoorStatus(char message[]);
	bool SetDoorStatus(char message[]);

	//iValve
	std::string GetValveStatus(char message[]);
	bool SetValveStatus(char message[]);

	//iLock
	std::string GetLockStatus(char message[]);
	bool SetLockStatus(char message[]);

private:
	HardwareConnection* hardwareConnection;
	// private copy constructor and assignment operator to prevent making copies
	Door(const Door&) { /* do nothing */ };
	Door& operator=(const Door&) { return *this; };
};

#endif
