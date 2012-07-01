#ifndef CLASS_LEGEND_AUTO_H
#define CLASS_LEGEND_AUTO_H

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


struct Legend_Struct
{
	QColor  fc;
	uint  ff;
	uint  fs;
	QString  fw;
	qreal  x;
	qreal  y;

	Legend_Struct& operator=(const Legend_Struct& cp)
	{
		this->fc = 		cp.fc;
		this->ff = 		cp.ff;
		this->fs = 		cp.fs;
		this->fw = 		cp.fw;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CLegend_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.fc;
		out << m_Info.ff;
		out << m_Info.fs;
		out << m_Info.fw;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.fc;
		out >> m_Info.ff;
		out >> m_Info.fs;
		out >> m_Info.fw;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

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
	Legend_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Legend_Struct m_Info ;
};

#endif
