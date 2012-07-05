// --------------------------------------------------------------------------
//    iestypedef.h - ��ƽ̨�������Ͷ���
//
//    ˵����Ϊ����Ϳ�ƽ̨���ǣ��������Ͷ������������ȷָ�������ͳ���
//          ���ļ�����VisiBroker��vdef.h��д
//
//    iES500U Group, iESLab. 2002.10
// --------------------------------------------------------------------------
#ifndef _IESTYPEDEF__H_
#define _IESTYPEDEF__H_

// �����Ҫ��ͷ�ļ�
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
#	error ��ƽ̨δ��֧�֣�

#endif

#if defined(sparc) || defined(__sparc) || defined(_AIX) || defined(hpux) || defined(__hpux)	// sparc(solaris)��powerpc(aix)��itanium(hpux) ƽ̨
#	define LITTLEENDIAN_PLATFORM	0
#else // x86 x64(windows / solaris x86 / linux) �� alpha(tru64) ƽ̨
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
#	error ��ƽ̨δ��֧�֣�

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
    #error ��ƽ̨δ��֧�֣�

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

// �����ڶ���
// ��ռ������ʱ�䣬Debug��Release �汾�д˶��Լ��
// ���� C++ ����λ��λ������ > 0��ģ�³������ڶ���
// f ���ʽ�����Ǳ������ܹ���ֵ�ģ����� sizeof
// ��� f ��ֵΪ false������������ڴ��󣺡�static_assert_false: λ�����Ͷ�λ��̫С��֮����ʾ
// �������˶���ֻ���ں����ڲ�ʹ�ã�������ȫ�ֱ���������ʹ��
#	define STATIC_ASSERT(f) \
		{ \
			struct static_assert \
			{ \
				Juint32 static_assert_false:((f)?1:-1); \
			}; \
		}

// �������ͳ��ȵĶ��ԣ���������Ӧ�ó������������
// �Լ��������������Ͷ����Ƿ���ȷ��
// ͨ��ָ��ĳ��Ƚ���32 λ��64λ���
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

/* DISALIGN: ������뷽ʽ�ĺ꣬�˺���GCC�������ã�����������ṹ����֮����ã�
 * ���磺
 *
 * int x DISALIGN;
 * struct Y
 * {
 *     char[2] a; 
 *     int b;
 * } DISALIGN;
 *
 * ��ָ��������ṹʹ�ÿ��ܵ���С�Ķ��뷽ʽ�����������ֽڶ��룬
 * λ��λ���룬ʵ��Ҳ���ǲ�����(��������DISALIGN)��
 *
 * Ϊ��ʹ��ƽ̨�Ľṹ��С�����뷽ʽһ�£���VC��Ӧ����
 * #pragma pack(push)
 * #pragma pack(1)	// ���ֽڷ�ʽ����
 * ... �ṹ����
 * #pragma pack(pop)
 */
#ifndef DISALIGN
#	if defined(__GNUG__)	// GCC������Ԥ����ĺ�
#		define DISALIGN __attribute__((packed))
#	else
#		define DISALIGN
#	endif
#endif

#endif //_IESTYPEDEF__H_
