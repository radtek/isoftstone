#ifndef GFILE_STRUCT_H
#define GFILE_STRUCT_H

class ACLine_Struct
{
public:
	uint  af;
	quint64  app1;
	quint64  app2;
	QPolygonF  d;
	QColor  fc;
	uint   fm;
	uint   id;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	QString  link;
	uint   ls;
	uint   lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	int  state1;
	int  state2;
	uint  switchapp;
	QThree  tfr;
	int  voltype1;
	int  voltype2;
};

class ACLineEnd_Struct
{
public:
	uint  af;
	quint64  app;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
};

class Bar_Struct
{
public:
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
};

class Bay_Struct
{
public:
	QString  conf;
	QString  devicegroup;
	QString  devref;
	quint64  keyid;
	QString  name;
	uint  type;
	qreal  x;
	qreal  y;
};

class Bus_Struct
{
public:
	uint  af;
	quint64  app;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x1;
	qreal  x2;
	qreal  y1;
	qreal  y2;
};

class CBreaker_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class CT_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class Capacitor_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	QString  index;
	quint64  keyid;
	QString  keyname;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  p_AutoChangeAppFlag;
	QString  rg;
	QString  transform;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Capacitor_P_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Capacitor_S_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class Clock_Struct
{
public:
	uint  af;
	QString  BorderColor;
	QColor  fc;
	uint  fm;
	uint  h;
	QString  HasBorder;
	QString  HourHandColor;
	uint  id;
	QString  IsDigital;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  MinHandColor;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	QString  SecHandColor;
	uint  switchapp;
	QThree  tfr;
	QString  TimeDifference;
	int  w;
	qreal  x;
	qreal  y;
};

class ConnectLine_Struct
{
public:
	uint  af;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	QColor  lc;
	QString  link;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  switchapp;
	QThree  tfr;
};

class Curve_Struct
{
public:
	uint  af;
	QString  devref;
	uint  fversion;
	uint  h;
	uint  id;
	uint  switch_rep;
	int  w;
	qreal  x;
	qreal  y;
};

class DText_Struct
{
public:
	uint  af;
	quint64  app;
	uint  dotlength;
	QColor  fc;
	uint  ff;
	uint  fm;
	uint  fs;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DataFrom;
	int  p_DataLowerLimit;
	uint  p_DataSetFlag;
	int  p_DataUpperLimit;
	uint  p_DyColorFlag;
	int  p_FontDeltaX;
	int  p_FontDeltaY;
	int  p_FontHeight;
	uint  p_FontInterval;
	uint  p_FontWidth;
	bool  p_IsAbs;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_MatrixFontFlag;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_RowInterval;
	uint  p_ShowModeMask;
	uint  p_ShowSignFlag;
	uint  p_ZoomMaxLevel;
	uint  state;
	QThree  tfr;
	QString  ts;
	uint  type;
	int  voltype;
	int  wm;
	qreal  x;
	qreal  y;
};

class DcDot_Struct
{
public:
	uint  af;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  switchapp;
	QThree  tfr;
};

class DcLine_Struct
{
public:
	uint  af;
	quint64  app1;
	quint64  app2;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype1;
	int  voltype2;
};

class Dial_Struct
{
public:
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
};

class Disconnector_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class DollyBreaker_Struct
{
public:
	uint  af;
	quint64  app1;
	quint64  app2;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	uint  ls;
	uint  lw;
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
	int  state1;
	int  state2;
	uint  switchapp;
	QThree  tfr;
	int  voltype1;
	int  voltype2;
	qreal  x;
	qreal  y;
};

class Dynamic_Struct
{
public:
	QString  abstime;
	quint64  app;
	QString  curve_type;
	QString  distant;
	QString  distantunit;
	QString  endtime;
	quint64  keyid;
	QString  mode;
	QString  period;
	QString  starttime;
	uint  type;
};

class EnergyConsumer_Struct
{
public:
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  name;
};

class Entity_Struct
{
public:
	QString  ds;
	QColor  lc;
	QString  legend;
	uint  ls;
	uint  lw;
	QString  title;
	QString  y_type;
};

class Field_Struct
{
public:
};

class Generator_Struct
{
public:
	QString  devref;
	QColor  fc;
	uint  fm;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	qreal  x;
	qreal  y;
};

class Grid_Struct
{
public:
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
};

class GroundDisconnector_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class HisTable_Struct
{
public:
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
};

class InterfaceLine_Struct
{
public:
	uint  af;
	quint64  app1;
	quint64  app2;
	QPolygonF  d;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	int  state1;
	int  state2;
	uint  switchapp;
	QThree  tfr;
	int  voltype1;
	int  voltype2;
};

