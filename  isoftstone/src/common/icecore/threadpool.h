/*********************************************************************************
 *
 * @file	threadpool.h
 * @version	1.0
 * @date	2010-01-15
 * @author	刘瑞功
 *
 * @brief	线程池类
 * 线程池的目的是能够动态有效的利用线程资源
 * 达到最佳执行任务的效果，平且能对任务进行有效监控
 * 如果使用定时器来做，则没有动态的效果
 *
 ********************************************************************************/

#ifndef __THREADPOOL_H
#define __THREADPOOL_H

#include <IceUtil/IceUtil.h>
#include <string>
#include <list>
#include "taskpool.h"
#include "icecore.h"


namespace HiRTDB
{

class CThreadWrapper;
class CThreadPool;

typedef IceUtil::Monitor<IceUtil::Mutex> IceMonitor;

typedef IceMonitor::Lock IceMonitorLock;

class LIB_ICECORE_EXPORT CThreadWorker : public HiRTDB::CThreadWrapper 
{
public:

	CThreadWorker(CThreadPool* threadPool,const std::string& StrName);

	virtual ~CThreadWorker(){}

	virtual void work();

	virtual void exit();

	void addTask(CTaskWrapper*);

	void setMaxTasks(int max_num);

	int getMaxTasks();

private:

	int max_tasks_num;

	// 因为任务为私有队列，所以应该不需要加锁保护
	std::list<CTaskWrapper*> m_tasks;

	CThreadPool* m_threadPool;

};

typedef IceUtil::Handle<CThreadWorker> CThreadWorkerPtr;

/** 
 * @class CThreadPool
 *
 * @brief 线程容器类单体
 *
 * 所有程序内得线程注册到线程管理容器中
 */

class LIB_ICECORE_EXPORT CThreadPool : virtual public IceUtil::Shared
{
public :

	friend class CThreadWorker;

	static CThreadPool* instance(void);

	// 启动线程池中线程，启动任务调度线程
	void start();

	// 关闭任务调度线程，关闭线程池中线程
	void destroy();

	void registerTask(CTaskWrapper*);

	void unRegisterTask(CTaskWrapper*);

	void setThreadRange(int minSize,int maxSize);

	volatile unsigned long m_canUsedWorkerNum;

	// 调度任务与线程信号量
	IceMonitor m_poolMonitor;

private:

	void addWorker(size_t size = 0);

private:

	CTaskPool m_taskPool;

	typedef std::map<unsigned long,CThreadWorker* > ThreadPoolMap;

	ThreadPoolMap m_ThreadPool;

	CThreadPool(void);

	~CThreadPool(void);

	CThreadPool(const CThreadPool& right);

	CThreadPool operator=(const CThreadPool& right);

	int m_minThreadNum;

	int m_maxThreadNum;

	int m_maxProcessNum;

	IceUtil::Mutex m_MonitorMutex;

	static CThreadPool* sm_Instance;

	static IceUtil::Mutex m_InstanceMutex; 

	static int m_nextThreadNum;

	friend class CSupervistorThread;
	// 调度者线程
	// 责任为统一调度线程来执行任务，对任务的完成和线程的使用情况进行监视
	class CSupervistorThread : public CThreadWrapper
	{
	public:

		CSupervistorThread(CThreadPool* monitor,const std::string& name);

		virtual void work();

		void notifyAll();
		
		CThreadPool* m_monitor;

	private:

		std::list<CTaskWrapper*> m_waittingTasks;

	};
	typedef IceUtil::Handle<CSupervistorThread> CSupervistorThreadPtr;

	CSupervistorThreadPtr m_supervisitorThread;

};

typedef IceUtil::Handle<CThreadPool> CThreadPoolPtr;

}

#endif __THREADMONITOR_H

