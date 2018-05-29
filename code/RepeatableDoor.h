#ifndef REPEATABLEDOOR_H
#define REPEATABLEDOOR_H

#include "Door.h"

class RepeatableDoor : public Door
{
public:
	RepeatableDoor();
	~RepeatableDoor();
	void GetDoorStatus();

	void SetDoorStatus();
};

#endif