class Layer_Struct
{
public:
	uint  h;
	uint  id;
	int  w;
	qreal  x;
	qreal  y;
};

class Legend_Struct
{
public:
	QColor  fc;
	uint  ff;
	uint  fs;
	QString  fw;
	qreal  x;
	qreal  y;
};

class Merge_Struct
{
public:
	uint  af;
	uint  id;
	uint  p_AssFlag;
	QString  p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_NameString;
	uint  p_ShowModeMask;
};

class Other_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Pie_Struct
{
public:
	uint  _3d_mark;
	uint  af;
	QString  app0;
	quint64  app1;
	quint64  app2;
	QString  color0;
	QString  color1;
	QString  color2;
	QColor  fc;
	uint  fm;
	uint  h;
	uint  id;
	QString  keyid0;
	quint64  keyid1;
	quint64  keyid2;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  num;
	QString  number;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QString  p_ReportType0;
	uint  p_ReportType1;
	uint  p_ReportType2;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  show_mark;
	QString  state0;
	int  state1;
	int  state2;
	uint  switchapp;
	QThree  tfr;
	uint  thickness;
	QString  voltype0;
	int  voltype1;
	int  voltype2;
	int  w;
	qreal  x;
	qreal  y;
};

class PowerFlow_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class Protect_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	QString  index;
	quint64  keyid;
	QString  keyname;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  p_AutoChangeAppFlag;
	QString  rg;
	QString  transform;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Reactor_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	QString  index;
	quint64  keyid;
	QString  keyname;
	QColor  lc;
	uint  ls;
	uint  lw;
	QString  p_AutoChangeAppFlag;
	QString  rg;
	QString  transform;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Reactor_P_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class Reactor_S_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class RectifierInverter_Struct
{
public:
	uint  af;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree  tfr;
	qreal  x;
	qreal  y;
};

class Sensitive_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	QString  link;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal  y;
};

class State_Struct
{
public:
	uint  af;
	quint64  app;
	QString  devref;
	QColor  fc;
	uint  fm;
	uint  id;
	quint64  keyid;
	QColor  lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect  p_RoundBox;
	uint  p_ShowModeMask;
	uint  state;
	uint  switchapp;
	QThree  tfr;
	int  voltype;
	qreal  x;
	qreal                               y;
};

class Status_Struct
{
public:
	uint                                 af;
	quint64                                app;
	QString                                devref;
	QColor    fc;
	uint     fm;
	uint     id;
	quint64    keyid;
	QColor    lc;
	uint     ls;
	uint     lw;
	uint     p_AssFlag;
	uint     p_DyColorFlag;
	uint     p_LevelEnd;
	uint     p_LevelStart;
	QString    p_MultiSelect;
	uint     p_NameString;
	uint     p_Plane;
	uint     p_ReportType;
	QRect    p_RoundBox;
	uint     p_ShowModeMask;
	uint     state;
	uint     switchapp;
	QThree    tfr;
	int     voltype;
	qreal  x;
	qreal  y;
};

class Table_Struct
{
public:
	QString    ahref;
	QColor    fc;
	uint     h;
	QString    hastree;
	int     w;
	qreal  x;
	qreal  y;
};

class Terminal_Struct
{
public:
	uint     af;
	QString    devref;
	QColor    fc;
	uint     fm;
	uint     id;
	quint64    keyid;
	QColor    lc;
	uint     ls;
	uint     lw;
	uint     p_AssFlag;
	uint     p_DyColorFlag;
	uint     p_LevelEnd;
	uint     p_LevelStart;
	uint     p_NameString;
	uint     p_Plane;
	uint     p_ReportType;
	QRect    p_RoundBox;
	uint     p_ShowModeMask;
	uint     switchapp;
	QThree    tfr;
	qreal  x;
	qreal  y;
};

class Text_Struct
{
public:
	uint     af;
	QColor    fc;
	uint     ff;
	uint     fm;
	uint     fs;
	uint     id;
	QColor    lc;
	uint     ls;
	uint     lw;
	uint     p_AssFlag;
	uint     p_DyColorFlag;
	int     p_FontDeltaX;
	int     p_FontDeltaY;
	int     p_FontHeight;
	uint     p_FontInterval;
	uint  p_FontWidth;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_MatrixFontFlag;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_RowInterval;
	uint  p_ShowModeMask;
	uint  p_ZoomMaxLevel;
	uint  switchapp;
	QThree    tfr;
	QString    ts;
	int  wm;
	qreal  x;
	qreal  y;
};

