#ifndef _SQLCOMMAND_H_
#define _SQLCOMMAND_H_

#include <occi.h>
#include "llogger.h"
#include "Macro.h"

using namespace oracle::occi;

inline unsigned int catchOcciException(SQLException ex)
{
	std::ostringstream out;
	out<<"������: "<<  ex.getErrorCode();

	CLogger::instance()->error(out.str());
	CLogger::instance()->error(ex.getMessage());
	return ex.getErrorCode();
}

/*
*  SQL��������
*/
class LIBCORE_EXPORT CSQLCommand : public IceUtil::Shared
{
public:

	CSQLCommand(){};

	CSQLCommand(const std::string& exeSQL):m_exeSQL(exeSQL)
	{
		m_state = NULL;
	};

	virtual ~CSQLCommand(){};

	virtual unsigned int execute() = 0;

	void setStatement(Statement* state)
	{
		m_state = state;
	}

	std::string m_exeSQL; 

protected:

	Statement* m_state;
};

/*
*  SQL���Ӽ����������
*/
class LIBCORE_EXPORT CStateCommand : public CSQLCommand
{
public:

	CStateCommand(Statement* stat):m_state(stat)
	{
	}

	CStateCommand(Statement* stat,CSQLCommand* sqlCommand)
		:m_state(stat),m_sqlCommand(sqlCommand)
	{

	}

	void setStatement(Statement* stat)
	{
		m_state = stat;
	}

	void setSQLCommand(CSQLCommand* sqlCommand)
	{
		m_sqlCommand = sqlCommand;
	}

protected:

	Statement* m_state;

	CSQLCommand* m_sqlCommand;
};

/*
*  SQL���Ӽ����������
*/
class LIBCORE_EXPORT CConnectCommand : public CSQLCommand
{
public:

	CConnectCommand(Connection* conn):m_connection(conn)
	{
	}

	CConnectCommand(Connection* conn,CSQLCommand* sqlCommand)
		:m_connection(conn),m_sqlCommand(sqlCommand)
	{

	}

	void setConnection(Connection* conn)
	{
		m_connection = conn;
	}

	void setSQLCommand(CSQLCommand* sqlCommand)
	{
		m_sqlCommand = sqlCommand;
	}

protected:

	Connection* m_connection;

	CSQLCommand* m_sqlCommand;
};

/*
*  ���ݿ��ѯ����
*/
class LIBCORE_EXPORT CSelectCommand : public CSQLCommand
{
public:

	CSelectCommand(const std::string& sql):CSQLCommand(sql){};

	// ��ѯ��������
	virtual unsigned int execute() = 0;

	void setResultSet(ResultSet* rs)
	{
		m_dataSet = rs;
	}

	// ��ѯ�����ǰ�ò�������
	virtual void setPreCondition(Statement*& state)
	{
		HI_UNUSEDP(state);
	}

protected:

	ResultSet * m_dataSet;
};

/*
*  ���ڻỰ�����ݲ�ѯ���ӻ���
*/
class LIBCORE_EXPORT CStateSelectCommand : public CStateCommand
{
public:

	CStateSelectCommand(Statement* stat,CSQLCommand* selectCommand)
		:CStateCommand(stat,selectCommand)
	{
	}

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			m_state->setSQL(m_sqlCommand->m_exeSQL);
			dynamic_cast<CSelectCommand*>(m_sqlCommand)->setPreCondition(m_state);
			ResultSet *rset = m_state->executeQuery();
			dynamic_cast<CSelectCommand*>(m_sqlCommand)->setResultSet(rset);
			m_sqlCommand->execute();
			ret = m_state->getUpdateCount();
			m_state->closeResultSet (rset);

		}
		catch(SQLException ex)
		{
			ret = catchOcciException(ex);
		}
		return ret;
	}

};

/*
*  �������ӵ����ݲ�ѯ���ӻ���
*/
class LIBCORE_EXPORT CConnectSelectCommand : public CConnectCommand
{
public:

