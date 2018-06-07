#include "HardwareConnection.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> // close sock
#include <stdexcept>

#include <iostream> // test

HardwareConnection::HardwareConnection(char ip[15], int port)
{
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); // list met meerdere sockets voor meerdere connecties?
	if (socket_desc <= -1)
	{
		throw std::logic_error("socket is <= -1"); //nog catche
	}

	simulator.sin_addr.s_addr = inet_addr(ip);
	simulator.sin_family = AF_INET;
	simulator.sin_port = htons(port);
	if (connect(socket_desc, (struct sockaddr *)&simulator, sizeof(simulator)) < 0)
	{
		throw std::logic_error("connect is <= -1"); //nog catchen
	}
	std::cout << "constructor voltooid" << std::endl;
}

HardwareConnection::~HardwareConnection()
{
	close(socket_desc);
}

std::string HardwareConnection::Transmit(char message[], int size,  int flags)
{
	if (send(socket_desc, message, size, flags) == -1)
	{
		std::cout << "fail message" << std::endl;
		return NULL;
	}
	std::cout << "sent message" << std::endl;
	const int bufferSize = 20;
	char receivedMessage[bufferSize];

	int actualSize = recv(socket_desc, receivedMessage, bufferSize, flags);

	if (actualSize <= 0)
	{
		throw std::logic_error("Niks ontvangen"); //nog catchen
	}
	receivedMessage[actualSize] = '\0';
	return (std::string) receivedMessage;
}

std::string HardwareConnection::GetDoorStatus(char message[])
{
	int size = strlen(message);
	return Transmit(message, size, 0);
}

bool HardwareConnection::SetDoorStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string HardwareConnection::GetValveStatus(char message[])
{
	int size = strlen(message);
	return Transmit(message, size, 0);
}

bool HardwareConnection::SetValveStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string HardwareConnection::GetLockStatus(char message[])
{
	int size = strlen(message);
	return Transmit(message, size, 0);
}

bool HardwareConnection::SetLockStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}

std::string HardwareConnection::GetWaterLevel(char message[])
{
	int size = strlen(message);
	return Transmit(message, size, 0);
}

std::string HardwareConnection::GetTrafficLightStatus(char message[])
{
	int size = strlen(message);
	return Transmit(message, size, 0);
}

bool HardwareConnection::SetTrafficLightStatus(char message[])
{
	int size = strlen(message);
	if ("ack" != Transmit(message, size, 0))
	{
		return false;
	}
	return true;
}