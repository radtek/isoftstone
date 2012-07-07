
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

	//	���ݵ���ID�Ͷ���л�ȡ���ֵ
	int		   getFiledsByID(int recID,const QVector<int>& vecField,QVariantList& vecValue);
	//	���ݵ���ID�˶��������ö��ֵ
	int		   getFiledsByName(int recID,const QStringList& vecField,QVariantList& vecValue);
	// ���ݵ���ID�����л�õ���ֵ
	int		   getFiledByID(int recID,int fieldID,QVariant& value);
	// ���ݵ���ID�͵���������õ���ֵ
	int		   getFiledsByName(int recID,const QString& fieldName,QVariant& value);
	// �õ������ƶ������м�¼
	int		   getTableFields(const QStringList& vecField,QVector<QVariantList>& vecRows);

	// �������������ID
	int		   getFieldNo(const QString& filedName);

	QString	   getFieldName(int fieldID);

	// ���������ƻ����Ӧ��ID
	bool	   getFiledIDByNames(const QStringList& vecField,QMap<QString,int>& mapValue);
	bool	   getFiledNameByIDS(const QVector<int>& vecField,QMap<int,QString>& mapValue);

	// ���ݶ��ID��õ����е�ֵ
	void	   getRecsByID(const QVector<int>& resourceIDS,int fieldID,QMap<int,QVariant>& valueMap);
	// ���ݶ��ID��ö����ֵ
	void	   getRecsByIDS(const QVector<int>& resourceIDS,QVector<int> vecField,QMap<int,QVariantList>& valueMap);

	// ��ñ������е����ݱ��浽 vecRows��
	void	   getTableRecs(QVector< QVariantList >& vecRows);  
	// ��õ�����¼�����е�ֵ
	void	   getRecByID(int keyid,QVariantList& vecValues);  
	// �õ�������¼�����е�ֵ
	void	   getRecsByID(QVector<int> vecKeyid,QVector< QVariantList >& vecRows); 
	void	   getRecsBySQL(const QString& strSQL,QVector< QVariantList>& vecRows);  
	void	   getRecsByCondition(const QString& strSQL,const QStringList& vecField,QVector< QVariantList>& vecRows);  

	// ��¼�Ƿ����
	bool	   isRecExist(int keyid);

	// ɾ������
	void	   deleteRecord(int keyID);
	void	   deleteRecByConditon(const QString& strSQL);

	// �޸ĵ�����¼����������
	void	   updateRecord(int keyID,const QVariantList& values);
	// �޸ĵ�����¼һ�е�ֵ
	void	   updateFiled(int keyID,int filed,const QVariant& value);

	// �������
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
