#ifndef CLASS_POKE_AUTO_H
#define CLASS_POKE_AUTO_H

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


struct Poke_Struct
{
	uint  af;
	QString    ahref;
	uint  domain;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	int  p_AppNo;
	uint  p_AssFlag;
	QString    p_AutoChangeAppFlag;
	uint  p_DisplayNo;
	uint  p_DyColorFlag;
	uint  p_Hint;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	int  p_MarkId;
	uint  p_NameString;
	uint  p_NetPos;
	uint  p_NodeName;
	uint  p_Plane;
	int  p_PlaneState0;
	int  p_PlaneState1;
	int  p_PlaneState10;
	int  p_PlaneState11;
	int  p_PlaneState12;
	int  p_PlaneState13;
	int  p_PlaneState14;
	int  p_PlaneState15;
	int  p_PlaneState16;
	int  p_PlaneState17;
	int  p_PlaneState18;
	int  p_PlaneState19;
	int  p_PlaneState2;
	int  p_PlaneState20;
	int  p_PlaneState21;
	int  p_PlaneState22;
	int  p_PlaneState23;
	int  p_PlaneState24;
	int  p_PlaneState25;
	int  p_PlaneState26;
	int  p_PlaneState27;
	int  p_PlaneState28;
	int  p_PlaneState29;
	int  p_PlaneState3;
	int  p_PlaneState30;
	int  p_PlaneState31;
	int  p_PlaneState32;
	int  p_PlaneState33;
	int  p_PlaneState34;
	int  p_PlaneState35;
	int  p_PlaneState36;
	int  p_PlaneState37;
	int  p_PlaneState38;
	int  p_PlaneState39;
	int  p_PlaneState4;
	int  p_PlaneState40;
	int  p_PlaneState41;
	int  p_PlaneState42;
	int  p_PlaneState43;
	int  p_PlaneState44;
	int  p_PlaneState45;
	int  p_PlaneState46;
	int  p_PlaneState47;
	int  p_PlaneState48;
	int  p_PlaneState49;
	int  p_PlaneState5;
	int  p_PlaneState6;
	int  p_PlaneState7;
	int  p_PlaneState8;
	int  p_PlaneState9;
	uint  p_Pos;
	QString    p_ProcName;
	uint  p_RectStyle;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  p_ShowStyle;
	uint  p_Style;
	uint  p_SubPos;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;

