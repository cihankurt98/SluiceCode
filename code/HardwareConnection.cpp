#include "HardwareConnection.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> // close sock
#include <stdexcept>

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
}

HardwareConnection::~HardwareConnection()
{
	close(socket_desc);
}

std::string HardwareConnection::Transmit(char message[], int size, int flags)
{
	if (send(socket_desc, message, size, flags) == -1)
	{
		return NULL;
	}
	char receivedMessage[20];
	recv(socket_desc, receivedMessage, size, flags);
	return (std::string) receivedMessage;
}
