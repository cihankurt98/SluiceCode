#ifndef DOOR_H
#define DOOR_H

#include "interfaces/iDoor.h"
#include "interfaces/iValve.h"
#include "interfaces/iLock.h"

class Door

{
public:
	Door(iDoor* door, iValve* valve, iLock* lock);
	//iDoor
	std::string GetDoorStatus(char message[]);
	bool SetDoorStatus(char message[]);
	std::string GetDoorValveStatus(char message[]);
	bool SetDoorValveStatus(char message[]);
	bool SetLockStatus(char message[]);

private:
	iDoor* door;
	iValve* valve;
	iLock* lock;

};
#endif
