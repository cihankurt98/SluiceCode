#ifndef DOOR_H
#define DOOR_H

#include "iDoor.h"
#include "Valve.h"
#include "Lock.h"

class Door : public iDoor, public iValve, public iLock

{
public:
	void GetDoorStatus();

	void SetDoorStatus();

	void GetLockStatus();

	void SetLockStatus();
private:
	// private copy constructor and assignment operator to prevent making copies
	Door(const Door&) { /* do nothing */ };
	Door& operator=(const Door&) { return *this; };
};

#endif
