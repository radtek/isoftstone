
#include <QStringList>
#include <QVector>
#include <QMetaType>
#include <QVariant>
#include <string.h>

#include "vcimdbdata.h"
#include "vcimdata_common.h"

VCimTable::VCimTable()
{
	initDataType();
}
VCimTable::VCimTable(int tableID)
{
	initDataType();
	m_TableID = tableID;
	m_TableName = getTableNameByID(tableID);
}

VCimTable::VCimTable(char* table_name)
{
	initDataType();
	m_TableID = getTableNoByName(table_name);
	m_TableName = QString(table_name);
}

VCimTable::~VCimTable()
{
	closeTable();
}

void VCimTable::initDataType()
{
	m_DataTypeToQt.clear();
	m_DataTypeToQt.insert(1,QMetaType::QString);
	m_DataTypeToQt.insert(2,QMetaType::UChar);
	m_DataTypeToQt.insert(4,QMetaType::Int);
	m_DataTypeToQt.insert(6,QMetaType::Float);
	m_DataTypeToQt.insert(15,QMetaType::Long);
}


bool VCimTable::openTableByID(qint64 appId,int contextId,int tableId)
{
	TABLE_PAIR pair;
	if (tableId == -1)
	{
		tableId = m_TableID;
	}
	int nResult = OpenTableByID("MAIN_APP_SERVER",		//主实时库
								contextId,				//态号
								appId,					//应用号
								tableId,				//表号
								&pair.second);			//描述符
	if (nResult < 0)
	{
		pair.first = false;
	}
	else
	{
		pair.first = true;
	}
	m_TableID = tableId;
	if (m_TableName.isEmpty())
	{
		m_TableName = getTableNameByID(tableId);
		
	}
	//qDebug()<<"VCimTable::openTableByID now TableName="<<m_TableName;
	m_TablePair = pair;
	return pair.first;
}

bool VCimTable::openTableByName(char* appName,char* contextName,char* tableName)
{
	TABLE_PAIR pair;
	TB_DESCR desc;
	int nResult = OpenTableByName("MAIN_APP_SERVER",		//主实时库
								contextName,			//态号
								appName,				//应用号
								tableName,				//表号
								&desc);					//描述符
	if (nResult < 0)
	{
		pair.first = false;
	}
	else
	{
		pair.first = true;
	}
	m_TableID = getTableNoByName(tableName);
	m_TableName = QString(tableName);
	pair.second = desc;
	m_TablePair = pair;
	return pair.first;
}

bool VCimTable::reOpen(qint64 appId,int contextId)
{
	closeTable();
	return openTableByID(appId,contextId,m_TableID);
}

int VCimTable::getFiledsByID(char* recID,int* filedArray,int fieldNum,int bufSize,char* pBuf)
{
	if (m_TablePair.first == false) return false;
	
	int nResult = GetFieldsByID(&m_TablePair.second,		//表描述符
								recID,						//记录关键字
								filedArray,					//域号数组
								fieldNum,					//域的个数
								bufSize,					//读缓冲区长度
								pBuf);						//读缓冲区
	return nResult;

}

int VCimTable::getFiledsByName(char* recID,char* filedName,int bufSize,char* pBuf)
{
	int field_num = QString(filedName).split(',').count();
	int* field_no_array = new int[field_num];
	int nResult = getFiledIDByNames(filedName, field_no_array,&field_num);
	if (nResult < 0)
	{
		delete field_no_array;
		return false;
	}
	nResult = getFiledsByID(recID,field_no_array,field_num,bufSize,pBuf);
	delete field_no_array;
	return nResult;
}

int VCimTable::getTableFields(char* filedNames,char** pBuf)
{
	if (m_TablePair.first == false) return false;
	
	int nResult = -1;
	int field_num = 2;
	int field_no_array[2] = {0,0};
	nResult = getFiledIDByNames(filedNames, field_no_array,&field_num);
	if (nResult < 0) 
	{
		return false;
	}

	nResult = GetTableFields(&m_TablePair.second, 0, field_no_array,field_num, pBuf);
	
	return nResult;
}

