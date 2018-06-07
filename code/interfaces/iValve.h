#ifndef IVALVE_H
#define IVALVE_H

#include <string>

class iValve 
{
public:
	virtual ~iValve(){};
	virtual std::string GetValveStatus(char message[]) = 0;

	virtual bool SetValveStatus(char message[]) = 0;
};

#endif
