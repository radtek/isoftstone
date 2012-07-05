
#ifndef __COREMACRO_H__
#define __COREMACRO_H__

#include <string>
#include <crtdbg.h>
#include <stdarg.h>

#define  SEPARATORS(OPERATOR) << OPERATOR

#define Hi_UNUSED(x) (void)x;
#define HI_UNUSEDP(x) (void*)x;

#define PRINT_ARGMENT_NAME(argment) #argment
#define PRINT_ARGMENT_VALUE(argment) cout << argment;

inline void Print_Argument(char* format, ...)
{
	va_list argp;

	va_start (argp, format);
	char cbuffer[100 + 1];
	memset(cbuffer,0x00,100 + 1);
	int nLen = 0;
#if defined(_WIN32)
	nLen = vsprintf_s(cbuffer,100,format,argp);
#else
	nLen = sprintf_s(cbuffer,format,argp);
#endif
	va_end (argp);

	printf(cbuffer);

}
#ifndef _UNUSE_HI_COUT_RET_OR_OUT

#define  _UNUSE_HI_COUT_RET_OR_OUT

#endif


#ifdef _UNUSE_HI_COUT_RET_OR_OUT
#define  HI_FORMAT__RET_OR_OUT(...)
#define HI_COUT_ARGNAME_VALUE(...)
#define HI_COUT_ARGNAME_VALUE_2(...)
#define HI_COUT_ARGNAME_VALUE_3(...)
#define HI_COUT_ARGNAME_VALUE_4(...)
#define HI_COUT_ARGNAME_VALUE_5(...)
#define HI_COUT_ARGNAME_VALUE_6(...)
#define HI_COUT_ARGNAME_VALUE_7(...)
#define HI_COUT_ARGNAME_VALUE_8(...)
#else
#define  HI_FORMAT__RET_OR_OUT(format,...) \
	Print_Argument( format,__VA_ARGS__);


#define HI_COUT_ARGNAME_VALUE(arg) \
{ \
	printf(PRINT_ARGMENT_NAME(arg)); \
	printf("  =   "); \
	PRINT_ARGMENT_VALUE(arg); \
	printf("\n"); \
}

#define HI_COUT_ARGNAME_VALUE_2(arg1,arg2) \
{ \
	HI_COUT_ARGNAME_VALUE(arg1) \
	HI_COUT_ARGNAME_VALUE(arg2) \
}

#define HI_COUT_ARGNAME_VALUE_3(arg1,arg2,arg3) \
{ \
	HI_COUT_ARGNAME_VALUE_2(arg1,arg2) \
	HI_COUT_ARGNAME_VALUE(arg3) \
}

#define HI_COUT_ARGNAME_VALUE_4(arg1,arg2,arg3,arg4) \
{ \
	HI_COUT_ARGNAME_VALUE_3(arg1,arg2,arg3) \
	HI_COUT_ARGNAME_VALUE(arg4) \
}
#define HI_COUT_ARGNAME_VALUE_5(arg1,arg2,arg3,arg4,arg5) \
{ \
	HI_COUT_ARGNAME_VALUE_4(arg1,arg2,arg3,arg4); \
	HI_COUT_ARGNAME_VALUE(arg5); \
}

#define HI_COUT_ARGNAME_VALUE_6(arg1,arg2,arg3,arg4,arg5,arg6) \
{ \
	HI_COUT_ARGNAME_VALUE_5(arg1,arg2,arg3,arg4,arg5); \
	HI_COUT_ARGNAME_VALUE(arg6); \
}

#endif //_UNUSE_HI_COUT_RET_OR_OUT


#define CLASSNAME(classptr) \
	HiStringList::split(" ",typeid(classptr).name())[1];


#ifndef _SERVICE_
#define PlatApplication Ice::Application
#else
#define PlatApplication Ice::Service
#endif 

#define GLOBALMUTEX \
namespace \
{ \
	IceUtil::Mutex* staticMutex = 0; \
	class Init \
	{ \
	public: \
		Init() \
		{ \
			staticMutex = new IceUtil::Mutex; \
		} \
		~Init() \
		{ \
			delete staticMutex; \
			staticMutex = 0; \
		} \
	}; \
	Init init; \
}

#endif // __COREMACRO_H__



