/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: vcimdata_common.h
** 摘要: 数据读取公用类
**       
**
** 当前版本: 1.0.0.0
** 作者:  刘瑞功
** 完成日期: 2011.07.06
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 刘瑞功      2011.10.11   V1.0      创建
**
****************************************************************************/

#ifndef VCIMDATA_COMMON_H
#define VCIMDATA_COMMON_H

#include <QVariant>
#include <QColor>

#include "Logger.h"

#ifdef WIN32
#include "rtdb_api_sim.h"
#else
#include "db_api/odb_define.h"
#endif

template<typename T>
inline QVariant toVariant_T(const char* strType,const char* strValue,int nLen)
{
	T tmp;
	memcpy(&tmp,strValue,nLen);
	//LoggerI::instance()->print(QString::number(tmp));
	return QVariant(tmp);
}

inline QVariant toVariant(const char* strType,const char* strValue,int nLen)
{
	if(QString(strType) == "long")
	{
		return toVariant_T<qlonglong>(strType,strValue,nLen);
	}
	else if(QString(strType) == "int")
	{
		return toVariant_T<int>(strType,strValue,nLen);
	}
	else if(QString(strType) == "float")
	{
		return toVariant_T<float>(strType,strValue,nLen);
	}
	else if(QString(strType) == "double")
	{
		return toVariant_T<double>(strType,strValue,nLen);
	}
	else if(QString(strType) == "string")
	{
		return QVariant(strValue);
	}
	else if(QString(strType) == "short")
	{
		return toVariant_T<short>(strType,strValue,nLen);
	}
	else if(QString(strType) == "uint")
	{
		return toVariant_T<uint>(strType,strValue,nLen);
	}
	else if(QString(strType) == "uchar")
	{
		return toVariant_T<uchar>(strType,strValue,nLen);
	}				
	else
	{
		return toVariant_T<float>(strType,strValue,nLen);
	}
}

inline QVariant toVariant(const char* strType,const char* strValue)
{
	if(QString(strType) == "long")
	{
		return QVariant(QString(strValue).toLongLong());
	}
	else if(QString(strType) == "int")
	{
		return QVariant(QString(strValue).toInt());
	}
	else if(QString(strType) == "float")
	{
		return QVariant(QString(strValue).toFloat());
	}
	else if(QString(strType) == "double")
	{
		return QVariant(QString(strValue).toDouble());
	}
	else if(QString(strType) == "string")
	{
		return QVariant(QString(strValue));
	}
	else if(QString(strType) == "short")
	{
		return QVariant(QString(strValue).toShort());
	}
	else if(QString(strType) == "uint")
	{
		return QVariant(QString(strValue).toUInt());
	}
	else if(QString(strType) == "uchar")
	{
		return QVariant(QString(strValue).toUShort());
	}				
	else
	{
		return QVariant(QString(strValue));
	}
}


inline std::string getTypeName(const int nType)
{
	switch(nType)
	{
	case C_STRING_TYPE:		return "string"		;
	case C_UCHAR_TYPE:		return "uchar"		;
	case C_SHORT_TYPE:		return "short"		;
	case C_INT_TYPE  :		return "int"		;
	case C_DATETIME_TYPE :  return "datetime"	;
	case C_FLOAT_TYPE:		return "float"		;
	case C_DOUBLE_TYPE:		return "double"		;
	case C_KEYID_TYPE:		return "long"		;
	case C_BINARY_TYPE :	return "string"		;
	case C_TEXT_TYPE :		return "string"		;
	case C_IMAGE_TYPE:		return "string"		;
	case C_APPKEY_TYPE:		return "string"		;
	case C_APPID_TYPE:		return "long"		;
	case C_UINT_TYPE :		return "uint"		;
	case C_LONG_TYPE :		return "long"		;
	default:				return "string"		;	

	}
}

inline QColor toColor(int nColor)
{
	QColor volColor(255,255,255);
	volColor.setRgb(nColor);
	return volColor;
}


#endif
