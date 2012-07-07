
#ifndef ODB_API_H
#define ODB_API_H

#include "odb_public.h"

class EXPORT_LIB CODBTable 
{
public:
	static CODBTable* instance();
	void destory();

	const QSqlDatabase& getDataBase() const;	
	const QMap<int,TABLE_PARA_STRU>& getTableMap() const;
	QMap<int,FIELD_PARA_STRU> getFieldMap(int tableID);
	TABLE_PARA_STRU getTableParam(int table_id);
	FIELD_PARA_STRU getFiledInfo(int tableID,int fieldID);

	int getTableNoByName(QString table_name);
	QString getTableNameByID(int table_id);
	int	getNextID(int table_id);

private:

	CODBTable();
	~CODBTable();

	void	   initTableAndField();
	
private:

	QMap<int,TABLE_PARA_STRU> m_tableMap;
	QMap<int,QMap<int,FIELD_PARA_STRU> > m_fieldMap;
	QSqlDatabase	m_db;
};

#endif