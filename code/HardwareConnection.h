#ifndef HARDWARECONNECTION_H
#define HARDWARECONNECTION_H

#include "iDoor.h"
#include "iTrafficLight.h"
#include "iWaterSensor.h"
#include "iValve.h"

#include <arpa/inet.h>

class HardwareConnection
{

  public:
	HardwareConnection(Door door, TrafficLight trafficLight, WaterSensor waterSensor, Valve valve);

	int Send(int socket, char message[], int size, int flags);

	int Receive(int socket, char message[], int size, int flags);

	int Connect(char ip[], int port);


	private:
	int socket_desc;
	struct sockaddr_in simulator;
	int CreateTCPSocket();
};

#endif
