
#ifndef VCIM_DB_DATA_H
#define VCIM_DB_DATA_H

#include <QString>
#include <QPair>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#ifdef WIN32
#include "rtdb_api_sim.h"
#else
#include "rtdb_api.h"
#endif


/*
	实时库封装类
*/

#define READBUFFER_SIZE 1024
#define MAX_LEN   1024

typedef QPair<bool,TB_DESCR> TABLE_PAIR;
typedef QPair<int,FIELD_PARA_STRU> FIELD_PARA_PAIR;


class VCimTable
{
public:
	
	VCimTable();
	VCimTable(int tableID);
	VCimTable(char* table_name);
	~VCimTable();

	bool	   openTableByID(qint64 appId,int contextId,int tableId = -1);
	bool       openTableByName(char* appName,char* contextName,char* tableName);
	bool	   reOpen(qint64 appId,int contextId);

	int		   getFiledsByID(char* recID,int* filedArray,int fieldNum,int bufSize,char* pBuf);
	int		   getFiledsByName(char* recID,char* filedName,int bufSize,char* pBuf);
	int		   getTableFields(char* filedNames,char** pBuf);
	bool	   getFiledIDByNames(char* filedNames,int* filedArray,int* fieldNum);
	void	   getStringField(const QVector<quint64>& resourceIDS,const QString& strField,QStringList& lstNames);
	void	   getLongField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<quint64>& vecValues);
	
	void       getSingleField(const quint64 &resourceID,const QString& strField,quint64 &vecValue);
	
	void	   getFloatField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<float>& vecValues);
	void	   getIntField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<int>& vecValues);

	// 获得表中特定列的值
	void	   getVariantField(const QVector<quint64>& resourceIDS,int fieldID,QMap<quint64,QVariant>& valueMap);
	void	   getVariantField2(const QVector<quint64>& resourceIDS,int fieldID,QMap<quint64,QVariant>& valueMap);
	void	   getVariantField(const quint64& resourceID,int fieldID,QVariant& value);
	void	   getVariantFiled(const FIELD_PARA_STRU& param,int nRecSize,char* buf_ptr,int nBufferSize,QMap<quint64,QVariant>& valueMap);

	//获得表中所有的数据保存到 vecRows中
	void	   getTableRecs(QVector< QVector<QVariant> >& vecRows);  
	void	   getRecByID(quint64 keyid,QVector<QVariant>& vecValues);  
	void	   getRecsByID(QVector<quint64> vecKeyid,QVector< QVector<QVariant> >& vecRows); 
	void	   getRecsBySQL(const QString& strSQL,QVector< QVector<QVariant> >& vecRows);  

	bool	   isRecordExist(quint64 keyid);

	// 删除数据
	void	   deleteRecord(quint64 keyID);

	// 修改数据
	void	   updateRecord(quint64 keyID,int buf_size,char* buf_ptr);
	void	   updateFiled(quint64 keyID,int filed,int buf_size,char* buf_ptr);

	// 添加数据
	void	   insertRecord(int buf_size,char* buf_ptr);

	bool	   isTableOpen();
	TB_DESCR   getTableDesc();
	int		   getTableID();
	int		   getContextID();
	qint64	   getAppID();
	bool	   getTableParam(TABLE_PARA_STRU& param);
	bool	   getFieldsPara(QVector<FIELD_PARA_STRU>& vecParams);
	int		   getFieldPara(int filedID,FIELD_PARA_STRU* param);
	QVariant   getFiledValue(char* tmp_ptr,int nLen,int qID);
	int		   getFiledNo(char* filedName);

	quint64    getNextID();
	void	   getFiledMap(int filedID,QMap<quint64,QVariant >& mapFiled);

	int		   free(void* ptr);
	void	   closeTable();

private:

	template<class T>
	void	   getNumberField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<T>& vecValues);

	void	   initDataType();

private:
	
	int		   m_TableID;
	QString	   m_TableName;
	qint64	   m_AppID;
	int		   m_ContextID;
	TABLE_PAIR m_TablePair;
	QMap<int,int>	m_DataTypeToQt;

public:

	static KEY_STRU long_to_keyid(unsigned long keyid);
	static short	long_to_tableNo(unsigned long keyid);
	static short	long_to_field_id(unsigned long keyid);
	static int		getTableNoByName(char* table_name);
	static QString	getTableNameByID(int nTableID);
	
};

template<class T>
inline void assign(QVariant& var,char* pos,int len)
{
	T v;
	memcpy(&v,pos,len);
	var = QVariant(v);
}

class VCimTableMgr
{
public:

	VCimTableMgr* instance();
	void destroy();

	void createTable(int tableID);
	void deleteTable(int tableID);
	VCimTable* getTable(int tableID);
	
	bool isTableOpen(int tableID);

private:

	VCimTableMgr();
	~VCimTableMgr();

private:

	QMap<int,VCimTable*> m_TableMap;
	QMutex*				 m_TableMutex;

	static VCimTableMgr*  s_TableManager;

};

#endif