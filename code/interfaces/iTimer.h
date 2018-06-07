#ifndef ITIMER_H
#define ITIMER_H

class iTimer {


public:
	virtual ~iTimer(){};
	virtual void setTime() = 0;

	virtual void Cancel() = 0;

	virtual bool isTimeout() = 0;
};

#endif
