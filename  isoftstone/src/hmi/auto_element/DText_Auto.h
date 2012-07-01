#ifndef CLASS_DTEXT_AUTO_H
#define CLASS_DTEXT_AUTO_H

#include <QGraphicsItem>
#include <QDataStream>
#include <QString>
#include <QObject>
#include <QFontMetrics>
#include <QFont>
#include <QRect>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPixmap>
#include <QVariant>

#include <math.h>

#include "rapidxml.hpp"
#include "interface.h"
#include "GEnum.h"
#include "itembase.h"


using namespace rapidxml;


struct DText_Struct
{
	uint  af;
	quint64  app;
	uint  dotlength;
	QColor  fc;
	uint  ff;
	uint  fm;
	uint  fs;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DataFrom;
	int  p_DataLowerLimit;
	uint  p_DataSetFlag;
	int  p_DataUpperLimit;
	uint  p_DyColorFlag;
	int  p_FontDeltaX;
	int  p_FontDeltaY;
	int  p_FontHeight;
	uint  p_FontInterval;
	uint  p_FontWidth;
	bool  p_IsAbs;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_MatrixFontFlag;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_RowInterval;
	uint  p_ShowModeMask;
	uint  p_ShowSignFlag;
	uint  p_ZoomMaxLevel;
	uint  state;
	QThree  tfr;
	QString  ts;
	uint  type;
	int  voltype;
	int  wm;
	qreal  x;
	qreal  y;

