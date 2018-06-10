#ifndef IDOOR_H
#define IDOOR_H


#include "iValve.h"
#include <string>


class iDoor
{
public:
	virtual ~iDoor(){};

	virtual std::string GetDoorStatusLeft() = 0;
	virtual std::string GetDoorStatusRight() = 0;
	virtual bool SetDoorStatusLeftOpen() = 0;
	virtual bool SetDoorStatusLeftClose() = 0;
	virtual bool SetDoorStatusRightOpen() = 0;
	virtual bool SetDoorStatusRightClose() = 0;
	virtual bool SetValveStatus(char message[]) = 0;
	virtual std::string GetValveStatus(char message[]) = 0;
};

#endif
