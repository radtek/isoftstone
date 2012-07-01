
/*

OCCI 经典用法使用说明：
1. 此命令将typ文件中的type类型元素转为成一个c++文件，非常方便使用。
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
		CLogger::instance()->debug("OCCI 连接池尝试创建！！");
		m_connPool = m_env->createConnectionPool(m_username, 
												 m_passWord,
												 m_netmgr, 
												 m_minConn, 
												 m_maxConn, 
												 m_incrConn);
		if (m_connPool)
		{
			std::string poolName =  m_connPool->getPoolName();
			std::string msg = std::string("创建OCCI连接池对象 - ");
			msg.append(poolName);
			msg.append("成功,");
			msg.append(" StmtCacheSize :");
			msg.append(HiRTDB::HiString::toString( m_connPool->getStmtCacheSize() ));
			CLogger::instance()->info(msg);

		}
		else
		{
			CLogger::instance()->info("创建OCCI连接池对象失败！！");
			return ;
		}

		m_connPool->setTimeOut(600);
		m_connection = m_connPool->createConnection (m_username, m_passWord);
		
		if (m_connection)
			CLogger::instance()->info("从OCCI连接池创建连接对象成功！！");
		else
			CLogger::instance()->info("从OCCI连接池创建连接对象失败！！");

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
		CLogger::instance()->debug("OCCI 连接池销毁！！");
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
		std::string msg = "OCCI 连接池重连，次数：";
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

