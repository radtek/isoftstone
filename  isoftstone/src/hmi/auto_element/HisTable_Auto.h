#ifndef CLASS_HISTABLE_AUTO_H
#define CLASS_HISTABLE_AUTO_H

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


struct HisTable_Struct
{
	uint  af;
	bool  allowdeleteflag;
	bool  allowinsetflag;
	bool  allowupdateflag;
	quint64  AppNo;
	QString  backgroudcolor;
	bool  backgroudflag;
	QString  backgroudpic;
	int  BaseTime;
	uint  BtnBackColor;
	uint  BtnFontColor;
	uint  BtnHeight;
	uint  BtnWidth;
	uint  cellshadestyle;
	QString  cellshapestyle;
	QString  colheadcolor;
	QString  colheadflag;
	uint  colheadheight;
	uint  dy_num;
	uint  EndTimeDay;
	uint  EndTimeHour;
	uint  EndTimeMinute;
	uint  EndTimeMonth;
	uint  EndTimeSecond;
	uint  EndTimeType;
	uint  EndTimeWeek;
	uint  EndTimeWeekday;
	uint  EndTimeYear;
	QColor  evenrowcolor;
	QColor  fc;
	uint  fieldnum;
	uint  fields;
	uint  fm;
	QString  fontcolor;
	QString  fontsize;
	QString  fonttype;
	QString  frameshadow;
	QString  frameshape;
	bool  gridflag;
	uint  h;
	uint  HisTableHeadColor;
	uint  HisTableHeadFontColor;
	uint  HisTableHeadFontSize;
	uint  HisTableHeadFontType;
	uint  HisTableHeadHeight;
	uint  id;
	uint  Interval;
	bool  IsByStep;
	bool  IsColumnTrig;
	QColor  lc;
	uint  ls;
	uint  lw;
	QColor  oddrowcolor;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  QueryMode;
	QString  refreshinterval;
	uint  reserved_var0;
	uint  reserved_var1;
	uint  reserved_var10;
	uint  reserved_var11;
	uint  reserved_var12;
	uint  reserved_var13;
	uint  reserved_var14;
	uint  reserved_var15;
	uint  reserved_var16;
	uint  reserved_var17;
	uint  reserved_var18;
	uint  reserved_var19;
	uint  reserved_var2;
	uint  reserved_var20;
	uint  reserved_var21;
	uint  reserved_var22;
	uint  reserved_var23;
	uint  reserved_var24;
	uint  reserved_var25;
	uint  reserved_var26;
	uint  reserved_var27;
	uint  reserved_var28;
	uint  reserved_var29;
	uint  reserved_var3;
	uint  reserved_var30;
	uint  reserved_var31;
	uint  reserved_var32;
	uint  reserved_var33;
	uint  reserved_var34;
	uint  reserved_var35;
	uint  reserved_var36;
	uint  reserved_var37;
	uint  reserved_var38;
	uint  reserved_var39;
	uint  reserved_var4;
	uint  reserved_var40;
	uint  reserved_var41;
	uint  reserved_var42;
	uint  reserved_var43;
	uint  reserved_var44;
	uint  reserved_var45;
	uint  reserved_var46;
	uint  reserved_var47;
	uint  reserved_var48;
	uint  reserved_var49;
	uint  reserved_var5;
	uint  reserved_var50;
	uint  reserved_var51;
	uint  reserved_var52;
	uint  reserved_var53;
	uint  reserved_var54;
	uint  reserved_var55;
	uint  reserved_var56;
	uint  reserved_var57;
	uint  reserved_var58;
	uint  reserved_var59;
	uint  reserved_var6;
	uint  reserved_var60;
	uint  reserved_var61;
	uint  reserved_var62;
	uint  reserved_var63;
	uint  reserved_var7;
	uint  reserved_var8;
	uint  reserved_var9;
	QString  rowheadflag;
	uint  rowheight;
	uint  SampleType;
	uint  scrollbarenabled;
	QString  shadowwidth;
	QString  showcolscrollflag;
	uint  ShowInOneLine;
	QString  showrowcolor;
	QString  showrowscrollflag;
	uint  SortByDateAscend;
	uint  StartTimeDay;
	uint  StartTimeHour;
	uint  StartTimeMinute;
	uint  StartTimeMonth;
	uint  StartTimeSecond;
	uint  StartTimeType;
	uint  StartTimeWeek;
	uint  StartTimeWeekday;
	uint  StartTimeYear;
	uint  StatusShowFlag;
	QThree  tfr;
	uint  TimeBackColor;
	uint  TimeDifColor;
	uint  TimeEvenColor;
	uint  TimeFontColor;
	uint  TimeOddColor;
	uint  TimeShowStyle;
	uint  trig_key_size;
	uint  TrigColExtend;
	uint  TrigSampleId;
	uint  ValueShowFlag;
	int  w;
	qreal  x;
	qreal  y;

