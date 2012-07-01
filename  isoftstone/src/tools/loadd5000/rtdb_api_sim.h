/*******************************************************************************
ModuleName:   Real Time Database management system
FileName:	  rtdb_api.h
DESCRIPTION:  rtdb api header
FUNCTION LIST:
COMMENT:
History:
Date          Version     Modifier                Activities
2009-01-10    1.1                              add net interfaces
================================================================================
2008-10-30    1.0                              created
*******************************************************************************/
#ifndef __RTDB_API_SIM_H__
#define __RTDB_API_SIM_H__

#ifdef WIN32

#define AC_MAX_NUM		  16 

#define AC_DEFAULT_NO		0

#define AC_REALTIME_NO 	1
#define AC_STUDY_NO	    2
#define AC_RESEARCH_NO  2
#define AC_PLAN_NO	    3
#define AC_TEST_NO	    4
#define AC_PDR_NO	      5
#define AC_DTS_NO	      6
#define AC_TRAINING_NO	6
#define AC_SYS_NO       15

#define	   ENG_NAME_LEN 	   		32
#define	   CHN_NAME_LEN 	   		64
#define	   MENU_NAME_LEN   		40
#define	   DEFAULT_VALUE_LEN   	20
#define		HOSTNAME_LEN	64

#define KEYIDTYPE 	200
#define STRINGTYPE 	201

//for GetRecsByAttr
#define GRT 		100
#define GRTE 		101
#define LSS  		102
#define LSSE 		103
#define EQU  		104
#define EQUN		105

#define AF_SCADA	     1
#define AF_PAS		     2
#define AF_DTS		     3
#define AF_FES		     4
#define AF_AGC		     5
#define AF_AVC		     6
#define AF_WAMS		     7
#define AF_CIM		     8
#define AF_WDM         9
#define AF_TMR         10
#define AF_DESUFS      11
#define AF_SCHEDULE    12
#define	AF_DSA	       13
#define AF_LLS         14
#define	AF_OMS	       15
#define AF_PUBLIC	   16
#define AF_OSM         17

#define AF_DATA_SRV    33
#define AF_BASE_SRV    34
#define AF_REPORT_SRV  35

#define 	  AP_SCADA				 100000
#define 	  AP_PAS_MODEL		 200000
#define 	  AP_DTS         	 300000
#define 	  AP_FES					 400000
#define     AP_FES_GPS       410000
#define     AP_AGC					 500000
#define     AP_AVC_SVC       600000
#define     AP_WAMS       	 700000
#define     AP_CIM					 800000
#define     AP_WDM           900000
#define     AP_TMR           1000000
#define     AP_DESUFS        1100000
#define     AP_SCHEDULE      1200000
#define     AP_DSA           1300000
#define     AP_LLS           1400000
#define     AP_OMS           1500000
#define     AP_PUBLIC        1600000
#define     AP_OSM           1700000


enum DIRECTION
{
	FORWARD = 0,
	BACKWARD = 1 ,
};

struct TB_DESCR //..
{
	char			context_name[ENG_NAME_LEN];	//̬��
	char 			app_name[ENG_NAME_LEN];		//Ӧ����
	char 			table_name[ENG_NAME_LEN];	//����
	char			host_name[ENG_NAME_LEN];	//�ڵ���
	int				context_id;					//̬��
	int 			app_id;						//Ӧ�ú�
	int 			table_id;					//���
	bool         	is_local;    				//����or����
// 	CTableOp*   	ptab;						//���ز��������
// 	CTableNet*  	ptabnet;					//������������
};

struct TABLE_PARA_STRU //..
{
	char 			table_name_eng[ENG_NAME_LEN]; 	//��Ӣ����
	char           	table_name_chn[CHN_NAME_LEN]; 	//��������
	int             record_number; 					//��Ч��¼����
	int				max_valid_rec;					//�����Ч��¼��
	int				min_valid_rec;					//��С��Ч��¼��
	int				max_idle_rec;					//�����м�¼��
	int				min_idle_rec;					//��С���м�¼��
	int             key_len; 						//�ؼ��ֳ���
	int             subkey_num; 					//�ؼ��������
	int             record_size; 					//��¼��С
	short           field_sum;	 					//�����
	unsigned char   is_auto_generated;   			//�Ƿ��Զ����ɹؼ���
};

struct FIELD_PARA_STRU //..
{
	short           column_id; 							//��ID��
	short           field_length; 						//�����ݳ���
	int            	column_special; 					//����������
	unsigned char   data_type; 							//��������	
	char            field_name_eng[ENG_NAME_LEN]; 		//��Ӣ����
	short   		field_no;   						//���ڲ������
	int             offset;     						//ƫ����
	int             ref_tableno; 						//���ñ��
	short       	ref_fieldno; 						//�������
	unsigned char   is_keyword; 						//�Ƿ�ؼ���
	unsigned char   is_index; 							//�Ƿ�����
	unsigned char   allow_null; 						//�Ƿ�����Ϊ��
	unsigned char   sort_order_no; 						//Ĭ������˳���**
	unsigned char   display_type; 						//��ʾ����
	unsigned char   reference_flag; 					//�������÷�ʽ
	unsigned char   reference_display; 					//�Ƿ�������ʾ
	char            field_name_chn[CHN_NAME_LEN]; 		//��������
	char            menu_name[MENU_NAME_LEN]; 			//�˵���
	char            default_asciival[DEFAULT_VALUE_LEN];//Ĭ��ֵ
	char            min_asciival[DEFAULT_VALUE_LEN]; 	//��Сֵ
	char            max_asciival[DEFAULT_VALUE_LEN]; 	//���ֵ
	int             search_attribute;   				//��������������
};

