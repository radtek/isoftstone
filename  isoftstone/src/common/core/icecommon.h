
#ifndef _ICECOMMON_H_
#define _ICECOMMON_H_

#include <Ice/Ice.h>
#include <Ice/Current.h>
#include "escore.h"
#include "Macro.h"

template <class Stream>
inline Stream& operator<<(Stream& out , const Ice::Current& curr)
{
	out << curr.adapter->getName() << std::endl;
	out << curr.con->toString() << std::endl;
	out << curr.id.name << std::endl;
	out << curr.id.category << std::endl;
	out << curr.facet << std::endl;
	out << curr.operation << std::endl;
	out << curr.mode << std::endl;
	for (::Ice::Context::const_iterator iter = curr.ctx.begin() ; iter != curr.ctx.end() ;iter++)
	{
		out << iter->first << " : " << iter->second << std::endl;
	}
	out << curr.requestId << std::endl;
	return out;
}

class  LIBCORE_EXPORT CIceCommon
{
public:

	static void displayCurrent(const Ice::Current& curr);

	static Ice::Context getEndpointInfoAsContext(const Ice::Current& c);

	static Ice::Context getConnectionInfoAsContext(const Ice::Current& c);

	
};

template <class ASYN_METHOD>
class AMI_ASYN_UNUSED_IMPL :  public ASYN_METHOD
{
public:

	virtual void ice_response()
	{
	}

	virtual void ice_exception(const ::Ice::Exception& ex) 
	{
		Hi_UNUSED(ex);
	}
};

#endif
