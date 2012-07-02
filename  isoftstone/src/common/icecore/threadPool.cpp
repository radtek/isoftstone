
#include <Ice/Ice.h>
#include <cstdlib>
#include <iterator>
#include <stdio.h>

#include "llogger.h"
#include "stringlist.h"
#include "histring.h"
#include "threadwrapper.h"
#include "threadpool.h"

using namespace std;

namespace HiRTDB
{

CThreadWorker::CThreadWorker(CThreadPool* threadPool,const std::string& StrName):CThreadWrapper(StrName)
{
	m_threadPool = threadPool;
	m_tasks.clear();
	max_tasks_num = 10;
	setRunTime(IceUtil::Time::seconds(10));
}

void CThreadWorker::work()
{
	m_threadPool->m_canUsedWorkerNum++;
	m_waitingTask = true;
	CThreadWrapper::wait(m_threadPool->m_poolMonitor);
	m_threadPool->m_canUsedWorkerNum--;
	m_waitingTask = false;
	if (m_tasks.size() > 0)
	{
		try
		{
			for (std::list<CTaskWrapper*>::iterator iter = m_tasks.begin();
													iter != m_tasks.end();
													iter++)
			{
				CTaskWrapper* task = *iter;
				task->runTimerTask();
				if (task->getPersistent() == HiRTDB::eOnceTime)
				{
					delete task;
				}
				task = NULL;
			}
			m_tasks.clear();
			
		}
		catch(const std::exception& e)
		{
			HI_LOG4CPLUS_ERROR("ThreadWorker:run uncaught exception:\n" << e.what());
		} 
		catch(...)
		{
			HI_LOG4CPLUS_ERROR("ThreadWorker:run uncaught exception:\n" );
		}
		
	}
	
	sleep(IceUtil::Time::milliSeconds(50));
	
}

void CThreadWorker::setMaxTasks(int max_num)
{
	max_tasks_num = max_num;
}

int CThreadWorker::getMaxTasks()
{
	return max_tasks_num;
}

void CThreadWorker::addTask(CTaskWrapper* task)
{
	m_tasks.push_back(task);
	HI_LOG4CPLUS_INFO(this->getThreadName() << "����ִ������..." << task->getTaskName());
}

void CThreadWorker::exit()
{
	CThreadWrapper::notifyAll(m_threadPool->m_poolMonitor);
	CThreadWrapper::exit();
} 


IceUtil::Mutex CThreadPool::m_InstanceMutex;
CThreadPool* CThreadPool::sm_Instance = NULL;
int CThreadPool::m_nextThreadNum = 1;

CThreadPool::CThreadPool():m_taskPool("�̳߳�������ض���")
{
	CLogger::instance()->debug("��������̳߳ض����ʼ��");
	m_ThreadPool.clear();
	m_minThreadNum = 2;
	m_maxThreadNum = 10;
	m_maxProcessNum = 10;
	m_canUsedWorkerNum = 0;
	m_taskPool.clear();
	m_ThreadPool.clear();
	m_supervisitorThread = new CSupervistorThread(this,"�̳߳��ڲ������߳�");
}

CThreadPool::~CThreadPool()
{
}

CThreadPool* CThreadPool::instance()
{
	if (NULL == sm_Instance) 
	{
		if (m_InstanceMutex.tryLock())
		{
			if (NULL == sm_Instance)
			{
				sm_Instance = new CThreadPool(); 
			}
			m_InstanceMutex.unlock();
		}
	}
	return sm_Instance; 
} 

void CThreadPool::addWorker(size_t size)
{
	string workerName = "�̳߳��й������߳�-";
	workerName.append(HiRTDB::HiString::toString(m_nextThreadNum++));

	CThreadWorker* worker = new CThreadWorker(this,workerName);
	worker->start(size);
	m_ThreadPool.insert(std::make_pair(worker->getThreadID(),worker));
}

void CThreadPool::start()
{
	HI_LOG4CPLUS_DEBUG("��������̳߳ض���ʼ����,��С��:" << m_minThreadNum << " �����:" << m_maxThreadNum );
	for (int i = 0 ; i< m_minThreadNum ; i++)
	{
		addWorker();
	}
	
	m_supervisitorThread->start();
	CLogger::instance()->debug("��������̳߳ض��������ɹ�����");
}

void CThreadPool::destroy()
{
	if (m_ThreadPool.empty())
	{
		return;
	}
	
	m_supervisitorThread->exit();
	CLogger::instance()->debug("��������̳߳ض���ʼ�˳�...");
	for (ThreadPoolMap::iterator iter = m_ThreadPool.begin() ; iter != m_ThreadPool.end() ;iter++)
	{
		CThreadWorker*& worker = iter->second;
		std::string workerName = worker->getThreadName() ;

		CLogger::instance()->debug(string(workerName).append("��ʼ�˳�..."));
		worker->exit();
		CLogger::instance()->debug(string(workerName).append("��ʼ�˳��ɹ�����"));
		worker = NULL;
	}
	m_ThreadPool.clear();
	CLogger::instance()->debug("��������̳߳ض����˳��ɹ�����");
}

void CThreadPool::registerTask(CTaskWrapper* task)
{
	IceUtil::Mutex::Lock lock(m_MonitorMutex);
	m_taskPool.registerTask(task);
}

void CThreadPool::unRegisterTask(CTaskWrapper* task)
{
	IceUtil::Mutex::Lock lock(m_MonitorMutex);
	m_taskPool.removeTask(task);
}

void CThreadPool::setThreadRange(int minSize,int maxSize)
{
	m_minThreadNum = minSize > m_minThreadNum ? minSize : m_minThreadNum;
	m_maxThreadNum = maxSize;
}

CThreadPool::CSupervistorThread::CSupervistorThread(CThreadPool* monitor,const std::string& name):HiRTDB::CThreadWrapper(name)
,m_monitor(monitor)
{
	
}

void CThreadPool::CSupervistorThread::notifyAll()
{
	CThreadWrapper::notifyAll(m_monitor->m_poolMonitor);
}

// ���߳����ڼ��ע�ᵽ�����е��߳��Ƿ�������������
// ������ȡ����ķ��乤��
// ԭ�����õ�һ������䵽������
// ���ڸ�Ϊ�����ߴ���������õ�һ������󣬸�������������͵�ǰ���й����߽��з���
// ���tasknum/workernum < �������������� ��ֱ�ӷ��䣬����
// ��������˽���������ȫ��������Ȼ��ʣ�µ����񽻸��µĹ�����������

void CThreadPool::CSupervistorThread::work()
{
	int isnotify = false;
	if (m_monitor->m_MonitorMutex.tryLock())
	{
		m_monitor->m_taskPool.getWaitingTasks(m_waittingTasks);
		
		int needProcess = m_waittingTasks.size();
		
		int idleWorker = m_monitor->m_canUsedWorkerNum;

		int max_process = m_monitor->m_maxProcessNum;
		if (idleWorker)
		{
			max_process = (needProcess / idleWorker) > m_monitor->m_maxProcessNum ? m_monitor->m_maxProcessNum : (needProcess / idleWorker)  ;
		}
		
		for (ThreadPoolMap::iterator iter = m_monitor->m_ThreadPool.begin() ;(needProcess > 0 )&&(iter != m_monitor->m_ThreadPool.end() );iter++)
		{
			CThreadWorker* worker = iter->second;
			if (worker->isWaitingTask())
			{
				for (int i = 0 ; !m_waittingTasks.empty() && i < max_process + 1 ; i++)
				{
					CTaskWrapper* task = m_waittingTasks.front();
					m_waittingTasks.pop_front();
					worker->addTask(task);
					needProcess--;
					//HI_LOG4CPLUS_DEBUG(iter->first << "		" << worker->getThreadName() << " ע��ִ�С� " << task->getTaskName() << " ��\n");

				}
				isnotify = true;
			}
			
		}
		// ����̹߳����߲��㣬�������
		// ����ʣ�����������Ҫ�Ĺ����߸���
		int needWorker = m_monitor->m_maxThreadNum - m_monitor->m_ThreadPool.size();
		needWorker = (needProcess/m_monitor->m_maxProcessNum) > needWorker ? needWorker : (needProcess/m_monitor->m_maxProcessNum);
		
		if (needWorker)
		{
			for (int i = 0 ; i< needWorker;i++)
			{
				m_monitor->addWorker();
			}
		}
		else
		{
			int removeNum = (int)(m_monitor->m_ThreadPool.size()) - m_monitor->m_minThreadNum;
			for (ThreadPoolMap::iterator iter = m_monitor->m_ThreadPool.begin() ;(removeNum > 0 )&&(iter != m_monitor->m_ThreadPool.end() );)
			{
				CThreadWorker* worker = iter->second;
				if (worker->isDeadLock())
				{
					HI_LOG4CPLUS_DEBUG("��⵽��" <<worker->getThreadName() << " ����ʱ��δ��������˳�");
					notifyAll();
					worker->exit();
					m_monitor->m_ThreadPool.erase(iter++);
					removeNum--;
				}
				else
				{
					++iter;
				}
			}
		}
		
		
	}
	m_monitor->m_MonitorMutex.unlock();
	// �������еȴ��ź��̶߳��󣬽�������ִ�й���
	notifyAll();
	if (isnotify) // �����������Ѹ��֪ͨ
	{
		sleep(IceUtil::Time::milliSeconds(100));
	}
	else // ������ӳ�����ʱ��
	{
		sleep(IceUtil::Time::seconds(2));
	}

}

}