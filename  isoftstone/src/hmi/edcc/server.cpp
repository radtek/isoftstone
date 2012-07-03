
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
	// 启动监听端口
	m_localServer.listen(QHostAddress::Any,nPort);
	// 创建主线程

	// 前置采集线程

	// 定时传送线程

	// 命令消息处理线程

	// 历史数据保存线程

	// 历史与告警查询线程

	// 协议管理类
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