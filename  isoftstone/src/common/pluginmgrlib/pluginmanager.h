/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: pluginmanager.cpp
** 摘要: 应用程序界面加载器功能动态库
**       
**
** 当前版本: 1.0.0.0
** 作者:  杜寅辰
** 完成日期: 2011.11.1
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 杜寅辰      2011.10.13   V1.0      创建
** 杜寅辰	   2011.11.1    V1.0      修改
**
****************************************************************************/
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QtGui>

#include "pluginbase.h"
#include "pluginapp.h"
#include "enum.h"


struct  PluginInfo
{
	bool bStatus;
	QString description;
	QIcon icon;
} ;


class CPluginManager
{
public:

	CPluginManager();
	~CPluginManager();
	IPluginBase* getPlugin(const QString& pluginName);											//得到插件窗口
	bool loadPlugin(const QString& pluginName);													//加载插件
	bool setPluginEnabled(const QString& pluginName, bool bEnabled);							//启用禁用插件
	QStringList loadEnabledPlugins();															//从配置读取可用插件
	void loadDir();																				//从目录中读取插件
	void destroy();																				//销毁插件
	void clearPluginList();																		//清除当前插件列表
	void initMenuBar(QMenuBar* pMenuBar);														//初始化菜单
	void setDataPointer(const QMap<int,void*>& pointerMap,bool bApp);							//设置数据源
	void setParentWindow(QWidget* pParentWindow);												//设置子窗体指针到插件
	void savePluginDescription(const QString& pluginName, const QString& description);			//保存插件描述
	void savePluginStatus(const QString& pluginName, const bool& bEnabled);						//保存插件状态
	char* getEnvStr(const char*);																//获得环境变量

public:

	QMap<QString, PluginInfo> m_pluginInfo; //存储插件加载信息

	QMap<QString, PluginInfo> getPluginInfo();	

private:

	void loadMenuBar(IPluginBase* pPluginlib);

private:

	typedef IPluginBase* (*DLLFun)();	

	QMenuBar* m_pMenuBar;

	QMap<QString, IPluginBase*> m_pluginMap;

	QWidget* m_pParent;
};

#endif
