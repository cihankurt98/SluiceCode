#include "Timer.h"
#include <iostream>

void Timer::setTime()
{
	std::cout << "SettimeCompileFix" << std::endl;
}

void Timer::Cancel()
{
	std::cout << "CancelCompileFix" << std::endl;
}

bool Timer::isTimeout()
{
	std::cout << "isTimeOutCompileFix" << std::endl;
	return true;
}
