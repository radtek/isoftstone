#ifndef CLASS_BAR_AUTO_H
#define CLASS_BAR_AUTO_H

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


struct Bar_Struct
{
	uint  _3d_mark;
	uint  _bar_num0;
	uint  _bar_num1;
	uint  _bar_num2;
	uint  af;
	quint64  app0_0;
	quint64  app0_1;
	quint64  app1_0;
	quint64  app1_1;
	quint64  app2_0;
	quint64  app2_1;
	bool  auto_scale;
	uint  axe_num;
	uint  bar_num0;
	uint  bar_num1;
	uint  bar_num2;
	uint  color0_0;
	uint  color0_1;
	uint  color1_0;
	uint  color1_1;
	uint  color2_0;
	uint  color2_1;
	int  color_mark;
	uint  decimal_num;
	QColor  fc;
	uint  fm;
	uint  group;
	uint  group_nums;
	uint  h;
	uint  id;
	quint64  keyid0_0;
	quint64  keyid0_1;
	quint64  keyid1_0;
	quint64  keyid1_1;
	quint64  keyid2_0;
	quint64  keyid2_1;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  max_num;
	uint  min_num;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType0_0;
	uint  p_ReportType0_1;
	uint  p_ReportType1_0;
	uint  p_ReportType1_1;
	uint  p_ReportType2_0;
	uint  p_ReportType2_1;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  scale_mark;
	uint  show_mark;
	int  state0_0;
	int  state0_1;
	int  state1_0;
	int  state1_1;
	int  state2_0;
	int  state2_1;
	uint  step_num;
	uint  switchapp;
	QThree  tfr;
	uint  thickness;
	uint  tmp_char;
	int  voltype0_0;
	int  voltype0_1;
	int  voltype1_0;
	int  voltype1_1;
	int  voltype2_0;
	int  voltype2_1;
	int  w;
	qreal  x;
	qreal  y;

