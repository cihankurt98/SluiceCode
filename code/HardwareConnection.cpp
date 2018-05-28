#include "HardwareConnection.h"

#include <sys/socket.h>
#include <string.h>

HardwareConnection::HardwareConnection(Door door, TrafficLight trafficLight, WaterSensor waterSensor, Valve valve)
{
	// TODO - implement HardwareConnection::HardwareConnection
	throw "Not yet implemented";
}

int HardwareConnection::Send(int socket, char message[], int size, int flags)
{
	if (send(socket, message, size, flags) == -1)
	{
		return -1;
	}
	return 0;
}

int HardwareConnection::Receive(int socket, char message[], int size, int flags)
{
	if (recv(socket, message, size, flags) <= 0)
	{
		memset(message, 0, sizeof(message)); //Clean array if corrupt bufferfill
		return -1;
	}
	return 0;
}

int HardwareConnection::Connect(char ip[], int port)
{
	simulator.sin_addr.s_addr = inet_addr(ip);
	simulator.sin_family = AF_INET;
	simulator.sin_port = htons(port);
	if (CreateTCPSocket() == 0 || connect(socket_desc, (struct sockaddr *)&simulator, sizeof(simulator)) < 0)
	{
		return -1;
	}
	return 1;
}

int HardwareConnection::CreateTCPSocket()
{
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); // list met meerdere sockets voor meerdere connecties?
	if (socket_desc == -1)
	{
		return -1;
	}
	return 1;
}