	HisTable_Struct& operator=(const HisTable_Struct& cp)
	{
		this->af = 		cp.af;
		this->allowdeleteflag = 		cp.allowdeleteflag;
		this->allowinsetflag = 		cp.allowinsetflag;
		this->allowupdateflag = 		cp.allowupdateflag;
		this->AppNo = 		cp.AppNo;
		this->backgroudcolor = 		cp.backgroudcolor;
		this->backgroudflag = 		cp.backgroudflag;
		this->backgroudpic = 		cp.backgroudpic;
		this->BaseTime = 		cp.BaseTime;
		this->BtnBackColor = 		cp.BtnBackColor;
		this->BtnFontColor = 		cp.BtnFontColor;
		this->BtnHeight = 		cp.BtnHeight;
		this->BtnWidth = 		cp.BtnWidth;
		this->cellshadestyle = 		cp.cellshadestyle;
		this->cellshapestyle = 		cp.cellshapestyle;
		this->colheadcolor = 		cp.colheadcolor;
		this->colheadflag = 		cp.colheadflag;
		this->colheadheight = 		cp.colheadheight;
		this->dy_num = 		cp.dy_num;
		this->EndTimeDay = 		cp.EndTimeDay;
		this->EndTimeHour = 		cp.EndTimeHour;
		this->EndTimeMinute = 		cp.EndTimeMinute;
		this->EndTimeMonth = 		cp.EndTimeMonth;
		this->EndTimeSecond = 		cp.EndTimeSecond;
		this->EndTimeType = 		cp.EndTimeType;
		this->EndTimeWeek = 		cp.EndTimeWeek;
		this->EndTimeWeekday = 		cp.EndTimeWeekday;
		this->EndTimeYear = 		cp.EndTimeYear;
		this->evenrowcolor = 		cp.evenrowcolor;
		this->fc = 		cp.fc;
		this->fieldnum = 		cp.fieldnum;
		this->fields = 		cp.fields;
		this->fm = 		cp.fm;
		this->fontcolor = 		cp.fontcolor;
		this->fontsize = 		cp.fontsize;
		this->fonttype = 		cp.fonttype;
		this->frameshadow = 		cp.frameshadow;
		this->frameshape = 		cp.frameshape;
		this->gridflag = 		cp.gridflag;
		this->h = 		cp.h;
		this->HisTableHeadColor = 		cp.HisTableHeadColor;
		this->HisTableHeadFontColor = 		cp.HisTableHeadFontColor;
		this->HisTableHeadFontSize = 		cp.HisTableHeadFontSize;
		this->HisTableHeadFontType = 		cp.HisTableHeadFontType;
		this->HisTableHeadHeight = 		cp.HisTableHeadHeight;
		this->id = 		cp.id;
		this->Interval = 		cp.Interval;
		this->IsByStep = 		cp.IsByStep;
		this->IsColumnTrig = 		cp.IsColumnTrig;
		this->lc = 		cp.lc;
		this->ls = 		cp.ls;
		this->lw = 		cp.lw;
		this->oddrowcolor = 		cp.oddrowcolor;
		this->p_AssFlag = 		cp.p_AssFlag;
		this->p_AutoChangeAppFlag = 		cp.p_AutoChangeAppFlag;
		this->p_DyColorFlag = 		cp.p_DyColorFlag;
		this->p_LevelEnd = 		cp.p_LevelEnd;
		this->p_LevelStart = 		cp.p_LevelStart;
		this->p_NameString = 		cp.p_NameString;
		this->p_Plane = 		cp.p_Plane;
		this->p_RoundBox = 		cp.p_RoundBox;
		this->p_ShowModeMask = 		cp.p_ShowModeMask;
		this->QueryMode = 		cp.QueryMode;
		this->refreshinterval = 		cp.refreshinterval;
		this->reserved_var0 = 		cp.reserved_var0;
		this->reserved_var1 = 		cp.reserved_var1;
		this->reserved_var10 = 		cp.reserved_var10;
		this->reserved_var11 = 		cp.reserved_var11;
		this->reserved_var12 = 		cp.reserved_var12;
		this->reserved_var13 = 		cp.reserved_var13;
		this->reserved_var14 = 		cp.reserved_var14;
		this->reserved_var15 = 		cp.reserved_var15;
		this->reserved_var16 = 		cp.reserved_var16;
		this->reserved_var17 = 		cp.reserved_var17;
		this->reserved_var18 = 		cp.reserved_var18;
		this->reserved_var19 = 		cp.reserved_var19;
		this->reserved_var2 = 		cp.reserved_var2;
		this->reserved_var20 = 		cp.reserved_var20;
		this->reserved_var21 = 		cp.reserved_var21;
		this->reserved_var22 = 		cp.reserved_var22;
		this->reserved_var23 = 		cp.reserved_var23;
		this->reserved_var24 = 		cp.reserved_var24;
		this->reserved_var25 = 		cp.reserved_var25;
		this->reserved_var26 = 		cp.reserved_var26;
		this->reserved_var27 = 		cp.reserved_var27;
		this->reserved_var28 = 		cp.reserved_var28;
		this->reserved_var29 = 		cp.reserved_var29;
		this->reserved_var3 = 		cp.reserved_var3;
		this->reserved_var30 = 		cp.reserved_var30;
		this->reserved_var31 = 		cp.reserved_var31;
		this->reserved_var32 = 		cp.reserved_var32;
		this->reserved_var33 = 		cp.reserved_var33;
		this->reserved_var34 = 		cp.reserved_var34;
		this->reserved_var35 = 		cp.reserved_var35;
		this->reserved_var36 = 		cp.reserved_var36;
		this->reserved_var37 = 		cp.reserved_var37;
		this->reserved_var38 = 		cp.reserved_var38;
		this->reserved_var39 = 		cp.reserved_var39;
		this->reserved_var4 = 		cp.reserved_var4;
		this->reserved_var40 = 		cp.reserved_var40;
		this->reserved_var41 = 		cp.reserved_var41;
		this->reserved_var42 = 		cp.reserved_var42;
		this->reserved_var43 = 		cp.reserved_var43;
		this->reserved_var44 = 		cp.reserved_var44;
		this->reserved_var45 = 		cp.reserved_var45;
		this->reserved_var46 = 		cp.reserved_var46;
		this->reserved_var47 = 		cp.reserved_var47;
		this->reserved_var48 = 		cp.reserved_var48;
		this->reserved_var49 = 		cp.reserved_var49;
		this->reserved_var5 = 		cp.reserved_var5;
		this->reserved_var50 = 		cp.reserved_var50;
		this->reserved_var51 = 		cp.reserved_var51;
		this->reserved_var52 = 		cp.reserved_var52;
		this->reserved_var53 = 		cp.reserved_var53;
		this->reserved_var54 = 		cp.reserved_var54;
		this->reserved_var55 = 		cp.reserved_var55;
		this->reserved_var56 = 		cp.reserved_var56;
		this->reserved_var57 = 		cp.reserved_var57;
		this->reserved_var58 = 		cp.reserved_var58;
		this->reserved_var59 = 		cp.reserved_var59;
		this->reserved_var6 = 		cp.reserved_var6;
		this->reserved_var60 = 		cp.reserved_var60;
		this->reserved_var61 = 		cp.reserved_var61;
		this->reserved_var62 = 		cp.reserved_var62;
		this->reserved_var63 = 		cp.reserved_var63;
		this->reserved_var7 = 		cp.reserved_var7;
		this->reserved_var8 = 		cp.reserved_var8;
		this->reserved_var9 = 		cp.reserved_var9;
		this->rowheadflag = 		cp.rowheadflag;
		this->rowheight = 		cp.rowheight;
		this->SampleType = 		cp.SampleType;
		this->scrollbarenabled = 		cp.scrollbarenabled;
		this->shadowwidth = 		cp.shadowwidth;
		this->showcolscrollflag = 		cp.showcolscrollflag;
		this->ShowInOneLine = 		cp.ShowInOneLine;
		this->showrowcolor = 		cp.showrowcolor;
		this->showrowscrollflag = 		cp.showrowscrollflag;
		this->SortByDateAscend = 		cp.SortByDateAscend;
		this->StartTimeDay = 		cp.StartTimeDay;
		this->StartTimeHour = 		cp.StartTimeHour;
		this->StartTimeMinute = 		cp.StartTimeMinute;
		this->StartTimeMonth = 		cp.StartTimeMonth;
		this->StartTimeSecond = 		cp.StartTimeSecond;
		this->StartTimeType = 		cp.StartTimeType;
		this->StartTimeWeek = 		cp.StartTimeWeek;
		this->StartTimeWeekday = 		cp.StartTimeWeekday;
		this->StartTimeYear = 		cp.StartTimeYear;
		this->StatusShowFlag = 		cp.StatusShowFlag;
		this->tfr = 		cp.tfr;
		this->TimeBackColor = 		cp.TimeBackColor;
		this->TimeDifColor = 		cp.TimeDifColor;
		this->TimeEvenColor = 		cp.TimeEvenColor;
		this->TimeFontColor = 		cp.TimeFontColor;
		this->TimeOddColor = 		cp.TimeOddColor;
		this->TimeShowStyle = 		cp.TimeShowStyle;
		this->trig_key_size = 		cp.trig_key_size;
		this->TrigColExtend = 		cp.TrigColExtend;
		this->TrigSampleId = 		cp.TrigSampleId;
		this->ValueShowFlag = 		cp.ValueShowFlag;
		this->w = 		cp.w;
		this->x = 		cp.x;
		this->y = 		cp.y;
		return *this;
	}
};