	Bar_Struct& operator=(const Bar_Struct& cp)
	{
		this->_3d_mark = 		cp._3d_mark;
		this->_bar_num0 = 		cp._bar_num0;
		this->_bar_num1 = 		cp._bar_num1;
		this->_bar_num2 = 		cp._bar_num2;
		this->af = 		cp.af;
		this->app0_0 = 		cp.app0_0;
		this->app0_1 = 		cp.app0_1;
		this->app1_0 = 		cp.app1_0;
		this->app1_1 = 		cp.app1_1;
		this->app2_0 = 		cp.app2_0;
		this->app2_1 = 		cp.app2_1;
		this->auto_scale = 		cp.auto_scale;
		this->axe_num = 		cp.axe_num;
		this->bar_num0 = 		cp.bar_num0;
		this->bar_num1 = 		cp.bar_num1;
		this->bar_num2 = 		cp.bar_num2;
		this->color0_0 = 		cp.color0_0;
		this->color0_1 = 		cp.color0_1;
		this->color1_0 = 		cp.color1_0;
		this->color1_1 = 		cp.color1_1;
		this->color2_0 = 		cp.color2_0;
		this->color2_1 = 		cp.color2_1;
		this->color_mark = 		cp.color_mark;
		this->decimal_num = 		cp.decimal_num;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->group = 		cp.group;
		this->group_nums = 		cp.group_nums;
		this->h = 		cp.h;
		this->id = 		cp.id;
		this->keyid0_0 = 		cp.keyid0_0;
		this->keyid0_1 = 		cp.keyid0_1;
		this->keyid1_0 = 		cp.keyid1_0;
		this->keyid1_1 = 		cp.keyid1_1;
		this->keyid2_0 = 		cp.keyid2_0;
		this->keyid2_1 = 		cp.keyid2_1;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->max_num = 		cp.max_num;
		this->min_num = 		cp.min_num;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_ReportType0_0 = 		cp.p_ReportType0_0;
		this->p_ReportType0_1 = 		cp.p_ReportType0_1;
		this->p_ReportType1_0 = 		cp.p_ReportType1_0;
		this->p_ReportType1_1 = 		cp.p_ReportType1_1;
		this->p_ReportType2_0 = 		cp.p_ReportType2_0;
		this->p_ReportType2_1 = 		cp.p_ReportType2_1;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->scale_mark = 		cp.scale_mark;
		this->show_mark = 		cp.show_mark;
		this->state0_0 = 		cp.state0_0;
		this->state0_1 = 		cp.state0_1;
		this->state1_0 = 		cp.state1_0;
		this->state1_1 = 		cp.state1_1;
		this->state2_0 = 		cp.state2_0;
		this->state2_1 = 		cp.state2_1;
		this->step_num = 		cp.step_num;
		this->switchapp = 		cp.switchapp;
		this->tfr = 		cp.tfr;
		this->thickness = 		cp.thickness;
		this->tmp_char = 		cp.tmp_char;
		this->voltype0_0 = 		cp.voltype0_0;
		this->voltype0_1 = 		cp.voltype0_1;
		this->voltype1_0 = 		cp.voltype1_0;
		this->voltype1_1 = 		cp.voltype1_1;
		this->voltype2_0 = 		cp.voltype2_0;
		this->voltype2_1 = 		cp.voltype2_1;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CBar_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info._3d_mark;
		out << m_Info._bar_num0;
		out << m_Info._bar_num1;
		out << m_Info._bar_num2;
		out << m_Info.af;
		out << m_Info.app0_0;
		out << m_Info.app0_1;
		out << m_Info.app1_0;
		out << m_Info.app1_1;
		out << m_Info.app2_0;
		out << m_Info.app2_1;
		out << m_Info.auto_scale;
		out << m_Info.axe_num;
		out << m_Info.bar_num0;
		out << m_Info.bar_num1;
		out << m_Info.bar_num2;
		out << m_Info.color0_0;
		out << m_Info.color0_1;
		out << m_Info.color1_0;
		out << m_Info.color1_1;
		out << m_Info.color2_0;
		out << m_Info.color2_1;
		out << m_Info.color_mark;
		out << m_Info.decimal_num;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.group;
		out << m_Info.group_nums;
		out << m_Info.h;
		out << m_Info.id;
		out << m_Info.keyid0_0;
		out << m_Info.keyid0_1;
		out << m_Info.keyid1_0;
		out << m_Info.keyid1_1;
		out << m_Info.keyid2_0;
		out << m_Info.keyid2_1;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.max_num;
		out << m_Info.min_num;
		out << m_Info.p_AssFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_ReportType0_0;
		out << m_Info.p_ReportType0_1;
		out << m_Info.p_ReportType1_0;
		out << m_Info.p_ReportType1_1;
		out << m_Info.p_ReportType2_0;
		out << m_Info.p_ReportType2_1;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShowModeMask;
		out << m_Info.scale_mark;
		out << m_Info.show_mark;
		out << m_Info.state0_0;
		out << m_Info.state0_1;
		out << m_Info.state1_0;
		out << m_Info.state1_1;
		out << m_Info.state2_0;
		out << m_Info.state2_1;
		out << m_Info.step_num;
		out << m_Info.switchapp;
		out << m_Info.tfr;
		out << m_Info.thickness;
		out << m_Info.tmp_char;
		out << m_Info.voltype0_0;
		out << m_Info.voltype0_1;
		out << m_Info.voltype1_0;
		out << m_Info.voltype1_1;
		out << m_Info.voltype2_0;
		out << m_Info.voltype2_1;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info._3d_mark;
		out >> m_Info._bar_num0;
		out >> m_Info._bar_num1;
		out >> m_Info._bar_num2;
		out >> m_Info.af;
		out >> m_Info.app0_0;
		out >> m_Info.app0_1;
		out >> m_Info.app1_0;
		out >> m_Info.app1_1;
		out >> m_Info.app2_0;
		out >> m_Info.app2_1;
		out >> m_Info.auto_scale;
		out >> m_Info.axe_num;
		out >> m_Info.bar_num0;
		out >> m_Info.bar_num1;
		out >> m_Info.bar_num2;
		out >> m_Info.color0_0;
		out >> m_Info.color0_1;
		out >> m_Info.color1_0;
		out >> m_Info.color1_1;
		out >> m_Info.color2_0;
		out >> m_Info.color2_1;
		out >> m_Info.color_mark;
		out >> m_Info.decimal_num;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.group;
		out >> m_Info.group_nums;
		out >> m_Info.h;
		out >> m_Info.id;
		out >> m_Info.keyid0_0;
		out >> m_Info.keyid0_1;
		out >> m_Info.keyid1_0;
		out >> m_Info.keyid1_1;
		out >> m_Info.keyid2_0;
		out >> m_Info.keyid2_1;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.max_num;
		out >> m_Info.min_num;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_ReportType0_0;
		out >> m_Info.p_ReportType0_1;
		out >> m_Info.p_ReportType1_0;
		out >> m_Info.p_ReportType1_1;
		out >> m_Info.p_ReportType2_0;
		out >> m_Info.p_ReportType2_1;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.scale_mark;
		out >> m_Info.show_mark;
		out >> m_Info.state0_0;
		out >> m_Info.state0_1;
		out >> m_Info.state1_0;
		out >> m_Info.state1_1;
		out >> m_Info.state2_0;
		out >> m_Info.state2_1;
		out >> m_Info.step_num;
		out >> m_Info.switchapp;
		out >> m_Info.tfr;
		out >> m_Info.thickness;
		out >> m_Info.tmp_char;
		out >> m_Info.voltype0_0;
		out >> m_Info.voltype0_1;
		out >> m_Info.voltype1_0;
		out >> m_Info.voltype1_1;
		out >> m_Info.voltype2_0;
		out >> m_Info.voltype2_1;
		out >> m_Info.w;
		out >> m_Info.x;
		out >> m_Info.y;
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

		attr = new xml_attribute<char>();
		attr->name( "_3d_mark" );
		attr->value(QString::number(m_Info._3d_mark).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "_bar_num0" );
		attr->value(QString::number(m_Info._bar_num0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "_bar_num1" );
		attr->value(QString::number(m_Info._bar_num1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "_bar_num2" );
		attr->value(QString::number(m_Info._bar_num2).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "af" );
		attr->value(QString::number(m_Info.af).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app0_0" );
		attr->value(QString::number(m_Info.app0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app0_1" );
		attr->value(QString::number(m_Info.app0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app1_0" );
		attr->value(QString::number(m_Info.app1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app1_1" );
		attr->value(QString::number(m_Info.app1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app2_0" );
		attr->value(QString::number(m_Info.app2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "app2_1" );
		attr->value(QString::number(m_Info.app2_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "auto_scale" );
		attr->value(QString::number(m_Info.auto_scale).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "axe_num" );
		attr->value(QString::number(m_Info.axe_num).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "bar_num0" );
		attr->value(QString::number(m_Info.bar_num0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "bar_num1" );
		attr->value(QString::number(m_Info.bar_num1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "bar_num2" );
		attr->value(QString::number(m_Info.bar_num2).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color0_0" );
		attr->value(QString::number(m_Info.color0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color0_1" );
		attr->value(QString::number(m_Info.color0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color1_0" );
		attr->value(QString::number(m_Info.color1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color1_1" );
		attr->value(QString::number(m_Info.color1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color2_0" );
		attr->value(QString::number(m_Info.color2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color2_1" );
		attr->value(QString::number(m_Info.color2_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "color_mark" );
		attr->value(QString::number(m_Info.color_mark).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "decimal_num" );
		attr->value(QString::number(m_Info.decimal_num).toLocal8Bit().data());
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
		attr->name( "group" );
		attr->value(QString::number(m_Info.group).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "group_nums" );
		attr->value(QString::number(m_Info.group_nums).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid0_0" );
		attr->value(QString::number(m_Info.keyid0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid0_1" );
		attr->value(QString::number(m_Info.keyid0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid1_0" );
		attr->value(QString::number(m_Info.keyid1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid1_1" );
		attr->value(QString::number(m_Info.keyid1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid2_0" );
		attr->value(QString::number(m_Info.keyid2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "keyid2_1" );
		attr->value(QString::number(m_Info.keyid2_1).toLocal8Bit().data());
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
		attr->name( "max_num" );
		attr->value(QString::number(m_Info.max_num).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "min_num" );
		attr->value(QString::number(m_Info.min_num).toLocal8Bit().data());
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
		attr->name( "p_ReportType0_0" );
		attr->value(QString::number(m_Info.p_ReportType0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType0_1" );
		attr->value(QString::number(m_Info.p_ReportType0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType1_0" );
		attr->value(QString::number(m_Info.p_ReportType1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType1_1" );
		attr->value(QString::number(m_Info.p_ReportType1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType2_0" );
		attr->value(QString::number(m_Info.p_ReportType2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ReportType2_1" );
		attr->value(QString::number(m_Info.p_ReportType2_1).toLocal8Bit().data());
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
		attr->name( "scale_mark" );
		attr->value(QString::number(m_Info.scale_mark).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "show_mark" );
		attr->value(QString::number(m_Info.show_mark).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state0_0" );
		attr->value(QString::number(m_Info.state0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state0_1" );
		attr->value(QString::number(m_Info.state0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state1_0" );
		attr->value(QString::number(m_Info.state1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state1_1" );
		attr->value(QString::number(m_Info.state1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state2_0" );
		attr->value(QString::number(m_Info.state2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "state2_1" );
		attr->value(QString::number(m_Info.state2_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "step_num" );
		attr->value(QString::number(m_Info.step_num).toLocal8Bit().data());
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
		attr->name( "thickness" );
		attr->value(QString::number(m_Info.thickness).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "tmp_char" );
		attr->value(QString::number(m_Info.tmp_char).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype0_0" );
		attr->value(QString::number(m_Info.voltype0_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype0_1" );
		attr->value(QString::number(m_Info.voltype0_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype1_0" );
		attr->value(QString::number(m_Info.voltype1_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype1_1" );
		attr->value(QString::number(m_Info.voltype1_1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype2_0" );
		attr->value(QString::number(m_Info.voltype2_0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "voltype2_1" );
		attr->value(QString::number(m_Info.voltype2_1).toLocal8Bit().data());
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

		attr = node->first_attribute("_3d_mark");
		if(attr)
		{
			 m_AttrInfo["_3d_mark"] = QString(attr->value());
			 m_Info._3d_mark = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("_bar_num0");
		if(attr)
		{
			 m_AttrInfo["_bar_num0"] = QString(attr->value());
			 m_Info._bar_num0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("_bar_num1");
		if(attr)
		{
			 m_AttrInfo["_bar_num1"] = QString(attr->value());
			 m_Info._bar_num1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("_bar_num2");
		if(attr)
		{
			 m_AttrInfo["_bar_num2"] = QString(attr->value());
			 m_Info._bar_num2 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("af");
		if(attr)
		{
			 m_AttrInfo["af"] = QString(attr->value());
			 m_Info.af = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("app0_0");
		if(attr)
		{
			 m_AttrInfo["app0_0"] = QString(attr->value());
			 m_Info.app0_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("app0_1");
		if(attr)
		{
			 m_AttrInfo["app0_1"] = QString(attr->value());
			 m_Info.app0_1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("app1_0");
		if(attr)
		{
			 m_AttrInfo["app1_0"] = QString(attr->value());
			 m_Info.app1_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("app1_1");
		if(attr)
		{
			 m_AttrInfo["app1_1"] = QString(attr->value());
			 m_Info.app1_1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("app2_0");
		if(attr)
		{
			 m_AttrInfo["app2_0"] = QString(attr->value());
			 m_Info.app2_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("app2_1");
		if(attr)
		{
			 m_AttrInfo["app2_1"] = QString(attr->value());
			 m_Info.app2_1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("auto_scale");
		if(attr)
		{
			 m_AttrInfo["auto_scale"] = QString(attr->value());
			 m_Info.auto_scale = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("axe_num");
		if(attr)
		{
			 m_AttrInfo["axe_num"] = QString(attr->value());
			 m_Info.axe_num = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("bar_num0");
		if(attr)
		{
			 m_AttrInfo["bar_num0"] = QString(attr->value());
			 m_Info.bar_num0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("bar_num1");
		if(attr)
		{
			 m_AttrInfo["bar_num1"] = QString(attr->value());
			 m_Info.bar_num1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("bar_num2");
		if(attr)
		{
			 m_AttrInfo["bar_num2"] = QString(attr->value());
			 m_Info.bar_num2 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color0_0");
		if(attr)
		{
			 m_AttrInfo["color0_0"] = QString(attr->value());
			 m_Info.color0_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color0_1");
		if(attr)
		{
			 m_AttrInfo["color0_1"] = QString(attr->value());
			 m_Info.color0_1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color1_0");
		if(attr)
		{
			 m_AttrInfo["color1_0"] = QString(attr->value());
			 m_Info.color1_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color1_1");
		if(attr)
		{
			 m_AttrInfo["color1_1"] = QString(attr->value());
			 m_Info.color1_1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color2_0");
		if(attr)
		{
			 m_AttrInfo["color2_0"] = QString(attr->value());
			 m_Info.color2_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color2_1");
		if(attr)
		{
			 m_AttrInfo["color2_1"] = QString(attr->value());
			 m_Info.color2_1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("color_mark");
		if(attr)
		{
			 m_AttrInfo["color_mark"] = QString(attr->value());
			 m_Info.color_mark = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("decimal_num");
		if(attr)
		{
			 m_AttrInfo["decimal_num"] = QString(attr->value());
			 m_Info.decimal_num = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("group");
		if(attr)
		{
			 m_AttrInfo["group"] = QString(attr->value());
			 m_Info.group = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("group_nums");
		if(attr)
		{
			 m_AttrInfo["group_nums"] = QString(attr->value());
			 m_Info.group_nums = QString(attr->value()).toUInt();
		}

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

		attr = node->first_attribute("keyid0_0");
		if(attr)
		{
			 m_AttrInfo["keyid0_0"] = QString(attr->value());
			 m_Info.keyid0_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid0_1");
		if(attr)
		{
			 m_AttrInfo["keyid0_1"] = QString(attr->value());
			 m_Info.keyid0_1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid1_0");
		if(attr)
		{
			 m_AttrInfo["keyid1_0"] = QString(attr->value());
			 m_Info.keyid1_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid1_1");
		if(attr)
		{
			 m_AttrInfo["keyid1_1"] = QString(attr->value());
			 m_Info.keyid1_1 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid2_0");
		if(attr)
		{
			 m_AttrInfo["keyid2_0"] = QString(attr->value());
			 m_Info.keyid2_0 = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("keyid2_1");
		if(attr)
		{
			 m_AttrInfo["keyid2_1"] = QString(attr->value());
			 m_Info.keyid2_1 = QString(attr->value()).toULongLong();
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

		attr = node->first_attribute("max_num");
		if(attr)
		{
			 m_AttrInfo["max_num"] = QString(attr->value());
			 m_Info.max_num = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("min_num");
		if(attr)
		{
			 m_AttrInfo["min_num"] = QString(attr->value());
			 m_Info.min_num = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_ReportType0_0");
		if(attr)
		{
			 m_AttrInfo["p_ReportType0_0"] = QString(attr->value());
			 m_Info.p_ReportType0_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType0_1");
		if(attr)
		{
			 m_AttrInfo["p_ReportType0_1"] = QString(attr->value());
			 m_Info.p_ReportType0_1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType1_0");
		if(attr)
		{
			 m_AttrInfo["p_ReportType1_0"] = QString(attr->value());
			 m_Info.p_ReportType1_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType1_1");
		if(attr)
		{
			 m_AttrInfo["p_ReportType1_1"] = QString(attr->value());
			 m_Info.p_ReportType1_1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType2_0");
		if(attr)
		{
			 m_AttrInfo["p_ReportType2_0"] = QString(attr->value());
			 m_Info.p_ReportType2_0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ReportType2_1");
		if(attr)
		{
			 m_AttrInfo["p_ReportType2_1"] = QString(attr->value());
			 m_Info.p_ReportType2_1 = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("scale_mark");
		if(attr)
		{
			 m_AttrInfo["scale_mark"] = QString(attr->value());
			 m_Info.scale_mark = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("show_mark");
		if(attr)
		{
			 m_AttrInfo["show_mark"] = QString(attr->value());
			 m_Info.show_mark = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("state0_0");
		if(attr)
		{
			 m_AttrInfo["state0_0"] = QString(attr->value());
			 m_Info.state0_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("state0_1");
		if(attr)
		{
			 m_AttrInfo["state0_1"] = QString(attr->value());
			 m_Info.state0_1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("state1_0");
		if(attr)
		{
			 m_AttrInfo["state1_0"] = QString(attr->value());
			 m_Info.state1_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("state1_1");
		if(attr)
		{
			 m_AttrInfo["state1_1"] = QString(attr->value());
			 m_Info.state1_1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("state2_0");
		if(attr)
		{
			 m_AttrInfo["state2_0"] = QString(attr->value());
			 m_Info.state2_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("state2_1");
		if(attr)
		{
			 m_AttrInfo["state2_1"] = QString(attr->value());
			 m_Info.state2_1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("step_num");
		if(attr)
		{
			 m_AttrInfo["step_num"] = QString(attr->value());
			 m_Info.step_num = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("thickness");
		if(attr)
		{
			 m_AttrInfo["thickness"] = QString(attr->value());
			 m_Info.thickness = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("tmp_char");
		if(attr)
		{
			 m_AttrInfo["tmp_char"] = QString(attr->value());
			 m_Info.tmp_char = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("voltype0_0");
		if(attr)
		{
			 m_AttrInfo["voltype0_0"] = QString(attr->value());
			 m_Info.voltype0_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype0_1");
		if(attr)
		{
			 m_AttrInfo["voltype0_1"] = QString(attr->value());
			 m_Info.voltype0_1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype1_0");
		if(attr)
		{
			 m_AttrInfo["voltype1_0"] = QString(attr->value());
			 m_Info.voltype1_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype1_1");
		if(attr)
		{
			 m_AttrInfo["voltype1_1"] = QString(attr->value());
			 m_Info.voltype1_1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype2_0");
		if(attr)
		{
			 m_AttrInfo["voltype2_0"] = QString(attr->value());
			 m_Info.voltype2_0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("voltype2_1");
		if(attr)
		{
			 m_AttrInfo["voltype2_1"] = QString(attr->value());
			 m_Info.voltype2_1 = QString(attr->value()).toInt();
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
	Bar_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Bar_Struct m_Info ;
};

#endif
