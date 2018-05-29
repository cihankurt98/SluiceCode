#ifndef IDOOR_H
#define IDOOR_H

class iDoor
{
public:
	virtual ~iDoor(){};

	void GetDoorStatus();

	void SetDoorStatus();
};

#endif
