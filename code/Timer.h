#ifndef TIMER_H
#define TIMER_H

#include "iTimer.h"

class Timer : public iTimer
{
public:
	Timer();
	void setTime();

	void Cancel();

	bool isTimeout();

private:
	// private copy constructor and assignment operator to prevent making copies
	Display(const Display&) { /* do nothing */ };
	Display& operator=(const Display&) { return *this; };
};
};

#endif