	CConnectSelectCommand(Connection* conn,CSQLCommand* selectCommand)
		:CConnectCommand(conn,selectCommand)
	{
	}

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			Statement* stmt = m_connection->createStatement (m_sqlCommand->m_exeSQL);
			dynamic_cast<CSelectCommand*>(m_sqlCommand)->setPreCondition(stmt);
			ResultSet *rset = stmt->executeQuery();
			dynamic_cast<CSelectCommand*>(m_sqlCommand)->setResultSet(rset);
			m_sqlCommand->execute();
			ret = stmt->getUpdateCount();
			stmt->closeResultSet (rset);
			m_connection->terminateStatement (stmt);

		}
		catch(SQLException ex)
		{
			ret= catchOcciException(ex);
		}
		return ret;
	}

};

/*
*  ���ݿ�����װ
*/
class LIBCORE_EXPORT CInsertCommand : public CSQLCommand
{
public:

	CInsertCommand(const std::string& exeSQL):CSQLCommand(exeSQL){};

	virtual unsigned int execute() = 0;

protected:

};


/*
*  ���ڻỰ�����ݿ����Ӳ����װ
*/
class LIBCORE_EXPORT CStateInsertCommand :public CStateCommand
{
public:

	CStateInsertCommand(Statement* stat,CSQLCommand* insertCommand)
		:CStateCommand(stat,insertCommand)
	{
	}

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			m_sqlCommand->setStatement( m_state );
			m_sqlCommand->execute();
			m_state->executeUpdate();
			ret = m_state->getUpdateCount();

		}
		catch(SQLException ex)
		{
			ret = catchOcciException(ex);
		}
		return ret;
	}

};


/*
*  �������ӵ����ݿ����Ӳ����װ
*/
class LIBCORE_EXPORT CConnectInsertCommand :public CConnectCommand
{
public:

	CConnectInsertCommand(Connection* conn,CSQLCommand* insertCommand)
		:CConnectCommand(conn,insertCommand)
	{
	}

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			Statement* stmt = m_connection->createStatement (m_sqlCommand->m_exeSQL);
			stmt->setAutoCommit(false);
			m_sqlCommand->setStatement( stmt );
			m_sqlCommand->execute();
			stmt->executeUpdate();
			m_connection->commit();
			ret = stmt->getUpdateCount();
			m_connection->terminateStatement (stmt);

		}
		catch(SQLException ex)
		{
			ret = catchOcciException(ex);
		}
		return ret;
	}

};


/*
*  ɾ����������
*/
class LIBCORE_EXPORT CDeleteCommand : public CSQLCommand
{
public:

	CDeleteCommand(const std::string& exeSQL):CSQLCommand(exeSQL)
	{

	}

	virtual unsigned int execute() = 0;
};

typedef CDeleteCommand CUpdateCommand;

/*
*  ���ڻỰ�����ݿ�����ɾ����װ
*/
class LIBCORE_EXPORT CStateDeleteCommand : public CStateCommand
{
public:

	CStateDeleteCommand(Statement* stat,CSQLCommand* deleteCommand)
		:CStateCommand(stat,deleteCommand)
	{
		m_state->setAutoCommit(true);
	};

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			unsigned int ret = 0;
			m_sqlCommand->setStatement(m_state);
			ret = m_sqlCommand->execute();
			return ret;
		}
		catch(SQLException ex)
		{
			ret = catchOcciException(ex);
		}
		return ret;
	}

};

typedef CStateDeleteCommand CStateUpdateCommand;
/*
*  �������ӵ����ݿ�����ɾ����װ
*/
class LIBCORE_EXPORT CConnectDeleteCommand : public CConnectCommand
{
public:

	CConnectDeleteCommand(Connection* conn,CSQLCommand* deleteCommand)
		:CConnectCommand(conn,deleteCommand)
	{
	};

	virtual unsigned int execute()
	{
		unsigned int ret = 0;
		try
		{
			Statement* stmt = m_connection->createStatement (m_sqlCommand->m_exeSQL);
			m_sqlCommand->setStatement(stmt);
			ret = m_sqlCommand->execute();
			m_connection->commit();
			m_connection->terminateStatement(stmt);
		}
		catch(SQLException ex)
		{
			ret = catchOcciException(ex);
			throw ex;
		}
		return ret;
	}

};

typedef CConnectDeleteCommand CConnectUpdateCommand;


#endif