void VCimTable::getStringField(const QVector<quint64>& resourceIDS,const QString& strField,QStringList& lstNames)
{
	struct SName
	{
		char pszBuf[64];//数据缓冲区
	};

	SName sName;

	int bufSize = sizeof(SName);
	lstNames.clear();

	for (int i = 0 ; i < resourceIDS.count() ; i++)
	{
		quint64 keyID = resourceIDS[i];
		int nResult = getFiledsByName((char*)(&keyID),strField.toLocal8Bit().data(),bufSize,(char*)(&sName));
		if (nResult < 0)
		{
			lstNames.append("NULL");
		}
		else
		{
			QString name = QString::fromLocal8Bit(sName.pszBuf);
			lstNames.append(name);
		}
	}
}

void VCimTable::getLongField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<quint64>& vecValues)
{
	getNumberField<quint64>(resourceIDS,strField,vecValues);
}

void VCimTable::getFloatField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<float>& vecValues)
{
	getNumberField<float>(resourceIDS,strField,vecValues);
}

void VCimTable::getIntField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<int>& vecValues)
{
	getNumberField<int>(resourceIDS,strField,vecValues);
}

template<class T>
void VCimTable::getNumberField(const QVector<quint64>& resourceIDS,const QString& strField,QVector<T>& vecValues)
{
	T fValue;
	int bufSize = sizeof(T);
	vecValues.clear();

	for (int i = 0 ; i < resourceIDS.count() ; i++)
	{
		quint64 keyID = resourceIDS[i];
		int nResult = getFiledsByName((char*)(&keyID),strField.toLocal8Bit().data(),bufSize,(char*)(&fValue));
		if (nResult < 0)
		{
			vecValues.append(0);
		}
		else
		{
			vecValues.append(fValue);
		}
	}
}

void VCimTable::getSingleField(const quint64 &resourceID,const QString& strField,quint64 &vecValue)
{
	quint64 fValue;
	int bufSize = sizeof(quint64);
	vecValue = 0;

	int nResult = getFiledsByName((char*)(&resourceID),strField.toLocal8Bit().data(),bufSize,(char*)(&fValue));

	if (nResult < 0)
	{
		vecValue = 0;
	}
	else
	{
		vecValue = fValue;
	}
}

void VCimTable::getVariantField(const QVector<quint64>& resourceIDS,int fieldID,QMap<quint64,QVariant>& valueMap)
{
	FIELD_PARA_STRU filed_param ;
	int ret = getFieldPara(fieldID,&filed_param);

	if (ret == 0)
	{
		int fieldNoArray[1] = {0};
		fieldNoArray[0] = fieldID; 
		char pszBuf[READBUFFER_SIZE];//数据缓冲区
		int nLen = filed_param.field_length;
		for (int i = 0 ; i < resourceIDS.count() ; i++)
		{
			quint64 keyID = resourceIDS[i];
			int res_Data = GetFieldsByID(&m_TablePair.second,			//表描述符
										(char*)&keyID,					//记录关键字 /*(char*)&vcimData.pIoData.gKeyID*/
										fieldNoArray,					//域号数组
										1,								//域的个数
										READBUFFER_SIZE,				//读缓冲区长度
										pszBuf);	

			QVariant varData = QString("");
			if (res_Data == 0)
			{
				varData = toVariant(getTypeName(filed_param.data_type).data(),pszBuf,nLen);
			}
			else
			{
				varData = 0;
			}
			valueMap[keyID] = varData;
		}
	}
}

void VCimTable::getVariantField2(const QVector<quint64>& resourceIDS,int fieldID,QMap<quint64,QVariant>& valueMap)
{
	FIELD_PARA_STRU filed_param ;
	TABLE_PARA_STRU table_Param;
	int ret = getFieldPara(fieldID,&filed_param);
	bool bTable = getTableParam(table_Param);
	if (ret == 0 && bTable )
	{
		int bufferSize1 = table_Param.record_size*resourceIDS.count();
		quint64 ids[READBUFFER_SIZE];
		char* pszBuf = new char[bufferSize1];
		for (int i = 0 ; i < resourceIDS.count() ; i++)
		{
			quint64 keyID = resourceIDS[i];
			ids[i] = keyID;
		}
		int bufferSize = GetRecsByID(&m_TablePair.second,(char*)ids,resourceIDS.count(),bufferSize1,pszBuf);
		getVariantFiled(filed_param,table_Param.record_size,pszBuf,bufferSize,valueMap);
		delete pszBuf;
	}
}

