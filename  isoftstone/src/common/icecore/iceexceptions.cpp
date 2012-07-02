
#include "iestypedef.h"
#include "iceexceptions.h"

namespace core
{

std::string exception2string(const Ice::Exception& e)
{
	std::string strMsg = std::string(e.ice_name());
	if (strMsg.empty())
	{
		strMsg =std::string("空内容的 ICE 标准异常");
	}
	return strMsg;
}

std::string exception2string(const Ice::SystemException& e)
{
	std::string strMsg = std::string(e.ice_name());
	if (strMsg.empty())
	{
		strMsg = std::string(e.what());
		if (strMsg.empty())
		{
			strMsg = std::string("空内容的 ICE 系统异常");
		}
	}
	return strMsg;
}

}