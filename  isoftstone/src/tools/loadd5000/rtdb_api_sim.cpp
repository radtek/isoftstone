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

#ifdef WIN32

#include <QtGlobal>
#include <QObject>
#include <string.h>

#include "rtdb_api_sim.h"


//打开表（按名称）
int OpenTableByName(char* host_name, char* context_name, char* app_name, 
					char* table_name, TB_DESCR* tb_descr)
{
	Q_UNUSED(host_name);
	Q_UNUSED(context_name);
	Q_UNUSED(app_name);
	Q_UNUSED(table_name);
	Q_UNUSED(tb_descr);
	return 0;
}

//打开表（按号）
int OpenTableByID(char* host_name, int context_id, int app_id, 
					int table_id, TB_DESCR* tb_descr)
{
	Q_UNUSED(host_name);
	Q_UNUSED(context_id);
	Q_UNUSED(app_id);
	Q_UNUSED(table_id);
	Q_UNUSED(tb_descr);
	return 0;
}

//关闭表
int CloseTable(TB_DESCR* tb_descr)
{
	Q_UNUSED(tb_descr);
	return 0;
}

//读全表
int GetTableRecs(TB_DESCR* tb_descr, int mode, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(mode);
	Q_UNUSED(buf_ptr);
	return 0;
}

//根据一个或者多个域名取得域号
int GetFieldNoByName(TB_DESCR* tb_descr, char* field_name, 
						int* field_no_array, int* field_num)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(field_name);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	return 0;
}

//读全表的一列或多列
int GetTableFields(TB_DESCR* tb_descr, int mode, int* field_no_array, 
					int field_num, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(mode);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_ptr);
	return 0;
}

//读一条记录的某一个或多个域（通过关键字）
int GetFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//读一条记录（通过关键字）
int GetRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//读多条记录（通过关键字）
int GetRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(key_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}


//读一条记录的某一个或多个域（通过名称）
int GetFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
					int field_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//读一条记录（通过名称）
int GetRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//通过名称获得关键字
int GetIDByName(TB_DESCR* tb_descr, char* name, int key_size, char* key_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	Q_UNUSED(key_size);
	Q_UNUSED(key_ptr);
	return 0;
}

//写一条记录（通过关键字）
int UpdateRecByID(TB_DESCR* tb_descr, char* key_ptr, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//写多条记录（通过关键字）
int UpdateRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(key_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//写一条记录的一个或多个域（通过关键字）
int UpdateFieldsByID(TB_DESCR* tb_descr, char* key_ptr, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//写一条记录（通过名称）
int UpdateRecByName(TB_DESCR* tb_descr, char* name, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//写一条记录的一个或多个域（通过名称）
int UpdateFieldsByName(TB_DESCR* tb_descr, char* name, int* field_no_array, 
						int field_num, int buf_size, char* buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	return 0;
}

//增加一条或多条记录
int InsertRec(TB_DESCR* tb_descr, int rec_num, int buf_size, char* buf_ptr, int mode)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(rec_num);
	Q_UNUSED(buf_size);
	Q_UNUSED(buf_ptr);
	Q_UNUSED(mode);
	return 0;
}

//删除一条记录（通过关键字）
int DeleteRecByID(TB_DESCR* tb_descr, char* key_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	return 0;
}

//删除多条记录（通过关键字）
int DeleteRecsByID(TB_DESCR* tb_descr, char* key_ptr, int key_num)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(key_num);
	return 0;
}

//删除从某条记录开始的向前或向后的所有记录，FORWARD向前，BACKWARD向后
int DeleteAlignRecsByID(TB_DESCR* tb_descr, char* key_ptr, int direction )
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(direction);
	return 0;
}

//删除一条记录（通过名称）
int DeleteRecByName(TB_DESCR* tb_descr, char* name)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(name);
	return 0;
}

//清空表（删除所有记录）
int ClearTable(TB_DESCR* tb_descr)
{
	Q_UNUSED(tb_descr);
	return 0;
}

//按SQL读记录
int GetBySql(TB_DESCR* tb_descr, char* sql_ptr, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(sql_ptr);
	Q_UNUSED(buf_ptr);
	return 0;
}

//根据mask_name得到mask_id
int GetMaskIDByName(TB_DESCR* tb_descr, int field_id, char* mask_name, int* mask_id)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(field_id);
	Q_UNUSED(mask_name);
	Q_UNUSED(mask_id);
	return 0;
}

