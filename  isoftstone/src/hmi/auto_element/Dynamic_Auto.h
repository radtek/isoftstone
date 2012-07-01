#ifndef CLASS_DYNAMIC_AUTO_H
#define CLASS_DYNAMIC_AUTO_H

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


struct Dynamic_Struct
{
	QString  abstime;
	quint64  app;
	QString  curve_type;
	QString  distant;
	QString  distantunit;
	QString  endtime;
	quint64  keyid;
	QString  mode;
	QString  period;
	QString  starttime;
	uint  type;

	Dynamic_Struct& operator=(const Dynamic_Struct& cp)
	{
		this->abstime = 		cp.abstime;
		this->app = 		cp.app;
		this->curve_type = 		cp.curve_type;
		this->distant = 		cp.distant;
		this->distantunit = 		cp.distantunit;
		this->endtime = 		cp.endtime;
		this->keyid = 		cp.keyid;
		this->mode = 		cp.mode;
		this->period = 		cp.period;
		this->starttime = 		cp.starttime;
		this->type = 		cp.type;
		return *this;
	}
};

class CDynamic_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.abstime;
		out << m_Info.app;
		out << m_Info.curve_type;
		out << m_Info.distant;
		out << m_Info.distantunit;
		out << m_Info.endtime;
		out << m_Info.keyid;
		out << m_Info.mode;
		out << m_Info.period;
		out << m_Info.starttime;
		out << m_Info.type;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.abstime;
		out >> m_Info.app;
		out >> m_Info.curve_type;
		out >> m_Info.distant;
		out >> m_Info.distantunit;
		out >> m_Info.endtime;
		out >> m_Info.keyid;
		out >> m_Info.mode;
		out >> m_Info.period;
		out >> m_Info.starttime;
		out >> m_Info.type;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "abstime" );
		attr->value( m_Info.abstime.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app" );
		attr->value(QString::number(m_Info.app).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "curve_type" );
		attr->value( m_Info.curve_type.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "distant" );
		attr->value( m_Info.distant.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "distantunit" );
		attr->value( m_Info.distantunit.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "endtime" );
		attr->value( m_Info.endtime.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid" );
		attr->value(QString::number(m_Info.keyid).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "mode" );
		attr->value( m_Info.mode.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "period" );
		attr->value( m_Info.period.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "starttime" );
		attr->value( m_Info.starttime.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "type" );
		attr->value(QString::number(m_Info.type).toLocal8Bit().data());
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("abstime");
		if(attr)
		{
			 m_AttrInfo["abstime"] = QString(attr->value());
			 m_Info.abstime = QObject::tr(attr->value());
		}

		attr = node->first_attribute("app");
		if(attr)
		{
			 m_AttrInfo["app"] = QString(attr->value());
			 m_Info.app = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("curve_type");
		if(attr)
		{
			 m_AttrInfo["curve_type"] = QString(attr->value());
			 m_Info.curve_type = QObject::tr(attr->value());
		}

		attr = node->first_attribute("distant");
		if(attr)
		{
			 m_AttrInfo["distant"] = QString(attr->value());
			 m_Info.distant = QObject::tr(attr->value());
		}

		attr = node->first_attribute("distantunit");
		if(attr)
		{
			 m_AttrInfo["distantunit"] = QString(attr->value());
			 m_Info.distantunit = QObject::tr(attr->value());
		}

		attr = node->first_attribute("endtime");
		if(attr)
		{
			 m_AttrInfo["endtime"] = QString(attr->value());
			 m_Info.endtime = QObject::tr(attr->value());
		}

		attr = node->first_attribute("keyid");
		if(attr)
		{
			 m_AttrInfo["keyid"] = QString(attr->value());
			 m_Info.keyid = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("mode");
		if(attr)
		{
			 m_AttrInfo["mode"] = QString(attr->value());
			 m_Info.mode = QObject::tr(attr->value());
		}

		attr = node->first_attribute("period");
		if(attr)
		{
			 m_AttrInfo["period"] = QString(attr->value());
			 m_Info.period = QObject::tr(attr->value());
		}

		attr = node->first_attribute("starttime");
		if(attr)
		{
			 m_AttrInfo["starttime"] = QString(attr->value());
			 m_Info.starttime = QObject::tr(attr->value());
		}

		attr = node->first_attribute("type");
		if(attr)
		{
			 m_AttrInfo["type"] = QString(attr->value());
			 m_Info.type = QString(attr->value()).toUInt();
		}

	}
	Dynamic_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Dynamic_Struct m_Info ;
};

#endif
