// --------------------------------------------------------------------------
//    iestypedef.h - 跨平台数据类型定义
//
//    说明：为传输和跨平台考虑，数据类型定义的名字中明确指明各类型长度
//          本文件根据VisiBroker的vdef.h改写
//
//    iES500U Group, iESLab. 2002.10
// --------------------------------------------------------------------------
#ifndef _IESTYPEDEF__H_
#define _IESTYPEDEF__H_

// 引入必要的头文件
// WIN32 is defined by a header that windows.h brings in.  Most BCB apps
// include vcl.h which does not bring in windows.h but rather our own
// windows.hpp.  There are two defines that the BCB compiler automatically turn
// on: _WIN32 and __WIN32__. So here we define WIN32 conditionally for Borland
// compiler 
#if (defined(_WIN32) || defined(__WIN32__))
#	ifndef WIN32
#		define WIN32
#	endif

#elif (defined(sun) || defined(__sun) || defined(__sun__))
#	ifndef SUN
#		define SUN
#	endif

#elif defined(__alpha)
#	ifndef ALPHA
#		define ALPHA
#	endif

#elif defined(_AIX)
#	ifndef AIX
#		define AIX
#	endif

#elif (defined(hpux) || defined(__hpux))
#	ifndef HPUX
#		define HPUX
#	endif

#elif (defined(linux) || defined(__linux) || defined(__linux__))
#	ifndef LINUX
#		define LINUX
#	endif

#else    /* other platform */
#	error 本平台未被支持！

#endif

#if defined(sparc) || defined(__sparc) || defined(_AIX) || defined(hpux) || defined(__hpux)	// sparc(solaris)、powerpc(aix)、itanium(hpux) 平台
#	define LITTLEENDIAN_PLATFORM	0
#else // x86 x64(windows / solaris x86 / linux) 及 alpha(tru64) 平台
#	define LITTLEENDIAN_PLATFORM	1
#endif

#if defined(WIN32)
#	if defined(_MSC_VER)	// microsoft compiler
#		include <wchar.h>
#endif

#elif defined(SUN)
#	include <wchar.h>
#	include <sys/types.h>

#elif defined(ALPHA)
#	include <wchar.h>

#elif defined(HPUX)
#	include <wchar.h>
#	include <sys/types.h>

#elif defined(LINUX)
#	include <wchar.h>
#	include <sys/types.h>

#elif defined(AIX)
#	include <wchar.h>
#	include <sys/types.h>

#else    /* other platform */
#	error 本平台未被支持！

#endif

    typedef char                Jchar;
    typedef wchar_t             Jwchar;

    typedef signed char         Jint8;
    typedef unsigned char       Juint8;
    typedef short               Jint16;
    typedef unsigned short      Juint16;
    typedef float               Jfloat;
    typedef double              Jdouble;

#if defined(AIX)                /* compiler: xlc(cc,c89) */
    typedef int                 Jint32;
    typedef unsigned int        Juint32;
    typedef long long           Jint64;
    typedef unsigned long long  Juint64;
    typedef long long			Jtime;

#elif defined(ALPHA)            /* compiler: cxx (True64) */
    typedef int                 Jint32;
    typedef unsigned int        Juint32;
    typedef long                Jint64;
    typedef unsigned long       Juint64;
    typedef long				Jtime;

#elif defined(WIN32)            /* compiler: microsoft C++ */
    typedef int					Jint32;
    typedef unsigned int		Juint32;
    typedef __int64             Jint64;
    typedef unsigned __int64    Juint64;
    typedef __int64				Jtime;

#elif defined(SUN)              /* SOLARIS: compiler: cc */
    typedef int                 Jint32;
    typedef unsigned int        Juint32;
	typedef long long           Jint64;
	typedef unsigned long long  Juint64;
	typedef long long           Jtime;

