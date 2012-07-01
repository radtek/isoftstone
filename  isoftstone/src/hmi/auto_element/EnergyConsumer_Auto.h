#ifndef CLASS_ENERGYCONSUMER_AUTO_H
#define CLASS_ENERGYCONSUMER_AUTO_H

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


struct EnergyConsumer_Struct
{
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  name;

	EnergyConsumer_Struct& operator=(const EnergyConsumer_Struct& cp)
	{
		this->d = 		cp.d;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->keyid = 		cp.keyid;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->name = 		cp.name;
		return *this;
	}
};

class CEnergyConsumer_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.d;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.keyid;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.name;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.d;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.keyid;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.name;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

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
		attr->name( "name" );
		attr->value( m_Info.name.toLocal8Bit().data() );
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

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

		attr = node->first_attribute("name");
		if(attr)
		{
			 m_AttrInfo["name"] = QString(attr->value());
			 m_Info.name = QObject::tr(attr->value());
		}

	}
	EnergyConsumer_Struct getInfo()
	{
		return m_Info;
	}
protected:

	EnergyConsumer_Struct m_Info ;
};

#endif
