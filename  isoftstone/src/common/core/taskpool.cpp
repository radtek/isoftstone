
#include <vector>
#include "TaskPool.h"

using namespace std;

namespace HiRTDB
{

CTaskPool::CTaskPool(const std::string& StrName)
{
	m_PoolName = StrName;
	m_nextTaskID = 0;
}

CTaskPool::~CTaskPool()
{
	clear();
}

CTaskWrapper* CTaskPool::getTask(int taskID ,bool erase )
{
	CTaskWrapper* task = NULL;
	m_TaskMutex.lock();
	if (!m_TaskPool.empty())
	{
		TaskPoolContainer::iterator iter = m_TaskPool.find(taskID);
		// 获取第一个任务
		if (taskID == 0)
		{
			iter = m_TaskPool.begin();
		}
		task = iter->second;
		if (erase)
		{
			m_TaskPool.erase(iter);
		}
	}
	m_TaskMutex.unlock();
	return task;
}

// 获得等待被执行的任务
CTaskWrapper* CTaskPool::getWaitingTask()
{
	CTaskWrapper* task = NULL;
	m_TaskMutex.lock();
	if (!m_TaskPool.empty())
	{
		for (TaskPoolContainer::iterator iter = m_TaskPool.begin();
			iter != m_TaskPool.end() ; iter++)
		{
			if (iter->second->isTaskNeededExecute())
			{
				task = iter->second;
				// 如果为一次性任务则从队列中删除，由外部释放内存
				if (task->getPersistent() == HiRTDB::eOnceTime)
				{
					m_TaskPool.erase(iter);
				}
				break;
			}
		}
	}
	m_TaskMutex.unlock();
	return task;
}

void CTaskPool::getWaitingTasks(std::list<CTaskWrapper*>& waitingTasks)
{
	CTaskWrapper* task = NULL;
	m_TaskMutex.lock();
	if (!m_TaskPool.empty())
	{
		for (TaskPoolContainer::iterator iter = m_TaskPool.begin();
			iter != m_TaskPool.end() ; )
		{
			if (iter->second->isTaskNeededExecute())
			{
				task = iter->second;
				waitingTasks.push_back(task);
				// 如果为一次性任务则从队列中删除，由外部释放内存
				if (task->getPersistent() == HiRTDB::eOnceTime)
				{
					m_TaskPool.erase(iter++);
				}
				else
				{
					++iter;
				}
			}
			else
			{
				++iter;
			}
		}
	}
	m_TaskMutex.unlock();
}

void CTaskPool::registerTask(CTaskWrapper* task)
{
	m_TaskMutex.lock();
	task->setTaskID(++m_nextTaskID);
	if (task->getTaskID() != 0)
	{
		m_TaskPool.insert(std::make_pair(task->getTaskID(),task));
	}
	m_TaskMutex.unlock();
}

void CTaskPool::removeTask()
{
	m_TaskMutex.lock();
	if (!m_TaskPool.empty())
	{
		delete m_TaskPool.begin()->second;
		m_TaskPool.erase(m_TaskPool.begin());
	}
	m_TaskMutex.unlock();
}

void CTaskPool::removeTask(CTaskWrapper* task)
{
	m_TaskRubbish.push_back(task->getTaskID());
	clearRubbish();
}

void CTaskPool::clearRubbish()
{
	m_TaskMutex.lock();
	for (std::vector<int>::iterator iter = m_TaskRubbish.begin();
		iter != m_TaskRubbish.end();
		iter++)
	{
		TaskPoolContainer::iterator iter2 = m_TaskPool.find(*iter);
		if (iter2 != m_TaskPool.end())
		{
			delete iter2->second;
			iter2->second = NULL;
			m_TaskPool.erase(iter2);
		}
	}
	m_TaskRubbish.clear();
	m_TaskMutex.unlock();
}

void CTaskPool::clear()
{
	if (m_TaskMutex.tryLock())
	{
		for (TaskPoolContainer::iterator iter = m_TaskPool.begin();
			iter != m_TaskPool.end();
			iter++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_TaskPool.clear();
	}
	m_TaskMutex.unlock();
}

bool CTaskPool::empty()
{
	bool bRet = true;;
	m_TaskMutex.lock();
	bRet = m_TaskPool.empty();
	m_TaskMutex.unlock();
	return bRet;
}

int CTaskPool::size()
{
	int bRet = 0;;
	m_TaskMutex.lock();
	bRet = m_TaskPool.size();
	m_TaskMutex.unlock();
	return bRet;
}


}