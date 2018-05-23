#ifndef HARDWARECONNECTION_H
#define HARDWARECONNECTION_H

class HardwareConnection {


public:
	HardwareConnection(Door door, TrafficLight trafficLight, WaterSensor waterSensor, Valve valve);

	void Send(int socket, char message[], int size, int flags);

	void Receive(int socket, char message[], int size, int flags);

	void CreateTCPSocket();
};

#endif
