#ifndef _ICE_CORE_H_
#define _ICE_CORE_H_

#ifdef WIN32		// windows platform
#  ifdef ICECORE
#    define LIB_ICECORE_EXPORT  __declspec(dllexport)
#  else
#    define LIB_ICECORE_EXPORT  __declspec(dllimport)
#  endif
#  pragma warning( disable : 4251 4275) 
#else	// other platform
#  define LIB_ICECORE_EXPORT
#endif // WIN32

#endif // _ESCORE_H_