//读Bit位（按mask名）
int GetBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
						char* mask_name, int* mask_value)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_id);
	Q_UNUSED(mask_name);
	Q_UNUSED(mask_value);
	return 0;
}

//读Bit位（按mask号）
int GetBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int* mask_value)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_id);
	Q_UNUSED(mask_id);
	Q_UNUSED(mask_value);
	return 0;
}

//写Bit位（按mask名）
int UpdateBitFieldByName(TB_DESCR* tb_descr, char* key_ptr, int field_id, 
							char* mask_name, int mask_value)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_id);
	Q_UNUSED(mask_name);
	Q_UNUSED(mask_value);
	return 0;
}

//写Bit位（按mask号）
int UpdateBitFieldByID(TB_DESCR* tb_descr, char* key_ptr, int field_id, int mask_id, int mask_value)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(key_ptr);
	Q_UNUSED(field_id);
	Q_UNUSED(mask_id);
	Q_UNUSED(mask_value);
	return 0;
}

//按属性读记录  change by Ralph .20080309
int GetRecsByAttr(TB_DESCR* tb_descr,  int con_field_id, int con_type, 
					char* field_value, int mask_value, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(con_field_id);
	Q_UNUSED(con_type);
	Q_UNUSED(field_value);
	Q_UNUSED(mask_value);
	Q_UNUSED(buf_ptr);
	return 0;
}

//按关系读记录（父读子）
int GetRecsByRel(TB_DESCR* tb_descr, TB_DESCR* son_tb_descr, char* field_value, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(son_tb_descr);
	Q_UNUSED(field_value);
	Q_UNUSED(buf_ptr);
	return 0;
}

//按关系读记录的一列或多列（父读子）
int GetFieldsByRel(TB_DESCR* tb_descr, TB_DESCR* son_tb_descr, char* field_value, 
					int* field_no_array, int field_num, char** buf_ptr)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(son_tb_descr);
	Q_UNUSED(field_value);
	Q_UNUSED(field_no_array);
	Q_UNUSED(field_num);
	Q_UNUSED(buf_ptr);
	return 0;
}

//读表参数
int GetTablePara(TB_DESCR* tb_descr, TABLE_PARA_STRU* table_para)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(table_para);

	strcpy(table_para->table_name_eng,"test");
	strcpy(table_para->table_name_chn,QObject::tr("测试表").toLocal8Bit().data());
	table_para->record_number = 200; 		
	table_para->max_valid_rec = 300;		
	table_para->min_valid_rec = 100;		
	table_para->max_idle_rec = 150;		
	table_para->min_idle_rec = 120;		
	table_para->key_len = 50; 			
	table_para->subkey_num = 10; 		
	table_para->record_size = 30; 		
	table_para->field_sum = 20;	 		
	table_para->is_auto_generated = 'y'; 

	return 0;
}

//读所有域参数
int GetFieldsPara(TB_DESCR* tb_descr, FIELD_PARA_STRU** field_para)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(field_para);

	return -1;
}

//读一个域参数
int GetFieldParaByID(TB_DESCR* tb_descr, int field_id, FIELD_PARA_STRU* field_para)
{
	Q_UNUSED(tb_descr);
	Q_UNUSED(field_id);
	Q_UNUSED(field_para);
	return 0;
}

//根据表名获取表号
int GetTableNoByName(char* table_name, int* table_id)
{
	Q_UNUSED(table_name);
	Q_UNUSED(table_id);
	return 0;
}

//根据表号获取表名
int GetTableNameByID(int table_id, char* table_name)
{
	Q_UNUSED(table_id);
	Q_UNUSED(table_name);
	return 0;
}

//释放内存
int BufFree(void* buf_ptr)
{
	Q_UNUSED(buf_ptr);
	return 0;
}

// 按照属性读一列或多列  change by Ralph .20080309
int GetFieldsByAttr (TB_DESCR *, int* , int  ,  int , 
             int ,char* , int , char **)
{
	return 0;
}
             
//按顺序读表多条记录
int GetSerialRecs(TB_DESCR* , int , int , char** )
{
	return 0;
}

//根据KEYID得到字符串
int GetNameString(TB_DESCR* , long* , int , char** )
{
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
void CCommon::keyid_to_long(struct KEY_STRU *,unsigned long*)
{

}
void CCommon::long_to_keyid(unsigned long ,struct KEY_STRU *)
{

}

void CCommon::long_to_tableNo(unsigned long ,short *)
{

}
void CCommon::long_to_field_id(unsigned long ,short *)
{

}
void CCommon::long_to_key(unsigned long ,int  *)
{

}



#endif // WIN32