	DText_Struct& operator=(const DText_Struct& cp)
	{
		this->af = 		cp.af;
		this->app = 		cp.app;
		this->dotlength = 		cp.dotlength;
		this->fc = 		cp.fc;
		this->ff = 		cp.ff;
		this->fm = 		cp.fm;
		this->fs = 		cp.fs;
		this->id = 		cp.id;
		this->keyid = 		cp.keyid;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_AutoChangeAppFlag = 		cp.p_AutoChangeAppFlag;
		this->p_DataFrom = 		cp.p_DataFrom;
		this->p_DataLowerLimit = 		cp.p_DataLowerLimit;
		this->p_DataSetFlag = 		cp.p_DataSetFlag;
		this->p_DataUpperLimit = 		cp.p_DataUpperLimit;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_FontDeltaX = 		cp.p_FontDeltaX;
		this->p_FontDeltaY = 		cp.p_FontDeltaY;
		this->p_FontHeight = 		cp.p_FontHeight;
		this->p_FontInterval = 		cp.p_FontInterval;
		this->p_FontWidth = 		cp.p_FontWidth;
		this->p_IsAbs = 		cp.p_IsAbs;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_MatrixFontFlag = 		cp.p_MatrixFontFlag;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_ReportType = 		cp.p_ReportType;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_RowInterval = 		cp.p_RowInterval;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->p_ShowSignFlag = 		cp.p_ShowSignFlag;
		this->p_ZoomMaxLevel = 		cp.p_ZoomMaxLevel;
		this->state = 		cp.state;
		this->tfr = 		cp.tfr;
		this->ts = 		cp.ts;
		this->type = 		cp.type;
		this->voltype = 		cp.voltype;
		this->wm = 		cp.wm;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CDText_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.app;
		out << m_Info.dotlength;
		out << m_Info.fc;
		out << m_Info.ff;
		out << m_Info.fm;
		out << m_Info.fs;
		out << m_Info.id;
		out << m_Info.keyid;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.p_AssFlag;
		out << m_Info.p_AutoChangeAppFlag;
		out << m_Info.p_DataFrom;
		out << m_Info.p_DataLowerLimit;
		out << m_Info.p_DataSetFlag;
		out << m_Info.p_DataUpperLimit;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_FontDeltaX;
		out << m_Info.p_FontDeltaY;
		out << m_Info.p_FontHeight;
		out << m_Info.p_FontInterval;
		out << m_Info.p_FontWidth;
		out << m_Info.p_IsAbs;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_MatrixFontFlag;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_ReportType;
		out << m_Info.p_RoundBox;
		out << m_Info.p_RowInterval;
		out << m_Info.p_ShowModeMask;
		out << m_Info.p_ShowSignFlag;
		out << m_Info.p_ZoomMaxLevel;
		out << m_Info.state;
		out << m_Info.tfr;
		out << m_Info.ts;
		out << m_Info.type;
		out << m_Info.voltype;
		out << m_Info.wm;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.app;
		out >> m_Info.dotlength;
		out >> m_Info.fc;
		out >> m_Info.ff;
		out >> m_Info.fm;
		out >> m_Info.fs;
		out >> m_Info.id;
		out >> m_Info.keyid;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_AutoChangeAppFlag;
		out >> m_Info.p_DataFrom;
		out >> m_Info.p_DataLowerLimit;
		out >> m_Info.p_DataSetFlag;
		out >> m_Info.p_DataUpperLimit;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_FontDeltaX;
		out >> m_Info.p_FontDeltaY;
		out >> m_Info.p_FontHeight;
		out >> m_Info.p_FontInterval;
		out >> m_Info.p_FontWidth;
		out >> m_Info.p_IsAbs;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_MatrixFontFlag;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_ReportType;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_RowInterval;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.p_ShowSignFlag;
		out >> m_Info.p_ZoomMaxLevel;
		out >> m_Info.state;
		out >> m_Info.tfr;
		out >> m_Info.ts;
		out >> m_Info.type;
		out >> m_Info.voltype;
		out >> m_Info.wm;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "af" );
		attr->value(QString::number(m_Info.af).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app" );
		attr->value(QString::number(m_Info.app).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "dotlength" );
		attr->value(QString::number(m_Info.dotlength).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.fc.red(),(int)m_Info.fc.green(),(int)m_Info.fc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "ff" );
		attr->value(QString::number(m_Info.ff).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fm" );
		attr->value(QString::number(m_Info.fm).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fs" );
		attr->value(QString::number(m_Info.fs).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid" );
		attr->value(QString::number(m_Info.keyid).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "lc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.lc.red(),(int)m_Info.lc.green(),(int)m_Info.lc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "ls" );
		attr->value(QString::number(m_Info.ls).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "lw" );
		attr->value(QString::number(m_Info.lw).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_AssFlag" );
		attr->value(QString::number(m_Info.p_AssFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_AutoChangeAppFlag" );
		attr->value( m_Info.p_AutoChangeAppFlag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DataFrom" );
		attr->value(QString::number(m_Info.p_DataFrom).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DataLowerLimit" );
		attr->value(QString::number(m_Info.p_DataLowerLimit).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DataSetFlag" );
		attr->value(QString::number(m_Info.p_DataSetFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DataUpperLimit" );
		attr->value(QString::number(m_Info.p_DataUpperLimit).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_FontDeltaX" );
		attr->value(QString::number(m_Info.p_FontDeltaX).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_FontDeltaY" );
		attr->value(QString::number(m_Info.p_FontDeltaY).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_FontHeight" );
		attr->value(QString::number(m_Info.p_FontHeight).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_FontInterval" );
		attr->value(QString::number(m_Info.p_FontInterval).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_FontWidth" );
		attr->value(QString::number(m_Info.p_FontWidth).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_IsAbs" );
		attr->value(QString::number(m_Info.p_IsAbs).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_LevelEnd" );
		attr->value(QString::number(m_Info.p_LevelEnd).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_LevelStart" );
		attr->value(QString::number(m_Info.p_LevelStart).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_MatrixFontFlag" );
		attr->value(QString::number(m_Info.p_MatrixFontFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NameString" );
		attr->value(QString::number(m_Info.p_NameString).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Plane" );
		attr->value(QString::number(m_Info.p_Plane).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType" );
		attr->value(QString::number(m_Info.p_ReportType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RowInterval" );
		attr->value(QString::number(m_Info.p_RowInterval).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowSignFlag" );
		attr->value(QString::number(m_Info.p_ShowSignFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ZoomMaxLevel" );
		attr->value(QString::number(m_Info.p_ZoomMaxLevel).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state" );
		attr->value(QString::number(m_Info.state).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "tfr" );
		QString strTfr = "rotate(";
		strTfr += QString::number(m_Info.tfr.rotate);
		strTfr += ") scale(";
		strTfr += QString::number(m_Info.tfr.scale_x);
		strTfr += ",";
		strTfr += QString::number(m_Info.tfr.scale_y);
		strTfr += " ";
		attr->value(strTfr.toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "ts" );
		attr->value( m_Info.ts.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "type" );
		attr->value(QString::number(m_Info.type).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype" );
		attr->value(QString::number(m_Info.voltype).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "wm" );
		attr->value(QString::number(m_Info.wm).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "x" );
		attr->value(QString::number(m_Info.x).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "y" );
		attr->value(QString::number(m_Info.y).toLocal8Bit().data());
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("af");
		if(attr)
		{
			 m_AttrInfo["af"] = QString(attr->value());
			 m_Info.af = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("app");
		if(attr)
		{
			 m_AttrInfo["app"] = QString(attr->value());
			 m_Info.app = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("dotlength");
		if(attr)
		{
			 m_AttrInfo["dotlength"] = QString(attr->value());
			 m_Info.dotlength = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fc");
		if(attr)
		{
			 m_AttrInfo["fc"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.fc.setRed(lstColor[0].toInt());
				 m_Info.fc.setGreen(lstColor[1].toInt());
				 m_Info.fc.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("ff");
		if(attr)
		{
			 m_AttrInfo["ff"] = QString(attr->value());
			 m_Info.ff = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fm");
		if(attr)
		{
			 m_AttrInfo["fm"] = QString(attr->value());
			 m_Info.fm = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fs");
		if(attr)
		{
			 m_AttrInfo["fs"] = QString(attr->value());
			 m_Info.fs = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("id");
		if(attr)
		{
			 m_AttrInfo["id"] = QString(attr->value());
			 m_Info.id = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("keyid");
		if(attr)
		{
			 m_AttrInfo["keyid"] = QString(attr->value());
			 m_Info.keyid = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("lc");
		if(attr)
		{
			 m_AttrInfo["lc"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.lc.setRed(lstColor[0].toInt());
				 m_Info.lc.setGreen(lstColor[1].toInt());
				 m_Info.lc.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("ls");
		if(attr)
		{
			 m_AttrInfo["ls"] = QString(attr->value());
			 m_Info.ls = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("lw");
		if(attr)
		{
			 m_AttrInfo["lw"] = QString(attr->value());
			 m_Info.lw = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_AssFlag");
		if(attr)
		{
			 m_AttrInfo["p_AssFlag"] = QString(attr->value());
			 m_Info.p_AssFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_AutoChangeAppFlag");
		if(attr)
		{
			 m_AttrInfo["p_AutoChangeAppFlag"] = QString(attr->value());
			 m_Info.p_AutoChangeAppFlag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("p_DataFrom");
		if(attr)
		{
			 m_AttrInfo["p_DataFrom"] = QString(attr->value());
			 m_Info.p_DataFrom = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_DataLowerLimit");
		if(attr)
		{
			 m_AttrInfo["p_DataLowerLimit"] = QString(attr->value());
			 m_Info.p_DataLowerLimit = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_DataSetFlag");
		if(attr)
		{
			 m_AttrInfo["p_DataSetFlag"] = QString(attr->value());
			 m_Info.p_DataSetFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_DataUpperLimit");
		if(attr)
		{
			 m_AttrInfo["p_DataUpperLimit"] = QString(attr->value());
			 m_Info.p_DataUpperLimit = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_FontDeltaX");
		if(attr)
		{
			 m_AttrInfo["p_FontDeltaX"] = QString(attr->value());
			 m_Info.p_FontDeltaX = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_FontDeltaY");
		if(attr)
		{
			 m_AttrInfo["p_FontDeltaY"] = QString(attr->value());
			 m_Info.p_FontDeltaY = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_FontHeight");
		if(attr)
		{
			 m_AttrInfo["p_FontHeight"] = QString(attr->value());
			 m_Info.p_FontHeight = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_FontInterval");
		if(attr)
		{
			 m_AttrInfo["p_FontInterval"] = QString(attr->value());
			 m_Info.p_FontInterval = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_FontWidth");
		if(attr)
		{
			 m_AttrInfo["p_FontWidth"] = QString(attr->value());
			 m_Info.p_FontWidth = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_IsAbs");
		if(attr)
		{
			 m_AttrInfo["p_IsAbs"] = QString(attr->value());
			 m_Info.p_IsAbs = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_LevelEnd");
		if(attr)
		{
			 m_AttrInfo["p_LevelEnd"] = QString(attr->value());
			 m_Info.p_LevelEnd = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_LevelStart");
		if(attr)
		{
			 m_AttrInfo["p_LevelStart"] = QString(attr->value());
			 m_Info.p_LevelStart = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_MatrixFontFlag");
		if(attr)
		{
			 m_AttrInfo["p_MatrixFontFlag"] = QString(attr->value());
			 m_Info.p_MatrixFontFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_NameString");
		if(attr)
		{
			 m_AttrInfo["p_NameString"] = QString(attr->value());
			 m_Info.p_NameString = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_Plane");
		if(attr)
		{
			 m_AttrInfo["p_Plane"] = QString(attr->value());
			 m_Info.p_Plane = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType");
		if(attr)
		{
			 m_AttrInfo["p_ReportType"] = QString(attr->value());
			 m_Info.p_ReportType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_RoundBox");
		if(attr)
		{
			 m_AttrInfo["p_RoundBox"] = QString(attr->value());
			 QStringList lstRect = QString(attr->value()).split(',');
			 m_Info.p_RoundBox.setLeft(lstRect[0].toInt());
			 m_Info.p_RoundBox.setRight(lstRect[1].toInt());
			 m_Info.p_RoundBox.setTop(lstRect[2].toInt());
			 m_Info.p_RoundBox.setBottom(lstRect[3].toInt());
		}

		attr = node->first_attribute("p_RowInterval");
		if(attr)
		{
			 m_AttrInfo["p_RowInterval"] = QString(attr->value());
			 m_Info.p_RowInterval = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowSignFlag");
		if(attr)
		{
			 m_AttrInfo["p_ShowSignFlag"] = QString(attr->value());
			 m_Info.p_ShowSignFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ZoomMaxLevel");
		if(attr)
		{
			 m_AttrInfo["p_ZoomMaxLevel"] = QString(attr->value());
			 m_Info.p_ZoomMaxLevel = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("state");
		if(attr)
		{
			 m_AttrInfo["state"] = QString(attr->value());
			 m_Info.state = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("tfr");
		if(attr)
		{
			 m_AttrInfo["tfr"] = QString(attr->value());
			QString strValue = QString(attr->value());
			if (strValue.split(' ').count() > 0)
			{
				QString strRotate = strValue.split(' ')[0];
				strRotate.remove("rotate(");
				strRotate.remove(")");
				 m_Info.tfr.rotate = strRotate.toDouble();
			}
			if (strValue.split(' ').count() > 1)
			{
				QString strScale = strValue.split(' ')[1];
				strScale.remove("scale(");
				strScale.remove(")");
				m_Info.tfr.scale_x = strScale.split(',')[0].toDouble();
				m_Info.tfr.scale_y = strScale.split(',')[1].toDouble();
			}
		}

		attr = node->first_attribute("ts");
		if(attr)
		{
			 m_AttrInfo["ts"] = QString(attr->value());
			 m_Info.ts = QObject::tr(attr->value());
		}

		attr = node->first_attribute("type");
		if(attr)
		{
			 m_AttrInfo["type"] = QString(attr->value());
			 m_Info.type = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("voltype");
		if(attr)
		{
			 m_AttrInfo["voltype"] = QString(attr->value());
			 m_Info.voltype = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("wm");
		if(attr)
		{
			 m_AttrInfo["wm"] = QString(attr->value());
			 m_Info.wm = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("x");
		if(attr)
		{
			 m_AttrInfo["x"] = QString(attr->value());
			 m_Info.x = QString(attr->value()).toFloat();
		}

		attr = node->first_attribute("y");
		if(attr)
		{
			 m_AttrInfo["y"] = QString(attr->value());
			 m_Info.y = QString(attr->value()).toFloat();
		}

	}
	DText_Struct getInfo()
	{
		return m_Info;
	}
protected:

	DText_Struct m_Info ;
};

#endif
