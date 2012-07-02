
#include "iestypedef.h"
#include "exceptions.h"
#include <qobject.h>

namespace core
{


CException::CException(const std::string& reason)
: m_reason(reason)
{
}

//##ModelId=407A3D910204
CException::~CException() throw ()
{
}

//##ModelId=407B41A900CF
const char* CException::what() const throw()
{
	return m_reason.c_str();
}

//##ModelId=407A3D91024D
CLogicException::CLogicException(const std::string& reason)
: CException(reason)
{
}

//##ModelId=407A3D91024B
CLogicException::~CLogicException() throw ()
{
}

//##ModelId=407A3D91034F
CRuntimeException::CRuntimeException(const std::string& reason)
: CException(reason)
{
}

//##ModelId=407A3D910331
CRuntimeException::~CRuntimeException() throw ()
{
}

//////////////////////////////////////////////////////////////////////
// CMemoryException
//////////////////////////////////////////////////////////////////////

//##ModelId=3E9A20A602BE
CMemoryException::CMemoryException()
: CRuntimeException(std::string("内存分配失败"))
{
}

//##ModelId=3E9CFDDA0017
CMemoryException::CMemoryException(const std::string& reason)
: CRuntimeException(reason)
{
}
//##ModelId=3E9A20A602BF
CMemoryException::~CMemoryException() throw ()
{
}

//////////////////////////////////////////////////////////////////////
// CFileException
//////////////////////////////////////////////////////////////////////

//##ModelId=3E9A20A602AA
CFileException::CFileException()
: CRuntimeException(std::string("未知的文件错误"))
{
}

//##ModelId=3E9A20A602B3
CFileException::CFileException(const std::string& reason)
: CRuntimeException(reason)
{
}

//##ModelId=3E9A20A602B5
CFileException::~CFileException() throw ()
{
}

CCommunicationException::CCommunicationException()
: CRuntimeException(std::string("通讯错误或通讯数据错误"))
{
}

//##ModelId=3E9CFDD902B4
CCommunicationException::CCommunicationException(const std::string& reason)
: CRuntimeException(reason)
{
}

//##ModelId=3E9CFDD9032C
CCommunicationException::~CCommunicationException() throw ()
{
}

//////////////////////////////////////////////////////////////////////
// CCommonException
//////////////////////////////////////////////////////////////////////

//##ModelId=3EA634A402F4
CCommonException::CCommonException()
: CRuntimeException(std::string("未说明原因的错误"))
{
}

//##ModelId=3EA634A40312
CCommonException::CCommonException(const std::string& reason)
: CRuntimeException(reason)
{
}

//##ModelId=3EA634A4033B
CCommonException::~CCommonException() throw ()
{
}

std::string exception2string(const std::exception& e)
{
	std::string strMsg = std::string(e.what());
	if (strMsg.empty())
	{
		strMsg = std::string("空内容的 C++ 标准异常");
	}
	return strMsg;
}

std::string exception2string(const CException& e)
{
	std::string strMsg = std::string(e.what());
	if (strMsg.empty())
	{
		strMsg = std::string("空内容的 LCSH 标准异常");
	}
	return strMsg;
}


}