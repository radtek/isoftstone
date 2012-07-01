#ifndef CLASS_X_AXIS_AUTO_H
#define CLASS_X_AXIS_AUTO_H

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


struct X_axis_Struct
{
	QString    abs_time;
	QString    end;
	QColor    fc;
	uint  ff;
	QString    format;
	uint  fs;
	QString    fw;
	QString    int_time;
	QString    int_time_value;
	QString    mainspace;
	QString    run;
	QString    scale;
	QString    show;
	QString    span;
	QString    start;
	QString    subspace;
	QString    unit;

	X_axis_Struct& operator=(const X_axis_Struct& cp)
	{
		this->abs_time = 		cp.abs_time;
		this->end = 		cp.end;
		this->fc = 		cp.fc;
		this->ff = 		cp.ff;
		this->format = 		cp.format;
		this->fs = 		cp.fs;
		this->fw = 		cp.fw;
		this->int_time = 		cp.int_time;
		this->int_time_value = 		cp.int_time_value;
		this->mainspace = 		cp.mainspace;
		this->run = 		cp.run;
		this->scale = 		cp.scale;
		this->show = 		cp.show;
		this->span = 		cp.span;
		this->start = 		cp.start;
		this->subspace = 		cp.subspace;
		this->unit = 		cp.unit;
		return *this;
	}
};

class CX_axis_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.abs_time;
		out << m_Info.end;
		out << m_Info.fc;
		out << m_Info.ff;
		out << m_Info.format;
		out << m_Info.fs;
		out << m_Info.fw;
		out << m_Info.int_time;
		out << m_Info.int_time_value;
		out << m_Info.mainspace;
		out << m_Info.run;
		out << m_Info.scale;
		out << m_Info.show;
		out << m_Info.span;
		out << m_Info.start;
		out << m_Info.subspace;
		out << m_Info.unit;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.abs_time;
		out >> m_Info.end;
		out >> m_Info.fc;
		out >> m_Info.ff;
		out >> m_Info.format;
		out >> m_Info.fs;
		out >> m_Info.fw;
		out >> m_Info.int_time;
		out >> m_Info.int_time_value;
		out >> m_Info.mainspace;
		out >> m_Info.run;
		out >> m_Info.scale;
		out >> m_Info.show;
		out >> m_Info.span;
		out >> m_Info.start;
		out >> m_Info.subspace;
		out >> m_Info.unit;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "abs_time" );
		attr->value( m_Info.abs_time.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "end" );
		attr->value( m_Info.end.toLocal8Bit().data() );
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
		attr->name( "format" );
		attr->value( m_Info.format.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fs" );
		attr->value(QString::number(m_Info.fs).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fw" );
		attr->value( m_Info.fw.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "int_time" );
		attr->value( m_Info.int_time.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "int_time_value" );
		attr->value( m_Info.int_time_value.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "mainspace" );
		attr->value( m_Info.mainspace.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "run" );
		attr->value( m_Info.run.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale" );
		attr->value( m_Info.scale.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "show" );
		attr->value( m_Info.show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "span" );
		attr->value( m_Info.span.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "start" );
		attr->value( m_Info.start.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "subspace" );
		attr->value( m_Info.subspace.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit" );
		attr->value( m_Info.unit.toLocal8Bit().data() );
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("abs_time");
		if(attr)
		{
			 m_AttrInfo["abs_time"] = QString(attr->value());
			 m_Info.abs_time = QObject::tr(attr->value());
		}

		attr = node->first_attribute("end");
		if(attr)
		{
			 m_AttrInfo["end"] = QString(attr->value());
			 m_Info.end = QObject::tr(attr->value());
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

		attr = node->first_attribute("format");
		if(attr)
		{
			 m_AttrInfo["format"] = QString(attr->value());
			 m_Info.format = QObject::tr(attr->value());
		}

		attr = node->first_attribute("fs");
		if(attr)
		{
			 m_AttrInfo["fs"] = QString(attr->value());
			 m_Info.fs = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fw");
		if(attr)
		{
			 m_AttrInfo["fw"] = QString(attr->value());
			 m_Info.fw = QObject::tr(attr->value());
		}

		attr = node->first_attribute("int_time");
		if(attr)
		{
			 m_AttrInfo["int_time"] = QString(attr->value());
			 m_Info.int_time = QObject::tr(attr->value());
		}

		attr = node->first_attribute("int_time_value");
		if(attr)
		{
			 m_AttrInfo["int_time_value"] = QString(attr->value());
			 m_Info.int_time_value = QObject::tr(attr->value());
		}

		attr = node->first_attribute("mainspace");
		if(attr)
		{
			 m_AttrInfo["mainspace"] = QString(attr->value());
			 m_Info.mainspace = QObject::tr(attr->value());
		}

		attr = node->first_attribute("run");
		if(attr)
		{
			 m_AttrInfo["run"] = QString(attr->value());
			 m_Info.run = QObject::tr(attr->value());
		}

		attr = node->first_attribute("scale");
		if(attr)
		{
			 m_AttrInfo["scale"] = QString(attr->value());
			 m_Info.scale = QObject::tr(attr->value());
		}

		attr = node->first_attribute("show");
		if(attr)
		{
			 m_AttrInfo["show"] = QString(attr->value());
			 m_Info.show = QObject::tr(attr->value());
		}

		attr = node->first_attribute("span");
		if(attr)
		{
			 m_AttrInfo["span"] = QString(attr->value());
			 m_Info.span = QObject::tr(attr->value());
		}

		attr = node->first_attribute("start");
		if(attr)
		{
			 m_AttrInfo["start"] = QString(attr->value());
			 m_Info.start = QObject::tr(attr->value());
		}

		attr = node->first_attribute("subspace");
		if(attr)
		{
			 m_AttrInfo["subspace"] = QString(attr->value());
			 m_Info.subspace = QObject::tr(attr->value());
		}

		attr = node->first_attribute("unit");
		if(attr)
		{
			 m_AttrInfo["unit"] = QString(attr->value());
			 m_Info.unit = QObject::tr(attr->value());
		}

	}
	X_axis_Struct getInfo()
	{
		return m_Info;
	}
protected:

	X_axis_Struct m_Info ;
};

#endif