void VCimTable::getVariantFiled(const FIELD_PARA_STRU& param,int nRecSize,char* buf_ptr,int nBufferSize,QMap<quint64,QVariant>& valueMap)
{
	int nPos = 0;
	valueMap.clear();
	// 根据类型构建对象
	int qID = param.data_type;
	int nLen = param.field_length;
	while(nPos < nBufferSize)
	{
		char* tmp_ptr = buf_ptr + nPos;
		quint64 keyid = getFiledValue(tmp_ptr,8,15).toULongLong();

		QVariant var;
		tmp_ptr = buf_ptr + nPos + param.offset;
		var = getFiledValue(tmp_ptr,nLen,qID);
		valueMap[keyid] = var;
		nPos += nRecSize;

		qDebug() << keyid << " = " << var;
	}
}

void VCimTable::getVariantField(const quint64& resourceID,int fieldID,QVariant& value)
{
	QMap<quint64,QVariant> valueMap;
	QVector<quint64> resourceIDS;
	resourceIDS.append(resourceID);
	getVariantField(resourceIDS,fieldID,valueMap);
	if (valueMap.count() > 0)
	{
		value = valueMap.begin().value();
	}
}

QVariant VCimTable::getFiledValue(char* tmp_ptr,int nLen,int qID)
{
	QVariant var;
	switch (qID)
	{
	case 1: // char* = string
		{
			char* str = new char[nLen];
			memcpy(str,tmp_ptr ,nLen);
			var = QString::fromLocal8Bit(str);
			delete str;
		}
		break;
	case 2: // uchar
		assign<unsigned char>(var,tmp_ptr ,nLen);
		break;
	case 4: // int
		assign<int>(var,tmp_ptr ,nLen);
		break;
	case 6: // float
		assign<float>(var,tmp_ptr ,nLen);
		break;
	case 15: // long
		assign<qlonglong>(var,tmp_ptr,nLen);
		break;
	default:
		{
			void *objPtr = QMetaType::construct(qID);
			memcpy(objPtr,tmp_ptr ,nLen );
			var = QVariant(qID,objPtr);
			QMetaType::destroy(qID, objPtr);
			objPtr = NULL;
		}
		break;
	}
	return var;
}

int VCimTable::getFiledNo(char* filedName)
{
	int field_no_array[1] = {0};
	int field_num[1] = {1};
	int ret = GetFieldNoByName(&m_TablePair.second,filedName,field_no_array,field_num);
	if (ret > 0)
	{
		return field_no_array[0];
	}
	else
	{
		return 0;
	}
}

//获得表中所有的数据保存到 vecRows中
void VCimTable::getTableRecs(QVector< QVector<QVariant> >& vecRows)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;
	
	vecRows.clear();
	bool bTable = getTableParam(table_Param);
	bool bFiled = getFieldsPara(vecFieldParams);
	if (bFiled && bTable)
	{
		QVector<QVariant> vecValues;
		vecValues.reserve(vecFieldParams.count());
		// 单个记录大小
		int nRecSize = table_Param.record_size;
		// 获取所有数据
		char* buf_ptr = NULL;
		// 此处如果数据量大于65536，不知道如何处理
		int nBufferSize = GetTableRecs(&m_TablePair.second,0,&buf_ptr);
		if (nBufferSize <= 0)
		{
			return;
		}
		vecRows.reserve(nBufferSize/nRecSize);
		int nPos = 0;
		if (nBufferSize > -1)
		{
			while(nPos < nBufferSize)
			{
				vecValues.clear();
				for (int i = 0 ; i < vecFieldParams.count() ; i++)
				{
					const FIELD_PARA_STRU& param = vecFieldParams[i];
					QVariant var;
					// 根据类型构建对象
					int qID = param.data_type;
					int nLen = param.field_length;

					char* tmp_ptr = buf_ptr + nPos + param.offset;

					var = getFiledValue(tmp_ptr,nLen,qID);
					//qDebug()<<","<<var;
					vecValues.append(var);
				}
				//qDebug()<<endl;
				vecRows.append(vecValues);
				nPos += nRecSize;
			}
		}
		BufFree(buf_ptr);
	}
}

