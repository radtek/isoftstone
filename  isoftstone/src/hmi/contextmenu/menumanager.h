
/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: proxy.h
** 摘要: 右键菜单代理类
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

#ifndef PROXY_MENU_H
#define PROXY_MENU_H

#include <QtGui>

#include "pluginaction.h"
#include "menuloader.h"
#include "cmloader.h"

#ifdef WIN32
#ifdef MENULIB 
#define EXPORT_MENU _declspec(dllexport)
#else 
#define EXPORT_MENU _declspec(dllimport)  
#endif
#else
#define EXPORT_MENU
#endif 

class EXPORT_MENU CMenuManager : public QObject
{
    Q_OBJECT

public:

	CMenuManager(QObject* parent = NULL);
	virtual ~CMenuManager();

public:																														

	virtual void init() ;

	virtual void destroy() ;

	virtual QMenu* getContextActions(int nMetaType, qint64 nAppType) ;	

	virtual IPluginAction* getPluginAction(const QString& strCommand); 

public slots:

	void onActionClick();

private:

	CMenuLoader*			m_MenuLoader;
	CMLoader*				m_ActionLoader;
	QWidget*				m_Parent;
};

#endif
