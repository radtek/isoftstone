/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: pluginmanager.cpp
** ժҪ: Ӧ�ó��������������ܶ�̬��
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2011.11.1
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.10.13   V1.0      ����
** ������	   2011.11.1    V1.0      �޸�
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
	IPluginBase* getPlugin(const QString& pluginName);											//�õ��������
	bool loadPlugin(const QString& pluginName);													//���ز��
	bool setPluginEnabled(const QString& pluginName, bool bEnabled);							//���ý��ò��
	QStringList loadEnabledPlugins();															//�����ö�ȡ���ò��
	void loadDir();																				//��Ŀ¼�ж�ȡ���
	void destroy();																				//���ٲ��
	void clearPluginList();																		//�����ǰ����б�
	void initMenuBar(QMenuBar* pMenuBar);														//��ʼ���˵�
	void setDataPointer(const QMap<int,void*>& pointerMap,bool bApp);							//��������Դ
	void setParentWindow(QWidget* pParentWindow);												//�����Ӵ���ָ�뵽���
	void savePluginDescription(const QString& pluginName, const QString& description);			//����������
	void savePluginStatus(const QString& pluginName, const bool& bEnabled);						//������״̬
	char* getEnvStr(const char*);																//��û�������

public:

	QMap<QString, PluginInfo> m_pluginInfo; //�洢���������Ϣ

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