void VCimTable::getRecByID(quint64 keyid,QVector<QVariant>& vecValues)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;

	vecValues.clear();
	bool bTable = getTableParam(table_Param);
	bool bFiled = getFieldsPara(vecFieldParams);
	if (bFiled && bTable)
	{
		vecValues.reserve(vecFieldParams.count());
		// 单个记录大小
		int nRecSize = table_Param.record_size;
		// 获取所有数据
		char* buf_ptr = NULL;
		// 返回读取记录数
		int nBufferSize = GetRecByID(&m_TablePair.second,(char*)(&keyid),READBUFFER_SIZE,buf_ptr);
		int nPos = 0;
		int num = 0;
		if (nBufferSize <= 0)
		{
			return;
		}
		if (nBufferSize > -1)
		{
			while(nPos < nBufferSize)
			{
				vecValues.clear();
				for (int i = 0 ; i < vecFieldParams.count() ; i++)
				{
					const FIELD_PARA_STRU& param = vecFieldParams[i];
					QVariant var;
					// 根据类型构建对象
					int qID = param.data_type;
					int nLen = param.field_length;

					char* tmp_ptr = buf_ptr + nPos + param.offset;

					var = getFiledValue(tmp_ptr,nLen,qID);
					//qDebug()<<","<<var;
					vecValues.append(var);
				}
				nPos += nRecSize;
			}
		}
		BufFree(buf_ptr);
	}
}

void VCimTable::getRecsByID(QVector<quint64> vecKeyid,QVector< QVector<QVariant> >& vecRows)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;

	vecRows.clear();
	bool bTable = getTableParam(table_Param);
	bool bFiled = getFieldsPara(vecFieldParams);
	if (bFiled && bTable)
	{

		quint64 ids[READBUFFER_SIZE];
		char pszBuf[READBUFFER_SIZE];
		for (int i = 0 ; i < vecKeyid.count() ; i++)
		{
			quint64 keyID = vecKeyid[i];
			ids[i] = keyID;
		}
		QVector<QVariant> vecValues;
		vecValues.reserve(vecFieldParams.count());
		// 单个记录大小
		int nRecSize = table_Param.record_size;
		// 获取所有数据
		char* buf_ptr = NULL;
		// 返回读取记录数
		int nBufferSize = GetRecsByID(&m_TablePair.second,(char*)ids,vecKeyid.count(),READBUFFER_SIZE,pszBuf);
		int nPos = 0;
		int num = 0;
		if (nBufferSize <= 0)
		{
			return;
		}
		if (nBufferSize > -1)
		{
			while(nPos < nBufferSize)
			{
				vecValues.clear();
				for (int i = 0 ; i < vecFieldParams.count() ; i++)
				{
					const FIELD_PARA_STRU& param = vecFieldParams[i];
					QVariant var;
					// 根据类型构建对象
					int qID = param.data_type;
					int nLen = param.field_length;

					char* tmp_ptr = buf_ptr + nPos + param.offset;

					var = getFiledValue(tmp_ptr,nLen,qID);
					//qDebug()<<","<<var;
					vecValues.append(var);
				}
				vecRows.append(vecValues);
				nPos += nRecSize;
			}
		}
		BufFree(buf_ptr);
	}
}

void VCimTable::getRecsBySQL(const QString& strSQL,QVector< QVector<QVariant> >& vecRows)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;

	vecRows.clear();
	bool bTable = getTableParam(table_Param);
	bool bFiled = getFieldsPara(vecFieldParams);
	if (bFiled && bTable)
	{
		QVector<QVariant> vecValues;
		vecValues.reserve(vecFieldParams.count());
		// 单个记录大小
		int nRecSize = table_Param.record_size;
		// 获取所有数据
		char* buf_ptr = NULL;
		// 返回读取记录数
		int recordCount = GetBySql(&m_TablePair.second,strSQL.toLocal8Bit().data(),&buf_ptr);
		vecRows.reserve(recordCount);
		int nPos = 0;
		int num = 0;
		if (recordCount > 0)
		{
			while(num < recordCount)
			{
				vecValues.clear();
				for (int i = 0 ; i < vecFieldParams.count() ; i++)
				{
					const FIELD_PARA_STRU& param = vecFieldParams[i];
					QVariant var;
					// 根据类型构建对象
					int qID = param.data_type;
					int nLen = param.field_length;

					char* tmp_ptr = buf_ptr + nPos + param.offset;
					var = getFiledValue(tmp_ptr,nLen,qID);
					//qDebug()<<","<<var;
					vecValues.append(var);
				}
				vecRows.append(vecValues);
				nPos += nRecSize;
				num++;
			}
		}
		BufFree(buf_ptr);
	}
}

