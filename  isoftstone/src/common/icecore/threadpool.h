/*********************************************************************************
 *
 * @file	threadpool.h
 * @version	1.0
 * @date	2010-01-15
 * @author	����
 *
 * @brief	�̳߳���
 * �̳߳ص�Ŀ�����ܹ���̬��Ч�������߳���Դ
 * �ﵽ���ִ�������Ч����ƽ���ܶ����������Ч���
 * ���ʹ�ö�ʱ����������û�ж�̬��Ч��
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

	// ��Ϊ����Ϊ˽�ж��У�����Ӧ�ò���Ҫ��������
	std::list<CTaskWrapper*> m_tasks;

	CThreadPool* m_threadPool;

};

typedef IceUtil::Handle<CThreadWorker> CThreadWorkerPtr;

/** 
 * @class CThreadPool
 *
 * @brief �߳������൥��
 *
 * ���г����ڵ��߳�ע�ᵽ�̹߳���������
 */

class LIB_ICECORE_EXPORT CThreadPool : virtual public IceUtil::Shared
{
public :

	friend class CThreadWorker;

	static CThreadPool* instance(void);

	// �����̳߳����̣߳�������������߳�
	void start();

	// �ر���������̣߳��ر��̳߳����߳�
	void destroy();

	void registerTask(CTaskWrapper*);

	void unRegisterTask(CTaskWrapper*);

	void setThreadRange(int minSize,int maxSize);

	volatile unsigned long m_canUsedWorkerNum;

	// �����������߳��ź���
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
	// �������߳�
	// ����Ϊͳһ�����߳���ִ�����񣬶��������ɺ��̵߳�ʹ��������м���
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

