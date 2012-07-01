#ifndef CLASS_ACLINEEND_AUTO_H
#define CLASS_ACLINEEND_AUTO_H

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


struct ACLineEnd_Struct
{
	uint  af;
	quint64  app;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;

	ACLineEnd_Struct& operator=(const ACLineEnd_Struct& cp)
	{
		this->af = 		cp.af;
		this->app = 		cp.app;
		this->d = 		cp.d;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->id = 		cp.id;
		this->keyid = 		cp.keyid;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_EndArrowSize = 		cp.p_EndArrowSize;
		this->p_EndArrowType = 		cp.p_EndArrowType;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_ReportType = 		cp.p_ReportType;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->p_StartArrowSize = 		cp.p_StartArrowSize;
		this->p_StartArrowType = 		cp.p_StartArrowType;
		this->state = 		cp.state;
		this->switchapp = 		cp.switchapp;
		this->tfr = 		cp.tfr;
		this->voltype = 		cp.voltype;
		return *this;
	}
};

class CACLineEnd_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.app;
		out << m_Info.d;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.id;
		out << m_Info.keyid;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.p_AssFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_EndArrowSize;
		out << m_Info.p_EndArrowType;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_ReportType;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShowModeMask;
		out << m_Info.p_StartArrowSize;
		out << m_Info.p_StartArrowType;
		out << m_Info.state;
		out << m_Info.switchapp;
		out << m_Info.tfr;
		out << m_Info.voltype;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.app;
		out >> m_Info.d;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.id;
		out >> m_Info.keyid;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_EndArrowSize;
		out >> m_Info.p_EndArrowType;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_ReportType;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.p_StartArrowSize;
		out >> m_Info.p_StartArrowType;
		out >> m_Info.state;
		out >> m_Info.switchapp;
		out >> m_Info.tfr;
		out >> m_Info.voltype;
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
		attr->name( "d" );
		QString strPolygon = "";
		for (int i = 0; i < m_Info.d.size(); ++i)
		{
			QPointF pos = m_Info.d[i];
			strPolygon += QString::number(pos.x());
			strPolygon += ",";
			strPolygon += QString::number(pos.y());
			strPolygon += " ";
		}
		attr->value(strPolygon.toLocal8Bit().data());
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
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_EndArrowSize" );
		attr->value(QString::number(m_Info.p_EndArrowSize).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_EndArrowType" );
		attr->value(QString::number(m_Info.p_EndArrowType).toLocal8Bit().data());
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
		attr->name( "p_ReportType" );
		attr->value(QString::number(m_Info.p_ReportType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_StartArrowSize" );
		attr->value(QString::number(m_Info.p_StartArrowSize).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_StartArrowType" );
		attr->value(QString::number(m_Info.p_StartArrowType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state" );
		attr->value(QString::number(m_Info.state).toLocal8Bit().data());
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
		attr->name( "voltype" );
		attr->value(QString::number(m_Info.voltype).toLocal8Bit().data());
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

		attr = node->first_attribute("d");
		if(attr)
		{
			 m_AttrInfo["d"] = QString(attr->value());
			 QStringList lstPoints = QString(attr->value()).split(' ');
			 foreach(QString strPoint,lstPoints)
			 {
				if(strPoint.split(',').count() > 1)
				{
					 QPointF pos;
					 pos.setX(strPoint.split(',')[0].toDouble());
					 pos.setY(strPoint.split(',')[1].toDouble());
					 m_Info.d.append(pos);
				 }
			 }
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

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_EndArrowSize");
		if(attr)
		{
			 m_AttrInfo["p_EndArrowSize"] = QString(attr->value());
			 m_Info.p_EndArrowSize = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_EndArrowType");
		if(attr)
		{
			 m_AttrInfo["p_EndArrowType"] = QString(attr->value());
			 m_Info.p_EndArrowType = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_StartArrowSize");
		if(attr)
		{
			 m_AttrInfo["p_StartArrowSize"] = QString(attr->value());
			 m_Info.p_StartArrowSize = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_StartArrowType");
		if(attr)
		{
			 m_AttrInfo["p_StartArrowType"] = QString(attr->value());
			 m_Info.p_StartArrowType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("state");
		if(attr)
		{
			 m_AttrInfo["state"] = QString(attr->value());
			 m_Info.state = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("voltype");
		if(attr)
		{
			 m_AttrInfo["voltype"] = QString(attr->value());
			 m_Info.voltype = QString(attr->value()).toInt();
		}

	}
	ACLineEnd_Struct getInfo()
	{
		return m_Info;
	}
protected:

	ACLineEnd_Struct m_Info ;
};

#endif
