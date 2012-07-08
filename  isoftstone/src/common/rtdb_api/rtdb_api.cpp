
#include "rtdb_api.h"
#include "config.h"

#include "odb_api.h"

const int limit_table_id = 0;

KEY_STRU CRtTable::long_to_keyid(unsigned int keyid)
{
	KEY_STRU stru;
	stru.table_no = (keyid && 0xFF000000) >> 3;
	stru.key = (keyid && 0x00FFFF00) >> 1;
	stru.table_no = keyid && 0x000000FF;
	return stru;
}

short	CRtTable::long_to_tableNo(unsigned int keyid)
{
	short tableno;
	tableno = (keyid && 0xFF000000) >> 3;
	return tableno;
}
short	CRtTable::long_to_field_id(unsigned int keyid)
{
	short fieldid;
	fieldid = (keyid && 0x00FFFF00) >> 1;
	return fieldid;
}


CRtTable::CRtTable(int tableID):m_db(CODBTable::instance()->getDataBase())
{
	openTableByID(tableID);
}

CRtTable::CRtTable(char* table_name):m_db(CODBTable::instance()->getDataBase())
{
	openTableByName(table_name);
}

CRtTable::~CRtTable()
{
	
}

// 限制rtdb 不能操作模型库，否则会造成意想不到的问题
bool CRtTable::openTableByID(int tableId )
{
	if (tableId > limit_table_id )
	{
		m_tb_descr.table_id = tableId;
		m_tb_descr.table_name = CODBTable::instance()->getTableNameByID(tableId);

		fillFieldArray();
		return true;
	}
	else
	{
		m_tb_descr.table_id = 0;
		m_tb_descr.table_name = "";
		return false;
	}
	
}

bool CRtTable::openTableByName(QString tableName)
{
	m_tb_descr.table_name = tableName;
	m_tb_descr.table_id = CODBTable::instance()->getTableNoByName(tableName);
	return openTableByID(m_tb_descr.table_id);
}

void CRtTable::closeTable()
{

}

int CRtTable::getFiledsByID(int recID,const QVector<int>& vecField,QVariantList& vecValue)
{
	return 1;
}

int CRtTable::getFiledsByName(int recID,const QStringList& vecField,QVariantList & lstValue)
{
	QString strSQL = getSelectSQL(vecField);
	strSQL += " where id = ";
	strSQL += QString::number(recID);
	QVector<QVariantList> vecList;
	getRecsBySQL(strSQL,vecList);
	if (vecList.count() > 0)
	{
		lstValue = vecList[0];
		return 1;
	}
	return -1;
}

int CRtTable::getFiledByID(int recID,int fieldID,QVariant& value)
{
	return 1;
}

int CRtTable::getFiledsByName(int recID,const QString& fieldName,QVariant& value)
{
	QStringList vecField;
	vecField.append(fieldName);
	QVariantList lstValue;
	getFiledsByName(recID,vecField,lstValue);
	if (lstValue.count() > 0)
	{
		value = lstValue[0];
		return 1;
	}
	return -1;
}

QString CRtTable::getSelectSQL(const QStringList& vecField)
{
	QString strSQL = "select ";
	for (int i = 0 ; i < vecField.count() ; i++)
	{
		strSQL += vecField[i];
		if (i != vecField.count() -1)
		{
			strSQL += ",";
		}
	}
	strSQL += " from ";
	strSQL += m_tb_descr.table_name;
	strSQL += " ";

	return strSQL;
}

QString CRtTable::getIDSet(const QVector<int>& vecID)
{
	QString strSQL = "(";
	for (int i = 0 ; i < vecID.count() ; i++)
	{
		strSQL += QString::number(vecID[i]);
		if (i != vecID.count() -1)
		{
			strSQL += ",";
		}
	}
	strSQL += ")";
	return strSQL;
}

QString CRtTable::getAllField()
{
	QString strSQL = "select * from ";
	strSQL += m_tb_descr.table_name;
	return strSQL;
}

void CRtTable::fillFieldArray()
{
	m_fields.clear();
	m_strfield.clear();

	QMap<int,FIELD_PARA_STRU> fieldMap = CODBTable::instance()->getFieldMap(m_tb_descr.table_id);
	QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
	while(iter.hasNext())
	{
		iter.next();
		const FIELD_PARA_STRU& field = iter.value();
		m_fields.append(field);

		m_strfield += field.field_name_eng;
		if (iter.hasNext())
		{
			m_strfield += ",";
		}
	}	
}

int CRtTable::getTableFields(const QStringList& vecField,QVector<QVariantList>& vecRows)
{
	vecRows.clear();
	QString strSQL = getSelectSQL(vecField);
	getRecsBySQL(strSQL,vecRows);
	return 1;
}

int CRtTable::getFieldNo(const QString& filedName)
{
	return 1;
}

QString CRtTable::getFieldName(int fieldID)
{
	return "";
}

bool CRtTable::getFiledIDByNames(const QStringList& vecField,QMap<QString,int>& mapValue)
{
	mapValue.clear();
	return true;
}

bool CRtTable::getFiledNameByIDS(const QVector<int>& vecField,QMap<int,QString>& mapValue)
{
	mapValue.clear();
	return true;
}

void CRtTable::getRecsByID(const QVector<int>& resourceIDS,int fieldID,QMap<int,QVariant>& valueMap)
{
	valueMap.clear();
}

