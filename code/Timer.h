#ifndef TIMER_H
#define TIMER_H

#include "interfaces/iTimer.h"

class Timer : public iTimer
{
public:
	Timer();
	void setTime();

	void Cancel();

	bool isTimeout();

private:
	// private copy constructor and assignment operator to prevent making copies
	Timer(const Timer&) { /* do nothing */ };
	Timer& operator=(const Timer&) { return *this; };
};

#endif
