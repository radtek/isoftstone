#ifndef CLASS_DIAL_AUTO_H
#define CLASS_DIAL_AUTO_H

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


struct Dial_Struct
{
	uint  af;
	quint64  app1;
	uint  begin_length1;
	bool  can_bigger;
	bool  can_little;
	uint  color_count;
	int  color_length1;
	QColor  dial_color;
	uint  end_length1;
	QColor  fc;
	uint  fixed_color;
	uint  fixed_font_size;
	uint  fm;
	uint  font_size;
	uint  h;
	uint  has_length;
	bool  has_unit;
	bool  has_value;
	uint  id;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  max_length;
	uint  max_radius;
	uint  max_scale_arc;
	uint  max_scale_intv;
	uint  max_scale_len;
	uint  max_value;
	uint  med_scale_len;
	uint  min_radius;
	uint  min_scale_arc;
	uint  min_scale_intv;
	uint  min_scale_len;
	uint  min_value;
	QColor  needle_color1;
	uint  needle_count;
	uint  needle_has_knob1;
	uint  needle_length1;
	uint  needle_style1;
	uint  needle_value1;
	uint  needle_width1;
	uint  origin;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  radius_scale1;
	uint  same_color;
	QColor  scale_back_color;
	uint  scale_backbone;
	uint  scale_clockwise;
	QColor  scale_color;
	uint  scale_horizon;
	uint  scale_label;
	uint  scale_pen;
	uint  scale_ticks;
	uint  special_needle;
	uint  state;
	uint  step;
	uint  switchapp;
	QThree  tfr;
	QString  unit;
	QColor  unit_color;
	uint  unit_location;
	int  unit_x;
	int  unit_y;
	int  voltype1;
	int  w;
	qreal  x;
	qreal  y;

