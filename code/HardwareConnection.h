#ifndef HARDWARECONNECTION_H
#define HARDWARECONNECTION_H

#include <string>
#include <string.h> //voor strlen in door etc.
#include <arpa/inet.h>

#include "interfaces/iDoor.h"
#include "interfaces/iValve.h"
#include "interfaces/iLock.h"
#include "interfaces/iWaterSensor.h"
#include "interfaces/iTrafficLight.h"


class HardwareConnection : public iDoor, public iValve, public iWaterSensor, public iTrafficLight, public iLock
{

  public:
	HardwareConnection(char ip[15], int port);
	~HardwareConnection();
	std::string Transmit(char message[], int size, int flags);

	//iDoor
	std::string GetDoorStatus(char message[]);
	bool SetDoorStatus(char message[]);

	//iValve
	std::string GetValveStatus(char message[]);
	bool SetValveStatus(char message[]);

	//iLock
	std::string GetLockStatus(char message[]);
	bool SetLockStatus(char message[]);

	//iWaterSensor
	std::string GetWaterLevel(char message[]);

	//iTrafficLight
	std::string GetTrafficLightStatus(char message[]);
	bool SetTrafficLightStatus(char message[]);


	private:
	int socket_desc;
	struct sockaddr_in simulator;
	// private copy constructor and assignment operator to prevent making copies
};

#endif