	Poke_Struct& operator=(const Poke_Struct& cp)
	{
		this->af = 		cp.af;
		this->ahref = 		cp.ahref;
		this->domain = 		cp.domain;
		this->fc = 		cp.fc;
		this->fm = 		cp.fm;
		this->h = 		cp.h;
		this->id = 		cp.id;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->p_AppNo = 		cp.p_AppNo;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_AutoChangeAppFlag = 		cp.p_AutoChangeAppFlag;
		this->p_DisplayNo = 		cp.p_DisplayNo;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_Hint = 		cp.p_Hint;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_MarkId = 		cp.p_MarkId;
		this->p_NameString = 		cp.p_NameString;
		this->p_NetPos = 		cp.p_NetPos;
		this->p_NodeName = 		cp.p_NodeName;
		this->p_Plane = 		cp.p_Plane;
		this->p_PlaneState0 = 		cp.p_PlaneState0;
		this->p_PlaneState1 = 		cp.p_PlaneState1;
		this->p_PlaneState10 = 		cp.p_PlaneState10;
		this->p_PlaneState11 = 		cp.p_PlaneState11;
		this->p_PlaneState12 = 		cp.p_PlaneState12;
		this->p_PlaneState13 = 		cp.p_PlaneState13;
		this->p_PlaneState14 = 		cp.p_PlaneState14;
		this->p_PlaneState15 = 		cp.p_PlaneState15;
		this->p_PlaneState16 = 		cp.p_PlaneState16;
		this->p_PlaneState17 = 		cp.p_PlaneState17;
		this->p_PlaneState18 = 		cp.p_PlaneState18;
		this->p_PlaneState19 = 		cp.p_PlaneState19;
		this->p_PlaneState2 = 		cp.p_PlaneState2;
		this->p_PlaneState20 = 		cp.p_PlaneState20;
		this->p_PlaneState21 = 		cp.p_PlaneState21;
		this->p_PlaneState22 = 		cp.p_PlaneState22;
		this->p_PlaneState23 = 		cp.p_PlaneState23;
		this->p_PlaneState24 = 		cp.p_PlaneState24;
		this->p_PlaneState25 = 		cp.p_PlaneState25;
		this->p_PlaneState26 = 		cp.p_PlaneState26;
		this->p_PlaneState27 = 		cp.p_PlaneState27;
		this->p_PlaneState28 = 		cp.p_PlaneState28;
		this->p_PlaneState29 = 		cp.p_PlaneState29;
		this->p_PlaneState3 = 		cp.p_PlaneState3;
		this->p_PlaneState30 = 		cp.p_PlaneState30;
		this->p_PlaneState31 = 		cp.p_PlaneState31;
		this->p_PlaneState32 = 		cp.p_PlaneState32;
		this->p_PlaneState33 = 		cp.p_PlaneState33;
		this->p_PlaneState34 = 		cp.p_PlaneState34;
		this->p_PlaneState35 = 		cp.p_PlaneState35;
		this->p_PlaneState36 = 		cp.p_PlaneState36;
		this->p_PlaneState37 = 		cp.p_PlaneState37;
		this->p_PlaneState38 = 		cp.p_PlaneState38;
		this->p_PlaneState39 = 		cp.p_PlaneState39;
		this->p_PlaneState4 = 		cp.p_PlaneState4;
		this->p_PlaneState40 = 		cp.p_PlaneState40;
		this->p_PlaneState41 = 		cp.p_PlaneState41;
		this->p_PlaneState42 = 		cp.p_PlaneState42;
		this->p_PlaneState43 = 		cp.p_PlaneState43;
		this->p_PlaneState44 = 		cp.p_PlaneState44;
		this->p_PlaneState45 = 		cp.p_PlaneState45;
		this->p_PlaneState46 = 		cp.p_PlaneState46;
		this->p_PlaneState47 = 		cp.p_PlaneState47;
		this->p_PlaneState48 = 		cp.p_PlaneState48;
		this->p_PlaneState49 = 		cp.p_PlaneState49;
		this->p_PlaneState5 = 		cp.p_PlaneState5;
		this->p_PlaneState6 = 		cp.p_PlaneState6;
		this->p_PlaneState7 = 		cp.p_PlaneState7;
		this->p_PlaneState8 = 		cp.p_PlaneState8;
		this->p_PlaneState9 = 		cp.p_PlaneState9;
		this->p_Pos = 		cp.p_Pos;
		this->p_ProcName = 		cp.p_ProcName;
		this->p_RectStyle = 		cp.p_RectStyle;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShadowType = 		cp.p_ShadowType;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->p_ShowStyle = 		cp.p_ShowStyle;
		this->p_Style = 		cp.p_Style;
		this->p_SubPos = 		cp.p_SubPos;
		this->tfr = 		cp.tfr;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CPoke_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.ahref;
		out << m_Info.domain;
		out << m_Info.fc;
		out << m_Info.fm;
		out << m_Info.h;
		out << m_Info.id;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.p_AppNo;
		out << m_Info.p_AssFlag;
		out << m_Info.p_AutoChangeAppFlag;
		out << m_Info.p_DisplayNo;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_Hint;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_MarkId;
		out << m_Info.p_NameString;
		out << m_Info.p_NetPos;
		out << m_Info.p_NodeName;
		out << m_Info.p_Plane;
		out << m_Info.p_PlaneState0;
		out << m_Info.p_PlaneState1;
		out << m_Info.p_PlaneState10;
		out << m_Info.p_PlaneState11;
		out << m_Info.p_PlaneState12;
		out << m_Info.p_PlaneState13;
		out << m_Info.p_PlaneState14;
		out << m_Info.p_PlaneState15;
		out << m_Info.p_PlaneState16;
		out << m_Info.p_PlaneState17;
		out << m_Info.p_PlaneState18;
		out << m_Info.p_PlaneState19;
		out << m_Info.p_PlaneState2;
		out << m_Info.p_PlaneState20;
		out << m_Info.p_PlaneState21;
		out << m_Info.p_PlaneState22;
		out << m_Info.p_PlaneState23;
		out << m_Info.p_PlaneState24;
		out << m_Info.p_PlaneState25;
		out << m_Info.p_PlaneState26;
		out << m_Info.p_PlaneState27;
		out << m_Info.p_PlaneState28;
		out << m_Info.p_PlaneState29;
		out << m_Info.p_PlaneState3;
		out << m_Info.p_PlaneState30;
		out << m_Info.p_PlaneState31;
		out << m_Info.p_PlaneState32;
		out << m_Info.p_PlaneState33;
		out << m_Info.p_PlaneState34;
		out << m_Info.p_PlaneState35;
		out << m_Info.p_PlaneState36;
		out << m_Info.p_PlaneState37;
		out << m_Info.p_PlaneState38;
		out << m_Info.p_PlaneState39;
		out << m_Info.p_PlaneState4;
		out << m_Info.p_PlaneState40;
		out << m_Info.p_PlaneState41;
		out << m_Info.p_PlaneState42;
		out << m_Info.p_PlaneState43;
		out << m_Info.p_PlaneState44;
		out << m_Info.p_PlaneState45;
		out << m_Info.p_PlaneState46;
		out << m_Info.p_PlaneState47;
		out << m_Info.p_PlaneState48;
		out << m_Info.p_PlaneState49;
		out << m_Info.p_PlaneState5;
		out << m_Info.p_PlaneState6;
		out << m_Info.p_PlaneState7;
		out << m_Info.p_PlaneState8;
		out << m_Info.p_PlaneState9;
		out << m_Info.p_Pos;
		out << m_Info.p_ProcName;
		out << m_Info.p_RectStyle;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShadowType;
		out << m_Info.p_ShowModeMask;
		out << m_Info.p_ShowStyle;
		out << m_Info.p_Style;
		out << m_Info.p_SubPos;
		out << m_Info.tfr;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.ahref;
		out >> m_Info.domain;
		out >> m_Info.fc;
		out >> m_Info.fm;
		out >> m_Info.h;
		out >> m_Info.id;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.p_AppNo;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_AutoChangeAppFlag;
		out >> m_Info.p_DisplayNo;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_Hint;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_MarkId;
		out >> m_Info.p_NameString;
		out >> m_Info.p_NetPos;
		out >> m_Info.p_NodeName;
		out >> m_Info.p_Plane;
		out >> m_Info.p_PlaneState0;
		out >> m_Info.p_PlaneState1;
		out >> m_Info.p_PlaneState10;
		out >> m_Info.p_PlaneState11;
		out >> m_Info.p_PlaneState12;
		out >> m_Info.p_PlaneState13;
		out >> m_Info.p_PlaneState14;
		out >> m_Info.p_PlaneState15;
		out >> m_Info.p_PlaneState16;
		out >> m_Info.p_PlaneState17;
		out >> m_Info.p_PlaneState18;
		out >> m_Info.p_PlaneState19;
		out >> m_Info.p_PlaneState2;
		out >> m_Info.p_PlaneState20;
		out >> m_Info.p_PlaneState21;
		out >> m_Info.p_PlaneState22;
		out >> m_Info.p_PlaneState23;
		out >> m_Info.p_PlaneState24;
		out >> m_Info.p_PlaneState25;
		out >> m_Info.p_PlaneState26;
		out >> m_Info.p_PlaneState27;
		out >> m_Info.p_PlaneState28;
		out >> m_Info.p_PlaneState29;
		out >> m_Info.p_PlaneState3;
		out >> m_Info.p_PlaneState30;
		out >> m_Info.p_PlaneState31;
		out >> m_Info.p_PlaneState32;
		out >> m_Info.p_PlaneState33;
		out >> m_Info.p_PlaneState34;
		out >> m_Info.p_PlaneState35;
		out >> m_Info.p_PlaneState36;
		out >> m_Info.p_PlaneState37;
		out >> m_Info.p_PlaneState38;
		out >> m_Info.p_PlaneState39;
		out >> m_Info.p_PlaneState4;
		out >> m_Info.p_PlaneState40;
		out >> m_Info.p_PlaneState41;
		out >> m_Info.p_PlaneState42;
		out >> m_Info.p_PlaneState43;
		out >> m_Info.p_PlaneState44;
		out >> m_Info.p_PlaneState45;
		out >> m_Info.p_PlaneState46;
		out >> m_Info.p_PlaneState47;
		out >> m_Info.p_PlaneState48;
		out >> m_Info.p_PlaneState49;
		out >> m_Info.p_PlaneState5;
		out >> m_Info.p_PlaneState6;
		out >> m_Info.p_PlaneState7;
		out >> m_Info.p_PlaneState8;
		out >> m_Info.p_PlaneState9;
		out >> m_Info.p_Pos;
		out >> m_Info.p_ProcName;
		out >> m_Info.p_RectStyle;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShadowType;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.p_ShowStyle;
		out >> m_Info.p_Style;
		out >> m_Info.p_SubPos;
		out >> m_Info.tfr;
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
		attr->name( "ahref" );
		attr->value( m_Info.ahref.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "domain" );
		attr->value(QString::number(m_Info.domain).toLocal8Bit().data());
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
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
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
		attr->name( "p_AppNo" );
		attr->value(QString::number(m_Info.p_AppNo).toLocal8Bit().data());
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
		attr->name( "p_DisplayNo" );
		attr->value(QString::number(m_Info.p_DisplayNo).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_DyColorFlag" );
		attr->value(QString::number(m_Info.p_DyColorFlag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Hint" );
		attr->value(QString::number(m_Info.p_Hint).toLocal8Bit().data());
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
		attr->name( "p_MarkId" );
		attr->value(QString::number(m_Info.p_MarkId).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NameString" );
		attr->value(QString::number(m_Info.p_NameString).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NetPos" );
		attr->value(QString::number(m_Info.p_NetPos).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_NodeName" );
		attr->value(QString::number(m_Info.p_NodeName).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Plane" );
		attr->value(QString::number(m_Info.p_Plane).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState0" );
		attr->value(QString::number(m_Info.p_PlaneState0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState1" );
		attr->value(QString::number(m_Info.p_PlaneState1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState10" );
		attr->value(QString::number(m_Info.p_PlaneState10).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState11" );
		attr->value(QString::number(m_Info.p_PlaneState11).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState12" );
		attr->value(QString::number(m_Info.p_PlaneState12).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState13" );
		attr->value(QString::number(m_Info.p_PlaneState13).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState14" );
		attr->value(QString::number(m_Info.p_PlaneState14).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState15" );
		attr->value(QString::number(m_Info.p_PlaneState15).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState16" );
		attr->value(QString::number(m_Info.p_PlaneState16).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState17" );
		attr->value(QString::number(m_Info.p_PlaneState17).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState18" );
		attr->value(QString::number(m_Info.p_PlaneState18).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState19" );
		attr->value(QString::number(m_Info.p_PlaneState19).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState2" );
		attr->value(QString::number(m_Info.p_PlaneState2).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState20" );
		attr->value(QString::number(m_Info.p_PlaneState20).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState21" );
		attr->value(QString::number(m_Info.p_PlaneState21).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState22" );
		attr->value(QString::number(m_Info.p_PlaneState22).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState23" );
		attr->value(QString::number(m_Info.p_PlaneState23).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState24" );
		attr->value(QString::number(m_Info.p_PlaneState24).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState25" );
		attr->value(QString::number(m_Info.p_PlaneState25).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState26" );
		attr->value(QString::number(m_Info.p_PlaneState26).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState27" );
		attr->value(QString::number(m_Info.p_PlaneState27).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState28" );
		attr->value(QString::number(m_Info.p_PlaneState28).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState29" );
		attr->value(QString::number(m_Info.p_PlaneState29).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState3" );
		attr->value(QString::number(m_Info.p_PlaneState3).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState30" );
		attr->value(QString::number(m_Info.p_PlaneState30).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState31" );
		attr->value(QString::number(m_Info.p_PlaneState31).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState32" );
		attr->value(QString::number(m_Info.p_PlaneState32).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState33" );
		attr->value(QString::number(m_Info.p_PlaneState33).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState34" );
		attr->value(QString::number(m_Info.p_PlaneState34).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState35" );
		attr->value(QString::number(m_Info.p_PlaneState35).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState36" );
		attr->value(QString::number(m_Info.p_PlaneState36).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState37" );
		attr->value(QString::number(m_Info.p_PlaneState37).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState38" );
		attr->value(QString::number(m_Info.p_PlaneState38).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState39" );
		attr->value(QString::number(m_Info.p_PlaneState39).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState4" );
		attr->value(QString::number(m_Info.p_PlaneState4).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState40" );
		attr->value(QString::number(m_Info.p_PlaneState40).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState41" );
		attr->value(QString::number(m_Info.p_PlaneState41).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState42" );
		attr->value(QString::number(m_Info.p_PlaneState42).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState43" );
		attr->value(QString::number(m_Info.p_PlaneState43).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState44" );
		attr->value(QString::number(m_Info.p_PlaneState44).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState45" );
		attr->value(QString::number(m_Info.p_PlaneState45).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState46" );
		attr->value(QString::number(m_Info.p_PlaneState46).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState47" );
		attr->value(QString::number(m_Info.p_PlaneState47).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState48" );
		attr->value(QString::number(m_Info.p_PlaneState48).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState49" );
		attr->value(QString::number(m_Info.p_PlaneState49).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState5" );
		attr->value(QString::number(m_Info.p_PlaneState5).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState6" );
		attr->value(QString::number(m_Info.p_PlaneState6).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState7" );
		attr->value(QString::number(m_Info.p_PlaneState7).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState8" );
		attr->value(QString::number(m_Info.p_PlaneState8).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_PlaneState9" );
		attr->value(QString::number(m_Info.p_PlaneState9).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Pos" );
		attr->value(QString::number(m_Info.p_Pos).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ProcName" );
		attr->value( m_Info.p_ProcName.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RectStyle" );
		attr->value(QString::number(m_Info.p_RectStyle).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShadowType" );
		attr->value(QString::number(m_Info.p_ShadowType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowStyle" );
		attr->value(QString::number(m_Info.p_ShowStyle).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_Style" );
		attr->value(QString::number(m_Info.p_Style).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_SubPos" );
		attr->value(QString::number(m_Info.p_SubPos).toLocal8Bit().data());
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

		attr = node->first_attribute("ahref");
		if(attr)
		{
			 m_AttrInfo["ahref"] = QString(attr->value());
			 m_Info.ahref = QObject::tr(attr->value());
		}

		attr = node->first_attribute("domain");
		if(attr)
		{
			 m_AttrInfo["domain"] = QString(attr->value());
			 m_Info.domain = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_AppNo");
		if(attr)
		{
			 m_AttrInfo["p_AppNo"] = QString(attr->value());
			 m_Info.p_AppNo = QString(attr->value()).toInt();
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

		attr = node->first_attribute("p_DisplayNo");
		if(attr)
		{
			 m_AttrInfo["p_DisplayNo"] = QString(attr->value());
			 m_Info.p_DisplayNo = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_DyColorFlag");
		if(attr)
		{
			 m_AttrInfo["p_DyColorFlag"] = QString(attr->value());
			 m_Info.p_DyColorFlag = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_Hint");
		if(attr)
		{
			 m_AttrInfo["p_Hint"] = QString(attr->value());
			 m_Info.p_Hint = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_MarkId");
		if(attr)
		{
			 m_AttrInfo["p_MarkId"] = QString(attr->value());
			 m_Info.p_MarkId = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_NameString");
		if(attr)
		{
			 m_AttrInfo["p_NameString"] = QString(attr->value());
			 m_Info.p_NameString = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_NetPos");
		if(attr)
		{
			 m_AttrInfo["p_NetPos"] = QString(attr->value());
			 m_Info.p_NetPos = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_NodeName");
		if(attr)
		{
			 m_AttrInfo["p_NodeName"] = QString(attr->value());
			 m_Info.p_NodeName = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_Plane");
		if(attr)
		{
			 m_AttrInfo["p_Plane"] = QString(attr->value());
			 m_Info.p_Plane = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_PlaneState0");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState0"] = QString(attr->value());
			 m_Info.p_PlaneState0 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState1");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState1"] = QString(attr->value());
			 m_Info.p_PlaneState1 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState10");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState10"] = QString(attr->value());
			 m_Info.p_PlaneState10 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState11");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState11"] = QString(attr->value());
			 m_Info.p_PlaneState11 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState12");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState12"] = QString(attr->value());
			 m_Info.p_PlaneState12 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState13");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState13"] = QString(attr->value());
			 m_Info.p_PlaneState13 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState14");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState14"] = QString(attr->value());
			 m_Info.p_PlaneState14 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState15");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState15"] = QString(attr->value());
			 m_Info.p_PlaneState15 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState16");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState16"] = QString(attr->value());
			 m_Info.p_PlaneState16 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState17");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState17"] = QString(attr->value());
			 m_Info.p_PlaneState17 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState18");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState18"] = QString(attr->value());
			 m_Info.p_PlaneState18 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState19");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState19"] = QString(attr->value());
			 m_Info.p_PlaneState19 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState2");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState2"] = QString(attr->value());
			 m_Info.p_PlaneState2 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState20");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState20"] = QString(attr->value());
			 m_Info.p_PlaneState20 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState21");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState21"] = QString(attr->value());
			 m_Info.p_PlaneState21 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState22");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState22"] = QString(attr->value());
			 m_Info.p_PlaneState22 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState23");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState23"] = QString(attr->value());
			 m_Info.p_PlaneState23 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState24");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState24"] = QString(attr->value());
			 m_Info.p_PlaneState24 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState25");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState25"] = QString(attr->value());
			 m_Info.p_PlaneState25 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState26");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState26"] = QString(attr->value());
			 m_Info.p_PlaneState26 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState27");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState27"] = QString(attr->value());
			 m_Info.p_PlaneState27 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState28");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState28"] = QString(attr->value());
			 m_Info.p_PlaneState28 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState29");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState29"] = QString(attr->value());
			 m_Info.p_PlaneState29 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState3");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState3"] = QString(attr->value());
			 m_Info.p_PlaneState3 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState30");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState30"] = QString(attr->value());
			 m_Info.p_PlaneState30 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState31");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState31"] = QString(attr->value());
			 m_Info.p_PlaneState31 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState32");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState32"] = QString(attr->value());
			 m_Info.p_PlaneState32 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState33");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState33"] = QString(attr->value());
			 m_Info.p_PlaneState33 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState34");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState34"] = QString(attr->value());
			 m_Info.p_PlaneState34 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState35");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState35"] = QString(attr->value());
			 m_Info.p_PlaneState35 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState36");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState36"] = QString(attr->value());
			 m_Info.p_PlaneState36 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState37");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState37"] = QString(attr->value());
			 m_Info.p_PlaneState37 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState38");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState38"] = QString(attr->value());
			 m_Info.p_PlaneState38 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState39");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState39"] = QString(attr->value());
			 m_Info.p_PlaneState39 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState4");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState4"] = QString(attr->value());
			 m_Info.p_PlaneState4 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState40");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState40"] = QString(attr->value());
			 m_Info.p_PlaneState40 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState41");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState41"] = QString(attr->value());
			 m_Info.p_PlaneState41 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState42");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState42"] = QString(attr->value());
			 m_Info.p_PlaneState42 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState43");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState43"] = QString(attr->value());
			 m_Info.p_PlaneState43 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState44");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState44"] = QString(attr->value());
			 m_Info.p_PlaneState44 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState45");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState45"] = QString(attr->value());
			 m_Info.p_PlaneState45 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState46");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState46"] = QString(attr->value());
			 m_Info.p_PlaneState46 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState47");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState47"] = QString(attr->value());
			 m_Info.p_PlaneState47 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState48");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState48"] = QString(attr->value());
			 m_Info.p_PlaneState48 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState49");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState49"] = QString(attr->value());
			 m_Info.p_PlaneState49 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState5");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState5"] = QString(attr->value());
			 m_Info.p_PlaneState5 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState6");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState6"] = QString(attr->value());
			 m_Info.p_PlaneState6 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState7");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState7"] = QString(attr->value());
			 m_Info.p_PlaneState7 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState8");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState8"] = QString(attr->value());
			 m_Info.p_PlaneState8 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_PlaneState9");
		if(attr)
		{
			 m_AttrInfo["p_PlaneState9"] = QString(attr->value());
			 m_Info.p_PlaneState9 = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("p_Pos");
		if(attr)
		{
			 m_AttrInfo["p_Pos"] = QString(attr->value());
			 m_Info.p_Pos = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ProcName");
		if(attr)
		{
			 m_AttrInfo["p_ProcName"] = QString(attr->value());
			 m_Info.p_ProcName = QObject::tr(attr->value());
		}

		attr = node->first_attribute("p_RectStyle");
		if(attr)
		{
			 m_AttrInfo["p_RectStyle"] = QString(attr->value());
			 m_Info.p_RectStyle = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("p_ShadowType");
		if(attr)
		{
			 m_AttrInfo["p_ShadowType"] = QString(attr->value());
			 m_Info.p_ShadowType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowModeMask");
		if(attr)
		{
			 m_AttrInfo["p_ShowModeMask"] = QString(attr->value());
			 m_Info.p_ShowModeMask = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_ShowStyle");
		if(attr)
		{
			 m_AttrInfo["p_ShowStyle"] = QString(attr->value());
			 m_Info.p_ShowStyle = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_Style");
		if(attr)
		{
			 m_AttrInfo["p_Style"] = QString(attr->value());
			 m_Info.p_Style = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("p_SubPos");
		if(attr)
		{
			 m_AttrInfo["p_SubPos"] = QString(attr->value());
			 m_Info.p_SubPos = QString(attr->value()).toUInt();
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
	Poke_Struct getInfo()
	{
		return m_Info;
	}
protected:

	Poke_Struct m_Info ;
};

#endif
