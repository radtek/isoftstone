
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <map>
#include <QVector>
#include <QVariant>
#include <QMutex>
#include <QMutexLocker>

/* 用于保存内存数据 
   对于界面数据的显示，有两种策略：
   其一：接收线程根据规约处理完报文数据后直接Post给主界面，这样可以节省内存操作，但是此操作不易保存历史数据。
   其二：接收线程根据规约处理完报文数据后放到内存保存，由主界面定时器主动去获取数据并显示，此处不需要另外线程。

   另外，历史线程也会定时去获取内存数据并保存到文件中，并且根据时间进行各类统计。
		 还有一个线程负责处理上位机实时数据请求，并且将数据打包发给上位机。
*/

struct SMeasureInfo
{
	SMeasureInfo()
	{
		resourceID = 0;
		type = -1;
	}
	quint64		resourceID;
	float		upper;
	float		lower;
	QString		name;
	int			type;
	QVariant	value;
};

class CResource 
{
public :

	static CResource* instance();

	void init();

	SMeasureInfo getInfo(quint64 id);

	QVariant	getValue(quint64 id);

	QMap<quint64,QVariant> getValues(const QList<quint64>& vecIDs);

	void		setValue(quint64 id ,const QVariant& value);

	QMap<quint64,SMeasureInfo> getValues();

	QList<quint64> getResourceIDs();

	void clear();

private:

	CResource(){};

private:

	QMap<quint64,SMeasureInfo>	m_MeaInfoMap;

	QMutex		m_Mutex;

	static CResource* s_Resource;
};

#endif