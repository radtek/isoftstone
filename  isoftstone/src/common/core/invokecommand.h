
#ifndef _INVOKECOMMAND_H
#define _INVOKECOMMAND_H

#include <IceUtil/Shared.h>
#include <Ice/Initialize.h>
#include <Ice/ObjectAdapter.h>
#include <Ice/Stream.h>
#include <Ice/LocalException.h>
#include <IceUtil/Mutex.h>

#include "escore.h"

class LIBCORE_EXPORT CInvokeCommand : public IceUtil::Shared
{
public:

	CInvokeCommand()
	{
	}

	CInvokeCommand(const std::vector<Ice::Byte>& inParams,
				   const Ice::Current& current)
	{
		setParams(inParams,current);
	}

	void setParams(const std::vector<Ice::Byte>& inParams,
					const Ice::Current& current)
	{
		m_inParams = inParams;
		m_current = current;
		m_communicatorPtr = m_current.adapter->getCommunicator();
		m_inStream = Ice::createInputStream(m_communicatorPtr, m_inParams);
		m_outStream = Ice::createOutputStream(m_communicatorPtr); 
	}

	virtual ~CInvokeCommand(){}

	virtual bool execute(std::vector<Ice::Byte>& outParams) = 0;

protected:

	Ice::CommunicatorPtr m_communicatorPtr;

	std::vector<Ice::Byte> m_inParams;

	Ice::Current m_current;

	Ice::InputStreamPtr m_inStream;

	Ice::OutputStreamPtr m_outStream;

};

typedef IceUtil::Handle< CInvokeCommand > CInvokeCommandPtr;

class LIBCORE_EXPORT CInvokeCommandProxy : public CInvokeCommand
{
public:

	CInvokeCommandProxy()
	{
		m_invokeCommands.clear();
	}

	virtual ~CInvokeCommandProxy()
	{
		IceUtil::Mutex::Lock lock(m_mutex);
		m_invokeCommands.clear();
	}

	void registerCommand(const std::string& oper, CInvokeCommand* command)
	{
		IceUtil::Mutex::Lock lock(m_mutex);
		m_invokeCommands.insert(std::make_pair(oper,CInvokeCommandPtr(command)));
	}

	virtual bool execute(std::vector<Ice::Byte>& outParams)
	{
		bool ret = false;
		IceUtil::Mutex::Lock lock(m_mutex);

		std::map<std::string , CInvokeCommandPtr>::iterator iter = m_invokeCommands.find(m_current.operation);
		if (iter != m_invokeCommands.end())
		{
			CInvokeCommandPtr command = iter->second;
			command->setParams(m_inParams,m_current);
			ret = command->execute(outParams);
		}
		else
		{
			Ice::OperationNotExistException ex(__FILE__, __LINE__);
			ex.id = m_current.id;
			ex.facet = m_current.facet;
			ex.operation = m_current.operation;
			throw ex;
		}
		return ret;
	}


private:

	IceUtil::Mutex m_mutex;

	std::map<std::string , CInvokeCommandPtr> m_invokeCommands;
};

typedef IceUtil::Handle< CInvokeCommandProxy > CInvokeCommandProxyPtr;

#endif