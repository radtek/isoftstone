
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