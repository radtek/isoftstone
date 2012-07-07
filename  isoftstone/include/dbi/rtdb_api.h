
#ifndef __RTDB_API_H__
#define __RTDB_API_H__

#include "odb_public.h"

class EXPORT_LIB CRtTable
{

public:

	static KEY_STRU long_to_keyid(unsigned int keyid);
	static short	long_to_tableNo(unsigned int keyid);
	static short	long_to_field_id(unsigned int keyid);

public:

	CRtTable(int tableID = 1);
	CRtTable(char* table_name);
	~CRtTable();

	bool	   openTableByID(int tableId = -1);
	bool       openTableByName(QString tableName);
	void	   closeTable();

	//	根据单个ID和多个列获取多个值
	int		   getFiledsByID(int recID,const QVector<int>& vecField,QVariantList& vecValue);
	//	根据单个ID核多个列名获得多个值
	int		   getFiledsByName(int recID,const QStringList& vecField,QVariantList& vecValue);
	// 根据单个ID单个列获得单个值
	int		   getFiledByID(int recID,int fieldID,QVariant& value);
	// 根据单个ID和单个列名获得单个值
	int		   getFiledsByName(int recID,const QString& fieldName,QVariant& value);
	// 得到表中制定列所有记录
	int		   getTableFields(const QStringList& vecField,QVector<QVariantList>& vecRows);

	// 根据域名获得列ID
	int		   getFieldNo(const QString& filedName);

	QString	   getFieldName(int fieldID);

	// 根据列名称获得相应列ID
	bool	   getFiledIDByNames(const QStringList& vecField,QMap<QString,int>& mapValue);
	bool	   getFiledNameByIDS(const QVector<int>& vecField,QMap<int,QString>& mapValue);

	// 根据多个ID获得单个列的值
	void	   getRecsByID(const QVector<int>& resourceIDS,int fieldID,QMap<int,QVariant>& valueMap);
	// 根据多个ID获得多个列值
	void	   getRecsByIDS(const QVector<int>& resourceIDS,QVector<int> vecField,QMap<int,QVariantList>& valueMap);

	// 获得表中所有的数据保存到 vecRows中
	void	   getTableRecs(QVector< QVariantList >& vecRows);  
	// 获得单个记录所有列的值
	void	   getRecByID(int keyid,QVariantList& vecValues);  
	// 得到多条记录所有列的值
	void	   getRecsByID(QVector<int> vecKeyid,QVector< QVariantList >& vecRows); 
	void	   getRecsBySQL(const QString& strSQL,QVector< QVariantList>& vecRows);  
	void	   getRecsByCondition(const QString& strSQL,const QStringList& vecField,QVector< QVariantList>& vecRows);  

	// 记录是否存在
	bool	   isRecExist(int keyid);

	// 删除数据
	void	   deleteRecord(int keyID);
	void	   deleteRecByConditon(const QString& strSQL);

	// 修改单个记录所有列数据
	void	   updateRecord(int keyID,const QVariantList& values);
	// 修改单个记录一列的值
	void	   updateFiled(int keyID,int filed,const QVariant& value);

	// 添加数据
	void	   insertRecord(const QVariantList& values);

	bool	   isTableOpen();
	TB_DESCR   getTableDesc();
	int		   getTableID();
	bool	   getTableParam(TABLE_PARA_STRU& param);
	bool	   getFieldsPara(QVector<FIELD_PARA_STRU>& vecParams);
	bool	   getFieldPara(int filedID,FIELD_PARA_STRU& param);
	quint64    getNextID();

private:
	void	   updateNextID();
	QString	   getSelectSQL(const QStringList& vecField);
	QString	   getIDSet(const QVector<int>& vecID);
	QString	   getAllField();

private:

	TB_DESCR   m_tb_descr;
	int		   m_next_id;
	QSqlDatabase m_db;

};

#endif
