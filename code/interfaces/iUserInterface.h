#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

class iUserInterface
{
public: 
	virtual ~iUserInterface() {};
	virtual void BtnStartPressed() = 0;
	virtual void BtnUitvarenPressed() = 0;
	virtual void BtnInvarenPressed() = 0;
	virtual void BtnAlarmPressed() = 0;
	virtual void BtnResetPressed() = 0;
};

#endif