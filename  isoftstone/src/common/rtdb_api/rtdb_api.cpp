
#include "rtdb_api.h"
#include "config.h"


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


CRtTable::CRtTable(int tableID)
{
	m_tb_descr.table_id = tableID;
	initTableAndField();
	m_next_id = m_tableMap[m_tb_descr.table_id].next_id;
	m_tb_descr.table_name = m_tableMap[m_tb_descr.table_id].table_name_eng;
}

CRtTable::CRtTable(char* table_name)
{
	m_tb_descr.table_name = table_name;
	initTableAndField();
	m_tb_descr.table_id = getTableNoByName(table_name);
	m_next_id = m_tableMap[m_tb_descr.table_id].next_id;
}

CRtTable::~CRtTable()
{
	m_tableMap.clear();
}

void CRtTable::initTableAndField()
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
// 		QByteArray br = stru.table_name_chn.toLocal8Bit();
// 		QString tmp = QString::fromLocal8Bit(br.data());
		stru.next_id = rec.value(i++).toInt();

		m_tableMap.insert(stru.table_id,stru);
	}
	
}

bool CRtTable::openTableByID(int tableId )
{
	m_tb_descr.table_id = tableId;
	m_tb_descr.table_name = m_tableMap[tableId].table_name_chn;
	return true;
}

bool CRtTable::openTableByName(QString tableName)
{
	m_tb_descr.table_name = tableName;
	m_tb_descr.table_id = getTableNoByName(tableName);
	return true;
}

void CRtTable::closeTable()
{
	m_tableMap.clear();
}

int CRtTable::getTableNoByName(QString table_name)
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
				qDebug() << var.toString();
// 				qDebug() << var.toString().toUtf8();
// 				qDebug() << var.toString().toLocal8Bit();
			}
			else
			{
				qDebug() << var;
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
	QString strSQL = "update tableinfo set next_rec_id = ";
	strSQL += QString::number(m_next_id + 1);
	strSQL += "where id = ";
	strSQL += QString::number(m_tb_descr.table_id);

	QSqlQuery query(m_db);
	query.exec(strSQL);
}

void CRtTable::insertRecord(const QVariantList& values)
{
	
}

bool CRtTable::isTableOpen()
{
	return true;
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
	if (m_tableMap.contains(m_tb_descr.table_id))
	{
		param = m_tableMap[m_tb_descr.table_id];
		return true;
	}
	return true;
}

bool CRtTable::getFieldsPara(QVector<FIELD_PARA_STRU>& vecParams)
{
	return true;
}

bool CRtTable::getFieldPara(int filedID,FIELD_PARA_STRU& param)
{
	return true;
}

quint64 CRtTable::getNextID()
{
	return m_next_id;
}