class CHisTable_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
		out << m_Info.af;
		out << m_Info.allowdeleteflag;
		out << m_Info.allowinsetflag;
		out << m_Info.allowupdateflag;
		out << m_Info.AppNo;
		out << m_Info.backgroudcolor;
		out << m_Info.backgroudflag;
		out << m_Info.backgroudpic;
		out << m_Info.BaseTime;
		out << m_Info.BtnBackColor;
		out << m_Info.BtnFontColor;
		out << m_Info.BtnHeight;
		out << m_Info.BtnWidth;
		out << m_Info.cellshadestyle;
		out << m_Info.cellshapestyle;
		out << m_Info.colheadcolor;
		out << m_Info.colheadflag;
		out << m_Info.colheadheight;
		out << m_Info.dy_num;
		out << m_Info.EndTimeDay;
		out << m_Info.EndTimeHour;
		out << m_Info.EndTimeMinute;
		out << m_Info.EndTimeMonth;
		out << m_Info.EndTimeSecond;
		out << m_Info.EndTimeType;
		out << m_Info.EndTimeWeek;
		out << m_Info.EndTimeWeekday;
		out << m_Info.EndTimeYear;
		out << m_Info.evenrowcolor;
		out << m_Info.fc;
		out << m_Info.fieldnum;
		out << m_Info.fields;
		out << m_Info.fm;
		out << m_Info.fontcolor;
		out << m_Info.fontsize;
		out << m_Info.fonttype;
		out << m_Info.frameshadow;
		out << m_Info.frameshape;
		out << m_Info.gridflag;
		out << m_Info.h;
		out << m_Info.HisTableHeadColor;
		out << m_Info.HisTableHeadFontColor;
		out << m_Info.HisTableHeadFontSize;
		out << m_Info.HisTableHeadFontType;
		out << m_Info.HisTableHeadHeight;
		out << m_Info.id;
		out << m_Info.Interval;
		out << m_Info.IsByStep;
		out << m_Info.IsColumnTrig;
		out << m_Info.lc;
		out << m_Info.ls;
		out << m_Info.lw;
		out << m_Info.oddrowcolor;
		out << m_Info.p_AssFlag;
		out << m_Info.p_AutoChangeAppFlag;
		out << m_Info.p_DyColorFlag;
		out << m_Info.p_LevelEnd;
		out << m_Info.p_LevelStart;
		out << m_Info.p_NameString;
		out << m_Info.p_Plane;
		out << m_Info.p_RoundBox;
		out << m_Info.p_ShowModeMask;
		out << m_Info.QueryMode;
		out << m_Info.refreshinterval;
		out << m_Info.reserved_var0;
		out << m_Info.reserved_var1;
		out << m_Info.reserved_var10;
		out << m_Info.reserved_var11;
		out << m_Info.reserved_var12;
		out << m_Info.reserved_var13;
		out << m_Info.reserved_var14;
		out << m_Info.reserved_var15;
		out << m_Info.reserved_var16;
		out << m_Info.reserved_var17;
		out << m_Info.reserved_var18;
		out << m_Info.reserved_var19;
		out << m_Info.reserved_var2;
		out << m_Info.reserved_var20;
		out << m_Info.reserved_var21;
		out << m_Info.reserved_var22;
		out << m_Info.reserved_var23;
		out << m_Info.reserved_var24;
		out << m_Info.reserved_var25;
		out << m_Info.reserved_var26;
		out << m_Info.reserved_var27;
		out << m_Info.reserved_var28;
		out << m_Info.reserved_var29;
		out << m_Info.reserved_var3;
		out << m_Info.reserved_var30;
		out << m_Info.reserved_var31;
		out << m_Info.reserved_var32;
		out << m_Info.reserved_var33;
		out << m_Info.reserved_var34;
		out << m_Info.reserved_var35;
		out << m_Info.reserved_var36;
		out << m_Info.reserved_var37;
		out << m_Info.reserved_var38;
		out << m_Info.reserved_var39;
		out << m_Info.reserved_var4;
		out << m_Info.reserved_var40;
		out << m_Info.reserved_var41;
		out << m_Info.reserved_var42;
		out << m_Info.reserved_var43;
		out << m_Info.reserved_var44;
		out << m_Info.reserved_var45;
		out << m_Info.reserved_var46;
		out << m_Info.reserved_var47;
		out << m_Info.reserved_var48;
		out << m_Info.reserved_var49;
		out << m_Info.reserved_var5;
		out << m_Info.reserved_var50;
		out << m_Info.reserved_var51;
		out << m_Info.reserved_var52;
		out << m_Info.reserved_var53;
		out << m_Info.reserved_var54;
		out << m_Info.reserved_var55;
		out << m_Info.reserved_var56;
		out << m_Info.reserved_var57;
		out << m_Info.reserved_var58;
		out << m_Info.reserved_var59;
		out << m_Info.reserved_var6;
		out << m_Info.reserved_var60;
		out << m_Info.reserved_var61;
		out << m_Info.reserved_var62;
		out << m_Info.reserved_var63;
		out << m_Info.reserved_var7;
		out << m_Info.reserved_var8;
		out << m_Info.reserved_var9;
		out << m_Info.rowheadflag;
		out << m_Info.rowheight;
		out << m_Info.SampleType;
		out << m_Info.scrollbarenabled;
		out << m_Info.shadowwidth;
		out << m_Info.showcolscrollflag;
		out << m_Info.ShowInOneLine;
		out << m_Info.showrowcolor;
		out << m_Info.showrowscrollflag;
		out << m_Info.SortByDateAscend;
		out << m_Info.StartTimeDay;
		out << m_Info.StartTimeHour;
		out << m_Info.StartTimeMinute;
		out << m_Info.StartTimeMonth;
		out << m_Info.StartTimeSecond;
		out << m_Info.StartTimeType;
		out << m_Info.StartTimeWeek;
		out << m_Info.StartTimeWeekday;
		out << m_Info.StartTimeYear;
		out << m_Info.StatusShowFlag;
		out << m_Info.tfr;
		out << m_Info.TimeBackColor;
		out << m_Info.TimeDifColor;
		out << m_Info.TimeEvenColor;
		out << m_Info.TimeFontColor;
		out << m_Info.TimeOddColor;
		out << m_Info.TimeShowStyle;
		out << m_Info.trig_key_size;
		out << m_Info.TrigColExtend;
		out << m_Info.TrigSampleId;
		out << m_Info.ValueShowFlag;
		out << m_Info.w;
		out << m_Info.x;
		out << m_Info.y;
	}

	virtual void deserialize( QDataStream& out)
	{
		out >> m_Info.af;
		out >> m_Info.allowdeleteflag;
		out >> m_Info.allowinsetflag;
		out >> m_Info.allowupdateflag;
		out >> m_Info.AppNo;
		out >> m_Info.backgroudcolor;
		out >> m_Info.backgroudflag;
		out >> m_Info.backgroudpic;
		out >> m_Info.BaseTime;
		out >> m_Info.BtnBackColor;
		out >> m_Info.BtnFontColor;
		out >> m_Info.BtnHeight;
		out >> m_Info.BtnWidth;
		out >> m_Info.cellshadestyle;
		out >> m_Info.cellshapestyle;
		out >> m_Info.colheadcolor;
		out >> m_Info.colheadflag;
		out >> m_Info.colheadheight;
		out >> m_Info.dy_num;
		out >> m_Info.EndTimeDay;
		out >> m_Info.EndTimeHour;
		out >> m_Info.EndTimeMinute;
		out >> m_Info.EndTimeMonth;
		out >> m_Info.EndTimeSecond;
		out >> m_Info.EndTimeType;
		out >> m_Info.EndTimeWeek;
		out >> m_Info.EndTimeWeekday;
		out >> m_Info.EndTimeYear;
		out >> m_Info.evenrowcolor;
		out >> m_Info.fc;
		out >> m_Info.fieldnum;
		out >> m_Info.fields;
		out >> m_Info.fm;
		out >> m_Info.fontcolor;
		out >> m_Info.fontsize;
		out >> m_Info.fonttype;
		out >> m_Info.frameshadow;
		out >> m_Info.frameshape;
		out >> m_Info.gridflag;
		out >> m_Info.h;
		out >> m_Info.HisTableHeadColor;
		out >> m_Info.HisTableHeadFontColor;
		out >> m_Info.HisTableHeadFontSize;
		out >> m_Info.HisTableHeadFontType;
		out >> m_Info.HisTableHeadHeight;
		out >> m_Info.id;
		out >> m_Info.Interval;
		out >> m_Info.IsByStep;
		out >> m_Info.IsColumnTrig;
		out >> m_Info.lc;
		out >> m_Info.ls;
		out >> m_Info.lw;
		out >> m_Info.oddrowcolor;
		out >> m_Info.p_AssFlag;
		out >> m_Info.p_AutoChangeAppFlag;
		out >> m_Info.p_DyColorFlag;
		out >> m_Info.p_LevelEnd;
		out >> m_Info.p_LevelStart;
		out >> m_Info.p_NameString;
		out >> m_Info.p_Plane;
		out >> m_Info.p_RoundBox;
		out >> m_Info.p_ShowModeMask;
		out >> m_Info.QueryMode;
		out >> m_Info.refreshinterval;
		out >> m_Info.reserved_var0;
		out >> m_Info.reserved_var1;
		out >> m_Info.reserved_var10;
		out >> m_Info.reserved_var11;
		out >> m_Info.reserved_var12;
		out >> m_Info.reserved_var13;
		out >> m_Info.reserved_var14;
		out >> m_Info.reserved_var15;
		out >> m_Info.reserved_var16;
		out >> m_Info.reserved_var17;
		out >> m_Info.reserved_var18;
		out >> m_Info.reserved_var19;
		out >> m_Info.reserved_var2;
		out >> m_Info.reserved_var20;
		out >> m_Info.reserved_var21;
		out >> m_Info.reserved_var22;
		out >> m_Info.reserved_var23;
		out >> m_Info.reserved_var24;
		out >> m_Info.reserved_var25;
		out >> m_Info.reserved_var26;
		out >> m_Info.reserved_var27;
		out >> m_Info.reserved_var28;
		out >> m_Info.reserved_var29;
		out >> m_Info.reserved_var3;
		out >> m_Info.reserved_var30;
		out >> m_Info.reserved_var31;
		out >> m_Info.reserved_var32;
		out >> m_Info.reserved_var33;
		out >> m_Info.reserved_var34;
		out >> m_Info.reserved_var35;
		out >> m_Info.reserved_var36;
		out >> m_Info.reserved_var37;
		out >> m_Info.reserved_var38;
		out >> m_Info.reserved_var39;
		out >> m_Info.reserved_var4;
		out >> m_Info.reserved_var40;
		out >> m_Info.reserved_var41;
		out >> m_Info.reserved_var42;
		out >> m_Info.reserved_var43;
		out >> m_Info.reserved_var44;
		out >> m_Info.reserved_var45;
		out >> m_Info.reserved_var46;
		out >> m_Info.reserved_var47;
		out >> m_Info.reserved_var48;
		out >> m_Info.reserved_var49;
		out >> m_Info.reserved_var5;
		out >> m_Info.reserved_var50;
		out >> m_Info.reserved_var51;
		out >> m_Info.reserved_var52;
		out >> m_Info.reserved_var53;
		out >> m_Info.reserved_var54;
		out >> m_Info.reserved_var55;
		out >> m_Info.reserved_var56;
		out >> m_Info.reserved_var57;
		out >> m_Info.reserved_var58;
		out >> m_Info.reserved_var59;
		out >> m_Info.reserved_var6;
		out >> m_Info.reserved_var60;
		out >> m_Info.reserved_var61;
		out >> m_Info.reserved_var62;
		out >> m_Info.reserved_var63;
		out >> m_Info.reserved_var7;
		out >> m_Info.reserved_var8;
		out >> m_Info.reserved_var9;
		out >> m_Info.rowheadflag;
		out >> m_Info.rowheight;
		out >> m_Info.SampleType;
		out >> m_Info.scrollbarenabled;
		out >> m_Info.shadowwidth;
		out >> m_Info.showcolscrollflag;
		out >> m_Info.ShowInOneLine;
		out >> m_Info.showrowcolor;
		out >> m_Info.showrowscrollflag;
		out >> m_Info.SortByDateAscend;
		out >> m_Info.StartTimeDay;
		out >> m_Info.StartTimeHour;
		out >> m_Info.StartTimeMinute;
		out >> m_Info.StartTimeMonth;
		out >> m_Info.StartTimeSecond;
		out >> m_Info.StartTimeType;
		out >> m_Info.StartTimeWeek;
		out >> m_Info.StartTimeWeekday;
		out >> m_Info.StartTimeYear;
		out >> m_Info.StatusShowFlag;
		out >> m_Info.tfr;
		out >> m_Info.TimeBackColor;
		out >> m_Info.TimeDifColor;
		out >> m_Info.TimeEvenColor;
		out >> m_Info.TimeFontColor;
		out >> m_Info.TimeOddColor;
		out >> m_Info.TimeShowStyle;
		out >> m_Info.trig_key_size;
		out >> m_Info.TrigColExtend;
		out >> m_Info.TrigSampleId;
		out >> m_Info.ValueShowFlag;
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
		attr->name( "allowdeleteflag" );
		attr->value(QString::number(m_Info.allowdeleteflag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "allowinsetflag" );
		attr->value(QString::number(m_Info.allowinsetflag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "allowupdateflag" );
		attr->value(QString::number(m_Info.allowupdateflag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "AppNo" );
		attr->value(QString::number(m_Info.AppNo).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "backgroudcolor" );
		attr->value( m_Info.backgroudcolor.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "backgroudflag" );
		attr->value(QString::number(m_Info.backgroudflag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "backgroudpic" );
		attr->value( m_Info.backgroudpic.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "BaseTime" );
		attr->value(QString::number(m_Info.BaseTime).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "BtnBackColor" );
		attr->value(QString::number(m_Info.BtnBackColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "BtnFontColor" );
		attr->value(QString::number(m_Info.BtnFontColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "BtnHeight" );
		attr->value(QString::number(m_Info.BtnHeight).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "BtnWidth" );
		attr->value(QString::number(m_Info.BtnWidth).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "cellshadestyle" );
		attr->value(QString::number(m_Info.cellshadestyle).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "cellshapestyle" );
		attr->value( m_Info.cellshapestyle.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "colheadcolor" );
		attr->value( m_Info.colheadcolor.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "colheadflag" );
		attr->value( m_Info.colheadflag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "colheadheight" );
		attr->value(QString::number(m_Info.colheadheight).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "dy_num" );
		attr->value(QString::number(m_Info.dy_num).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeDay" );
		attr->value(QString::number(m_Info.EndTimeDay).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeHour" );
		attr->value(QString::number(m_Info.EndTimeHour).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeMinute" );
		attr->value(QString::number(m_Info.EndTimeMinute).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeMonth" );
		attr->value(QString::number(m_Info.EndTimeMonth).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeSecond" );
		attr->value(QString::number(m_Info.EndTimeSecond).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeType" );
		attr->value(QString::number(m_Info.EndTimeType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeWeek" );
		attr->value(QString::number(m_Info.EndTimeWeek).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeWeekday" );
		attr->value(QString::number(m_Info.EndTimeWeekday).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "EndTimeYear" );
		attr->value(QString::number(m_Info.EndTimeYear).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "evenrowcolor" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.evenrowcolor.red(),(int)m_Info.evenrowcolor.green(),(int)m_Info.evenrowcolor.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fc" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.fc.red(),(int)m_Info.fc.green(),(int)m_Info.fc.blue()).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fieldnum" );
		attr->value(QString::number(m_Info.fieldnum).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fields" );
		attr->value(QString::number(m_Info.fields).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fm" );
		attr->value(QString::number(m_Info.fm).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fontcolor" );
		attr->value( m_Info.fontcolor.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fontsize" );
		attr->value( m_Info.fontsize.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "fonttype" );
		attr->value( m_Info.fonttype.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "frameshadow" );
		attr->value( m_Info.frameshadow.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "frameshape" );
		attr->value( m_Info.frameshape.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "gridflag" );
		attr->value(QString::number(m_Info.gridflag).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "h" );
		attr->value(QString::number(m_Info.h).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "HisTableHeadColor" );
		attr->value(QString::number(m_Info.HisTableHeadColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "HisTableHeadFontColor" );
		attr->value(QString::number(m_Info.HisTableHeadFontColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "HisTableHeadFontSize" );
		attr->value(QString::number(m_Info.HisTableHeadFontSize).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "HisTableHeadFontType" );
		attr->value(QString::number(m_Info.HisTableHeadFontType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "HisTableHeadHeight" );
		attr->value(QString::number(m_Info.HisTableHeadHeight).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "id" );
		attr->value(QString::number(m_Info.id).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "Interval" );
		attr->value(QString::number(m_Info.Interval).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "IsByStep" );
		attr->value(QString::number(m_Info.IsByStep).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "IsColumnTrig" );
		attr->value(QString::number(m_Info.IsColumnTrig).toLocal8Bit().data());
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
		attr->name( "oddrowcolor" );
		attr->value(QString("%1,%2,%3").arg((int)m_Info.oddrowcolor.red(),(int)m_Info.oddrowcolor.green(),(int)m_Info.oddrowcolor.blue()).toLocal8Bit().data());
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
		attr->name( "p_RoundBox" );
		attr->value(QString("%1,%2,%3,%4").arg(QString::number(m_Info.p_RoundBox.left()),QString::number(m_Info.p_RoundBox.right()),QString::number(m_Info.p_RoundBox.top()),QString::number(m_Info.p_RoundBox.bottom())).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "p_ShowModeMask" );
		attr->value(QString::number(m_Info.p_ShowModeMask).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "QueryMode" );
		attr->value(QString::number(m_Info.QueryMode).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "refreshinterval" );
		attr->value( m_Info.refreshinterval.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var0" );
		attr->value(QString::number(m_Info.reserved_var0).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var1" );
		attr->value(QString::number(m_Info.reserved_var1).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var10" );
		attr->value(QString::number(m_Info.reserved_var10).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var11" );
		attr->value(QString::number(m_Info.reserved_var11).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var12" );
		attr->value(QString::number(m_Info.reserved_var12).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var13" );
		attr->value(QString::number(m_Info.reserved_var13).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var14" );
		attr->value(QString::number(m_Info.reserved_var14).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var15" );
		attr->value(QString::number(m_Info.reserved_var15).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var16" );
		attr->value(QString::number(m_Info.reserved_var16).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var17" );
		attr->value(QString::number(m_Info.reserved_var17).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var18" );
		attr->value(QString::number(m_Info.reserved_var18).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var19" );
		attr->value(QString::number(m_Info.reserved_var19).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var2" );
		attr->value(QString::number(m_Info.reserved_var2).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var20" );
		attr->value(QString::number(m_Info.reserved_var20).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var21" );
		attr->value(QString::number(m_Info.reserved_var21).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var22" );
		attr->value(QString::number(m_Info.reserved_var22).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var23" );
		attr->value(QString::number(m_Info.reserved_var23).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var24" );
		attr->value(QString::number(m_Info.reserved_var24).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var25" );
		attr->value(QString::number(m_Info.reserved_var25).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var26" );
		attr->value(QString::number(m_Info.reserved_var26).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var27" );
		attr->value(QString::number(m_Info.reserved_var27).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var28" );
		attr->value(QString::number(m_Info.reserved_var28).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var29" );
		attr->value(QString::number(m_Info.reserved_var29).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var3" );
		attr->value(QString::number(m_Info.reserved_var3).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var30" );
		attr->value(QString::number(m_Info.reserved_var30).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var31" );
		attr->value(QString::number(m_Info.reserved_var31).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var32" );
		attr->value(QString::number(m_Info.reserved_var32).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var33" );
		attr->value(QString::number(m_Info.reserved_var33).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var34" );
		attr->value(QString::number(m_Info.reserved_var34).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var35" );
		attr->value(QString::number(m_Info.reserved_var35).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var36" );
		attr->value(QString::number(m_Info.reserved_var36).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var37" );
		attr->value(QString::number(m_Info.reserved_var37).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var38" );
		attr->value(QString::number(m_Info.reserved_var38).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var39" );
		attr->value(QString::number(m_Info.reserved_var39).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var4" );
		attr->value(QString::number(m_Info.reserved_var4).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var40" );
		attr->value(QString::number(m_Info.reserved_var40).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var41" );
		attr->value(QString::number(m_Info.reserved_var41).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var42" );
		attr->value(QString::number(m_Info.reserved_var42).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var43" );
		attr->value(QString::number(m_Info.reserved_var43).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var44" );
		attr->value(QString::number(m_Info.reserved_var44).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var45" );
		attr->value(QString::number(m_Info.reserved_var45).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var46" );
		attr->value(QString::number(m_Info.reserved_var46).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var47" );
		attr->value(QString::number(m_Info.reserved_var47).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var48" );
		attr->value(QString::number(m_Info.reserved_var48).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var49" );
		attr->value(QString::number(m_Info.reserved_var49).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var5" );
		attr->value(QString::number(m_Info.reserved_var5).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var50" );
		attr->value(QString::number(m_Info.reserved_var50).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var51" );
		attr->value(QString::number(m_Info.reserved_var51).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var52" );
		attr->value(QString::number(m_Info.reserved_var52).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var53" );
		attr->value(QString::number(m_Info.reserved_var53).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var54" );
		attr->value(QString::number(m_Info.reserved_var54).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var55" );
		attr->value(QString::number(m_Info.reserved_var55).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var56" );
		attr->value(QString::number(m_Info.reserved_var56).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var57" );
		attr->value(QString::number(m_Info.reserved_var57).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var58" );
		attr->value(QString::number(m_Info.reserved_var58).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var59" );
		attr->value(QString::number(m_Info.reserved_var59).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var6" );
		attr->value(QString::number(m_Info.reserved_var6).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var60" );
		attr->value(QString::number(m_Info.reserved_var60).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var61" );
		attr->value(QString::number(m_Info.reserved_var61).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var62" );
		attr->value(QString::number(m_Info.reserved_var62).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var63" );
		attr->value(QString::number(m_Info.reserved_var63).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var7" );
		attr->value(QString::number(m_Info.reserved_var7).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var8" );
		attr->value(QString::number(m_Info.reserved_var8).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "reserved_var9" );
		attr->value(QString::number(m_Info.reserved_var9).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "rowheadflag" );
		attr->value( m_Info.rowheadflag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "rowheight" );
		attr->value(QString::number(m_Info.rowheight).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "SampleType" );
		attr->value(QString::number(m_Info.SampleType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "scrollbarenabled" );
		attr->value(QString::number(m_Info.scrollbarenabled).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "shadowwidth" );
		attr->value( m_Info.shadowwidth.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "showcolscrollflag" );
		attr->value( m_Info.showcolscrollflag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "ShowInOneLine" );
		attr->value(QString::number(m_Info.ShowInOneLine).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "showrowcolor" );
		attr->value( m_Info.showrowcolor.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "showrowscrollflag" );
		attr->value( m_Info.showrowscrollflag.toLocal8Bit().data() );
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "SortByDateAscend" );
		attr->value(QString::number(m_Info.SortByDateAscend).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeDay" );
		attr->value(QString::number(m_Info.StartTimeDay).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeHour" );
		attr->value(QString::number(m_Info.StartTimeHour).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeMinute" );
		attr->value(QString::number(m_Info.StartTimeMinute).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeMonth" );
		attr->value(QString::number(m_Info.StartTimeMonth).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeSecond" );
		attr->value(QString::number(m_Info.StartTimeSecond).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeType" );
		attr->value(QString::number(m_Info.StartTimeType).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeWeek" );
		attr->value(QString::number(m_Info.StartTimeWeek).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeWeekday" );
		attr->value(QString::number(m_Info.StartTimeWeekday).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StartTimeYear" );
		attr->value(QString::number(m_Info.StartTimeYear).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "StatusShowFlag" );
		attr->value(QString::number(m_Info.StatusShowFlag).toLocal8Bit().data());
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
		attr->name( "TimeBackColor" );
		attr->value(QString::number(m_Info.TimeBackColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TimeDifColor" );
		attr->value(QString::number(m_Info.TimeDifColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TimeEvenColor" );
		attr->value(QString::number(m_Info.TimeEvenColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TimeFontColor" );
		attr->value(QString::number(m_Info.TimeFontColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TimeOddColor" );
		attr->value(QString::number(m_Info.TimeOddColor).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TimeShowStyle" );
		attr->value(QString::number(m_Info.TimeShowStyle).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "trig_key_size" );
		attr->value(QString::number(m_Info.trig_key_size).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TrigColExtend" );
		attr->value(QString::number(m_Info.TrigColExtend).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "TrigSampleId" );
		attr->value(QString::number(m_Info.TrigSampleId).toLocal8Bit().data());
		node->append_attribute(attr) ;

		attr = new xml_attribute<char>();
		attr->name( "ValueShowFlag" );
		attr->value(QString::number(m_Info.ValueShowFlag).toLocal8Bit().data());
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

		attr = node->first_attribute("allowdeleteflag");
		if(attr)
		{
			 m_AttrInfo["allowdeleteflag"] = QString(attr->value());
			 m_Info.allowdeleteflag = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("allowinsetflag");
		if(attr)
		{
			 m_AttrInfo["allowinsetflag"] = QString(attr->value());
			 m_Info.allowinsetflag = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("allowupdateflag");
		if(attr)
		{
			 m_AttrInfo["allowupdateflag"] = QString(attr->value());
			 m_Info.allowupdateflag = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("AppNo");
		if(attr)
		{
			 m_AttrInfo["AppNo"] = QString(attr->value());
			 m_Info.AppNo = QString(attr->value()).toULongLong();
		}

		attr = node->first_attribute("backgroudcolor");
		if(attr)
		{
			 m_AttrInfo["backgroudcolor"] = QString(attr->value());
			 m_Info.backgroudcolor = QObject::tr(attr->value());
		}

		attr = node->first_attribute("backgroudflag");
		if(attr)
		{
			 m_AttrInfo["backgroudflag"] = QString(attr->value());
			 m_Info.backgroudflag = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("backgroudpic");
		if(attr)
		{
			 m_AttrInfo["backgroudpic"] = QString(attr->value());
			 m_Info.backgroudpic = QObject::tr(attr->value());
		}

		attr = node->first_attribute("BaseTime");
		if(attr)
		{
			 m_AttrInfo["BaseTime"] = QString(attr->value());
			 m_Info.BaseTime = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("BtnBackColor");
		if(attr)
		{
			 m_AttrInfo["BtnBackColor"] = QString(attr->value());
			 m_Info.BtnBackColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("BtnFontColor");
		if(attr)
		{
			 m_AttrInfo["BtnFontColor"] = QString(attr->value());
			 m_Info.BtnFontColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("BtnHeight");
		if(attr)
		{
			 m_AttrInfo["BtnHeight"] = QString(attr->value());
			 m_Info.BtnHeight = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("BtnWidth");
		if(attr)
		{
			 m_AttrInfo["BtnWidth"] = QString(attr->value());
			 m_Info.BtnWidth = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("cellshadestyle");
		if(attr)
		{
			 m_AttrInfo["cellshadestyle"] = QString(attr->value());
			 m_Info.cellshadestyle = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("cellshapestyle");
		if(attr)
		{
			 m_AttrInfo["cellshapestyle"] = QString(attr->value());
			 m_Info.cellshapestyle = QObject::tr(attr->value());
		}

		attr = node->first_attribute("colheadcolor");
		if(attr)
		{
			 m_AttrInfo["colheadcolor"] = QString(attr->value());
			 m_Info.colheadcolor = QObject::tr(attr->value());
		}

		attr = node->first_attribute("colheadflag");
		if(attr)
		{
			 m_AttrInfo["colheadflag"] = QString(attr->value());
			 m_Info.colheadflag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("colheadheight");
		if(attr)
		{
			 m_AttrInfo["colheadheight"] = QString(attr->value());
			 m_Info.colheadheight = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("dy_num");
		if(attr)
		{
			 m_AttrInfo["dy_num"] = QString(attr->value());
			 m_Info.dy_num = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeDay");
		if(attr)
		{
			 m_AttrInfo["EndTimeDay"] = QString(attr->value());
			 m_Info.EndTimeDay = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeHour");
		if(attr)
		{
			 m_AttrInfo["EndTimeHour"] = QString(attr->value());
			 m_Info.EndTimeHour = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeMinute");
		if(attr)
		{
			 m_AttrInfo["EndTimeMinute"] = QString(attr->value());
			 m_Info.EndTimeMinute = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeMonth");
		if(attr)
		{
			 m_AttrInfo["EndTimeMonth"] = QString(attr->value());
			 m_Info.EndTimeMonth = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeSecond");
		if(attr)
		{
			 m_AttrInfo["EndTimeSecond"] = QString(attr->value());
			 m_Info.EndTimeSecond = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeType");
		if(attr)
		{
			 m_AttrInfo["EndTimeType"] = QString(attr->value());
			 m_Info.EndTimeType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeWeek");
		if(attr)
		{
			 m_AttrInfo["EndTimeWeek"] = QString(attr->value());
			 m_Info.EndTimeWeek = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeWeekday");
		if(attr)
		{
			 m_AttrInfo["EndTimeWeekday"] = QString(attr->value());
			 m_Info.EndTimeWeekday = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("EndTimeYear");
		if(attr)
		{
			 m_AttrInfo["EndTimeYear"] = QString(attr->value());
			 m_Info.EndTimeYear = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("evenrowcolor");
		if(attr)
		{
			 m_AttrInfo["evenrowcolor"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.evenrowcolor.setRed(lstColor[0].toInt());
				 m_Info.evenrowcolor.setGreen(lstColor[1].toInt());
				 m_Info.evenrowcolor.setBlue(lstColor[2].toInt());
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

		attr = node->first_attribute("fieldnum");
		if(attr)
		{
			 m_AttrInfo["fieldnum"] = QString(attr->value());
			 m_Info.fieldnum = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fields");
		if(attr)
		{
			 m_AttrInfo["fields"] = QString(attr->value());
			 m_Info.fields = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fm");
		if(attr)
		{
			 m_AttrInfo["fm"] = QString(attr->value());
			 m_Info.fm = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("fontcolor");
		if(attr)
		{
			 m_AttrInfo["fontcolor"] = QString(attr->value());
			 m_Info.fontcolor = QObject::tr(attr->value());
		}

		attr = node->first_attribute("fontsize");
		if(attr)
		{
			 m_AttrInfo["fontsize"] = QString(attr->value());
			 m_Info.fontsize = QObject::tr(attr->value());
		}

		attr = node->first_attribute("fonttype");
		if(attr)
		{
			 m_AttrInfo["fonttype"] = QString(attr->value());
			 m_Info.fonttype = QObject::tr(attr->value());
		}

		attr = node->first_attribute("frameshadow");
		if(attr)
		{
			 m_AttrInfo["frameshadow"] = QString(attr->value());
			 m_Info.frameshadow = QObject::tr(attr->value());
		}

		attr = node->first_attribute("frameshape");
		if(attr)
		{
			 m_AttrInfo["frameshape"] = QString(attr->value());
			 m_Info.frameshape = QObject::tr(attr->value());
		}

		attr = node->first_attribute("gridflag");
		if(attr)
		{
			 m_AttrInfo["gridflag"] = QString(attr->value());
			 m_Info.gridflag = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("h");
		if(attr)
		{
			 m_AttrInfo["h"] = QString(attr->value());
			 m_Info.h = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("HisTableHeadColor");
		if(attr)
		{
			 m_AttrInfo["HisTableHeadColor"] = QString(attr->value());
			 m_Info.HisTableHeadColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("HisTableHeadFontColor");
		if(attr)
		{
			 m_AttrInfo["HisTableHeadFontColor"] = QString(attr->value());
			 m_Info.HisTableHeadFontColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("HisTableHeadFontSize");
		if(attr)
		{
			 m_AttrInfo["HisTableHeadFontSize"] = QString(attr->value());
			 m_Info.HisTableHeadFontSize = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("HisTableHeadFontType");
		if(attr)
		{
			 m_AttrInfo["HisTableHeadFontType"] = QString(attr->value());
			 m_Info.HisTableHeadFontType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("HisTableHeadHeight");
		if(attr)
		{
			 m_AttrInfo["HisTableHeadHeight"] = QString(attr->value());
			 m_Info.HisTableHeadHeight = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("id");
		if(attr)
		{
			 m_AttrInfo["id"] = QString(attr->value());
			 m_Info.id = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("Interval");
		if(attr)
		{
			 m_AttrInfo["Interval"] = QString(attr->value());
			 m_Info.Interval = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("IsByStep");
		if(attr)
		{
			 m_AttrInfo["IsByStep"] = QString(attr->value());
			 m_Info.IsByStep = QString(attr->value()).toInt();
		}

		attr = node->first_attribute("IsColumnTrig");
		if(attr)
		{
			 m_AttrInfo["IsColumnTrig"] = QString(attr->value());
			 m_Info.IsColumnTrig = QString(attr->value()).toInt();
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

		attr = node->first_attribute("oddrowcolor");
		if(attr)
		{
			 m_AttrInfo["oddrowcolor"] = QString(attr->value());
			 QStringList lstColor = QString(attr->value()).split(',');
			 if(lstColor.count() > 3)
			 {
				 m_Info.oddrowcolor.setRed(lstColor[0].toInt());
				 m_Info.oddrowcolor.setGreen(lstColor[1].toInt());
				 m_Info.oddrowcolor.setBlue(lstColor[2].toInt());
			 }
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

		attr = node->first_attribute("QueryMode");
		if(attr)
		{
			 m_AttrInfo["QueryMode"] = QString(attr->value());
			 m_Info.QueryMode = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("refreshinterval");
		if(attr)
		{
			 m_AttrInfo["refreshinterval"] = QString(attr->value());
			 m_Info.refreshinterval = QObject::tr(attr->value());
		}

		attr = node->first_attribute("reserved_var0");
		if(attr)
		{
			 m_AttrInfo["reserved_var0"] = QString(attr->value());
			 m_Info.reserved_var0 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var1");
		if(attr)
		{
			 m_AttrInfo["reserved_var1"] = QString(attr->value());
			 m_Info.reserved_var1 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var10");
		if(attr)
		{
			 m_AttrInfo["reserved_var10"] = QString(attr->value());
			 m_Info.reserved_var10 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var11");
		if(attr)
		{
			 m_AttrInfo["reserved_var11"] = QString(attr->value());
			 m_Info.reserved_var11 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var12");
		if(attr)
		{
			 m_AttrInfo["reserved_var12"] = QString(attr->value());
			 m_Info.reserved_var12 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var13");
		if(attr)
		{
			 m_AttrInfo["reserved_var13"] = QString(attr->value());
			 m_Info.reserved_var13 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var14");
		if(attr)
		{
			 m_AttrInfo["reserved_var14"] = QString(attr->value());
			 m_Info.reserved_var14 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var15");
		if(attr)
		{
			 m_AttrInfo["reserved_var15"] = QString(attr->value());
			 m_Info.reserved_var15 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var16");
		if(attr)
		{
			 m_AttrInfo["reserved_var16"] = QString(attr->value());
			 m_Info.reserved_var16 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var17");
		if(attr)
		{
			 m_AttrInfo["reserved_var17"] = QString(attr->value());
			 m_Info.reserved_var17 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var18");
		if(attr)
		{
			 m_AttrInfo["reserved_var18"] = QString(attr->value());
			 m_Info.reserved_var18 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var19");
		if(attr)
		{
			 m_AttrInfo["reserved_var19"] = QString(attr->value());
			 m_Info.reserved_var19 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var2");
		if(attr)
		{
			 m_AttrInfo["reserved_var2"] = QString(attr->value());
			 m_Info.reserved_var2 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var20");
		if(attr)
		{
			 m_AttrInfo["reserved_var20"] = QString(attr->value());
			 m_Info.reserved_var20 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var21");
		if(attr)
		{
			 m_AttrInfo["reserved_var21"] = QString(attr->value());
			 m_Info.reserved_var21 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var22");
		if(attr)
		{
			 m_AttrInfo["reserved_var22"] = QString(attr->value());
			 m_Info.reserved_var22 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var23");
		if(attr)
		{
			 m_AttrInfo["reserved_var23"] = QString(attr->value());
			 m_Info.reserved_var23 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var24");
		if(attr)
		{
			 m_AttrInfo["reserved_var24"] = QString(attr->value());
			 m_Info.reserved_var24 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var25");
		if(attr)
		{
			 m_AttrInfo["reserved_var25"] = QString(attr->value());
			 m_Info.reserved_var25 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var26");
		if(attr)
		{
			 m_AttrInfo["reserved_var26"] = QString(attr->value());
			 m_Info.reserved_var26 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var27");
		if(attr)
		{
			 m_AttrInfo["reserved_var27"] = QString(attr->value());
			 m_Info.reserved_var27 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var28");
		if(attr)
		{
			 m_AttrInfo["reserved_var28"] = QString(attr->value());
			 m_Info.reserved_var28 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var29");
		if(attr)
		{
			 m_AttrInfo["reserved_var29"] = QString(attr->value());
			 m_Info.reserved_var29 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var3");
		if(attr)
		{
			 m_AttrInfo["reserved_var3"] = QString(attr->value());
			 m_Info.reserved_var3 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var30");
		if(attr)
		{
			 m_AttrInfo["reserved_var30"] = QString(attr->value());
			 m_Info.reserved_var30 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var31");
		if(attr)
		{
			 m_AttrInfo["reserved_var31"] = QString(attr->value());
			 m_Info.reserved_var31 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var32");
		if(attr)
		{
			 m_AttrInfo["reserved_var32"] = QString(attr->value());
			 m_Info.reserved_var32 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var33");
		if(attr)
		{
			 m_AttrInfo["reserved_var33"] = QString(attr->value());
			 m_Info.reserved_var33 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var34");
		if(attr)
		{
			 m_AttrInfo["reserved_var34"] = QString(attr->value());
			 m_Info.reserved_var34 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var35");
		if(attr)
		{
			 m_AttrInfo["reserved_var35"] = QString(attr->value());
			 m_Info.reserved_var35 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var36");
		if(attr)
		{
			 m_AttrInfo["reserved_var36"] = QString(attr->value());
			 m_Info.reserved_var36 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var37");
		if(attr)
		{
			 m_AttrInfo["reserved_var37"] = QString(attr->value());
			 m_Info.reserved_var37 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var38");
		if(attr)
		{
			 m_AttrInfo["reserved_var38"] = QString(attr->value());
			 m_Info.reserved_var38 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var39");
		if(attr)
		{
			 m_AttrInfo["reserved_var39"] = QString(attr->value());
			 m_Info.reserved_var39 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var4");
		if(attr)
		{
			 m_AttrInfo["reserved_var4"] = QString(attr->value());
			 m_Info.reserved_var4 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var40");
		if(attr)
		{
			 m_AttrInfo["reserved_var40"] = QString(attr->value());
			 m_Info.reserved_var40 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var41");
		if(attr)
		{
			 m_AttrInfo["reserved_var41"] = QString(attr->value());
			 m_Info.reserved_var41 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var42");
		if(attr)
		{
			 m_AttrInfo["reserved_var42"] = QString(attr->value());
			 m_Info.reserved_var42 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var43");
		if(attr)
		{
			 m_AttrInfo["reserved_var43"] = QString(attr->value());
			 m_Info.reserved_var43 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var44");
		if(attr)
		{
			 m_AttrInfo["reserved_var44"] = QString(attr->value());
			 m_Info.reserved_var44 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var45");
		if(attr)
		{
			 m_AttrInfo["reserved_var45"] = QString(attr->value());
			 m_Info.reserved_var45 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var46");
		if(attr)
		{
			 m_AttrInfo["reserved_var46"] = QString(attr->value());
			 m_Info.reserved_var46 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var47");
		if(attr)
		{
			 m_AttrInfo["reserved_var47"] = QString(attr->value());
			 m_Info.reserved_var47 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var48");
		if(attr)
		{
			 m_AttrInfo["reserved_var48"] = QString(attr->value());
			 m_Info.reserved_var48 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var49");
		if(attr)
		{
			 m_AttrInfo["reserved_var49"] = QString(attr->value());
			 m_Info.reserved_var49 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var5");
		if(attr)
		{
			 m_AttrInfo["reserved_var5"] = QString(attr->value());
			 m_Info.reserved_var5 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var50");
		if(attr)
		{
			 m_AttrInfo["reserved_var50"] = QString(attr->value());
			 m_Info.reserved_var50 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var51");
		if(attr)
		{
			 m_AttrInfo["reserved_var51"] = QString(attr->value());
			 m_Info.reserved_var51 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var52");
		if(attr)
		{
			 m_AttrInfo["reserved_var52"] = QString(attr->value());
			 m_Info.reserved_var52 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var53");
		if(attr)
		{
			 m_AttrInfo["reserved_var53"] = QString(attr->value());
			 m_Info.reserved_var53 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var54");
		if(attr)
		{
			 m_AttrInfo["reserved_var54"] = QString(attr->value());
			 m_Info.reserved_var54 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var55");
		if(attr)
		{
			 m_AttrInfo["reserved_var55"] = QString(attr->value());
			 m_Info.reserved_var55 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var56");
		if(attr)
		{
			 m_AttrInfo["reserved_var56"] = QString(attr->value());
			 m_Info.reserved_var56 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var57");
		if(attr)
		{
			 m_AttrInfo["reserved_var57"] = QString(attr->value());
			 m_Info.reserved_var57 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var58");
		if(attr)
		{
			 m_AttrInfo["reserved_var58"] = QString(attr->value());
			 m_Info.reserved_var58 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var59");
		if(attr)
		{
			 m_AttrInfo["reserved_var59"] = QString(attr->value());
			 m_Info.reserved_var59 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var6");
		if(attr)
		{
			 m_AttrInfo["reserved_var6"] = QString(attr->value());
			 m_Info.reserved_var6 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var60");
		if(attr)
		{
			 m_AttrInfo["reserved_var60"] = QString(attr->value());
			 m_Info.reserved_var60 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var61");
		if(attr)
		{
			 m_AttrInfo["reserved_var61"] = QString(attr->value());
			 m_Info.reserved_var61 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var62");
		if(attr)
		{
			 m_AttrInfo["reserved_var62"] = QString(attr->value());
			 m_Info.reserved_var62 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var63");
		if(attr)
		{
			 m_AttrInfo["reserved_var63"] = QString(attr->value());
			 m_Info.reserved_var63 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var7");
		if(attr)
		{
			 m_AttrInfo["reserved_var7"] = QString(attr->value());
			 m_Info.reserved_var7 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var8");
		if(attr)
		{
			 m_AttrInfo["reserved_var8"] = QString(attr->value());
			 m_Info.reserved_var8 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("reserved_var9");
		if(attr)
		{
			 m_AttrInfo["reserved_var9"] = QString(attr->value());
			 m_Info.reserved_var9 = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("rowheadflag");
		if(attr)
		{
			 m_AttrInfo["rowheadflag"] = QString(attr->value());
			 m_Info.rowheadflag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("rowheight");
		if(attr)
		{
			 m_AttrInfo["rowheight"] = QString(attr->value());
			 m_Info.rowheight = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("SampleType");
		if(attr)
		{
			 m_AttrInfo["SampleType"] = QString(attr->value());
			 m_Info.SampleType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("scrollbarenabled");
		if(attr)
		{
			 m_AttrInfo["scrollbarenabled"] = QString(attr->value());
			 m_Info.scrollbarenabled = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("shadowwidth");
		if(attr)
		{
			 m_AttrInfo["shadowwidth"] = QString(attr->value());
			 m_Info.shadowwidth = QObject::tr(attr->value());
		}

		attr = node->first_attribute("showcolscrollflag");
		if(attr)
		{
			 m_AttrInfo["showcolscrollflag"] = QString(attr->value());
			 m_Info.showcolscrollflag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("ShowInOneLine");
		if(attr)
		{
			 m_AttrInfo["ShowInOneLine"] = QString(attr->value());
			 m_Info.ShowInOneLine = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("showrowcolor");
		if(attr)
		{
			 m_AttrInfo["showrowcolor"] = QString(attr->value());
			 m_Info.showrowcolor = QObject::tr(attr->value());
		}

		attr = node->first_attribute("showrowscrollflag");
		if(attr)
		{
			 m_AttrInfo["showrowscrollflag"] = QString(attr->value());
			 m_Info.showrowscrollflag = QObject::tr(attr->value());
		}

		attr = node->first_attribute("SortByDateAscend");
		if(attr)
		{
			 m_AttrInfo["SortByDateAscend"] = QString(attr->value());
			 m_Info.SortByDateAscend = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeDay");
		if(attr)
		{
			 m_AttrInfo["StartTimeDay"] = QString(attr->value());
			 m_Info.StartTimeDay = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeHour");
		if(attr)
		{
			 m_AttrInfo["StartTimeHour"] = QString(attr->value());
			 m_Info.StartTimeHour = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeMinute");
		if(attr)
		{
			 m_AttrInfo["StartTimeMinute"] = QString(attr->value());
			 m_Info.StartTimeMinute = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeMonth");
		if(attr)
		{
			 m_AttrInfo["StartTimeMonth"] = QString(attr->value());
			 m_Info.StartTimeMonth = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeSecond");
		if(attr)
		{
			 m_AttrInfo["StartTimeSecond"] = QString(attr->value());
			 m_Info.StartTimeSecond = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeType");
		if(attr)
		{
			 m_AttrInfo["StartTimeType"] = QString(attr->value());
			 m_Info.StartTimeType = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeWeek");
		if(attr)
		{
			 m_AttrInfo["StartTimeWeek"] = QString(attr->value());
			 m_Info.StartTimeWeek = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeWeekday");
		if(attr)
		{
			 m_AttrInfo["StartTimeWeekday"] = QString(attr->value());
			 m_Info.StartTimeWeekday = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StartTimeYear");
		if(attr)
		{
			 m_AttrInfo["StartTimeYear"] = QString(attr->value());
			 m_Info.StartTimeYear = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("StatusShowFlag");
		if(attr)
		{
			 m_AttrInfo["StatusShowFlag"] = QString(attr->value());
			 m_Info.StatusShowFlag = QString(attr->value()).toUInt();
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

		attr = node->first_attribute("TimeBackColor");
		if(attr)
		{
			 m_AttrInfo["TimeBackColor"] = QString(attr->value());
			 m_Info.TimeBackColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TimeDifColor");
		if(attr)
		{
			 m_AttrInfo["TimeDifColor"] = QString(attr->value());
			 m_Info.TimeDifColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TimeEvenColor");
		if(attr)
		{
			 m_AttrInfo["TimeEvenColor"] = QString(attr->value());
			 m_Info.TimeEvenColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TimeFontColor");
		if(attr)
		{
			 m_AttrInfo["TimeFontColor"] = QString(attr->value());
			 m_Info.TimeFontColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TimeOddColor");
		if(attr)
		{
			 m_AttrInfo["TimeOddColor"] = QString(attr->value());
			 m_Info.TimeOddColor = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TimeShowStyle");
		if(attr)
		{
			 m_AttrInfo["TimeShowStyle"] = QString(attr->value());
			 m_Info.TimeShowStyle = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("trig_key_size");
		if(attr)
		{
			 m_AttrInfo["trig_key_size"] = QString(attr->value());
			 m_Info.trig_key_size = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TrigColExtend");
		if(attr)
		{
			 m_AttrInfo["TrigColExtend"] = QString(attr->value());
			 m_Info.TrigColExtend = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("TrigSampleId");
		if(attr)
		{
			 m_AttrInfo["TrigSampleId"] = QString(attr->value());
			 m_Info.TrigSampleId = QString(attr->value()).toUInt();
		}

		attr = node->first_attribute("ValueShowFlag");
		if(attr)
		{
			 m_AttrInfo["ValueShowFlag"] = QString(attr->value());
			 m_Info.ValueShowFlag = QString(attr->value()).toUInt();
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
	HisTable_Struct getInfo()
	{
		return m_Info;
	}
protected:

	HisTable_Struct m_Info ;
};

#endif
