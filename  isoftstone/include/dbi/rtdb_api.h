
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
	QString			table_name;	//表名
	int 			table_id;					//表号
	bool         	is_local;    			//本地or网络
};

struct TABLE_PARA_STRU 
{
	int				table_id;
	QString 		table_name_eng; 	//表英文名
	QString         table_name_chn; 	//表中文名
	int             record_number; 			//有效记录个数
	int				max_valid_rec;			//最大有效记录号
	int				min_valid_rec;			//最小有效记录号
	int				max_idle_rec;			//最大空闲记录号
	int				min_idle_rec;			//最小空闲记录号
	int             key_len; 				//关键字长度
	int             subkey_num; 			//关键字域个数
	int             record_size; 			//记录大小
	short           field_sum;	 			//域个数
	unsigned char   is_auto_generated;   	//是否自动生成关键字
	int				next_id;
};

struct FIELD_PARA_STRU //..
{                                                               
	short           column_id; 					//域ID号
	short           field_length; 				//域数据长度
	int            	column_special; 			//域特殊属性
	unsigned char   data_type; 					//数据类型	
	QString         field_name_eng; 		//域英文名
	QString         field_name_chn; 		//域中文名
	short   		field_no;   				//域内部排序号
	int             offset;     				//偏移量
	int             ref_tableno; 				//引用表号
	short       	ref_fieldno; 				//引用域号
	unsigned char   is_keyword; 				//是否关键字
	unsigned char   is_index; 					//是否索引
	unsigned char   allow_null; 				//是否允许为空
	unsigned char   sort_order_no; 				//默认排序顺序号**
	unsigned char   display_type; 				//显示类型
	unsigned char   reference_flag; 			//数据引用方式
	unsigned char   reference_display; 			//是否引用显示
	int             search_attribute;   		//检索器的域特性
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