class Transformer2_Struct
{
public:
	QString    devref;
	QColor    fc;
	uint  fm;
	quint64    keyid1;
	quint64    keyid2;
	QColor    lc;
	uint  ls;
	uint  lw;
        uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	uint  p_ReportType3;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	int  state1;
	int  state2;
	int  state3;
	uint  switchapp;
	QThree    tfr;
	int  voltype1;
	int  voltype2;
	int  voltype3;
	qreal  x;
	qreal  y;
};

class Transformer3_Struct
{
public:
	uint  af;
	quint64    app1;
	quint64    app2;
	quint64    app3;
	QString    devref;
	QColor    fc;
	uint  fm;
	uint  id;
	quint64    keyid1;
	quint64    keyid2;
	quint64    keyid3;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType1;
	uint  p_ReportType2;
	uint  p_ReportType3;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	int  state1;
	int  state2;
	int  state3;
	uint  switchapp;
	QThree    tfr;
	int  voltype1;
	int  voltype2;
	int  voltype3;
	qreal  x;
	qreal  y;
};

class X_axis_Struct
{
public:
	QString    abs_time;
	QString    end;
	QColor    fc;
	uint  ff;
	QString    format;
	uint  fs;
	QString    fw;
	QString    int_time;
	QString    int_time_value;
	QString    mainspace;
	QString    run;
	QString    scale;
	QString    show;
	QString    span;
	QString    start;
	QString    subspace;
	QString    unit;
};

class Y_axis_Struct
{
public:
	QString    autowithlimit;
	QString    decimal;
	QColor    fc;
	uint  ff;
	uint  fs;
	QString    fw;
	QString    isinteger;
	QString    main_auto;
	QString    mainspace;
	QString    max;
	QString    maxrate;
	QString    min;
	QString    minrate;
	QString    multi_axis_def;
	QString    show;
	QString    subspace;
};

class Zxddd_Struct
{
public:
	uint  af;
	QString    devref;
	QColor    fc;
	uint  fm;
	uint  id;
	quint64    keyid;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	uint  p_ReportType;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
	qreal  x;
	qreal  y;
};

class Circle_Struct
{
public:
	uint  af;
	QString    cx;
	QString    cy;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	QString    r;
	uint  switchapp;
	QThree    tfr;
};

class Circlearc_Struct
{
public:
	QString    a1;
	QString    a2;
	uint  af;
	QString    cx;
	QString    cy;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	QString    p_ArcShape;
	uint  p_AssFlag;
	QString    p_DrawFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	QString    r;
	uint  switchapp;
	QThree    tfr;
};

class Diamond_Struct
{
public:
	uint  af;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;
};

class Ellipse_Struct
{
public:
	uint  af;
	QString    cx;
	QString    cy;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString    p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  rx;
	uint  ry;
	QThree    tfr;
};

class Handline_Struct
{
public:
	uint  af;
	QPolygonF    d;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  switchapp;
	QThree    tfr;
};

class Image_Struct
{
public:
	uint  af;
	QString    ahref;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	QString    p_AutoChangeAppFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_ShowStyle;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;
};

class Line_Struct
{
public:
	uint  af;
	QPolygonF    d;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  switchapp;
	QThree    tfr;
	int  x1;
	int  x2;
	int  y1;
	int  y2;
};

class Poke_Struct
{
public:
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
};

class Polygon_Struct
{
public:
	uint  af;
	QPolygonF    d;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
};

class Polyline_Struct
{
public:
	uint  af;
	QPolygonF    d;
	QColor    fc;
	uint  fm;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_EndArrowSize;
	uint  p_EndArrowType;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShowModeMask;
	uint  p_StartArrowSize;
	uint  p_StartArrowType;
	uint  switchapp;
	QThree    tfr;
};

class Rect_Struct
{
public:
	uint  af;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;
};

class Roundrect_Struct
{
public:
	uint  af;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  rx;
	uint  ry;
	uint  switchapp;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;
};

class Triangle_Struct
{
public:
	uint  af;
	QColor    fc;
	uint  fm;
	uint  h;
	uint  id;
	QColor    lc;
	uint  ls;
	uint  lw;
	uint  p_AssFlag;
	uint  p_DyColorFlag;
	uint  p_LevelEnd;
	uint  p_LevelStart;
	uint  p_NameString;
	uint  p_Plane;
	QRect    p_RoundBox;
	uint  p_ShadowType;
	uint  p_ShowModeMask;
	uint  switchapp;
	QThree    tfr;
	int  w;
	qreal  x;
	qreal  y;
};

class UiContext_Struct
{
public:
};

#endif
