#include "Valve.h"
#include <iostream>
Valve::Valve(iValve& valve)
	: valve(valve)
{
	std::cout << "kanker valve" << std::endl;
}

std::string Valve::GetDoorValveStatus(char message[])
{
	return valve.GetValveStatus(message);
}

bool Valve::SetDoorValveStatus(char message[])
{
	return valve.SetValveStatus(message);
}