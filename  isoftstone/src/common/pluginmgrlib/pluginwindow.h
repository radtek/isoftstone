/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: pluginwindow.h
** 摘要: 应用程序界面加载器界面管理类
**       
**
** 当前版本: 1.0.0.0
** 作者:  杜寅辰
** 完成日期: 2011.11.2
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 杜寅辰      2011.11.2   V1.0      创建
**
****************************************************************************/

#ifndef PLUGINWINDOW_H
#define PLUGINWINDOW_H

#include <QtGlobal>
#include <QWidget>
#include <QPushButton>

#include "pluginmanager.h"
#include "tablewidget.h"

class QGraphicsItem;
class QMenuBar;

#ifdef Q_WS_WIN
#ifdef  PLUGINMGR_LIB
#define EXPORT_PLUGINMGR _declspec(dllexport)
#else 
#define EXPORT_PLUGINMGR _declspec(dllimport)  
#endif
#else
#define EXPORT_PLUGINMGR
#endif 

class EXPORT_PLUGINMGR CPluginWindow : public QWidget
{
	Q_OBJECT

public:

	CPluginWindow(QWidget *parent = 0);
	virtual ~CPluginWindow(){};
	virtual QObject* getObject();
	virtual IPluginBase* getPlugin(const QString& pluginName);	
	virtual void setMenuBar(QMenuBar* pMenuBar);				
	virtual void setParentWindow(QWidget* pParentWindow); 
	virtual void setDataPointer(const QMap<int,void*>& pointerMap,bool bApp = true);															
private slots:

	void refresh();
	void changeStatus(int row, int column);
	void saveDescription(int row, int column);

private:

	void updateTable();
	void init();
	void createConnect();
	void initWidget();
	
private:

	CPluginManager m_pluginManager;
	CTableWidget* tableWidget;
	QPushButton* refreshButton;
	QPushButton* closeButton;
};

#endif