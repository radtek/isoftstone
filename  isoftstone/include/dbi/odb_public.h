
#ifndef ODB_PUBLIC_H
#define ODB_PUBLIC_H


#include "macro.h"

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>

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

// 扩展
const int C_BOOLEAN_TYPE = 16;

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

struct FIELD_PARA_STRU
{                        
	int				table_id;					// 表号
	short           field_id; 					//域ID号
	QString         field_name_eng; 			//域英文名
	QString         field_name_chn; 			//域中文名
	unsigned char   data_type; 					//数据类型	
	short           data_length; 				//域数据长度
	bool		    is_keyword; 				//是否关键字
	bool		    allow_null; 				//是否允许为空
	unsigned char   display_type; 				//显示类型
	bool		    ref_flag; 					//数据引用方式
	unsigned char   ref_mode; 					//数据模式
	int             ref_tableno; 				//引用表号
	short       	ref_fieldno; 				//引用域号
	unsigned char   ref_display; 				//显示列
};

#endif