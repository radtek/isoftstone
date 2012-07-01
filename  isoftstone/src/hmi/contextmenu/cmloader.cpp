
#include <QCoreApplication>
#include <QDir>
#include <QLibrary>
#include <QDebug>

#include "cmloader.h"


CMLoader::CMLoader()
{
	
}

IPluginAction* CMLoader::getAction(int nCommand)
{
	if (m_ActionMap.contains(nCommand))
	{
		return m_ActionMap[nCommand];
	}
	return NULL;
}

IPluginAction* CMLoader::getAction(const QString& strCommand)
{
	return getAction(m_CommandMap[strCommand]);
}

void CMLoader::destory()
{
	QMapIterator<int,IPluginAction*> iter(m_ActionMap);
	while(iter.hasNext())
	{
		iter.next();

		iter.value()->destroy();
		delete iter.value();
	}
}