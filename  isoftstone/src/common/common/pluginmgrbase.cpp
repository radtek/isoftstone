
#include "pluginmgrbase.h"

int  CPluginMgrBase::loadBatchDLL(const QString& dirName,const QString& filter,const QString& strFun)
{
	QDir dir(dirName, filter, QDir::Name, QDir::Files);
	QStringList pluginList = dir.entryList();
	QStringList currentDirPlugin;	//存储当前目录插件	

	int nSuccess = 0;
	foreach(QString pluginName, pluginList)
	{
		bool bRet = loadDLL(pluginName,strFun);
		if (bRet)
		{
			nSuccess++;
		}
	}
	return nSuccess;
}
bool CPluginMgrBase::loadDLL(const QString& strPlugin,const QString& strFun)
{
#ifdef Q_WS_WIN
	QString ext = ".dll";
#else
	QString ext = ".so";
#endif

	DLLFun fun = reinterpret_cast<DLLFun>(QLibrary::resolve(strPlugin, strFun.toLocal8Bit().data()));
	IPluginBase* pBase = NULL;
	if(fun != NULL)
	{
		pBase = (*fun)();
		if (pBase != NULL)	//导出插件成功
		{
			qDebug() << QObject::tr("加载行为插件:") << strPlugin << "\n";
			m_pluginMap.insert(std::make_pair(strPlugin,pBase));
			return true;
		}
	}
	return false;
}

void CPluginMgrBase::destory()
{
	std::map<QString,IPluginBase*>::iterator iter = m_pluginMap.begin();
	for (;iter != m_pluginMap.end() ; iter++)
	{
		IPluginBase* pBase = iter->second;
		pBase->destroy();
	}
	m_pluginMap.clear();
}

IPluginBase* CPluginMgrBase::getPlugin(const QString& strPlugin)
{
	if (m_pluginMap.find(strPlugin) != m_pluginMap.end())
	{
		return m_pluginMap[strPlugin];
	}
	else
	{
		return NULL;
	}
}