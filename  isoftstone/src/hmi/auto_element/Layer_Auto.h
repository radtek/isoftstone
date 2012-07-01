#ifndef CLASS_LAYER_AUTO_H
#define CLASS_LAYER_AUTO_H

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


struct Layer_Struct
{
	uint  h;
	uint  id;
	int  w;
	qreal  x;
	qreal  y;

	Layer_Struct& operator=(const Layer_Struct& cp)
	{
		this->h = 		cp.h;
		this->id = 		cp.id;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CLayer_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.h;
		out << m_Info.id;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.h;
		out >> m_Info.id;
		out >> m_Info.w;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
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
	Layer_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Layer_Struct m_Info ;
};

#endif
