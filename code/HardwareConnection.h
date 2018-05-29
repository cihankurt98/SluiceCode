#ifndef HARDWARECONNECTION_H
#define HARDWARECONNECTION_H

#include "Door.h"
#include "TrafficLight.h"
#include "WaterSensor.h"
#include "Valve.h"

#include <arpa/inet.h>

class HardwareConnection
{

  public:
	HardwareConnection(iDoor door, iTrafficLight trafficLight, iWaterSensor waterSensor, iValve valve);
	~HardwareConnection();
	int Send(int socket, char message[], int size, int flags);

	int Receive(int socket, char message[], int size, int flags);

	int Connect(char ip[], int port);


	private:
	int socket_desc;
	struct sockaddr_in simulator;
	int CreateTCPSocket();
};

#endif
