
#ifndef __TIMEVALUE_ICE
#define __TIMEVALUE_ICE

module LCSH
{
	
	struct Time
	{
		short year;
		short month;
		short day;
		short hour;
		short minite;
		short second;
		short milisecond;
	};

	interface TimeFormat
	{
		string format();
	};

	class TimeOfDay
	{
		short hour;
		short minute;
		short second;

	};

	class Date
	{
		short year;
		short month;
		short day;
	};

	// ��ֻ�����̳з�ʽ�����ܶ�̳�
	class DateTime extends TimeOfDay
	{
		short year;
		short month;
		short day;
	};
};

#endif
