
#include "odb_api.h"
#include "config.h"

CODBTable* CODBTable::instance()
{
	static CODBTable* s_odb = NULL;
	if (!s_odb)
	{
		s_odb = new CODBTable;
	}
	return s_odb;
}

void CODBTable::destory()
{
	m_tableMap.clear();
	m_fieldMap.clear();
}

CODBTable::CODBTable()
{
	initTableAndField();
}

CODBTable::~CODBTable()
{	

}

void CODBTable::initTableAndField()
{
	QString strDir = CConfig::instance()->getBackupDir();
	QString strDB = strDir + "edcc.s3db";
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(strDB);
	if (!m_db.open())
	{
		qDebug() << "Open Database Error!";
		return;
	}

	// 从表信息表和域信息表中读取模型信息，这两个表内容不会在dbi中修改
	QSqlQuery query(m_db);
	query.exec("select id,en_name,cn_name,next_rec_id from tableinfo");
	while (query.next())
	{
		QSqlRecord rec = query.record();
		TABLE_PARA_STRU stru;
		int i = 0;
		stru.table_id = rec.value(i++).toInt();
		stru.table_name_eng = rec.value(i++).toString();
		stru.table_name_chn = rec.value(i++).toString();
		stru.next_id = rec.value(i++).toInt();

		m_tableMap.insert(stru.table_id,stru);
	}

	query.exec("select * from fieldinfo");
	while (query.next())
	{
		QSqlRecord rec = query.record();
		FIELD_PARA_STRU stru;
		int i = 0;
		stru.table_id = rec.value(i++).toInt();
		stru.field_id = rec.value(i++).toInt();
		stru.field_name_eng = rec.value(i++).toString(); 	
		stru.field_name_chn = rec.value(i++).toString();  
		stru.data_type = rec.value(i++).toInt(); 		
		stru.data_length = rec.value(i++).toInt(); 	
		stru.is_keyword = rec.value(i++).toBool(); 
		stru.allow_null = rec.value(i++).toBool(); 	
		stru.display_type = rec.value(i++).toInt();
		stru.ref_flag = rec.value(i++).toBool(); 	
		stru.ref_mode = rec.value(i++).toInt(); 	
		stru.ref_tableno = rec.value(i++).toInt(); 		
		stru.ref_fieldno = rec.value(i++).toInt(); 			
		stru.ref_display = rec.value(i++).toInt(); 

		m_fieldMap[stru.table_id][stru.field_id] = stru;
	}
}

int CODBTable::getTableNoByName(QString table_name)
{
	QMapIterator<int,TABLE_PARA_STRU> iter(m_tableMap);
	while (iter.hasNext())
	{
		iter.next();

		if (iter.value().table_name_eng.toUpper() == QString(table_name).toUpper())
		{
			return iter.key();
		}
	}
	return -1;
}

QString CODBTable::getTableNameByID(int table_id)
{
	return m_tableMap[table_id].table_name_eng;
}

int	CODBTable::getNextID(int table_id)
{
	return m_tableMap[table_id].next_id;
}

const QSqlDatabase& CODBTable::getDataBase() const
{
	return m_db;
}

const QMap<int,TABLE_PARA_STRU>& CODBTable::getTableMap() const
{
	return m_tableMap;
}

QMap<int,FIELD_PARA_STRU> CODBTable::getFieldMap(int tableID)
{
	return m_fieldMap[tableID];
}

FIELD_PARA_STRU CODBTable::getFiledInfo(int tableID,int fieldID)
{
	return m_fieldMap[tableID][fieldID];
}

TABLE_PARA_STRU CODBTable::getTableParam(int table_id)
{
	TABLE_PARA_STRU param;
	if (m_tableMap.contains(table_id))
	{
		param = m_tableMap[table_id];
	}
	return param;
}