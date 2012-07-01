
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <map>
#include <QVector>
#include <QVariant>
#include <QMutex>
#include <QMutexLocker>

/* ���ڱ����ڴ����� 
   ���ڽ������ݵ���ʾ�������ֲ��ԣ�
   ��һ�������̸߳��ݹ�Լ�����걨�����ݺ�ֱ��Post�������棬�������Խ�ʡ�ڴ���������Ǵ˲������ױ�����ʷ���ݡ�
   ����������̸߳��ݹ�Լ�����걨�����ݺ�ŵ��ڴ汣�棬�������涨ʱ������ȥ��ȡ���ݲ���ʾ���˴�����Ҫ�����̡߳�

   ���⣬��ʷ�߳�Ҳ�ᶨʱȥ��ȡ�ڴ����ݲ����浽�ļ��У����Ҹ���ʱ����и���ͳ�ơ�
		 ����һ���̸߳�������λ��ʵʱ�������󣬲��ҽ����ݴ��������λ����
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