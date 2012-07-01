
/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: dtext.h
** ժҪ: �Ҽ���Ϊ���������
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