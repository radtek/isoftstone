#ifndef CLASS_Y_AXIS_AUTO_H
#define CLASS_Y_AXIS_AUTO_H

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


struct Y_axis_Struct
{
	QString    autowithlimit;
	QString    decimal;
	QColor    fc;
	uint  ff;
	uint  fs;
	QString    fw;
	QString    isinteger;
	QString    main_auto;
	QString    mainspace;
	QString    max;
	QString    maxrate;
	QString    min;
	QString    minrate;
	QString    multi_axis_def;
	QString    show;
	QString    subspace;

	Y_axis_Struct& operator=(const Y_axis_Struct& cp)
	{
		this->autowithlimit = 		cp.autowithlimit;
		this->decimal = 		cp.decimal;
		this->fc = 		cp.fc;
		this->ff = 		cp.ff;
		this->fs = 		cp.fs;
		this->fw = 		cp.fw;
		this->isinteger = 		cp.isinteger;
		this->main_auto = 		cp.main_auto;
		this->mainspace = 		cp.mainspace;
		this->max = 		cp.max;
		this->maxrate = 		cp.maxrate;
		this->min = 		cp.min;
		this->minrate = 		cp.minrate;
		this->multi_axis_def = 		cp.multi_axis_def;
		this->show = 		cp.show;
		this->subspace = 		cp.subspace;
		return *this;
	}
};

class CY_axis_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.autowithlimit;
		out << m_Info.decimal;
		out << m_Info.fc;
		out << m_Info.ff;
		out << m_Info.fs;
		out << m_Info.fw;
		out << m_Info.isinteger;
		out << m_Info.main_auto;
		out << m_Info.mainspace;
		out << m_Info.max;
		out << m_Info.maxrate;
		out << m_Info.min;
		out << m_Info.minrate;
		out << m_Info.multi_axis_def;
		out << m_Info.show;
		out << m_Info.subspace;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.autowithlimit;
		out >> m_Info.decimal;
		out >> m_Info.fc;
		out >> m_Info.ff;
		out >> m_Info.fs;
		out >> m_Info.fw;
		out >> m_Info.isinteger;
		out >> m_Info.main_auto;
		out >> m_Info.mainspace;
		out >> m_Info.max;
		out >> m_Info.maxrate;
		out >> m_Info.min;
		out >> m_Info.minrate;
		out >> m_Info.multi_axis_def;
		out >> m_Info.show;
		out >> m_Info.subspace;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "autowithlimit" );
		attr->value( m_Info.autowithlimit.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "decimal" );
		attr->value( m_Info.decimal.toLocal8Bit().data() );
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
		attr->name( "fs" );
		attr->value(QString::number(m_Info.fs).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fw" );
		attr->value( m_Info.fw.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "isinteger" );
		attr->value( m_Info.isinteger.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_auto" );
		attr->value( m_Info.main_auto.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "mainspace" );
		attr->value( m_Info.mainspace.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max" );
		attr->value( m_Info.max.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "maxrate" );
		attr->value( m_Info.maxrate.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min" );
		attr->value( m_Info.min.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "minrate" );
		attr->value( m_Info.minrate.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "multi_axis_def" );
		attr->value( m_Info.multi_axis_def.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "show" );
		attr->value( m_Info.show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "subspace" );
		attr->value( m_Info.subspace.toLocal8Bit().data() );
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("autowithlimit");
		if(attr)
		{
			 m_AttrInfo["autowithlimit"] = QString(attr->value());
			 m_Info.autowithlimit = QObject::tr(attr->value());
		}

		attr = node->first_attribute("decimal");
		if(attr)
		{
			 m_AttrInfo["decimal"] = QString(attr->value());
			 m_Info.decimal = QObject::tr(attr->value());
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

		attr = node->first_attribute("isinteger");
		if(attr)
		{
			 m_AttrInfo["isinteger"] = QString(attr->value());
			 m_Info.isinteger = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_auto");
		if(attr)
		{
			 m_AttrInfo["main_auto"] = QString(attr->value());
			 m_Info.main_auto = QObject::tr(attr->value());
		}

		attr = node->first_attribute("mainspace");
		if(attr)
		{
			 m_AttrInfo["mainspace"] = QString(attr->value());
			 m_Info.mainspace = QObject::tr(attr->value());
		}

		attr = node->first_attribute("max");
		if(attr)
		{
			 m_AttrInfo["max"] = QString(attr->value());
			 m_Info.max = QObject::tr(attr->value());
		}

		attr = node->first_attribute("maxrate");
		if(attr)
		{
			 m_AttrInfo["maxrate"] = QString(attr->value());
			 m_Info.maxrate = QObject::tr(attr->value());
		}

		attr = node->first_attribute("min");
		if(attr)
		{
			 m_AttrInfo["min"] = QString(attr->value());
			 m_Info.min = QObject::tr(attr->value());
		}

		attr = node->first_attribute("minrate");
		if(attr)
		{
			 m_AttrInfo["minrate"] = QString(attr->value());
			 m_Info.minrate = QObject::tr(attr->value());
		}

		attr = node->first_attribute("multi_axis_def");
		if(attr)
		{
			 m_AttrInfo["multi_axis_def"] = QString(attr->value());
			 m_Info.multi_axis_def = QObject::tr(attr->value());
		}

		attr = node->first_attribute("show");
		if(attr)
		{
			 m_AttrInfo["show"] = QString(attr->value());
			 m_Info.show = QObject::tr(attr->value());
		}

		attr = node->first_attribute("subspace");
		if(attr)
		{
			 m_AttrInfo["subspace"] = QString(attr->value());
			 m_Info.subspace = QObject::tr(attr->value());
		}

	}
	Y_axis_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Y_axis_Struct m_Info ;
};

#endif
