#include "HardwareConnection.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> // close sock

HardwareConnection::HardwareConnection(iDoor door, iTrafficLight trafficLight, iWaterSensor waterSensor, iValve valve)
{
	if (CreateTCPSocket() == -1 )
	{
		//exception
	}
}

HardwareConnection::~HardwareConnection()
{
	close(socket_desc);
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
		memset(message, 0, 20); //Clean array if corrupt bufferfill //sizeof chararray ipv 20 vanwege compiler error
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