#ifndef ILOCK_H
#define ILOCK_H

#include <string>

class iLock 
{

public:
	virtual std::string GetLockStatus(char message[]) = 0;
	virtual bool SetLockStatus(char message[]) = 0;
};

#endif
