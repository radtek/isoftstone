
/*

OCCI �����÷�ʹ��˵����
1. �����typ�ļ��е�type����Ԫ��תΪ��һ��c++�ļ����ǳ�����ʹ�á�
	ott userid=demousr intype=demo2.typ code=cpp hfile=demo2.h
	cppfile=demo2.cpp mapfile= mappings.cpp attraccess=private

*/
#include <string>
#include "connectpool.h"
#include "llogger.h"
#include "HiString.h"

using namespace std;

COcciPool* COcciPool::s_occiPool = NULL;

COcciPool* COcciPool::instance(void)
{
	if (s_occiPool == NULL)
	{
		s_occiPool = new COcciPool();
	}
	return s_occiPool;
}

COcciPool::COcciPool() 
{
}

COcciPool::~COcciPool () throw (SQLException)
{
	if (m_env)
	{
		destroyPool();
	}
} 

void COcciPool::init(const std::string& user,const std::string& passwd,
					 const std::string& netmgr,
					 unsigned int minConn,unsigned int maxConn,unsigned int incrConn )
{
	m_username = user;
	m_passWord = passwd;
	m_netmgr= netmgr;
	m_maxConn = maxConn;
	m_minConn = minConn;
	m_incrConn = incrConn;
	m_connPool = NULL;
	m_connection = NULL;
	m_reconnectCount = 0;
	m_occiErrorCode = 0;
	m_env = Environment::createEnvironment (Environment::DEFAULT);
}

void COcciPool::connectPool()
{
	try
	{
		CLogger::instance()->debug("OCCI ���ӳس��Դ�������");
		m_connPool = m_env->createConnectionPool(m_username, 
												 m_passWord,
												 m_netmgr, 
												 m_minConn, 
												 m_maxConn, 
												 m_incrConn);
		if (m_connPool)
		{
			std::string poolName =  m_connPool->getPoolName();
			std::string msg = std::string("����OCCI���ӳض��� - ");
			msg.append(poolName);
			msg.append("�ɹ�,");
			msg.append(" StmtCacheSize :");
			msg.append(HiRTDB::HiString::toString( m_connPool->getStmtCacheSize() ));
			CLogger::instance()->info(msg);

		}
		else
		{
			CLogger::instance()->info("����OCCI���ӳض���ʧ�ܣ���");
			return ;
		}

		m_connPool->setTimeOut(600);
		m_connection = m_connPool->createConnection (m_username, m_passWord);
		
		if (m_connection)
			CLogger::instance()->info("��OCCI���ӳش������Ӷ���ɹ�����");
		else
			CLogger::instance()->info("��OCCI���ӳش������Ӷ���ʧ�ܣ���");

		m_occiErrorCode = 0;

	}
	catch(SQLException ex)
	{
		m_occiErrorCode = catchOcciException(ex);
		throw ex;
	}

}

void COcciPool::destroyPool() throw (SQLException)
{
	try
	{
		CLogger::instance()->debug("OCCI ���ӳ����٣���");
		if (m_connection && m_connPool)
		{
			m_connPool->terminateConnection (m_connection);
			m_env->terminateConnectionPool (m_connPool);
			Environment::terminateEnvironment(m_env);
			m_connection = NULL;
			m_connPool = NULL;
			m_env = NULL;
		}
	}
	catch(SQLException ex)
	{
		catchOcciException(ex);
		m_connection = NULL;
		m_connPool = NULL;
		m_env = NULL;
		throw ex;
	}
}

void COcciPool::reconnectPool() throw (SQLException)
{
	if (m_occiErrorCode == 12154 ||m_occiErrorCode == 12532)
	{
		std::string msg = "OCCI ���ӳ�������������";
		msg.append(HiRTDB::HiString::toString(++m_reconnectCount));
		CLogger::instance()->debug( msg );
		destroyPool();

		if (m_connPool == NULL || m_connection == NULL)
		{
			connectPool();
		}
	}
}
int COcciPool::select(CSelectCommand* command) throw (SQLException)
{
	try
	{
		if (m_connection)
		{
			CConnectSelectCommand connCommand(m_connection,command);
			return connCommand.execute();
		}
	}
	catch(SQLException ex)
	{
		m_occiErrorCode = catchOcciException(ex);
	}

	return 0;
} 

int COcciPool::insert(CInsertCommand* command) throw (SQLException)
{
	try
	{
		if (m_connection)
		{
			CConnectInsertCommand connCommand(m_connection,command);
			return connCommand.execute();
		}
	}
	catch(SQLException ex)
	{
		m_occiErrorCode = catchOcciException(ex);
	}
	return 0;
} 

unsigned int COcciPool::tableAction(CTableActionCommand* command) throw (SQLException)
{
	try
	{
		if (m_connection)
		{
			CConnectUpdateCommand connCommand(m_connection,command);
			return connCommand.execute();
		}
	}
	catch(SQLException ex)
	{
		m_occiErrorCode = catchOcciException(ex);
	}
	return 0;
}

unsigned int COcciPool::tableAction( const std::string& actionSQL,const ETableAction action ) throw (SQLException)
{
	try
	{
		if (m_connection)
		{
			CTableActionCommand command(actionSQL,action);
			return tableAction(&command);
		}
	}
	catch(SQLException ex)
	{
		m_occiErrorCode = catchOcciException(ex);
	}
	return 0;
}

