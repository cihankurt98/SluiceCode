#ifndef DOOR_H
#define DOOR_H

#include "HardwareConnection.h"
#include "interfaces/iDoor.h"
#include "interfaces/iValve.h"

class Door : public iDoor

{
public:
	Door(HardwareConnection& hardwareConnection, iValve& valve);

	//iDoor
	std::string GetDoorStatus(char message[]);
	bool SetDoorStatus(char message[]);
	bool SetValveStatus(char message[]);
	std::string GetValveStatus(char message[]);

protected:
	HardwareConnection& hardwareConnection;
	iValve& valve;
};

#endif
