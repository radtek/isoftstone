
#ifndef _CONNECTPOOL_H
#define _CONNECTPOOL_H

#include "escore.h"
#include <IceUtil/Shared.h>
#include "otlv4.h"
#include <iostream>
#include <occi.h>
#include "llogger.h"
#include "TaskPool.h"
#include "sqlcommand.h"
#include "commoncommand.h"

using namespace oracle::occi;

class LIBCORE_EXPORT COcciPool 
{
public:

	static COcciPool* instance(void);
	static COcciPool* s_occiPool;

	Environment * m_env;

	ConnectionPool * m_connPool;

	Connection * m_connection;

public:

	void init(const std::string& user,const std::string& passwd,
			  const std::string& netmgr,
			  unsigned int minConn = 1,unsigned int maxConn = 2,unsigned int incrConn = 1);

	void connectPool();

	void destroyPool() throw (SQLException);

	void reconnectPool() throw (SQLException);

	int select(CSelectCommand* command) throw (SQLException);

	int insert(CInsertCommand* command) throw (SQLException);

	unsigned int tableAction(CTableActionCommand* count) throw (SQLException);

public:

	unsigned int tableAction(const std::string& ,const ETableAction = eUnknownTableAction ) throw (SQLException);

	unsigned int m_occiErrorCode;

protected:

	std::string m_netmgr;
	std::string m_username ;
	std::string m_passWord ;
	unsigned int m_maxConn ;
	unsigned int m_minConn ;
	unsigned int m_incrConn ;

	unsigned int m_reconnectCount;

private :

	COcciPool () ;

	~COcciPool () throw (SQLException);

}; 

class COcciCheckTask : public HiRTDB::CTaskWrapper
{
public:

	COcciCheckTask(COcciPool* occiPool,const std::string& StrName,IceUtil::Int64 delay = 5000,HiRTDB::ETaskPersistent persistent = HiRTDB::eForever)
		:HiRTDB::CTaskWrapper(StrName,delay,persistent),m_occiPool(occiPool)
	{

	}

	virtual void realizeTask()
	{
		m_occiPool->reconnectPool();
	}

private:

	COcciPool* m_occiPool;
};

#endif _CONNECTPOOL_H