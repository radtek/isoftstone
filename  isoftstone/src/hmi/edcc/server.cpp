
#include "server.h"
#include "task.h"

CService::CService()
{
	init();
}

void CService::init()
{
	// 增加任务和线程
	CThread* pThread = NULL;
	pThread = new CThread;
	pThread->addTask(new CDealDataTask());
	m_Threads.push_back(pThread);

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