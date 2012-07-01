
#include <iostream>
#include <stdio.h>

#include "otlclient.h"
#include "otlv4.h"
#include "llogger.h"
#include "Properties.h"
#include "TimeWrapper.h"
#include "Macro.h"

#define OTL_ODBC 

using namespace std;


COtlConnection::~COtlConnection()
{
	
}

void COtlConnection::connect(const std::string& userName,
						const std::string& userPassword,
						const std::string& sid,
						EDbType dbType)
{
	m_db_type = dbType;
	std::string strConnect = "";
	switch(dbType)
	{
	case eSqlServer:
		{
			strConnect = "UID=";
			strConnect.append(userName);
			strConnect.append("PWD=");
			strConnect.append(userPassword);
			strConnect.append("DSN=");
			strConnect.append(sid);
		}

		break;
	case eOracle:
	default:
		{
			strConnect.append(userName);
			strConnect.append("/");
			strConnect.append(userPassword);
			strConnect.append("@");
			strConnect.append(sid);
		}
		break;
	}

	try
	{
		m_otl_db.rlogon(strConnect.c_str());
	}
	catch ( otl_exception& e)
	{
		catchException(e);
	}

}

bool COtlConnection::isConnected()
{
	return m_connected;
}

CStatement* COtlConnection::createStatement(const std::string& exeSQL)
{
	CStatement* state = new CStatement(this,exeSQL);
	return state;
}

void COtlConnection::terminateStatement(CStatement* state)
{
	state->destroy();
}

void COtlConnection::disConnected()
{
	try
	{
		m_otl_db.logoff();
	}
	catch (otl_exception& e)
	{
		catchException(e);
	}
	
}


bool COtlConnection::expDB(const std::string& user,const std::string& passwd,const std::string& sid,
			 const std::string& file)
{
	// 获取 ORACLE 安装目录
	string oracle_home = HiRTDB::CEnvVariable::instance()->getEnv("ORACLE_HOME");

	string expstr;
	if (oracle_home.empty())
	{
		return 0;
	}
	expstr = oracle_home;
	expstr += "/bin/";
	expstr += "exp ";
	expstr += user;
	expstr += "/";
	expstr += passwd;
	expstr += "@";
	expstr += sid;
	expstr += " file=";
	expstr += file;

	return (system(expstr.c_str()) == 0);
}

bool COtlConnection::autoExpDB(const std::string& user,const std::string& passwd,const std::string& sid)
{
	string file = HiRTDB::CEnvVariable::instance()->getTempPath("minidbarchive");
	file +=	HiRTDB::CTimeWrapper::getCurrentTimeString(eHiHour);
	file += ".dmp";
	return expDB(user,passwd,sid,file);
}

////////////// statement //////

CStatement::CStatement(COtlConnection* connection)
{
	m_connection = connection;
}

CStatement::CStatement(COtlConnection* connection,const std::string& exeSQL)
{
	m_connection = connection;
	m_executeSQL = exeSQL;
}

CStatement::~CStatement()
{
}

long CStatement::executeNoQuery(const std::string& sql)
{
	long ret = 0;
	try
	{
		return otl_cursor::direct_exec(m_connection->m_otl_db,sql.c_str(),otl_exception::enabled); 
	}
	catch (otl_exception& e)
	{
		catchException(e);
	}
	return ret;
}


void CStatement::executeQuery(const std::string& sql)
{
	Hi_UNUSED(sql);
}

void CStatement::execute(ESQLQuery query)
{
	switch (query)
	{
	case eNoQuery:
	default:
		executeNoQuery(m_executeSQL);
		break;

	}
}

unsigned int CStatement::executeTable(const std::string& table,ETableOperation oper)
{
	string exeSQL = "";
	switch (oper)
	{
	case eGetCount:  // 计算表格行数
		{
			unsigned int count = 0;
			switch (m_connection->m_db_type)
			{
			case eSqlServer:
				{
					exeSQL = "SELECT SUM(*) FROM ";
				}
				break;
			case eOracle:
			default:
				{
					exeSQL = "SELECT COUNT(*) FROM ";
				}
				break;
			}
	
			exeSQL.append(table);
			try
			{
				otl_stream otl_st(1,exeSQL.c_str(),m_connection->m_otl_db ); 
				if (!otl_st.eof())
				{
					otl_st >> count;
				}
			}
			catch (otl_exception& e)
			{
				catchException(e);
			}
			return count;
		}
		break;
	case eDropTable: // 删除表格
		{
			exeSQL = "DROP TABLE ";
			exeSQL.append(table);
			return executeNoQuery(exeSQL);
		}
		break;

	case eTruncateTable:
		{
			exeSQL = "TRUNCATE TABLE ";
			exeSQL.append(table);
			return executeNoQuery(exeSQL);
		}
		break;
	}
	return 0;

}

void CStatement::setSQL(const std::string& exeSQL)
{
	m_executeSQL = exeSQL;
}

void CStatement::insertRecord(CRecord* record)
{	
	(*record)();
}

void CStatement::insertRecords(CRecordSeq* records)
{
	std::for_each(records->begin(),records->end(),std::mem_fun_ref(&CRecord::operator ()));
}

void CStatement::destroy()
{
	
}