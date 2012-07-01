
/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: dtext.h
** 摘要: 右键行为插件管理类
**       
**
** 当前版本: 1.0.0.0
** 作者:  刘瑞功
** 完成日期: 2011.11.1
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 刘瑞功      2011.11.1   V1.0      创建
**
****************************************************************************/

#ifndef CONTEXT_LOADER_H
#define CONTEXT_LOADER_H

#include <QtCore>

#include "pluginbase.h"
#include "pluginmgrbase.h"
#include "pluginaction.h"

class CMLoader : public CPluginMgrBase
{
public:

	CMLoader();

	IPluginAction* getAction(int nCommand);
	IPluginAction* getAction(const QString& strCommand);
	void destory();

private:

	QMap<int,IPluginAction*>	m_ActionMap;
	QMap<QString,int>			m_CommandMap;
};


#endif