
#ifndef __RTDB_API_H__
#define __RTDB_API_H__

#include "macro.h"

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#define HOSTNAME_LEN	64

#define KEYIDTYPE 	200
#define STRINGTYPE 	201
#define ENG_NAME_LEN 32
#define CHN_NAME_LEN 64

const int C_STRING_TYPE   = 1;
const int C_UCHAR_TYPE    = 2;
const int C_SHORT_TYPE    = 3;
const int C_INT_TYPE      = 4;
const int C_DATETIME_TYPE = 5;
const int C_FLOAT_TYPE    = 6;
const int C_DOUBLE_TYPE   = 7;
const int C_KEYID_TYPE    = 8;
const int C_BINARY_TYPE   = 9;
const int C_TEXT_TYPE     = 10;
const int C_IMAGE_TYPE    = 11;
const int C_APPKEY_TYPE   = 12;
const int C_APPID_TYPE    = 13;
const int C_UINT_TYPE     = 14;
const int C_LONG_TYPE     = 15;

struct KEY_STRU
{
	int key;
	short field_id;
	short table_no;
};

typedef long KEY_ID_STRU;

struct TB_DESCR 
{
	QString			table_name;	//����
	int 			table_id;					//���
	bool         	is_local;    			//����or����
};

struct TABLE_PARA_STRU 
{
	int				table_id;
	QString 		table_name_eng; 	//��Ӣ����
	QString         table_name_chn; 	//��������
	int             record_number; 			//��Ч��¼����
	int				max_valid_rec;			//�����Ч��¼��
	int				min_valid_rec;			//��С��Ч��¼��
	int				max_idle_rec;			//�����м�¼��
	int				min_idle_rec;			//��С���м�¼��
	int             key_len; 				//�ؼ��ֳ���
	int             subkey_num; 			//�ؼ��������
	int             record_size; 			//��¼��С
	short           field_sum;	 			//�����
	unsigned char   is_auto_generated;   	//�Ƿ��Զ����ɹؼ���
	int				next_id;
};

struct FIELD_PARA_STRU //..
{                                                               
	short           column_id; 					//��ID��
	short           field_length; 				//�����ݳ���
	int            	column_special; 			//����������
	unsigned char   data_type; 					//��������	
	QString         field_name_eng; 		//��Ӣ����
	QString         field_name_chn; 		//��������
	short   		field_no;   				//���ڲ������
	int             offset;     				//ƫ����
	int             ref_tableno; 				//���ñ��
	short       	ref_fieldno; 				//�������
	unsigned char   is_keyword; 				//�Ƿ�ؼ���
	unsigned char   is_index; 					//�Ƿ�����
	unsigned char   allow_null; 				//�Ƿ�����Ϊ��
	unsigned char   sort_order_no; 				//Ĭ������˳���**
	unsigned char   display_type; 				//��ʾ����
	unsigned char   reference_flag; 			//�������÷�ʽ
	unsigned char   reference_display; 			//�Ƿ�������ʾ
	int             search_attribute;   		//��������������
};

class EXPORT_LIB CRtTable
{

public:

	static KEY_STRU long_to_keyid(unsigned int keyid);
	static short	long_to_tableNo(unsigned int keyid);
	static short	long_to_field_id(unsigned int keyid);

public:

	CRtTable(int tableID);
	CRtTable(char* table_name);
	~CRtTable();

	bool	   openTableByID(int tableId = -1);
	bool       openTableByName(QString tableName);
	void	   closeTable();
	
	int		   getTableNoByName(QString table_name);
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

	void	   initTableAndField();
	void	   updateNextID();
	QString	   getSelectSQL(const QStringList& vecField);
	QString	   getIDSet(const QVector<int>& vecID);
	QString	   getAllField();

private:

	TB_DESCR   m_tb_descr;
	int		   m_next_id;

	QMap<int,TABLE_PARA_STRU> m_tableMap;
	QSqlDatabase	m_db;

};

#endif
