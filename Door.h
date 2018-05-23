#ifndef DOOR_H
#define DOOR_H

class Door : iDoor, iValve, iLock {


public:
	void GetDoorStatus();

	void SetDoorStatus();

	void GetLockStatus();

	void SetLockStatus();
};

#endif
