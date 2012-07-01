/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: pluginwindow.h
** ժҪ: Ӧ�ó��������������������
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2011.11.2
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.11.2   V1.0      ����
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