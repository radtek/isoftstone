#ifndef CLASS_DIAMOND_AUTO_H
#define CLASS_DIAMOND_AUTO_H

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


struct Diamond_Struct
{
	uint  af;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;

	Diamond_Struct& operator=(const Diamond_Struct& cp)
	{
		this->af = 		cp.af;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->h = 		cp.h;
		this->id = 		cp.id;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShadowType = 		cp.p_ShadowType;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->switchapp = 		cp.switchapp;
		this->tfr = 		cp.tfr;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CDiamond_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.h;
		out << m_Info.id;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.p_AssFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShadowType;
		out << m_Info.p_ShowModeMask;
		out << m_Info.switchapp;
		out << m_Info.tfr;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.h;
		out >> m_Info.id;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShadowType;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.switchapp;
		out >> m_Info.tfr;
		out >> m_Info.w;
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
		attr->name( "fc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.fc.red(),(int)m_Info.fc.green(),(int)m_Info.fc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fm" );
		attr->value(QString::number(m_Info.fm).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
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
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
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
		attr->name( "p_NameString" );
		attr->value(QString::number(m_Info.p_NameString).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Plane" );
		attr->value(QString::number(m_Info.p_Plane).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShadowType" );
		attr->value(QString::number(m_Info.p_ShadowType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "switchapp" );
		attr->value(QString::number(m_Info.switchapp).toLocal8Bit().data());
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
		attr->name( "w" );
		attr->value(QString::number(m_Info.w).toLocal8Bit().data());
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

		attr = node->first_attribute("fm");
		if(attr)
		{
			 m_AttrInfo["fm"] = QString(attr->value());
			 m_Info.fm = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("h");
		if(attr)
		{
			 m_AttrInfo["h"] = QString(attr->value());
			 m_Info.h = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("id");
		if(attr)
		{
			 m_AttrInfo["id"] = QString(attr->value());
			 m_Info.id = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_ShadowType");
		if(attr)
		{
			 m_AttrInfo["p_ShadowType"] = QString(attr->value());
			 m_Info.p_ShadowType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("switchapp");
		if(attr)
		{
			 m_AttrInfo["switchapp"] = QString(attr->value());
			 m_Info.switchapp = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("w");
		if(attr)
		{
			 m_AttrInfo["w"] = QString(attr->value());
			 m_Info.w = QString(attr->value()).toInt();
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
	Diamond_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Diamond_Struct m_Info ;
};

#endif
