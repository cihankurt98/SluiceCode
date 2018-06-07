#ifndef VALVE_H
#define VALVE_H

#include "interfaces/iValve.h"

class Valve

{
public:
	Valve(iValve& valve);
	std::string GetDoorValveStatus(char message[]);
	bool SetDoorValveStatus(char message[]);
private:
	iValve& valve;
};
#endif