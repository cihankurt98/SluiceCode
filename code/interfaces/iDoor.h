#ifndef IDOOR_H
#define IDOOR_H

#include <string>

class iDoor
{
public:
	virtual ~iDoor(){};

	virtual std::string GetDoorStatus(char message[]) = 0;
	virtual bool SetDoorStatus(char message[]) = 0;
};

#endif
