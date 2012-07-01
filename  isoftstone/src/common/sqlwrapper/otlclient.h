

#ifndef _OTLCLIENT_H_
#define _OTLCLIENT_H_

#define  OTL_ORA11G
#define  OTL_ORA_OCI_ENV_CREATE


#include <Ice/Ice.h>
#include <iostream>
#include <stdio.h>
#include <occi.h>
#include "otlv4.h"
#include "escore.h"
#include "llogger.h"


enum EDbType
{
	eOracle,
	eSqlServer,
	eDB2,
	eMySql
};


enum ESQLQuery
{
	eNoQuery,
	eQuery
};

enum ETableOperation
{
	eGetCount,
	eDropTable,
	eTruncateTable
};

inline void catchException(otl_exception& e)
{
	char* msg = new char[1000];
	sprintf_s(msg,1000,"%s",e.msg);
	CLogger::instance()->error(msg);      // print out error message
	delete msg;
	msg = NULL;
	CLogger::instance()->error(e.stm_text); // print out SQL that caused the error
	CLogger::instance()->error(e.var_info); // print out the variable that caused the error
}

class CStatement;

class LIBCORE_EXPORT COtlConnection : public IceUtil::Shared
{
public:

	COtlConnection()
	{
		otl_connect::otl_initialize();
		m_connected = false;
		m_db_type = eOracle;
	}

	virtual ~COtlConnection();

	void connect(const std::string& userName,
						const std::string& userPassword,
						const std::string& sid,
						EDbType dbType);

	bool isConnected();

	CStatement* createStatement(const std::string& exeSQL);

	void terminateStatement(CStatement* state);

	void disConnected();


public:

	static bool expDB(const std::string& user,const std::string& passwd,const std::string& sid,
				 const std::string& file);

	static bool autoExpDB(const std::string& user,const std::string& passwd,const std::string& sid);

private:

	bool m_connected;

	EDbType m_db_type;

public:

	otl_connect m_otl_db;

	friend class CStatement;

};


class CRecord;
typedef std::vector< CRecord > CRecordSeq;

class LIBCORE_EXPORT CStatement 
{
public:

	CStatement(COtlConnection* connection,const std::string& exeSQL);

	CStatement(COtlConnection* connection);

	virtual ~CStatement();

	long executeNoQuery(const std::string& sql);

	void executeQuery(const std::string& sql);

	void execute(ESQLQuery query = eNoQuery);

	unsigned int executeTable(const std::string& table,ETableOperation oper);

	void setSQL(const std::string& exeSQL);

	void insertRecord(CRecord* record);

	void insertRecords(CRecordSeq* records);

	void destroy();

private:

	std::string m_executeSQL;

	COtlConnection* m_connection;

public:

	friend CRecord;
};

// 需要被继承来实现数据的封装工作
// 并且派生类要设置成员变量结构

class LIBCORE_EXPORT CRecord
{
public:

	CRecord(CStatement* state,const std::string& exeSQL = ""):
	  m_connect_db(state->m_connection->m_otl_db)
	  {
		  m_state  = state;
		  m_bufferSize = 10;
		  m_exeSQL = exeSQL;
		  m_exeSQL = m_state->m_executeSQL;
		  m_stream.set_commit(false);
	  }

	  virtual ~CRecord()
	  {
		 m_stream.close();
	  }

	  void setSQL(const std::string& exeSQL)
	  {
		  m_exeSQL = exeSQL;
	  }

	  virtual void operator()()
	  {
		  try
		  {	
			  m_stream.open(m_bufferSize,m_exeSQL.c_str(),m_connect_db);
			  setData();
			  m_connect_db.commit_nowait();
		  }
		  catch (otl_exception& e)
		  {
			  catchException(e);
		  }

	  }

	  virtual void setData()
	  {
		  
	  }

	  void setBufferSize(int size)
	  {
		  m_bufferSize = size;
	  }
protected:

	std::string m_exeSQL;

	int m_bufferSize;

	otl_stream m_stream;

	CStatement* m_state;

	otl_connect& m_connect_db;
};

template <class SData>
class LIBCORE_EXPORT CRecordSet : public CRecord
{
public:

	CRecordSet(CStatement* state,const std::string& exeSQL = ""):CRecord(state,exeSQL)
	{
		
	}

	virtual void setData()
	{
	}
	
	virtual void fillData(SData& data)
	{

	}

	virtual void getData()
	{
		m_dataSeq.clear();
		
		m_dataSeq.reserve(255);
		while(!m_stream.eof())
		{
			SData data;
			fillData(data);
			m_dataSeq.push_back(data);
		}

	}

	std::vector< SData > m_dataSeq;
};

#endif _OTLCLIENT_H_