#ifndef CLASS_MERGE_AUTO_H
#define CLASS_MERGE_AUTO_H

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


struct Merge_Struct
{
	uint  af;
	uint  id;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_NameString;
	uint  p_ShowModeMask;

	Merge_Struct& operator=(const Merge_Struct& cp)
	{
		this->af = 		cp.af;
		this->id = 		cp.id;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_AutoChangeAppFlag = 		cp.p_AutoChangeAppFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_NameString = 		cp.p_NameString;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		return *this;
	}
};

class CMerge_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.id;
		out << m_Info.p_AssFlag;
		out << m_Info.p_AutoChangeAppFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_NameString;
		out << m_Info.p_ShowModeMask;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.id;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_AutoChangeAppFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_NameString;
		out >> m_Info.p_ShowModeMask;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "af" );
		attr->value(QString::number(m_Info.af).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_AssFlag" );
		attr->value(QString::number(m_Info.p_AssFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_AutoChangeAppFlag" );
		attr->value( m_Info.p_AutoChangeAppFlag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NameString" );
		attr->value(QString::number(m_Info.p_NameString).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
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

		attr = node->first_attribute("id");
		if(attr)
		{
			 m_AttrInfo["id"] = QString(attr->value());
			 m_Info.id = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_AssFlag");
		if(attr)
		{
			 m_AttrInfo["p_AssFlag"] = QString(attr->value());
			 m_Info.p_AssFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_AutoChangeAppFlag");
		if(attr)
		{
			 m_AttrInfo["p_AutoChangeAppFlag"] = QString(attr->value());
			 m_Info.p_AutoChangeAppFlag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_NameString");
		if(attr)
		{
			 m_AttrInfo["p_NameString"] = QString(attr->value());
			 m_Info.p_NameString = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

	}
	Merge_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Merge_Struct m_Info ;
};

#endif
