#ifndef IDOOR_H
#define IDOOR_H

#include <string>

class iDoor
{
public:
	virtual ~iDoor(){};

	std::string GetDoorStatus(char message[]);

	bool SetDoorStatus(char message[]);
};

#endif
