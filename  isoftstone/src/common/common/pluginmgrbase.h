
#ifndef PLUGIN_MGR_BASE_H
#define PLUGIN_MGR_BASE_H

#include <map>
#include <QtCore>

#include "common.h"
#include "pluginbase.h"

// 插件管理基础类
class EXPORT_COMMON CPluginMgrBase
{
public:

	int  loadBatchDLL(const QString& dirName,const QString& filter,const QString& strFun);
	bool loadDLL(const QString& strPlugin,const QString& strFun);
	IPluginBase* getPlugin(const QString& strPlugin);
	void destory();

protected:

	typedef IPluginBase* (*DLLFun)();

	std::map<QString,IPluginBase*>	m_pluginMap;
};

#endif