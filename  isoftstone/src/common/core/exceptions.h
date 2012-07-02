
#ifndef __HI_EXCEPTION_H__
#define __HI_EXCEPTION_H__


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

}

#endif // __HI_EXCEPTION_H__