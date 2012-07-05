#ifndef _ESCORE_H_
#define _ESCORE_H_

#ifdef WIN32		// windows platform
#  ifdef ESCORE
#    define LIBCORE_EXPORT  __declspec(dllexport)
#  else
#    define LIBCORE_EXPORT  __declspec(dllimport)
#  endif
#  pragma warning( disable : 4251 4275) 
#else	// other platform
#  define LIBCORE_EXPORT
#endif // WIN32

#ifdef WIN32		// windows platform
#  ifndef ESCORE
#    define LIBCORE_EXPORT_DLL  __declspec(dllexport)
#  else
#    define LIBCORE_EXPORT_DLL  __declspec(dllimport)
#  endif
#  pragma warning( disable : 4251 4275) 
#else	// other platform
#  define LIBCORE_EXPORT
#endif // WIN32

#ifdef WIN32		// windows platform
#  ifndef ESCOMMON 
#    define LIBESCOMMON_EXPORT  __declspec(dllexport)
#  else
#    define LIBESCOMMON_EXPORT  __declspec(dllimport)
#  endif
#  pragma warning( disable : 4251 4275) 
#else	// other platform
#  define LIBCORE_EXPORT
#endif // WIN32


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#endif // _ESCORE_H_
