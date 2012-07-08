
#ifndef ODB_API_H
#define ODB_API_H

#include "odb_public.h"

class EXPORT_LIB CODBTable 
{
public:
	static CODBTable* instance();
	static QString getDataType(int datatype,int data_length,bool iskey,bool isNull);
	void destory();

	const QSqlDatabase& getDataBase() const;	
	const QMap<int,TABLE_PARA_STRU>& getTableMap() const;
	QMap<int,FIELD_PARA_STRU> getFieldMap(int tableID);
	TABLE_PARA_STRU getTableParam(int table_id);
	FIELD_PARA_STRU getFiledInfo(int tableID,int fieldID);

	int getTableNoByName(QString table_name);
	QString getTableNameByID(int table_id);
	QString getFieldNameByID(int table_id,int field_id);
	int	getNextID(int table_id);

	void deleteField(int tableID,int field);
	void deleteTable(int tableID);

	void addTable(const TABLE_PARA_STRU& stTable);
	void addField(const FIELD_PARA_STRU& stField);
	void insertToFieldInfo(const FIELD_PARA_STRU& stField);

	void modifyTable(const TABLE_PARA_STRU& stTable);
	void modifyField(const FIELD_PARA_STRU& stField);

private:

	CODBTable();
	~CODBTable();

	void	   initTableAndField();
	FIELD_PARA_STRU idKeyToField(int tableID);
	
private:

	QSqlDatabase	m_db;
	QMap<int,TABLE_PARA_STRU> m_tableMap;
	QMap<int,QMap<int,FIELD_PARA_STRU> > m_fieldMap;
};

#endif