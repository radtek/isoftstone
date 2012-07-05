
#ifndef PROTOCAL_H
#define PROTOCAL_H

#include <QString>

class IProtocal
{
public:

	virtual bool checkValid(const char* pData) = 0;
	
};

#endif