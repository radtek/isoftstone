#ifndef CLASS_CAPACITOR_AUTO_H
#define CLASS_CAPACITOR_AUTO_H

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


struct Capacitor_Struct
{
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	QString  index;
	quint64  keyid;
	QString  keyname;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  p_AutoChangeAppFlag;
	QString  rg;
	QString  transform;
	int  voltype;
	qreal  x;
	qreal  y;

	Capacitor_Struct& operator=(const Capacitor_Struct& cp)
	{
		this->af = 		cp.af;
		this->app = 		cp.app;
		this->devref = 		cp.devref;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->id = 		cp.id;
		this->index = 		cp.index;
		this->keyid = 		cp.keyid;
		this->keyname = 		cp.keyname;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->p_AutoChangeAppFlag = 		cp.p_AutoChangeAppFlag;
		this->rg = 		cp.rg;
		this->transform = 		cp.transform;
		this->voltype = 		cp.voltype;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CCapacitor_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.app;
		out << m_Info.devref;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.id;
		out << m_Info.index;
		out << m_Info.keyid;
		out << m_Info.keyname;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.p_AutoChangeAppFlag;
		out << m_Info.rg;
		out << m_Info.transform;
		out << m_Info.voltype;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.app;
		out >> m_Info.devref;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.id;
		out >> m_Info.index;
		out >> m_Info.keyid;
		out >> m_Info.keyname;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.p_AutoChangeAppFlag;
		out >> m_Info.rg;
		out >> m_Info.transform;
		out >> m_Info.voltype;
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
		attr->name( "devref" );
		attr->value( m_Info.devref.toLocal8Bit().data() );
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
		attr->name( "index" );
		attr->value( m_Info.index.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid" );
		attr->value(QString::number(m_Info.keyid).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyname" );
		attr->value( m_Info.keyname.toLocal8Bit().data() );
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
		attr->name( "p_AutoChangeAppFlag" );
		attr->value( m_Info.p_AutoChangeAppFlag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "rg" );
		attr->value( m_Info.rg.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "transform" );
		attr->value( m_Info.transform.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype" );
		attr->value(QString::number(m_Info.voltype).toLocal8Bit().data());
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

		attr = node->first_attribute("devref");
		if(attr)
		{
			 m_AttrInfo["devref"] = QString(attr->value());
			 m_Info.devref = QObject::tr(attr->value());
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

		attr = node->first_attribute("index");
		if(attr)
		{
			 m_AttrInfo["index"] = QString(attr->value());
			 m_Info.index = QObject::tr(attr->value());
		}

		attr = node->first_attribute("keyid");
		if(attr)
		{
			 m_AttrInfo["keyid"] = QString(attr->value());
			 m_Info.keyid = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyname");
		if(attr)
		{
			 m_AttrInfo["keyname"] = QString(attr->value());
			 m_Info.keyname = QObject::tr(attr->value());
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

		attr = node->first_attribute("p_AutoChangeAppFlag");
		if(attr)
		{
			 m_AttrInfo["p_AutoChangeAppFlag"] = QString(attr->value());
			 m_Info.p_AutoChangeAppFlag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("rg");
		if(attr)
		{
			 m_AttrInfo["rg"] = QString(attr->value());
			 m_Info.rg = QObject::tr(attr->value());
		}

		attr = node->first_attribute("transform");
		if(attr)
		{
			 m_AttrInfo["transform"] = QString(attr->value());
			 m_Info.transform = QObject::tr(attr->value());
		}

		attr = node->first_attribute("voltype");
		if(attr)
		{
			 m_AttrInfo["voltype"] = QString(attr->value());
			 m_Info.voltype = QString(attr->value()).toInt();
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
	Capacitor_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Capacitor_Struct m_Info ;
};

#endif
