#ifndef ITIMER_H
#define ITIMER_H

class iTimer {


public:
	virtual ~iTimer();
	void setTime();

	void Cancel();

	bool isTimeout();
};

#endif
