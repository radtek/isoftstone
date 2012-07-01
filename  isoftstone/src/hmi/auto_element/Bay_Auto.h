#ifndef CLASS_BAY_AUTO_H
#define CLASS_BAY_AUTO_H

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


struct Bay_Struct
{
	QString  conf;
	QString  devicegroup;
	QString  devref;
	quint64  keyid;
	QString  name;
	uint  type;
	qreal  x;
	qreal  y;

	Bay_Struct& operator=(const Bay_Struct& cp)
	{
		this->conf = 		cp.conf;
		this->devicegroup = 		cp.devicegroup;
		this->devref = 		cp.devref;
		this->keyid = 		cp.keyid;
		this->name = 		cp.name;
		this->type = 		cp.type;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CBay_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.conf;
		out << m_Info.devicegroup;
		out << m_Info.devref;
		out << m_Info.keyid;
		out << m_Info.name;
		out << m_Info.type;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.conf;
		out >> m_Info.devicegroup;
		out >> m_Info.devref;
		out >> m_Info.keyid;
		out >> m_Info.name;
		out >> m_Info.type;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "conf" );
		attr->value( m_Info.conf.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "devicegroup" );
		attr->value( m_Info.devicegroup.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "devref" );
		attr->value( m_Info.devref.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid" );
		attr->value(QString::number(m_Info.keyid).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "name" );
		attr->value( m_Info.name.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "type" );
		attr->value(QString::number(m_Info.type).toLocal8Bit().data());
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

		attr = node->first_attribute("conf");
		if(attr)
		{
			 m_AttrInfo["conf"] = QString(attr->value());
			 m_Info.conf = QObject::tr(attr->value());
		}

		attr = node->first_attribute("devicegroup");
		if(attr)
		{
			 m_AttrInfo["devicegroup"] = QString(attr->value());
			 m_Info.devicegroup = QObject::tr(attr->value());
		}

		attr = node->first_attribute("devref");
		if(attr)
		{
			 m_AttrInfo["devref"] = QString(attr->value());
			 m_Info.devref = QObject::tr(attr->value());
		}

		attr = node->first_attribute("keyid");
		if(attr)
		{
			 m_AttrInfo["keyid"] = QString(attr->value());
			 m_Info.keyid = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("name");
		if(attr)
		{
			 m_AttrInfo["name"] = QString(attr->value());
			 m_Info.name = QObject::tr(attr->value());
		}

		attr = node->first_attribute("type");
		if(attr)
		{
			 m_AttrInfo["type"] = QString(attr->value());
			 m_Info.type = QString(attr->value()).toUInt();
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
	Bay_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Bay_Struct m_Info ;
};

#endif
