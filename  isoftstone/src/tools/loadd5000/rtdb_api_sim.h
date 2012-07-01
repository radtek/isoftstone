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
	char			context_name[ENG_NAME_LEN];	//态名
	char 			app_name[ENG_NAME_LEN];		//应用名
	char 			table_name[ENG_NAME_LEN];	//表名
	char			host_name[ENG_NAME_LEN];	//节点名
	int				context_id;					//态号
	int 			app_id;						//应用号
	int 			table_id;					//表号
	bool         	is_local;    				//本地or网络
// 	CTableOp*   	ptab;						//本地操作类对象
// 	CTableNet*  	ptabnet;					//网络操作类对象
};

struct TABLE_PARA_STRU //..
{
	char 			table_name_eng[ENG_NAME_LEN]; 	//表英文名
	char           	table_name_chn[CHN_NAME_LEN]; 	//表中文名
	int             record_number; 					//有效记录个数
	int				max_valid_rec;					//最大有效记录号
	int				min_valid_rec;					//最小有效记录号
	int				max_idle_rec;					//最大空闲记录号
	int				min_idle_rec;					//最小空闲记录号
	int             key_len; 						//关键字长度
	int             subkey_num; 					//关键字域个数
	int             record_size; 					//记录大小
	short           field_sum;	 					//域个数
	unsigned char   is_auto_generated;   			//是否自动生成关键字
};

struct FIELD_PARA_STRU //..
{
	short           column_id; 							//域ID号
	short           field_length; 						//域数据长度
	int            	column_special; 					//域特殊属性
	unsigned char   data_type; 							//数据类型	
	char            field_name_eng[ENG_NAME_LEN]; 		//域英文名
	short   		field_no;   						//域内部排序号
	int             offset;     						//偏移量
	int             ref_tableno; 						//引用表号
	short       	ref_fieldno; 						//引用域号
	unsigned char   is_keyword; 						//是否关键字
	unsigned char   is_index; 							//是否索引
	unsigned char   allow_null; 						//是否允许为空
	unsigned char   sort_order_no; 						//默认排序顺序号**
	unsigned char   display_type; 						//显示类型
	unsigned char   reference_flag; 					//数据引用方式
	unsigned char   reference_display; 					//是否引用显示
	char            field_name_chn[CHN_NAME_LEN]; 		//域中文名
	char            menu_name[MENU_NAME_LEN]; 			//菜单名
	char            default_asciival[DEFAULT_VALUE_LEN];//默认值
	char            min_asciival[DEFAULT_VALUE_LEN]; 	//最小值
	char            max_asciival[DEFAULT_VALUE_LEN]; 	//最大值
	int             search_attribute;   				//检索器的域特性
};

//打开表（按名称）
int OpenTableByName(char* host_name, char* context_name, char* app_name, 
						char* table_name, TB_DESCR* tb_descr);

//打开表（按号）
int OpenTableByID(char* host_name, int context_id, int app_id, 
					int table_id, TB_DESCR* tb_descr);

//关闭表
int CloseTable(TB_DESCR* tb_descr);

//读全表
int GetTableRecs(TB_DESCR* tb_descr, int mode, char** buf_ptr);

//根据一个或者多个域名取得域号
int GetFieldNoByName(TB_DESCR* tb_descr, char* field_name, 
						int* field_no_array, int* field_num);

//读全表的一列或多列
int GetTableFields(TB_DESCR* tb_descr, int mode, int* field_no_array, 
					int field_num, char** buf_ptr);

//读一条记录的某一个或多个域（通过关键字）
int GetFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr);

//读一条记录（通过关键字）
int GetRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr);

//读多条记录（通过关键字）
int GetRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr);

//读一条记录的某一个或多个域（通过名称）
int GetFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr);

//读一条记录（通过名称）
int GetRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr);

//通过名称获得关键字
int GetIDByName(TB_DESCR* tb_descr, char* name, int key_size, char* key_ptr);

//写一条记录（通过关键字）
int UpdateRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr);

//写多条记录（通过关键字）
int UpdateRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr);

//写一条记录的一个或多个域（通过关键字）
int UpdateFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr);

//写一条记录（通过名称）
int UpdateRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr);

//写一条记录的一个或多个域（通过名称）
int UpdateFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr);

//增加一条或多条记录
int InsertRec(TB_DESCR* tb_descr, int rec_num, int buf_size, char* buf_ptr, int mode);

//删除一条记录（通过关键字）
int DeleteRecByID(TB_DESCR* tb_descr, char* key_ptr);

//删除多条记录（通过关键字）
int DeleteRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num);

//删除从某条记录开始的向前或向后的所有记录，FORWARD向前，BACKWARD向后
int DeleteAlignRecsByID(TB_DESCR* tb_descr, char* key_ptr, int direction = FORWARD);

//删除一条记录（通过名称）
int DeleteRecByName(TB_DESCR* tb_descr, char* name);

//清空表（删除所有记录）
int ClearTable(TB_DESCR* tb_descr);

//按SQL读记录
int GetBySql(TB_DESCR* tb_descr, char* sql_ptr, char** buf_ptr);

//根据mask_name得到mask_id
int GetMaskIDByName(TB_DESCR* tb_descr, int field_id, char* mask_name, int* mask_id);

//读Bit位（按mask名）
int GetBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
						char* mask_name, int* mask_value);

//读Bit位（按mask号）
int GetBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int* mask_value);

//写Bit位（按mask名）
int UpdateBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
							char* mask_name, int mask_value);

//写Bit位（按mask号）
int UpdateBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int mask_value);

//按属性读记录  change by Ralph .20080309
int GetRecsByAttr(TB_DESCR* tb_descr,  int con_field_id, int con_type, 
					char* field_value, int mask_value, char** buf_ptr);

//按关系读记录（父读子）
int GetRecsByRel(TB_DESCR* fth_tb_descr, TB_DESCR* son_tb_descr, char* field_value, char** buf_ptr);

//按关系读记录的一列或多列（父读子）
int GetFieldsByRel(TB_DESCR* fth_tb_descr, TB_DESCR* son_tb_descr, char* field_value, 
					int* field_no_array, int field_num, char** buf_ptr);

//读表参数
int GetTablePara(TB_DESCR* tb_descr, TABLE_PARA_STRU* table_para);

//读所有域参数
int GetFieldsPara(TB_DESCR* tb_descr, FIELD_PARA_STRU** field_para);

//读一个域参数
int GetFieldParaByID(TB_DESCR* tb_descr, int field_id, FIELD_PARA_STRU* field_para);

//根据表名获取表号
int GetTableNoByName(char* table_name, int* table_id);

//根据表号获取表名
int GetTableNameByID(int table_id, char* table_name);

//释放内存
int BufFree(void* buf_ptr);

// 按照属性读一列或多列  change by Ralph .20080309
int GetFieldsByAttr (TB_DESCR *tb_descr, int* get_field_id, int get_field_num ,  int con_field_id, 
             int con_type,char* field_value, int mask_value, char **buf_ptr);
             
//按顺序读表多条记录
int GetSerialRecs(TB_DESCR* tb_descr, int offset, int num, char** buf_ptr);

//根据KEYID得到字符串
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
