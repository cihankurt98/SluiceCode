#ifndef TIMER_H
#define TIMER_H

class Timer : iTimer {


public:
	void setTime();

	void Cancel();

	bool isTimeout();
};

#endif
