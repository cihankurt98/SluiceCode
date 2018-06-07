#ifndef HARDWARECONNECTION_H
#define HARDWARECONNECTION_H

#include <string>
#include <string.h> //voor strlen in door etc.
#include <arpa/inet.h>

class HardwareConnection
{

  public:
	HardwareConnection(char ip[15], int port);
	~HardwareConnection();
	std::string Transmit(char message[], int size, int flags);


	private:
	int socket_desc;
	struct sockaddr_in simulator;
	// private copy constructor and assignment operator to prevent making copies
	HardwareConnection(const HardwareConnection&) { /* do nothing */ };
	HardwareConnection& operator=(const HardwareConnection&) { return *this; };
};

#endif
