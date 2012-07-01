#ifndef CLASS_ENTITY_AUTO_H
#define CLASS_ENTITY_AUTO_H

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


struct Entity_Struct
{
	QString  ds;
	QColor  lc;
	QString  legend;
	uint  ls;
	uint  lw;
	QString  title;
	QString  y_type;

	Entity_Struct& operator=(const Entity_Struct& cp)
	{
		this->ds = 		cp.ds;
		this->lc = 		cp.lc;
		this->legend = 		cp.legend;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->title = 		cp.title;
		this->y_type = 		cp.y_type;
		return *this;
	}
};

class CEntity_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.ds;
		out << m_Info.lc;
		out << m_Info.legend;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.title;
		out << m_Info.y_type;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.ds;
		out >> m_Info.lc;
		out >> m_Info.legend;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.title;
		out >> m_Info.y_type;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "ds" );
		attr->value( m_Info.ds.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "lc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.lc.red(),(int)m_Info.lc.green(),(int)m_Info.lc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "legend" );
		attr->value( m_Info.legend.toLocal8Bit().data() );
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
		attr->name( "title" );
		attr->value( m_Info.title.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "y_type" );
		attr->value( m_Info.y_type.toLocal8Bit().data() );
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("ds");
		if(attr)
		{
			 m_AttrInfo["ds"] = QString(attr->value());
			 m_Info.ds = QObject::tr(attr->value());
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

		attr = node->first_attribute("legend");
		if(attr)
		{
			 m_AttrInfo["legend"] = QString(attr->value());
			 m_Info.legend = QObject::tr(attr->value());
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

		attr = node->first_attribute("title");
		if(attr)
		{
			 m_AttrInfo["title"] = QString(attr->value());
			 m_Info.title = QObject::tr(attr->value());
		}

		attr = node->first_attribute("y_type");
		if(attr)
		{
			 m_AttrInfo["y_type"] = QString(attr->value());
			 m_Info.y_type = QObject::tr(attr->value());
		}

	}
	Entity_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Entity_Struct m_Info ;
};

#endif
