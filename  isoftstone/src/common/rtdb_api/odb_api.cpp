
#include "odb_api.h"
#include "config.h"

QString CODBTable::getDataType(int datatype,int data_length,bool iskey,bool isNull)
{
	QString strSQL;
	switch(datatype)
	{
	case C_STRING_TYPE:
		strSQL += "VARCHAR(";
		strSQL += QString::number(data_length);
		strSQL += ")";
		break;
	case C_UCHAR_TYPE:
		strSQL += "VARCHAR(";
		strSQL += QString::number(1);
		strSQL += ")";
		break;
	case C_SHORT_TYPE:
	case C_INT_TYPE:
		strSQL += "INTEGER";
		break;
	case C_BOOLEAN_TYPE:
		strSQL += "BOOLEAN";
		break;
	case C_DATETIME_TYPE:
		strSQL += "TIMESTAMP";
		break;
	case C_FLOAT_TYPE:
		strSQL += "FLOAT";
		break;
	case C_DOUBLE_TYPE:
		strSQL += "REAL";
		break;
	case C_KEYID_TYPE:
		strSQL += "INTEGER";
		break;
	case C_IMAGE_TYPE:
	case C_BINARY_TYPE:
		strSQL += "BLOB";
		break;
	case C_TEXT_TYPE:
		strSQL += "TEXT";
		break;
	case C_UINT_TYPE:
		strSQL += "INTEGER";
		break;
	case C_LONG_TYPE:
		strSQL += "INTEGER";
		break;
	default:
		strSQL += "VARCHAR(10)";
		break;
	}
	if (iskey)
	{
		strSQL += " PRIMARY KEY";
	}
	if (!isNull&& iskey)
	{
		strSQL += " NOT NULL";
	}
	return strSQL;
}

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