#elif defined(HPUX)				/* HP-UX: compiler: aCC */
	typedef int					Jint32;
	typedef unsigned int		Juint32;
	typedef long long			Jint64;
	typedef unsigned long long	Juint64;
	typedef long long			Jtime;

#elif defined(LINUX)            /* LINUX: compiler: gcc */
	typedef int                 Jint32;
	typedef unsigned int        Juint32;
	typedef long long           Jint64;
	typedef unsigned long long  Juint64;
	typedef long long           Jtime;

#else    /* other platform */
    #error 本平台未被支持！

#endif


typedef bool              Jboolean;

const Jboolean JFALSE = 0;
const Jboolean JTRUE  = 1;

/* Define NULL pointer value */
#ifndef NULL
#	ifdef __cplusplus
#		define NULL    0
#	else
#		define NULL    ((void *)0)
#	endif
#endif

#include <cassert>
#if defined(DEBUG) || defined(_DEBUG)
#	undef ASSERT
#	define ASSERT(f)	assert(f)
#endif // DEBUG

// 编译期断言
// 不占用运行时间，Debug、Release 版本有此断言检查
// 采用 C++ 规则：位域位数必须 > 0，模仿出编译期断言
// f 表达式必须是编译期能够求值的，比如 sizeof
// 如果 f 求值为 false，则产生编译期错误：“static_assert_false: 位域类型对位数太小”之类提示
// ！！！此断言只能在函数内部使用，不能在全局变量声明处使用
#	define STATIC_ASSERT(f) \
		{ \
			struct static_assert \
			{ \
				Juint32 static_assert_false:((f)?1:-1); \
			}; \
		}

// 数据类型长度的断言，可以用在应用程序的主函数中
// 以检查上面的数据类型定义是否正确。
// 通过指针的长度进行32 位、64位检查
#ifdef ICCS_64
#	define ASSERTTYPESIZE  \
		STATIC_ASSERT(sizeof(Jint8) == 1 && sizeof(Juint8) == 1 && \
		sizeof(Jint16) == 2 && sizeof(Juint16) == 2 && \
		sizeof(Jint32) == 4 && sizeof(Juint32) == 4 && \
		sizeof(Jint64) == 8 && sizeof(Juint64) == 8 && \
		sizeof(Jfloat) == 4 && sizeof(Jdouble) == 8 && \
		sizeof(Jtime) == 8 && sizeof(Jint32*) == 8)
#else
#	define ASSERTTYPESIZE  \
		STATIC_ASSERT(sizeof(Jint8) == 1 && sizeof(Juint8) == 1 && \
		sizeof(Jint16) == 2 && sizeof(Juint16) == 2 && \
		sizeof(Jint32) == 4 && sizeof(Juint32) == 4 && \
		sizeof(Jint64) == 8 && sizeof(Juint64) == 8 && \
		sizeof(Jfloat) == 4 && sizeof(Jdouble) == 8 && \
		sizeof(Jtime) == 8 && sizeof(Jint32*) == 4)
#endif

/* DISALIGN: 定义对齐方式的宏，此宏在GCC下起作用，紧靠变量或结构定义之后放置，
 * 例如：
 *
 * int x DISALIGN;
 * struct Y
 * {
 *     char[2] a; 
 *     int b;
 * } DISALIGN;
 *
 * 它指定变量或结构使用可能的最小的对齐方式，即变量按字节对齐，
 * 位域按位对齐，实际也就是不对齐(所以起名DISALIGN)。
 *
 * 为了使各平台的结构大小及对齐方式一致，在VC下应定义
 * #pragma pack(push)
 * #pragma pack(1)	// 以字节方式对齐
 * ... 结构定义
 * #pragma pack(pop)
 */
#ifndef DISALIGN
#	if defined(__GNUG__)	// GCC编译器预定义的宏
#		define DISALIGN __attribute__((packed))
#	else
#		define DISALIGN
#	endif
#endif

#endif //_IESTYPEDEF__H_