//�򿪱������ƣ�
int OpenTableByName(char* host_name, char* context_name, char* app_name, 
						char* table_name, TB_DESCR* tb_descr);

//�򿪱����ţ�
int OpenTableByID(char* host_name, int context_id, int app_id, 
					int table_id, TB_DESCR* tb_descr);

//�رձ�
int CloseTable(TB_DESCR* tb_descr);

//��ȫ��
int GetTableRecs(TB_DESCR* tb_descr, int mode, char** buf_ptr);

//����һ�����߶������ȡ�����
int GetFieldNoByName(TB_DESCR* tb_descr, char* field_name, 
						int* field_no_array, int* field_num);

//��ȫ���һ�л����
int GetTableFields(TB_DESCR* tb_descr, int mode, int* field_no_array, 
					int field_num, char** buf_ptr);

//��һ����¼��ĳһ��������ͨ���ؼ��֣�
int GetFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr);

//��һ����¼��ͨ���ؼ��֣�
int GetRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr);

//��������¼��ͨ���ؼ��֣�
int GetRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr);

//��һ����¼��ĳһ��������ͨ�����ƣ�
int GetFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr);

//��һ����¼��ͨ�����ƣ�
int GetRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr);

//ͨ�����ƻ�ùؼ���
int GetIDByName(TB_DESCR* tb_descr, char* name, int key_size, char* key_ptr);

//дһ����¼��ͨ���ؼ��֣�
int UpdateRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr);

//д������¼��ͨ���ؼ��֣�
int UpdateRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr);

//дһ����¼��һ��������ͨ���ؼ��֣�
int UpdateFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr);

//дһ����¼��ͨ�����ƣ�
int UpdateRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr);

//дһ����¼��һ��������ͨ�����ƣ�
int UpdateFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr);

//����һ���������¼
int InsertRec(TB_DESCR* tb_descr, int rec_num, int buf_size, char* buf_ptr, int mode);

//ɾ��һ����¼��ͨ���ؼ��֣�
int DeleteRecByID(TB_DESCR* tb_descr, char* key_ptr);

//ɾ��������¼��ͨ���ؼ��֣�
int DeleteRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num);

//ɾ����ĳ����¼��ʼ����ǰ���������м�¼��FORWARD��ǰ��BACKWARD���
int DeleteAlignRecsByID(TB_DESCR* tb_descr, char* key_ptr, int direction = FORWARD);

//ɾ��һ����¼��ͨ�����ƣ�
int DeleteRecByName(TB_DESCR* tb_descr, char* name);

//��ձ�ɾ�����м�¼��
int ClearTable(TB_DESCR* tb_descr);

//��SQL����¼
int GetBySql(TB_DESCR* tb_descr, char* sql_ptr, char** buf_ptr);

//����mask_name�õ�mask_id
int GetMaskIDByName(TB_DESCR* tb_descr, int field_id, char* mask_name, int* mask_id);

//��Bitλ����mask����
int GetBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
						char* mask_name, int* mask_value);

//��Bitλ����mask�ţ�
int GetBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int* mask_value);

//дBitλ����mask����
int UpdateBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
							char* mask_name, int mask_value);

//дBitλ����mask�ţ�
int UpdateBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int mask_value);

//�����Զ���¼  change by Ralph .20080309
int GetRecsByAttr(TB_DESCR* tb_descr,  int con_field_id, int con_type, 
					char* field_value, int mask_value, char** buf_ptr);

//����ϵ����¼�������ӣ�
int GetRecsByRel(TB_DESCR* fth_tb_descr, TB_DESCR* son_tb_descr, char* field_value, char** buf_ptr);

//����ϵ����¼��һ�л���У������ӣ�
int GetFieldsByRel(TB_DESCR* fth_tb_descr, TB_DESCR* son_tb_descr, char* field_value, 
					int* field_no_array, int field_num, char** buf_ptr);

//�������
int GetTablePara(TB_DESCR* tb_descr, TABLE_PARA_STRU* table_para);

//�����������
int GetFieldsPara(TB_DESCR* tb_descr, FIELD_PARA_STRU** field_para);

//��һ�������
int GetFieldParaByID(TB_DESCR* tb_descr, int field_id, FIELD_PARA_STRU* field_para);

//���ݱ�����ȡ���
int GetTableNoByName(char* table_name, int* table_id);

//���ݱ�Ż�ȡ����
int GetTableNameByID(int table_id, char* table_name);

//�ͷ��ڴ�
int BufFree(void* buf_ptr);

// �������Զ�һ�л����  change by Ralph .20080309
int GetFieldsByAttr (TB_DESCR *tb_descr, int* get_field_id, int get_field_num ,  int con_field_id, 
             int con_type,char* field_value, int mask_value, char **buf_ptr);
             
//��˳����������¼
int GetSerialRecs(TB_DESCR* tb_descr, int offset, int num, char** buf_ptr);

//����KEYID�õ��ַ���
int GetNameString(TB_DESCR* tb_descr, long* ref_id, int ref_id_num, char** ref_str);


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct KEY_STRU
{
	int key;
	short field_id;
	short table_no;
};

typedef long KEY_ID_STRU;

class CCommon
{
public:

	static void keyid_to_long(struct KEY_STRU *key_stru_ptr,unsigned long*key_id_ptr);
	static void long_to_keyid(unsigned long key_id,struct KEY_STRU *key_stru_ptr);

	static void long_to_tableNo(unsigned long key_id,short *table_no_ptr);
	static void long_to_field_id(unsigned long key_id,short *field_id_ptr);
	static void long_to_key(unsigned long key_id,int  *key_ptr);
};

////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////

#endif // WIN32

#endif
