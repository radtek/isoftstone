
#include <Ice/Ice.h>
#include <cstdlib>
#include <iterator>
#include <stdio.h>

#include "llogger.h"
#include "ThreadWrapper.h"
#include "ThreadMonitor.h"

using namespace std;

namespace HiRTDB
{

IceUtil::Mutex CThreadMonitor::m_InstanceMutex;
CThreadMonitor* CThreadMonitor::sm_Instance = NULL;

CThreadMonitor::CThreadMonitor()
{
	std::ostringstream out;
	out << "  创建线程监视管理器 " << "\n";
	CLogger::instance()->info(out.str());
	m_ThreadContainer.clear();
	m_DefaultThreadNum = 0;
	m_checkThread = new CCheckActivityThread(this,"线程容器内部管理线程");
}

CThreadMonitor::~CThreadMonitor()
{
}

CThreadMonitor* CThreadMonitor::instance()
{
	if (NULL == sm_Instance) 
	{
		if (m_InstanceMutex.tryLock())
		{
			if (NULL == sm_Instance)
			{
				sm_Instance = new CThreadMonitor(); 
			}
			m_InstanceMutex.unlock();
		}
	}
	return sm_Instance; 
} 

void CThreadMonitor::start()
{
	m_checkThread->start();
}

void CThreadMonitor::destroy()
{
	m_checkThread->exit();
}

void CThreadMonitor::registerThread(const unsigned long& lThreadID,CThreadWrapper* cthread)
{
	IceUtil::Mutex::Lock lock(m_MonitorMutex);
	m_ThreadContainer.insert(std::make_pair(lThreadID,cthread));
}

void CThreadMonitor::unRegisterThread(const unsigned long& lThreadID)
{
	IceUtil::Mutex::Lock lock(m_MonitorMutex);
	m_ThreadContainer.erase(lThreadID);
}

void CThreadMonitor::updateThreadInfo(unsigned long lThreadID,CThreadWrapper* cthread)
{
	IceUtil::Mutex::Lock lock(m_MonitorMutex);
	m_ThreadContainer[lThreadID] = cthread;
}

CThreadMonitor::CCheckActivityThread::CCheckActivityThread(CThreadMonitor* monitor,const std::string& name):HiRTDB::CThreadWrapper(name)
,m_monitor(monitor)
{
	
}

// 本线程用于检测注册到容器中的线程是否存在死锁情况。
void CThreadMonitor::CCheckActivityThread::run()
{
	while(!m_Exit)
	{
		sleep(2);
		beginWork();
		if (m_monitor->m_MonitorMutex.tryLock())
		{
			for (ThreadContainerMap::iterator iter = m_monitor->m_ThreadContainer.begin() ;iter != m_monitor->m_ThreadContainer.end() ;iter++)
			{
				CThreadWrapper* cthread = iter->second;
				if (iter->second->isDeadLock())
				{
					std::ostringstream m_out;
					m_out << iter->first << "		" << cthread->getThreadName() << " 可能存在死锁" << "\n";
					CLogger::instance()->debug(m_out.str());
					char buf[32] = {0};
					IceUtil::Time timeout = IceUtil::Time::now() - cthread->getLastTime();
					sprintf_s(buf,"%30d",timeout.toSeconds());
					m_out.clear();
					m_out << "超时时间为【 " << buf << " 】 秒钟" << "\n";
					CLogger::instance()->debug(m_out.str());
				}
				
			}
			
		}
		m_monitor->m_MonitorMutex.unlock();
		
	}
}

}