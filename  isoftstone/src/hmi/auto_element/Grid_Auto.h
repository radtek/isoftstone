#ifndef CLASS_GRID_AUTO_H
#define CLASS_GRID_AUTO_H

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


struct Grid_Struct
{
	QString  main_grid_c;
	QString  main_grid_h;
	QString  main_grid_ls;
	QString  main_grid_lw;
	QString  main_grid_w;
	QString  main_grid_x;
	QString  main_grid_x_show;
	QString  main_grid_y;
	QString  main_grid_y_show;
	QString  sub_grid_c;
	QString  sub_grid_ls;
	QString  sub_grid_lw;
	QString  sub_grid_x_show;
	QString  sub_grid_y_show;

	Grid_Struct& operator=(const Grid_Struct& cp)
	{
		this->main_grid_c = 		cp.main_grid_c;
		this->main_grid_h = 		cp.main_grid_h;
		this->main_grid_ls = 		cp.main_grid_ls;
		this->main_grid_lw = 		cp.main_grid_lw;
		this->main_grid_w = 		cp.main_grid_w;
		this->main_grid_x = 		cp.main_grid_x;
		this->main_grid_x_show = 		cp.main_grid_x_show;
		this->main_grid_y = 		cp.main_grid_y;
		this->main_grid_y_show = 		cp.main_grid_y_show;
		this->sub_grid_c = 		cp.sub_grid_c;
		this->sub_grid_ls = 		cp.sub_grid_ls;
		this->sub_grid_lw = 		cp.sub_grid_lw;
		this->sub_grid_x_show = 		cp.sub_grid_x_show;
		this->sub_grid_y_show = 		cp.sub_grid_y_show;
		return *this;
	}
};

class CGrid_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.main_grid_c;
		out << m_Info.main_grid_h;
		out << m_Info.main_grid_ls;
		out << m_Info.main_grid_lw;
		out << m_Info.main_grid_w;
		out << m_Info.main_grid_x;
		out << m_Info.main_grid_x_show;
		out << m_Info.main_grid_y;
		out << m_Info.main_grid_y_show;
		out << m_Info.sub_grid_c;
		out << m_Info.sub_grid_ls;
		out << m_Info.sub_grid_lw;
		out << m_Info.sub_grid_x_show;
		out << m_Info.sub_grid_y_show;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.main_grid_c;
		out >> m_Info.main_grid_h;
		out >> m_Info.main_grid_ls;
		out >> m_Info.main_grid_lw;
		out >> m_Info.main_grid_w;
		out >> m_Info.main_grid_x;
		out >> m_Info.main_grid_x_show;
		out >> m_Info.main_grid_y;
		out >> m_Info.main_grid_y_show;
		out >> m_Info.sub_grid_c;
		out >> m_Info.sub_grid_ls;
		out >> m_Info.sub_grid_lw;
		out >> m_Info.sub_grid_x_show;
		out >> m_Info.sub_grid_y_show;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_c" );
		attr->value( m_Info.main_grid_c.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_h" );
		attr->value( m_Info.main_grid_h.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_ls" );
		attr->value( m_Info.main_grid_ls.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_lw" );
		attr->value( m_Info.main_grid_lw.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_w" );
		attr->value( m_Info.main_grid_w.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_x" );
		attr->value( m_Info.main_grid_x.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_x_show" );
		attr->value( m_Info.main_grid_x_show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_y" );
		attr->value( m_Info.main_grid_y.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "main_grid_y_show" );
		attr->value( m_Info.main_grid_y_show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "sub_grid_c" );
		attr->value( m_Info.sub_grid_c.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "sub_grid_ls" );
		attr->value( m_Info.sub_grid_ls.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "sub_grid_lw" );
		attr->value( m_Info.sub_grid_lw.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "sub_grid_x_show" );
		attr->value( m_Info.sub_grid_x_show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "sub_grid_y_show" );
		attr->value( m_Info.sub_grid_y_show.toLocal8Bit().data() );
		node->append_attribute(attr) ;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

		attr = node->first_attribute("main_grid_c");
		if(attr)
		{
			 m_AttrInfo["main_grid_c"] = QString(attr->value());
			 m_Info.main_grid_c = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_h");
		if(attr)
		{
			 m_AttrInfo["main_grid_h"] = QString(attr->value());
			 m_Info.main_grid_h = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_ls");
		if(attr)
		{
			 m_AttrInfo["main_grid_ls"] = QString(attr->value());
			 m_Info.main_grid_ls = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_lw");
		if(attr)
		{
			 m_AttrInfo["main_grid_lw"] = QString(attr->value());
			 m_Info.main_grid_lw = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_w");
		if(attr)
		{
			 m_AttrInfo["main_grid_w"] = QString(attr->value());
			 m_Info.main_grid_w = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_x");
		if(attr)
		{
			 m_AttrInfo["main_grid_x"] = QString(attr->value());
			 m_Info.main_grid_x = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_x_show");
		if(attr)
		{
			 m_AttrInfo["main_grid_x_show"] = QString(attr->value());
			 m_Info.main_grid_x_show = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_y");
		if(attr)
		{
			 m_AttrInfo["main_grid_y"] = QString(attr->value());
			 m_Info.main_grid_y = QObject::tr(attr->value());
		}

		attr = node->first_attribute("main_grid_y_show");
		if(attr)
		{
			 m_AttrInfo["main_grid_y_show"] = QString(attr->value());
			 m_Info.main_grid_y_show = QObject::tr(attr->value());
		}

		attr = node->first_attribute("sub_grid_c");
		if(attr)
		{
			 m_AttrInfo["sub_grid_c"] = QString(attr->value());
			 m_Info.sub_grid_c = QObject::tr(attr->value());
		}

		attr = node->first_attribute("sub_grid_ls");
		if(attr)
		{
			 m_AttrInfo["sub_grid_ls"] = QString(attr->value());
			 m_Info.sub_grid_ls = QObject::tr(attr->value());
		}

		attr = node->first_attribute("sub_grid_lw");
		if(attr)
		{
			 m_AttrInfo["sub_grid_lw"] = QString(attr->value());
			 m_Info.sub_grid_lw = QObject::tr(attr->value());
		}

		attr = node->first_attribute("sub_grid_x_show");
		if(attr)
		{
			 m_AttrInfo["sub_grid_x_show"] = QString(attr->value());
			 m_Info.sub_grid_x_show = QObject::tr(attr->value());
		}

		attr = node->first_attribute("sub_grid_y_show");
		if(attr)
		{
			 m_AttrInfo["sub_grid_y_show"] = QString(attr->value());
			 m_Info.sub_grid_y_show = QObject::tr(attr->value());
		}

	}
	Grid_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Grid_Struct m_Info ;
};

#endif
