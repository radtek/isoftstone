
#include "iestypedef.h"
#include "iceexceptions.h"

namespace core
{

std::string exception2string(const Ice::Exception& e)
{
	std::string strMsg = std::string(e.ice_name());
	if (strMsg.empty())
	{
		strMsg =std::string("�����ݵ� ICE ��׼�쳣");
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
			strMsg = std::string("�����ݵ� ICE ϵͳ�쳣");
		}
	}
	return strMsg;
}

}