QString CODBTable::getFieldNameByID(int table_id,int field_id)
{
	return m_fieldMap[table_id][field_id].field_name_eng;
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

QStringList CODBTable::getHeaerList(int tableID)
{
	QStringList lstHeaders;
	const QMap<int,FIELD_PARA_STRU>& fieldMap = m_fieldMap[tableID];
	QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
	QVector<FIELD_PARA_STRU> vecFields;
	while(iter.hasNext())
	{
		iter.next();
		const FIELD_PARA_STRU& field = iter.value();
		lstHeaders.append(field.field_name_chn);
	}
	return lstHeaders;
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

void CODBTable::deleteField(int tableID,int fieldID)
{
	QSqlQuery query(m_db);
	// 修改表字段结构

	QString strSQL = "alter table ";
	strSQL += getTableNameByID(tableID);
	strSQL += " drop column ";
	strSQL += getFieldNameByID(tableID,fieldID);
	query.exec(strSQL);

	// 从域信息表中删除

	strSQL = "delete from fieldinfo where table_id = ";
	strSQL += QString::number(tableID);
	strSQL += " and field_id = ";
	strSQL += QString::number(fieldID);
	query.exec(strSQL);

	// 从内存表中删除

	m_fieldMap[tableID].remove(fieldID);
}

void CODBTable::deleteTable(int tableID)
{
	// 从域信息表中删除

	QSqlQuery query(m_db);	
	QString strSQL = "delete from fieldinfo where table_id = ";
	strSQL += QString::number(tableID);
	query.exec(strSQL);

	// 从表信息表删除

	strSQL = "delete from tableinfo where id = ";
	strSQL += QString::number(tableID);
	query.exec(strSQL);

	// 删除表

	strSQL = "drop table ";
	strSQL += getTableNameByID(tableID);
	query.exec(strSQL);

	// 从内存表中删除

	m_fieldMap.remove(tableID);
}

void CODBTable::addTable(const TABLE_PARA_STRU& stTable)
{
	// 内存中增加
	m_tableMap.insert(stTable.table_id,stTable);
	// 更改内存中表信息表nextid
	m_tableMap[1].next_id++;
	QSqlQuery query(m_db);
	
	// 创建表
	QString strSQL  = "CREATE TABLE ";
	strSQL += stTable.table_name_eng;
	strSQL += "(id INTEGER PRIMARY KEY NOT NULL)";
	query.exec(strSQL);
	
	// 在表信息表中增加
	strSQL = "insert into tableinfo(id,en_name,cn_name,next_rec_id) values(:id,:en_name,:cn_name,:next_rec_id)";
	query.prepare(strSQL);
	int i = 0;
	query.bindValue(i++,stTable.table_id);
	query.bindValue(i++,stTable.table_name_eng);
	query.bindValue(i++,stTable.table_name_chn);
	query.bindValue(i++,stTable.next_id);
	query.exec();

	// 表信息表nextid + 1
	strSQL = "update tableinfo set next_rec_id = ";
	strSQL += QString::number(m_tableMap[1].next_id);
	strSQL += " where id = 1";
	query.exec(strSQL);
	// 增加域，由于默认增加了id 这个关键字段
	
	FIELD_PARA_STRU stField = idKeyToField(stTable.table_id);
	m_fieldMap[stField.table_id][stField.field_id] = stField;
	insertToFieldInfo(stField);
}

FIELD_PARA_STRU CODBTable::idKeyToField(int tableID)
{
	FIELD_PARA_STRU stField;
	stField.table_id = tableID;
	stField.field_id = 1;
	stField.field_name_eng = "id";
	stField.field_name_chn = "ID";
	stField.data_type = C_INT_TYPE;
	stField.data_length= 4;
	stField.is_keyword = true;
	stField.allow_null = false;
	stField.display_type = C_STRING_TYPE;
	stField.ref_flag = false;
	stField.ref_mode = 0;
	stField.ref_tableno = 0;
	stField.ref_fieldno = 0;
	stField.ref_display = 0;

	return stField;

}

void CODBTable::addField(const FIELD_PARA_STRU& stField)
{
	// 内存中增加
	m_fieldMap[stField.table_id][stField.field_id] = stField;

	QSqlQuery query(m_db);
	QString strSQL;
	if (stField.table_id != 1 && stField.table_id != 2)
	{
		// 创建字段
		strSQL  = "ALTER TABLE ";
		strSQL += getTableNameByID(stField.table_id);
		strSQL += " add ";
		strSQL += stField.field_name_eng;
		strSQL += " ";

		strSQL += CODBTable::getDataType(stField.data_type,stField.data_length,stField.is_keyword,stField.allow_null);
		query.exec(strSQL);
	}

	insertToFieldInfo(stField);
	
}

void CODBTable::insertToFieldInfo(const FIELD_PARA_STRU& stField)
{
	QString strSQL;
	QSqlQuery query(m_db);
	// 域信息表中增加
	strSQL = "insert into fieldinfo(table_id,field_id,en_name,cn_name,data_type,data_length,is_key,allow_null,display_type,reference_flag,reference_mode,reference_table,reference_column,reference_display)"
		"values(:table_id,:field_id,:en_name,:cn_name,:data_type,:data_length,:is_key,:allow_null,:display_type,:reference_flag,:reference_mode,:reference_table,:reference_column,:reference_display)";
	query.prepare(strSQL);
	int i = 0;
	query.bindValue(i++,stField.table_id);
	query.bindValue(i++,stField.field_id);
	query.bindValue(i++,stField.field_name_eng);
	query.bindValue(i++,stField.field_name_chn);
	query.bindValue(i++,stField.data_type);
	query.bindValue(i++,stField.data_length);
	query.bindValue(i++,stField.is_keyword);
	query.bindValue(i++,stField.allow_null);
	query.bindValue(i++,stField.display_type);
	query.bindValue(i++,stField.ref_flag);
	query.bindValue(i++,stField.ref_mode);
	query.bindValue(i++,stField.ref_tableno);
	query.bindValue(i++,stField.ref_fieldno);
	query.bindValue(i++,stField.ref_display);
	query.exec();
}

void CODBTable::modifyTable(const TABLE_PARA_STRU& stTable)
{
	// 只能修改表的中文名和nextid
	// 内存中修改
	m_tableMap[stTable.table_id].table_name_chn = stTable.table_name_chn;
	m_tableMap[stTable.table_id].next_id = stTable.next_id;
	// 表信息表中修改

	QSqlQuery query(m_db);
	QString strSQL = "update tableinfo";
	strSQL += " set cn_name = '";
	strSQL += stTable.table_name_chn ;
	strSQL += "' ,next_rec_id = ";
	strSQL += QString::number(stTable.next_id);
	strSQL += " where id = ";
	strSQL += QString::number(stTable.table_id);

	query.exec(strSQL);
}

void CODBTable::modifyField(const FIELD_PARA_STRU& stField)
{
	// 内存中修改
	FIELD_PARA_STRU oldField = m_fieldMap[stField.table_id][stField.field_id];
	m_fieldMap[stField.table_id][stField.field_id] = stField;
	
	// 修改域
	// sqllite 不支持直接修改和删除字段
	
	// 域信息表中修改

	QString strSQL = "update fieldinfo set ";
	QSqlQuery query(m_db);
	if (oldField.field_name_chn != stField.field_name_chn)
	{
		strSQL += " cn_name = '";
		strSQL += stField.field_name_chn;
		strSQL += "' , ";
	}
	if (oldField.display_type != stField.display_type)
	{
		strSQL += " display_type = ";
		strSQL += QString::number(stField.display_type);
		strSQL += " , ";
	}
	if (oldField.ref_flag != stField.ref_flag)
	{
		strSQL += " reference_flag = ";
		strSQL += QString::number(stField.ref_flag);
		strSQL += " , ";
	}
	if (oldField.ref_mode != stField.ref_mode)
	{
		strSQL += " reference_mode = ";
		strSQL += QString::number(stField.ref_mode);
		strSQL += " , ";
	}
	if (oldField.ref_tableno != stField.ref_tableno)
	{
		strSQL += " reference_table = ";
		strSQL += QString::number(stField.ref_tableno);
		strSQL += " , ";

	}
	if (oldField.ref_fieldno != stField.ref_fieldno)
	{
		strSQL += " reference_column = ";
		strSQL += QString::number(stField.ref_fieldno);
		strSQL += " , ";
	}
	if (oldField.ref_display != stField.ref_display)
	{
		strSQL += " reference_display = ";
		strSQL += QString::number(stField.ref_display);
		strSQL += " , ";
	}

	strSQL.simplified();
	int index = -1;
	index = strSQL.lastIndexOf(",");
	if (strSQL.endsWith(", "))
	{
		if (index > 0)
		{
			strSQL.remove(index,1);
		}
	}

	index = strSQL.lastIndexOf("set");
	if (strSQL.endsWith("set "))
	{
		if (index > 0)
		{
			strSQL.remove(index,3);
		}
	}
	else
	{
		strSQL += " where table_id = ";
		strSQL += QString::number(stField.table_id);
		strSQL += " and field_id = ";
		strSQL += QString::number(stField.field_id);
		strSQL.simplified();
		query.exec(strSQL);
	}
}

void CODBTable::updateNextID(int tableID)
{
	m_tableMap[tableID].next_id++;

	QString strSQL = "update tableinfo set next_rec_id = ";
	strSQL += QString::number(m_tableMap[tableID].next_id);
	strSQL += " where id = ";
	strSQL += QString::number(tableID);

	QSqlQuery query(m_db);
	query.exec(strSQL);
}