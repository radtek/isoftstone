
#ifndef __COREMACRO_H__
#define __COREMACRO_H__

#define  SEPARATORS(OPERATOR) << OPERATOR

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

#define HI_UNUSED(PARAM) void(PARAM);
#define HI_UNUSEDP(PARAM) (void*)(PARAM);

#endif // __COREMACRO_H__



