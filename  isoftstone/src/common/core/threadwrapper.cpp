
#include <Ice/Ice.h>
#include <cstdlib>
#include <iterator>
#include <stdio.h>
#include <sstream>

#include "llogger.h"
#include "threadwrapper.h"
#include "threadmonitor.h"


using namespace std;

namespace HiRTDB
{

CThreadWrapper::CThreadWrapper()
{
	stringstream sNum;
	sNum<< ++CThreadMonitor::instance()->m_DefaultThreadNum;
	m_ThreadName = "Default_" +  sNum.str();
	init();
}


CThreadWrapper::CThreadWrapper(const std::string& name)
{
	m_ThreadName = name;
	init();
}

void CThreadWrapper::init()
{
	m_Exit = false;
	m_runTime = IceUtil::Time::seconds(600);
	m_sleepTime = IceUtil::Time::seconds(1);
	m_deadLock = false;
	m_lastRefresh = IceUtil::Time::now();
	m_waitingTask = true;
	HI_LOG4CPLUS_INFO("创建线程:" << m_ThreadName  <<  "\n");
}

CThreadWrapper::~CThreadWrapper()
{
	if (false == m_Exit)
	{
		exit();
	}
}

void CThreadWrapper::run()
{
	while(!m_Exit)
	{
		beginWork();
		work();
		endWork();
	}
}

IceUtil::ThreadControl CThreadWrapper::start(size_t t)
{
	IceUtil::ThreadControl control = IceUtil::Thread::start(t);
	HI_LOG4CPLUS_INFO("线程号【" << getThreadID()  << "】  线程名【" << m_ThreadName << " 】启动！！\n");
	registerd();
	return control;
}

void CThreadWrapper::exit()
{
	std::ostringstream out;
	out << "线程号【" << m_ThreadID  << "】  线程名【" << m_ThreadName << " 】开始退出！！\n";
	CLogger::instance()->info(out.str());
	unsigned long threadID = m_ThreadID;
	std::string threadName = m_ThreadName;
	m_Exit = true;
	unRegisterd();
	getThreadControl().join();
	out.clear();
	out << "线程号【" << threadID  << "】  线程名【" << threadName << " 】退出成功！！\n";
	CLogger::instance()->info(out.str());
}

void CThreadWrapper::setThreadName(const string& StrThreadName)
{
	m_ThreadName = StrThreadName;
	CThreadMonitor::instance()->updateThreadInfo(getThreadID(),this);
	
}

std::string CThreadWrapper::getThreadName()
{
	return m_ThreadName ;
}

unsigned long CThreadWrapper::getThreadID()
{
#ifdef _WIN32
	return m_ThreadID = _id;
#else
	return m_ThreadID =  _thread;
#endif

}

void CThreadWrapper::registerd()
{
	CThreadMonitor::instance()->registerThread(this->getThreadID(),this);
}

void CThreadWrapper::unRegisterd()
{
	CThreadMonitor::instance()->unRegisterThread(this->getThreadID());
}

void CThreadWrapper::setSleepTime(IceUtil::Time sleepTime)
{
	m_sleepTime = sleepTime;
}

void CThreadWrapper::setRunTime(IceUtil::Time runTime)
{
	m_runTime = runTime;
}

IceUtil::Time CThreadWrapper::getRunTime()
{
	return m_runTime;
}

bool CThreadWrapper::detectDeadLock()
{
	// 如果运行刷新时间超过了最大期望运行时间，则认为可能存在死锁
	if ((IceUtil::Time::now() - m_lastRefresh).toSeconds() > (m_runTime + m_sleepTime).toSeconds())
	{
		return m_deadLock = true;
	}
	else
	{
		return false;
	}
}

bool CThreadWrapper::isDeadLock()
{
	return m_deadLock = detectDeadLock();
}

IceUtil::Time CThreadWrapper::getLastTime()
{
	return m_lastRefresh;
}

bool CThreadWrapper::isWaitingTask()
{
	return m_waitingTask;
}

void CThreadWrapper::beginWork()
{
	m_deadLock = false;
	m_lastRefresh = IceUtil::Time::now();
	m_waitingTask = true;
}

void CThreadWrapper::endWork()
{
	
}

void CThreadWrapper::sleep(IceUtil::Int64 sec,IceUtil::Int64 millisec,IceUtil::Int64 microsec)
{
	IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(sec)
								+ IceUtil::Time::milliSeconds(millisec)
								+ IceUtil::Time::microSeconds(microsec));
}

void CThreadWrapper::sleep(const IceUtil::Time& time)
{
	IceUtil::ThreadControl::sleep(time);
}

void CThreadWrapper::sleep()
{
	IceUtil::ThreadControl::sleep(m_sleepTime);
}

void CThreadWrapper::notify(IceUtil::Monitor<IceUtil::Mutex>& monitor)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(monitor);
	monitor.notify();
}

void CThreadWrapper::notifyAll(IceUtil::Monitor<IceUtil::Mutex>& monitor)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(monitor);
	monitor.notifyAll();
}

void CThreadWrapper::wait(IceUtil::Monitor<IceUtil::Mutex>& monitor)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(monitor);
	monitor.wait();
}

void CThreadWrapper::timeWait(IceUtil::Monitor<IceUtil::Mutex>& monitor)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(monitor);
	monitor.timedWait(getRunTime());
}

}