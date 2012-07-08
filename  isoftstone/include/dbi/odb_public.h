
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

// ��չ
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

struct FIELD_PARA_STRU
{                        
	int				table_id;					// ���
	short           field_id; 					//��ID��
	QString         field_name_eng; 			//��Ӣ����
	QString         field_name_chn; 			//��������
	unsigned char   data_type; 					//��������	
	short           data_length; 				//�����ݳ���
	bool		    is_keyword; 				//�Ƿ�ؼ���
	bool		    allow_null; 				//�Ƿ�����Ϊ��
	unsigned char   display_type; 				//��ʾ����
	bool		    ref_flag; 					//�������÷�ʽ
	unsigned char   ref_mode; 					//����ģʽ
	int             ref_tableno; 				//���ñ��
	short       	ref_fieldno; 				//�������
	unsigned char   ref_display; 				//��ʾ��
};

#endif