	Dial_Struct& operator=(const Dial_Struct& cp)
	{
		this->af = 		cp.af;
		this->app1 = 		cp.app1;
		this->begin_length1 = 		cp.begin_length1;
		this->can_bigger = 		cp.can_bigger;
		this->can_little = 		cp.can_little;
		this->color_count = 		cp.color_count;
		this->color_length1 = 		cp.color_length1;
		this->dial_color = 		cp.dial_color;
		this->end_length1 = 		cp.end_length1;
		this->fc = 		cp.fc;
		this->fixed_color = 		cp.fixed_color;
		this->fixed_font_size = 		cp.fixed_font_size;
		this->fm = 		cp.fm;
		this->font_size = 		cp.font_size;
		this->h = 		cp.h;
		this->has_length = 		cp.has_length;
		this->has_unit = 		cp.has_unit;
		this->has_value = 		cp.has_value;
		this->id = 		cp.id;
		this->keyid1 = 		cp.keyid1;
		this->keyid2 = 		cp.keyid2;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->max_length = 		cp.max_length;
		this->max_radius = 		cp.max_radius;
		this->max_scale_arc = 		cp.max_scale_arc;
		this->max_scale_intv = 		cp.max_scale_intv;
		this->max_scale_len = 		cp.max_scale_len;
		this->max_value = 		cp.max_value;
		this->med_scale_len = 		cp.med_scale_len;
		this->min_radius = 		cp.min_radius;
		this->min_scale_arc = 		cp.min_scale_arc;
		this->min_scale_intv = 		cp.min_scale_intv;
		this->min_scale_len = 		cp.min_scale_len;
		this->min_value = 		cp.min_value;
		this->needle_color1 = 		cp.needle_color1;
		this->needle_count = 		cp.needle_count;
		this->needle_has_knob1 = 		cp.needle_has_knob1;
		this->needle_length1 = 		cp.needle_length1;
		this->needle_style1 = 		cp.needle_style1;
		this->needle_value1 = 		cp.needle_value1;
		this->needle_width1 = 		cp.needle_width1;
		this->origin = 		cp.origin;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_ReportType1 = 		cp.p_ReportType1;
		this->p_ReportType2 = 		cp.p_ReportType2;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->radius_scale1 = 		cp.radius_scale1;
		this->same_color = 		cp.same_color;
		this->scale_back_color = 		cp.scale_back_color;
		this->scale_backbone = 		cp.scale_backbone;
		this->scale_clockwise = 		cp.scale_clockwise;
		this->scale_color = 		cp.scale_color;
		this->scale_horizon = 		cp.scale_horizon;
		this->scale_label = 		cp.scale_label;
		this->scale_pen = 		cp.scale_pen;
		this->scale_ticks = 		cp.scale_ticks;
		this->special_needle = 		cp.special_needle;
		this->state = 		cp.state;
		this->step = 		cp.step;
		this->switchapp = 		cp.switchapp;
		this->tfr = 		cp.tfr;
		this->unit = 		cp.unit;
		this->unit_color = 		cp.unit_color;
		this->unit_location = 		cp.unit_location;
		this->unit_x = 		cp.unit_x;
		this->unit_y = 		cp.unit_y;
		this->voltype1 = 		cp.voltype1;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CDial_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.app1;
		out << m_Info.begin_length1;
		out << m_Info.can_bigger;
		out << m_Info.can_little;
		out << m_Info.color_count;
		out << m_Info.color_length1;
		out << m_Info.dial_color;
		out << m_Info.end_length1;
		out << m_Info.fc;
		out << m_Info.fixed_color;
		out << m_Info.fixed_font_size;
		out << m_Info.fm;
		out << m_Info.font_size;
		out << m_Info.h;
		out << m_Info.has_length;
		out << m_Info.has_unit;
		out << m_Info.has_value;
		out << m_Info.id;
		out << m_Info.keyid1;
		out << m_Info.keyid2;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.max_length;
		out << m_Info.max_radius;
		out << m_Info.max_scale_arc;
		out << m_Info.max_scale_intv;
		out << m_Info.max_scale_len;
		out << m_Info.max_value;
		out << m_Info.med_scale_len;
		out << m_Info.min_radius;
		out << m_Info.min_scale_arc;
		out << m_Info.min_scale_intv;
		out << m_Info.min_scale_len;
		out << m_Info.min_value;
		out << m_Info.needle_color1;
		out << m_Info.needle_count;
		out << m_Info.needle_has_knob1;
		out << m_Info.needle_length1;
		out << m_Info.needle_style1;
		out << m_Info.needle_value1;
		out << m_Info.needle_width1;
		out << m_Info.origin;
		out << m_Info.p_AssFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_ReportType1;
		out << m_Info.p_ReportType2;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShowModeMask;
		out << m_Info.radius_scale1;
		out << m_Info.same_color;
		out << m_Info.scale_back_color;
		out << m_Info.scale_backbone;
		out << m_Info.scale_clockwise;
		out << m_Info.scale_color;
		out << m_Info.scale_horizon;
		out << m_Info.scale_label;
		out << m_Info.scale_pen;
		out << m_Info.scale_ticks;
		out << m_Info.special_needle;
		out << m_Info.state;
		out << m_Info.step;
		out << m_Info.switchapp;
		out << m_Info.tfr;
		out << m_Info.unit;
		out << m_Info.unit_color;
		out << m_Info.unit_location;
		out << m_Info.unit_x;
		out << m_Info.unit_y;
		out << m_Info.voltype1;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.app1;
		out >> m_Info.begin_length1;
		out >> m_Info.can_bigger;
		out >> m_Info.can_little;
		out >> m_Info.color_count;
		out >> m_Info.color_length1;
		out >> m_Info.dial_color;
		out >> m_Info.end_length1;
		out >> m_Info.fc;
		out >> m_Info.fixed_color;
		out >> m_Info.fixed_font_size;
		out >> m_Info.fm;
		out >> m_Info.font_size;
		out >> m_Info.h;
		out >> m_Info.has_length;
		out >> m_Info.has_unit;
		out >> m_Info.has_value;
		out >> m_Info.id;
		out >> m_Info.keyid1;
		out >> m_Info.keyid2;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.max_length;
		out >> m_Info.max_radius;
		out >> m_Info.max_scale_arc;
		out >> m_Info.max_scale_intv;
		out >> m_Info.max_scale_len;
		out >> m_Info.max_value;
		out >> m_Info.med_scale_len;
		out >> m_Info.min_radius;
		out >> m_Info.min_scale_arc;
		out >> m_Info.min_scale_intv;
		out >> m_Info.min_scale_len;
		out >> m_Info.min_value;
		out >> m_Info.needle_color1;
		out >> m_Info.needle_count;
		out >> m_Info.needle_has_knob1;
		out >> m_Info.needle_length1;
		out >> m_Info.needle_style1;
		out >> m_Info.needle_value1;
		out >> m_Info.needle_width1;
		out >> m_Info.origin;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_ReportType1;
		out >> m_Info.p_ReportType2;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.radius_scale1;
		out >> m_Info.same_color;
		out >> m_Info.scale_back_color;
		out >> m_Info.scale_backbone;
		out >> m_Info.scale_clockwise;
		out >> m_Info.scale_color;
		out >> m_Info.scale_horizon;
		out >> m_Info.scale_label;
		out >> m_Info.scale_pen;
		out >> m_Info.scale_ticks;
		out >> m_Info.special_needle;
		out >> m_Info.state;
		out >> m_Info.step;
		out >> m_Info.switchapp;
		out >> m_Info.tfr;
		out >> m_Info.unit;
		out >> m_Info.unit_color;
		out >> m_Info.unit_location;
		out >> m_Info.unit_x;
		out >> m_Info.unit_y;
		out >> m_Info.voltype1;
		out >> m_Info.w;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "af" );
		attr->value(QString::number(m_Info.af).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app1" );
		attr->value(QString::number(m_Info.app1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "begin_length1" );
		attr->value(QString::number(m_Info.begin_length1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "can_bigger" );
		attr->value(QString::number(m_Info.can_bigger).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "can_little" );
		attr->value(QString::number(m_Info.can_little).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color_count" );
		attr->value(QString::number(m_Info.color_count).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color_length1" );
		attr->value(QString::number(m_Info.color_length1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "dial_color" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.dial_color.red(),(int)m_Info.dial_color.green(),(int)m_Info.dial_color.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "end_length1" );
		attr->value(QString::number(m_Info.end_length1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.fc.red(),(int)m_Info.fc.green(),(int)m_Info.fc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fixed_color" );
		attr->value(QString::number(m_Info.fixed_color).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fixed_font_size" );
		attr->value(QString::number(m_Info.fixed_font_size).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fm" );
		attr->value(QString::number(m_Info.fm).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "font_size" );
		attr->value(QString::number(m_Info.font_size).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "has_length" );
		attr->value(QString::number(m_Info.has_length).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "has_unit" );
		attr->value(QString::number(m_Info.has_unit).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "has_value" );
		attr->value(QString::number(m_Info.has_value).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid1" );
		attr->value(QString::number(m_Info.keyid1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid2" );
		attr->value(QString::number(m_Info.keyid2).toLocal8Bit().data());
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
		attr->name( "max_length" );
		attr->value(QString::number(m_Info.max_length).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max_radius" );
		attr->value(QString::number(m_Info.max_radius).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max_scale_arc" );
		attr->value(QString::number(m_Info.max_scale_arc).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max_scale_intv" );
		attr->value(QString::number(m_Info.max_scale_intv).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max_scale_len" );
		attr->value(QString::number(m_Info.max_scale_len).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "max_value" );
		attr->value(QString::number(m_Info.max_value).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "med_scale_len" );
		attr->value(QString::number(m_Info.med_scale_len).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_radius" );
		attr->value(QString::number(m_Info.min_radius).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_scale_arc" );
		attr->value(QString::number(m_Info.min_scale_arc).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_scale_intv" );
		attr->value(QString::number(m_Info.min_scale_intv).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_scale_len" );
		attr->value(QString::number(m_Info.min_scale_len).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_value" );
		attr->value(QString::number(m_Info.min_value).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_color1" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.needle_color1.red(),(int)m_Info.needle_color1.green(),(int)m_Info.needle_color1.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_count" );
		attr->value(QString::number(m_Info.needle_count).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_has_knob1" );
		attr->value(QString::number(m_Info.needle_has_knob1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_length1" );
		attr->value(QString::number(m_Info.needle_length1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_style1" );
		attr->value(QString::number(m_Info.needle_style1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_value1" );
		attr->value(QString::number(m_Info.needle_value1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "needle_width1" );
		attr->value(QString::number(m_Info.needle_width1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "origin" );
		attr->value(QString::number(m_Info.origin).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_AssFlag" );
		attr->value(QString::number(m_Info.p_AssFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_LevelEnd" );
		attr->value(QString::number(m_Info.p_LevelEnd).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_LevelStart" );
		attr->value(QString::number(m_Info.p_LevelStart).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NameString" );
		attr->value(QString::number(m_Info.p_NameString).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Plane" );
		attr->value(QString::number(m_Info.p_Plane).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType1" );
		attr->value(QString::number(m_Info.p_ReportType1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType2" );
		attr->value(QString::number(m_Info.p_ReportType2).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "radius_scale1" );
		attr->value(QString::number(m_Info.radius_scale1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "same_color" );
		attr->value(QString::number(m_Info.same_color).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_back_color" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.scale_back_color.red(),(int)m_Info.scale_back_color.green(),(int)m_Info.scale_back_color.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_backbone" );
		attr->value(QString::number(m_Info.scale_backbone).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_clockwise" );
		attr->value(QString::number(m_Info.scale_clockwise).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_color" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.scale_color.red(),(int)m_Info.scale_color.green(),(int)m_Info.scale_color.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_horizon" );
		attr->value(QString::number(m_Info.scale_horizon).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_label" );
		attr->value(QString::number(m_Info.scale_label).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_pen" );
		attr->value(QString::number(m_Info.scale_pen).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scale_ticks" );
		attr->value(QString::number(m_Info.scale_ticks).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "special_needle" );
		attr->value(QString::number(m_Info.special_needle).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state" );
		attr->value(QString::number(m_Info.state).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "step" );
		attr->value(QString::number(m_Info.step).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "switchapp" );
		attr->value(QString::number(m_Info.switchapp).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "tfr" );
		QString strTfr = "rotate(";
		strTfr += QString::number(m_Info.tfr.rotate);
		strTfr += ") scale(";
		strTfr += QString::number(m_Info.tfr.scale_x);
		strTfr += ",";
		strTfr += QString::number(m_Info.tfr.scale_y);
		strTfr += " ";
		attr->value(strTfr.toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit" );
		attr->value( m_Info.unit.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit_color" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.unit_color.red(),(int)m_Info.unit_color.green(),(int)m_Info.unit_color.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit_location" );
		attr->value(QString::number(m_Info.unit_location).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit_x" );
		attr->value(QString::number(m_Info.unit_x).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "unit_y" );
		attr->value(QString::number(m_Info.unit_y).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype1" );
		attr->value(QString::number(m_Info.voltype1).toLocal8Bit().data());
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

		attr = node->first_attribute("af");
		if(attr)
		{
			 m_AttrInfo["af"] = QString(attr->value());
			 m_Info.af = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("app1");
		if(attr)
		{
			 m_AttrInfo["app1"] = QString(attr->value());
			 m_Info.app1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("begin_length1");
		if(attr)
		{
			 m_AttrInfo["begin_length1"] = QString(attr->value());
			 m_Info.begin_length1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("can_bigger");
		if(attr)
		{
			 m_AttrInfo["can_bigger"] = QString(attr->value());
			 m_Info.can_bigger = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("can_little");
		if(attr)
		{
			 m_AttrInfo["can_little"] = QString(attr->value());
			 m_Info.can_little = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("color_count");
		if(attr)
		{
			 m_AttrInfo["color_count"] = QString(attr->value());
			 m_Info.color_count = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color_length1");
		if(attr)
		{
			 m_AttrInfo["color_length1"] = QString(attr->value());
			 m_Info.color_length1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("dial_color");
		if(attr)
		{
			 m_AttrInfo["dial_color"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.dial_color.setRed(lstColor[0].toInt());
				 m_Info.dial_color.setGreen(lstColor[1].toInt());
				 m_Info.dial_color.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("end_length1");
		if(attr)
		{
			 m_AttrInfo["end_length1"] = QString(attr->value());
			 m_Info.end_length1 = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("fixed_color");
		if(attr)
		{
			 m_AttrInfo["fixed_color"] = QString(attr->value());
			 m_Info.fixed_color = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fixed_font_size");
		if(attr)
		{
			 m_AttrInfo["fixed_font_size"] = QString(attr->value());
			 m_Info.fixed_font_size = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fm");
		if(attr)
		{
			 m_AttrInfo["fm"] = QString(attr->value());
			 m_Info.fm = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("font_size");
		if(attr)
		{
			 m_AttrInfo["font_size"] = QString(attr->value());
			 m_Info.font_size = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("h");
		if(attr)
		{
			 m_AttrInfo["h"] = QString(attr->value());
			 m_Info.h = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("has_length");
		if(attr)
		{
			 m_AttrInfo["has_length"] = QString(attr->value());
			 m_Info.has_length = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("has_unit");
		if(attr)
		{
			 m_AttrInfo["has_unit"] = QString(attr->value());
			 m_Info.has_unit = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("has_value");
		if(attr)
		{
			 m_AttrInfo["has_value"] = QString(attr->value());
			 m_Info.has_value = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("id");
		if(attr)
		{
			 m_AttrInfo["id"] = QString(attr->value());
			 m_Info.id = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("keyid1");
		if(attr)
		{
			 m_AttrInfo["keyid1"] = QString(attr->value());
			 m_Info.keyid1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid2");
		if(attr)
		{
			 m_AttrInfo["keyid2"] = QString(attr->value());
			 m_Info.keyid2 = QString(attr->value()).toULongLong();
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

		attr = node->first_attribute("max_length");
		if(attr)
		{
			 m_AttrInfo["max_length"] = QString(attr->value());
			 m_Info.max_length = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("max_radius");
		if(attr)
		{
			 m_AttrInfo["max_radius"] = QString(attr->value());
			 m_Info.max_radius = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("max_scale_arc");
		if(attr)
		{
			 m_AttrInfo["max_scale_arc"] = QString(attr->value());
			 m_Info.max_scale_arc = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("max_scale_intv");
		if(attr)
		{
			 m_AttrInfo["max_scale_intv"] = QString(attr->value());
			 m_Info.max_scale_intv = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("max_scale_len");
		if(attr)
		{
			 m_AttrInfo["max_scale_len"] = QString(attr->value());
			 m_Info.max_scale_len = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("max_value");
		if(attr)
		{
			 m_AttrInfo["max_value"] = QString(attr->value());
			 m_Info.max_value = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("med_scale_len");
		if(attr)
		{
			 m_AttrInfo["med_scale_len"] = QString(attr->value());
			 m_Info.med_scale_len = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_radius");
		if(attr)
		{
			 m_AttrInfo["min_radius"] = QString(attr->value());
			 m_Info.min_radius = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_scale_arc");
		if(attr)
		{
			 m_AttrInfo["min_scale_arc"] = QString(attr->value());
			 m_Info.min_scale_arc = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_scale_intv");
		if(attr)
		{
			 m_AttrInfo["min_scale_intv"] = QString(attr->value());
			 m_Info.min_scale_intv = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_scale_len");
		if(attr)
		{
			 m_AttrInfo["min_scale_len"] = QString(attr->value());
			 m_Info.min_scale_len = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_value");
		if(attr)
		{
			 m_AttrInfo["min_value"] = QString(attr->value());
			 m_Info.min_value = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_color1");
		if(attr)
		{
			 m_AttrInfo["needle_color1"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.needle_color1.setRed(lstColor[0].toInt());
				 m_Info.needle_color1.setGreen(lstColor[1].toInt());
				 m_Info.needle_color1.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("needle_count");
		if(attr)
		{
			 m_AttrInfo["needle_count"] = QString(attr->value());
			 m_Info.needle_count = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_has_knob1");
		if(attr)
		{
			 m_AttrInfo["needle_has_knob1"] = QString(attr->value());
			 m_Info.needle_has_knob1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_length1");
		if(attr)
		{
			 m_AttrInfo["needle_length1"] = QString(attr->value());
			 m_Info.needle_length1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_style1");
		if(attr)
		{
			 m_AttrInfo["needle_style1"] = QString(attr->value());
			 m_Info.needle_style1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_value1");
		if(attr)
		{
			 m_AttrInfo["needle_value1"] = QString(attr->value());
			 m_Info.needle_value1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("needle_width1");
		if(attr)
		{
			 m_AttrInfo["needle_width1"] = QString(attr->value());
			 m_Info.needle_width1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("origin");
		if(attr)
		{
			 m_AttrInfo["origin"] = QString(attr->value());
			 m_Info.origin = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_AssFlag");
		if(attr)
		{
			 m_AttrInfo["p_AssFlag"] = QString(attr->value());
			 m_Info.p_AssFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_LevelEnd");
		if(attr)
		{
			 m_AttrInfo["p_LevelEnd"] = QString(attr->value());
			 m_Info.p_LevelEnd = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_LevelStart");
		if(attr)
		{
			 m_AttrInfo["p_LevelStart"] = QString(attr->value());
			 m_Info.p_LevelStart = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_NameString");
		if(attr)
		{
			 m_AttrInfo["p_NameString"] = QString(attr->value());
			 m_Info.p_NameString = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_Plane");
		if(attr)
		{
			 m_AttrInfo["p_Plane"] = QString(attr->value());
			 m_Info.p_Plane = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType1");
		if(attr)
		{
			 m_AttrInfo["p_ReportType1"] = QString(attr->value());
			 m_Info.p_ReportType1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType2");
		if(attr)
		{
			 m_AttrInfo["p_ReportType2"] = QString(attr->value());
			 m_Info.p_ReportType2 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_RoundBox");
		if(attr)
		{
			 m_AttrInfo["p_RoundBox"] = QString(attr->value());
			 QStringList lstRect = QString(attr->value()).split(',');
			 m_Info.p_RoundBox.setLeft(lstRect[0].toInt());
			 m_Info.p_RoundBox.setRight(lstRect[1].toInt());
			 m_Info.p_RoundBox.setTop(lstRect[2].toInt());
			 m_Info.p_RoundBox.setBottom(lstRect[3].toInt());
		}

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("radius_scale1");
		if(attr)
		{
			 m_AttrInfo["radius_scale1"] = QString(attr->value());
			 m_Info.radius_scale1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("same_color");
		if(attr)
		{
			 m_AttrInfo["same_color"] = QString(attr->value());
			 m_Info.same_color = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_back_color");
		if(attr)
		{
			 m_AttrInfo["scale_back_color"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.scale_back_color.setRed(lstColor[0].toInt());
				 m_Info.scale_back_color.setGreen(lstColor[1].toInt());
				 m_Info.scale_back_color.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("scale_backbone");
		if(attr)
		{
			 m_AttrInfo["scale_backbone"] = QString(attr->value());
			 m_Info.scale_backbone = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_clockwise");
		if(attr)
		{
			 m_AttrInfo["scale_clockwise"] = QString(attr->value());
			 m_Info.scale_clockwise = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_color");
		if(attr)
		{
			 m_AttrInfo["scale_color"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.scale_color.setRed(lstColor[0].toInt());
				 m_Info.scale_color.setGreen(lstColor[1].toInt());
				 m_Info.scale_color.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("scale_horizon");
		if(attr)
		{
			 m_AttrInfo["scale_horizon"] = QString(attr->value());
			 m_Info.scale_horizon = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_label");
		if(attr)
		{
			 m_AttrInfo["scale_label"] = QString(attr->value());
			 m_Info.scale_label = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_pen");
		if(attr)
		{
			 m_AttrInfo["scale_pen"] = QString(attr->value());
			 m_Info.scale_pen = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scale_ticks");
		if(attr)
		{
			 m_AttrInfo["scale_ticks"] = QString(attr->value());
			 m_Info.scale_ticks = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("special_needle");
		if(attr)
		{
			 m_AttrInfo["special_needle"] = QString(attr->value());
			 m_Info.special_needle = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("state");
		if(attr)
		{
			 m_AttrInfo["state"] = QString(attr->value());
			 m_Info.state = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("step");
		if(attr)
		{
			 m_AttrInfo["step"] = QString(attr->value());
			 m_Info.step = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("switchapp");
		if(attr)
		{
			 m_AttrInfo["switchapp"] = QString(attr->value());
			 m_Info.switchapp = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("tfr");
		if(attr)
		{
			 m_AttrInfo["tfr"] = QString(attr->value());
			QString strValue = QString(attr->value());
			if (strValue.split(' ').count() > 0)
			{
				QString strRotate = strValue.split(' ')[0];
				strRotate.remove("rotate(");
				strRotate.remove(")");
				 m_Info.tfr.rotate = strRotate.toDouble();
			}
			if (strValue.split(' ').count() > 1)
			{
				QString strScale = strValue.split(' ')[1];
				strScale.remove("scale(");
				strScale.remove(")");
				m_Info.tfr.scale_x = strScale.split(',')[0].toDouble();
				m_Info.tfr.scale_y = strScale.split(',')[1].toDouble();
			}
		}

		attr = node->first_attribute("unit");
		if(attr)
		{
			 m_AttrInfo["unit"] = QString(attr->value());
			 m_Info.unit = QObject::tr(attr->value());
		}

		attr = node->first_attribute("unit_color");
		if(attr)
		{
			 m_AttrInfo["unit_color"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.unit_color.setRed(lstColor[0].toInt());
				 m_Info.unit_color.setGreen(lstColor[1].toInt());
				 m_Info.unit_color.setBlue(lstColor[2].toInt());
			 }
		}

		attr = node->first_attribute("unit_location");
		if(attr)
		{
			 m_AttrInfo["unit_location"] = QString(attr->value());
			 m_Info.unit_location = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("unit_x");
		if(attr)
		{
			 m_AttrInfo["unit_x"] = QString(attr->value());
			 m_Info.unit_x = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("unit_y");
		if(attr)
		{
			 m_AttrInfo["unit_y"] = QString(attr->value());
			 m_Info.unit_y = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype1");
		if(attr)
		{
			 m_AttrInfo["voltype1"] = QString(attr->value());
			 m_Info.voltype1 = QString(attr->value()).toInt();
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
	Dial_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Dial_Struct m_Info ;
};

#endif
