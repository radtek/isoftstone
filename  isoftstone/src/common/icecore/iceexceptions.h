

#ifndef __HI_ICE_EXCEPTION_H__
#define __HI_ICE_EXCEPTION_H__


#include <Ice/Exception.h>
#include <Ice/LocalException.h>
#include "icecore.h"

#define  TRY try 

#define CATCH_ICE_EXCEPTION() \
catch(const Ice::SystemException& e) \
{ \
	COUT_ICE_EXCEPTION("1",e.what()); \
} \
catch(const Ice::LocalException& e) \
{ \
	COUT_ICE_EXCEPTION("2",e.what()); \
} \
catch(const Ice::UserException& e) \
{ \
	COUT_ICE_EXCEPTION("3",e.what()); \
} \
catch(const Ice::Exception& e) \
{ \
	COUT_ICE_EXCEPTION("4",e.what()); \
} \
catch(const std::exception & e) \
{ \
	COUT_SYSTEM_EXCEPTION("5",e.what()) \
} \
catch(const string &e) \
{ \
	COUT_SYSTEM_EXCEPTION("6",e) \
} \
catch(const char *e) \
{ \
	COUT_SYSTEM_EXCEPTION("7",e) \
} \
catch(const int e) \
{ \
	COUT_SYSTEM_EXCEPTION("8",e) \
} \
catch(...) \
{ \
	COUT_SYSTEM_EXCEPTION("δ֪","δ֪�쳣") \
}

namespace core
{

LIB_ICECORE_EXPORT std::string exception2string(const Ice::Exception& e);
LIB_ICECORE_EXPORT std::string exception2string(const Ice::SystemException& e);


}

#endif // __HI_EXCEPTION_H__