/*********************************************************************************
 *
 * @file	HiException.h
 * @version	1.0
 * @date	2010-01-11
 * @author	刘瑞功
 *
 * @brief	异常处理类
 *
 ********************************************************************************/
 // 版权(C) 2009 - 2010 海信网络科技
 // 改动历史
 // 日期		作者	改动内容
 // 2010-01-11  刘瑞功  创建文件
 //===============================================================================

#ifndef __HI_EXCEPTION_H__
#define __HI_EXCEPTION_H__


#include <Ice/Exception.h>
#include <Ice/LocalException.h>
#include <stdexcept>
#include "escore.h"
#include "iestypedef.h"

#define COUT_ICE_EXCEPTION(NUM,ECONTEXT) \
{ \
	cout << "异常" << NUM <<" = 异常文件:  " << __FILE__ << "\n异常函数:  " << __FUNCTION__ << "\n异常行数:  " << __LINE__ << endl; \
	cout << "\n异常内容  :" << ECONTEXT << endl; \
}

#define COUT_SYSTEM_EXCEPTION(NUM,ECONTEXT) \
{ \
	cout << "\n异常" << NUM <<" = 异常文件:  " << __FILE__ << "\n异常函数:  " << __FUNCTION__ << "\n异常行数:  " << __LINE__ << endl; \
	ostringstream ostr; \
	ostr<< "caught unhandled std::exception:"<< ECONTEXT; \
	cout << ostr.str();\
}

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
	COUT_SYSTEM_EXCEPTION("未知","未知异常") \
}

namespace core
{


class LIBCORE_EXPORT CException : public std::exception
{
public:

	virtual ~CException() throw ();

	virtual const char* what() const throw();

protected:

	CException(const std::string& reason);

private:

	std::string m_reason;
};


class LIBCORE_EXPORT CLogicException : public CException
{
public:

	virtual ~CLogicException() throw ();
protected:

	CLogicException(const std::string& reason);
};


class LIBCORE_EXPORT CRuntimeException : public CException
{
public:

	virtual ~CRuntimeException() throw ();
protected:

	CRuntimeException(const std::string& reason);
};


class LIBCORE_EXPORT CMemoryException : public CRuntimeException
{
public:

	CMemoryException();

	CMemoryException(const std::string& reason);

	virtual ~CMemoryException() throw ();
};


class LIBCORE_EXPORT CFileException : public CRuntimeException
{
public:

	CFileException();

	CFileException(const std::string& reason);

	virtual ~CFileException() throw ();
};

class LIBCORE_EXPORT CCommunicationException : public CRuntimeException
{
public:
	
	CCommunicationException();
	
	CCommunicationException(const std::string& reason);
	
	virtual ~CCommunicationException() throw ();
};


class LIBCORE_EXPORT CCommonException : public CRuntimeException
{
public:
	
	CCommonException();
	
	CCommonException(const std::string& reason);
	
	virtual ~CCommonException() throw ();
};

LIBCORE_EXPORT std::string exception2string(const std::exception& e);
LIBCORE_EXPORT std::string exception2string(const CException& e);
LIBCORE_EXPORT std::string exception2string(const Ice::Exception& e);
LIBCORE_EXPORT std::string exception2string(const Ice::SystemException& e);


}

#endif // __HI_EXCEPTION_H__