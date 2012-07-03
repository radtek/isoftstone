
#include "edcc-global.h"
#include "server.h"
#include "task.h"
#include "setting.h"
#include "config.h"

#include <QThreadPool>

CService::CService()
{
	init();
}

void CService::init()
{
	QString configFile = CConfig::instance()->getConfigDir() + CONFIG_FILE;
	CSettings cst(configFile);
	int nPort = cst.getValue("SERVER","PORT","10001").toInt();
	// ���������˿�
	m_localServer.listen(QHostAddress::Any,nPort);
	// �������߳�

	// ǰ�òɼ��߳�

	// ��ʱ�����߳�

	// ������Ϣ�����߳�

	// ��ʷ���ݱ����߳�

	// ��ʷ��澯��ѯ�߳�

	// Э�������
}

void CService::start()
{
	for (int i = 0 ; i < m_Threads.size() ; i++)
	{
		m_Threads[i]->start();
	}
}

void CService::stop()
{
	for (int i = 0 ; i < m_Threads.size() ; i++)
	{
		m_Threads[i]->exit();
	}
}