
#include "resource.h"

CResource* CResource::s_Resource = NULL;

CResource* CResource::instance()
{
	if (!s_Resource)
	{
		s_Resource = new CResource;
	}
	return s_Resource;
}

void CResource::init()
{
	// 初始化数据信息，将测点信息加入内存
	for (int i = 0 ; i < 10 ; i++)
	{
		SMeasureInfo info;
		info.resourceID = i;
		info.name = QString::number(i);
		info.type = 1;

		m_MeaInfoMap.insert(info.resourceID,info);
	}
}

void CResource::clear()
{
	QMutexLocker lock(&m_Mutex);
	m_MeaInfoMap.clear();
}

SMeasureInfo CResource::getInfo(quint64 id)
{
	QMutexLocker lock(&m_Mutex);
	if (m_MeaInfoMap.find(id) != m_MeaInfoMap.end())
	{
		return m_MeaInfoMap[id];
	}
	else
	{
		return SMeasureInfo();
	}
}

QVariant CResource::getValue(quint64 id)
{
	SMeasureInfo info = getInfo(id);
	return info.value;
}

QMap<quint64,QVariant> CResource::getValues(const QList<quint64>& vecIDs)
{
	QMap<quint64,QVariant> mapValues;
	QMutexLocker lock(&m_Mutex);
	foreach(quint64 id,vecIDs)
	{
		if (m_MeaInfoMap.find(id) != m_MeaInfoMap.end())
		{
			mapValues.insert(id, m_MeaInfoMap[id].value);
		}
	}
	return mapValues;
}

QList<quint64> CResource::getResourceIDs()
{
	return m_MeaInfoMap.keys();
}

void CResource::setValue(quint64 id ,const QVariant& value)
{
	QMutexLocker lock(&m_Mutex);
	m_MeaInfoMap[id].value = value;
}

QMap<quint64,SMeasureInfo> CResource::getValues()
{
	QMutexLocker lock(&m_Mutex);
	return m_MeaInfoMap;
}