void CRtTable::getRecsByIDS(const QVector<int>& resourceIDS,QVector<int> vecField,QMap<int,QVariantList>& valueMap)
{
	valueMap.clear();
}

void CRtTable::getTableRecs(QVector< QVariantList >& vecRows)
{
	vecRows.clear();
	QString strSQL = getAllField();
	getRecsBySQL(strSQL,vecRows);
}

void CRtTable::getRecByID(int keyid,QVariantList& vecValues)
{
	vecValues.clear();
	QString strSQL = getAllField();
	strSQL += " where id = ";
	strSQL += QString::number(keyid);
	QVector<QVariantList> vecList;
	getRecsBySQL(strSQL,vecList);
	if (vecList.count() > 0)
	{
		vecValues = vecList[0];
	}
}

void CRtTable::getRecsByID(QVector<int> vecKeyid,QVector< QVariantList >& vecRows)
{
	vecRows.clear();
	QString strSet = getIDSet(vecKeyid);
	QString strSQL = getAllField();
	strSQL += " where id in ";
	strSQL += strSet;
	getRecsBySQL(strSQL,vecRows);
}

void CRtTable::getRecsBySQL(const QString& strSQL,QVector<QVariantList>& vecRows)
{
	vecRows.clear();
	QSqlQuery query(m_db);
	query.exec(strSQL);
	while (query.next())
	{
		QSqlRecord rec = query.record();
		QVariantList lstValue;
		QString strRec = "";
		for (int i = 0 ; i < rec.count() ;i++)
		{
			QVariant& var = query.value(i);
			lstValue.append(var);
			strRec += var.toString();

			if (var.type() == QVariant::String)
			{
				//qDebug() << var.toString();
// 				qDebug() << var.toString().toUtf8();
// 				qDebug() << var.toString().toLocal8Bit();
			}
			else
			{
				//qDebug() << var;
			}
			
		}
		vecRows.append(lstValue);
		//qDebug() << strRec;
	}
}

void CRtTable::getRecsByCondition(const QString& strCon,const QStringList& vecField,QVector< QVariantList>& vecRows)
{
	vecRows.clear();
	QString strSQL = getSelectSQL(vecField);
	strSQL += strCon;
	getRecsBySQL(strSQL,vecRows);
}

bool CRtTable::isRecExist(int keyid)
{
	
	return true;
}

void CRtTable::deleteRecord(int keyID)
{
	QString strCon = "id = ";
	strCon += QString::number(keyID);
	deleteRecByConditon(strCon);
}

void CRtTable::deleteRecByConditon(const QString& strCon)
{
	QSqlQuery query(m_db);
	QString strSQL = "delete from ";
	strSQL += m_tb_descr.table_name;
	strSQL += " where ";
	strSQL += strCon;
	query.exec(strSQL);
	
}

void CRtTable::updateRecord(int keyID,const QVariantList& values)
{
	
}

void CRtTable::updateFiled(int keyID,int filed,const QVariant& value)
{
	
}

void CRtTable::updateNextID()
{
	CODBTable::instance()->updateNextID(m_tb_descr.table_id);
}

void CRtTable::addRecord(const QVariantList& values)
{
	// 按顺序添加记录到表中,分析各字段的数据类型，然后根据类型解析值，放到数据库中
	
	if (m_fields.count() == values.count())
	{
		QString strSQL ;
		strSQL = "INSERT INTO ";
		strSQL += m_tb_descr.table_name;
		strSQL += "(";
		strSQL += m_strfield;
		strSQL += ") VALUES(";
		QSqlQuery query(m_db);
		for (int i = 0 ; i < m_fields.count() ;i++)
		{
			const FIELD_PARA_STRU& stField = m_fields[i];

			// 添加KEYID
			if (i == 0)
			{
				int keyid = getNextID();
				strSQL += QString::number(keyid);
				strSQL += ",";
				continue;
			}
			
			switch (stField.data_type)
			{
			case C_STRING_TYPE:
				strSQL += "'";
				strSQL += values[i].toString();
				strSQL += "'";
				break;
			default:
				strSQL += QString::number(values[i].toInt());
				break;
			}
			if (i < m_fields.count() -1)
			{
				strSQL +=  ",";
			}
		}
		strSQL += ")";
		query.exec(strSQL);
	}
}

bool CRtTable::isTableOpen()
{
	if (m_tb_descr.table_id > limit_table_id)
	{
		return true;
	}
	return false;
}

TB_DESCR CRtTable::getTableDesc()
{
	return m_tb_descr;
}

int CRtTable::getTableID()
{
	return m_tb_descr.table_id;
}

bool CRtTable::getTableParam(TABLE_PARA_STRU& param)
{
	param = CODBTable::instance()->getTableParam(getTableID());
	return true;
}

bool CRtTable::getFieldsPara(QVector<FIELD_PARA_STRU>& vecParams)
{
	vecParams = m_fields;
	return true;
}

bool CRtTable::getFieldPara(int fieldID,FIELD_PARA_STRU& param)
{
	for (int i = 0 ; i < m_fields.count() ;i++)
	{
		const FIELD_PARA_STRU& stField = m_fields[i];
		if (stField.field_id == fieldID)
		{
			param = stField;
			return true;
		}
	}
	return false;
}

quint64 CRtTable::getNextID()
{
	int nextid = CODBTable::instance()->getNextID(m_tb_descr.table_id);;
	CODBTable::instance()->updateNextID(m_tb_descr.table_id);
	return nextid;
}