bool VCimTable::isRecordExist(quint64 keyid)
{
	char buf_ptr[READBUFFER_SIZE];
	int ret = GetRecByID(&m_TablePair.second,(char*)(&keyid),READBUFFER_SIZE,buf_ptr);
	if (ret == 0)
	{
		return true;
	}
	return false;
}


void VCimTable::deleteRecord(quint64 keyID)
{
	quint64 recID = keyID;
	DeleteRecByID(&m_TablePair.second,(char*)(&recID));
}

void VCimTable::updateRecord(quint64 keyID,int buf_size,char* buf_ptr)
{
	UpdateRecByID(&m_TablePair.second,(char*)(&keyID),buf_size,buf_ptr);
}

void VCimTable::updateFiled(quint64 keyID,int filed,int buf_size,char* buf_ptr)
{
	int filedIDs[1] = {0};
	filedIDs[0] = filed;
	int ret = UpdateFieldsByID(&m_TablePair.second,(char*)(&keyID),filedIDs,1,buf_size,buf_ptr);
	if (ret > 0)
	{
		//qDebug() << ret ;
	}
}

void VCimTable::insertRecord(int buf_size,char* buf_ptr)
{
	InsertRec(&m_TablePair.second,1,buf_size,buf_ptr,1);
}

bool VCimTable::getFiledIDByNames(char* filedNames,int* filedArray,int* field_num)
{
	int nResult = GetFieldNoByName(&m_TablePair.second, filedNames, filedArray,field_num);
	return nResult < 0;
}

bool VCimTable::isTableOpen()
{
	return m_TablePair.first ;
}

TB_DESCR VCimTable::getTableDesc()
{
	return m_TablePair.second;
}

int VCimTable::getTableID()
{
	return m_TableID;
}
int VCimTable::getContextID()
{
	return m_ContextID;
}
qint64 VCimTable::getAppID()
{
	return m_AppID;
}

bool VCimTable::getTableParam(TABLE_PARA_STRU& param)
{
	int result = GetTablePara(&m_TablePair.second,&param);

#ifdef WIN32
	strcpy(param.table_name_eng ,m_TableName.toLocal8Bit().data());
#endif

	if (result < 0)
	{
		return false;
	}
	return true;
}

bool VCimTable::getFieldsPara(QVector<FIELD_PARA_STRU>& vecParams)
{
	vecParams.clear();
	FIELD_PARA_STRU* filed_Ptr = NULL;
	int result = GetFieldsPara(&m_TablePair.second, &filed_Ptr);
	if (result < 0)
	{
		return false;
	}
	int nSize = 0;
	FIELD_PARA_STRU* ptr = filed_Ptr;
	vecParams.reserve(result/sizeof(FIELD_PARA_STRU));
	while(nSize < result)
	{
		vecParams.append(*ptr);
		qDebug() << "column_id" << (*ptr).column_id << " filed_no" << (*ptr).field_no << " ref_fieldno " << (*ptr).ref_fieldno;
		ptr += 1;
		nSize += sizeof(FIELD_PARA_STRU);
	}
	BufFree(filed_Ptr);
	return true;
}

int VCimTable::getFieldPara(int filedID,FIELD_PARA_STRU* param)
{
	int result = GetFieldParaByID(&m_TablePair.second, filedID, param);
	return result;
}

int	VCimTable::free(void* ptr)
{
	return BufFree(ptr);
}

void VCimTable::closeTable()
{
	if (m_TablePair.first == true)
	{
		CloseTable(&m_TablePair.second);
		m_TablePair.first = false;
	}
}

KEY_STRU VCimTable::long_to_keyid(unsigned long keyid)
{
	KEY_STRU tmp;
	CCommon::long_to_keyid(keyid,& tmp);
	return tmp;
}

short VCimTable::long_to_tableNo(unsigned long keyid)
{
	short tmp;
	CCommon::long_to_tableNo(keyid,&tmp);
	return tmp;
}

short VCimTable::long_to_field_id(unsigned long keyid)
{
	short tmp;
	CCommon::long_to_field_id(keyid,&tmp);
	return tmp;
}

int VCimTable::getTableNoByName(char* table_name)
{
	int nTableNo;
	int ret = GetTableNoByName(table_name,&nTableNo);
	if (ret > -1)
	{
		return nTableNo;
	}
	return -1;
}

QString	VCimTable::getTableNameByID(int nTableID)
{
	char tableName[20];
	int ret = GetTableNameByID(nTableID,tableName);
	if (ret > -1)
	{
		return QString(tableName);
	}
	return "";
}

