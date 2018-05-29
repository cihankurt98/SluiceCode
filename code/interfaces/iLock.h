#ifndef ILOCK_H
#define ILOCK_H

class iLock {


public:
	virtual ~iLock();
	void GetLockStatus();

	void SetLockStatus();
};

#endif
