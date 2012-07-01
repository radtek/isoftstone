
/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: proxy.h
** ժҪ: �Ҽ��˵�������
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ����
** �������: 2011.11.1
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ����      2011.11.1   V1.0      ����
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