quint64 VCimTable::getNextID()
{
	quint64 keyID = 0;
	
	QVector< QVector<QVariant> > vecRows;
	getTableRecs(vecRows);
	if (vecRows.count() > 0)
	{
		for (int i = 0 ; i < vecRows.count() ; i++)
		{
			for (int j = 0 ; j < 1 ; j++)
			{
				quint64 tmpID = vecRows[i][0].toLongLong();
				if (keyID < tmpID)
				{
					keyID = tmpID;
				}
			}
		}
	}
	else
	{
		KEY_STRU key_stru;
		key_stru.key = 1;
		key_stru.field_id = 0;
		key_stru.table_no = m_TableID;
		unsigned long nextID;
		CCommon::keyid_to_long(&key_stru, &nextID);
		keyID = nextID;
	}
	return keyID;
}

void VCimTable::getFiledMap(int filedID,QMap<quint64,QVariant >& mapFiled)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;

	mapFiled.clear();
	bool bTable = getTableParam(table_Param);
	bool bFiled = getFieldsPara(vecFieldParams);
	if (bFiled && bTable)
	{
		QVector<QVariant> vecValues;
		vecValues.reserve(vecFieldParams.count());
		// 单个记录大小
		int nRecSize = table_Param.record_size;
		int filed_no[2] = {1,2};
		filed_no[1] = filedID;
		// 获取所有数据
		char* buf_ptr = NULL;
		
		// 此处如果数据量大于65536，不知道如何处理
		int nBufferSize = GetTableFields(&m_TablePair.second,0,filed_no,2,&buf_ptr);
		int nPos = 0;
		if (nBufferSize > -1)
		{
			char* tmp_ptr = buf_ptr;
			while(nPos < nBufferSize)
			{
				vecValues.clear();
				nRecSize = 0; 
				for (int i = 0 ; i < 2 ; i++)
				{
					int filed_id = filed_no[i];
					const FIELD_PARA_STRU& param = vecFieldParams[filed_id - 1];
					nRecSize += param.field_length;
					QVariant var;
					// 根据类型构建对象
					int qID = param.data_type;
					int nLen = param.field_length;
					var = getFiledValue(tmp_ptr,nLen,qID);
					tmp_ptr += param.field_length;
					//qDebug()<<","<<var;
					vecValues.append(var);
				}
				mapFiled.insert(vecValues[0].toLongLong(),vecValues[1]);
				nPos += nRecSize;
			}
		}
		BufFree(buf_ptr);
	}
}

////////////////////////////////////////////////////////////
/////////////  表格管理器 /////////////////////////////////

VCimTableMgr* VCimTableMgr::s_TableManager = new VCimTableMgr();

VCimTableMgr::VCimTableMgr()
{
	m_TableMutex = new QMutex();
}

VCimTableMgr::~VCimTableMgr()
{
}


VCimTableMgr* VCimTableMgr::instance()
{
	return s_TableManager;
}

void VCimTableMgr::destroy()
{
	QMapIterator<int,VCimTable*> iter(m_TableMap);
	while(iter.hasNext())
	{
		iter.next();
		delete iter.value();
	}
	m_TableMap.clear();

	delete m_TableMutex;
	m_TableMutex = NULL;
}

void VCimTableMgr::createTable(int tableID)
{
	QMutexLocker lock(m_TableMutex);

	VCimTable* newTable = new VCimTable(tableID);
	m_TableMap.insert(tableID,newTable);
}

void VCimTableMgr::deleteTable(int tableID)
{
	QMutexLocker lock(m_TableMutex);

	QMap<int,VCimTable*>::Iterator iter = m_TableMap.find(tableID);
	if (iter != m_TableMap.end())
	{
		delete iter.value();
		m_TableMap.remove(tableID);
	}
}

VCimTable* VCimTableMgr::getTable(int tableID)
{
	QMutexLocker lock(m_TableMutex);

	QMap<int,VCimTable*>::Iterator iter = m_TableMap.find(tableID);
	if (iter != m_TableMap.end())
	{
		return iter.value();
	}
	return NULL;
}

bool VCimTableMgr::isTableOpen(int tableID)
{
	QMutexLocker lock(m_TableMutex);

	QMap<int,VCimTable*>::Iterator iter = m_TableMap.find(tableID);
	if (iter != m_TableMap.end())
	{
		return iter.value()->isTableOpen();
	}
	return false;
}