
// 任务池
#ifndef __TASKPOOL_H_
#define  __TASKPOOL_H_

#include <IceUtil/IceUtil.h>
#include <IceUtil/Timer.h>
#include <Ice/LoggerUtil.h>
#include <Ice/Initialize.h>
#include <string>
#include <vector>
#include <list>
#include <ostream>
#include "llogger.h"
#include "icecore.h"
#include "objects.h"


namespace HiRTDB
{

	enum ETaskPriority
	{
		eSimpleTask,
		eQuickTask,
		eEmergencyTask
	};

	enum ETaskPersistent
	{
		eOnceTime,
		eForever
	};

	class  LIB_ICECORE_EXPORT CTaskWrapper :public IceUtil::TimerTask
	{

	public:
		
		CTaskWrapper(const std::string& StrName,
					 IceUtil::Int64 delay = 5000,
					 ETaskPersistent persistent = eOnceTime,
					 ETaskPriority priority = eSimpleTask)
		{
			m_TaskName = StrName;
			m_delayTime = delay;
			m_taskPriority = priority;
			m_taskPersistent = persistent;
			m_taskID = 0;
			m_taskExecuteNumber = 0 ;
			std::ostringstream m_out;
			m_out << "创建任务：" << getTaskName() <<"\n";
			CLogger::instance()->info(m_out.str());
		}

		virtual ~CTaskWrapper()
		{
			std::ostringstream m_out;
			m_out << "销毁任务：" << getTaskName() << "\n";
			CLogger::instance()->info(m_out.str());
		}

		virtual void realizeTask() = 0;

		virtual void runTimerTask()
		{
			//std::ostringstream m_out;
			//m_out << "开始执行任务：" << getTaskName() << "\n";
			//CLogger::instance()->info(m_out.str());
			realizeTask();
			m_taskExecuteNumber++;
			m_lastExecuteTime = IceUtil::Time::now();
			//m_out.clear();
			//m_out << "结束执行任务：" << getTaskName() << "\n";
			//CLogger::instance()->info(m_out.str());
		}

		// 查看任务是否需要被执行
		bool isTaskNeededExecute()
		{
			// 如果上次任务已经执行完毕，并且本次任务的等待时间已经到达
			return ((IceUtil::Time::now() - m_lastExecuteTime).toSeconds() > (m_delayTime/1000))
				|| m_taskPersistent == eOnceTime;
		}

		// 获取任务被执行次数 
		unsigned long getTaskExecuteNumber()
		{
			return m_taskExecuteNumber;
		}

		void setPersistent(ETaskPersistent persistent)
		{
			m_taskPersistent = persistent;
		}

		ETaskPersistent getPersistent()
		{
			return m_taskPersistent;
		}

		void setPriority(ETaskPriority priority)
		{
			m_taskPriority = priority;
		}

		ETaskPriority getPriority()
		{
			return m_taskPriority;
		}

		void setDelayTime(IceUtil::Int64 delay)
		{
			m_delayTime = delay;
		}

		IceUtil::Int64 getDelayTime()
		{
			return m_delayTime;
		}

		void setTaskName(const std::string& taskName)
		{
			m_TaskName = taskName;
		}

		std::string getTaskName()
		{
			return m_TaskName;
		}

		void setTaskID(int taskid)
		{
			m_taskID = taskid;
		}

		int getTaskID()
		{
			return m_taskID;
		}

	protected:

		int m_taskID;

		std::string m_TaskName;

		ETaskPriority m_taskPriority;

		ETaskPersistent m_taskPersistent;

		IceUtil::Int64 m_delayTime;

		IceUtil::Time m_lastExecuteTime;

		unsigned long m_taskExecuteNumber; // 任务被执行次数

		bool m_taskOver; // 本次任务的完成情况

	};

	typedef IceUtil::Handle<CTaskWrapper> CTaskWrapperPtr;

	// 任务池，以后扩展出任务工作策略，暂定为先来先服务，以后可以根据任务优先级来确定。
	// 或者根据任务期待时间来确定。
	// 用map容器来组织任务池，这样比较清晰点
	class LIB_ICECORE_EXPORT CTaskPool : public IceUtil::Shared
	{
	public:
		CTaskPool(const std::string& StrName);

		virtual ~CTaskPool();

		// 获取任务函数，调度任务
		CTaskWrapper* getTask(int taskID = 0,bool erase = false);

		// 获得等待被执行的任务
		CTaskWrapper* getWaitingTask();

		void getWaitingTasks(std::list<CTaskWrapper*>& waitingTasks);
		// 任务ID为任务池分配，对外部来说是透明的
		void registerTask(CTaskWrapper* task);

		void removeTask();

		void removeTask(CTaskWrapper* task);

		void clearRubbish();

		void clear();

		bool empty();

		int size();

	protected:

		std::string m_PoolName;

	private:

		CTaskPool(){}

		IceUtil::Mutex m_TaskMutex;

		typedef std::map<int,CTaskWrapper*> TaskPoolContainer;

		TaskPoolContainer m_TaskPool;

		volatile int m_nextTaskID;

		std::vector<int> m_TaskRubbish;
	};

	typedef IceUtil::Handle<CTaskPool> CTaskPoolPtr;
}


class CPostTask : public HiRTDB::CTaskWrapper
{
public:

	CPostTask(CLObject* reciver,LCustomEvent* event)
		:HiRTDB::CTaskWrapper(reciver->getObjectName(),0,HiRTDB::eOnceTime,HiRTDB::eSimpleTask)
	{
		m_reciver = reciver;
		m_event = event;
	}

	virtual void realizeTask()
	{
		m_reciver->customEvent(m_event);
		delete m_event;
		m_event = NULL;
	}

	CLObject* m_reciver;
	LCustomEvent* m_event;
};

#endif