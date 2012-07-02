
// �����
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
			m_out << "��������" << getTaskName() <<"\n";
			CLogger::instance()->info(m_out.str());
		}

		virtual ~CTaskWrapper()
		{
			std::ostringstream m_out;
			m_out << "��������" << getTaskName() << "\n";
			CLogger::instance()->info(m_out.str());
		}

		virtual void realizeTask() = 0;

		virtual void runTimerTask()
		{
			//std::ostringstream m_out;
			//m_out << "��ʼִ������" << getTaskName() << "\n";
			//CLogger::instance()->info(m_out.str());
			realizeTask();
			m_taskExecuteNumber++;
			m_lastExecuteTime = IceUtil::Time::now();
			//m_out.clear();
			//m_out << "����ִ������" << getTaskName() << "\n";
			//CLogger::instance()->info(m_out.str());
		}

		// �鿴�����Ƿ���Ҫ��ִ��
		bool isTaskNeededExecute()
		{
			// ����ϴ������Ѿ�ִ����ϣ����ұ�������ĵȴ�ʱ���Ѿ�����
			return ((IceUtil::Time::now() - m_lastExecuteTime).toSeconds() > (m_delayTime/1000))
				|| m_taskPersistent == eOnceTime;
		}

		// ��ȡ����ִ�д��� 
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

		unsigned long m_taskExecuteNumber; // ����ִ�д���

		bool m_taskOver; // ���������������

	};

	typedef IceUtil::Handle<CTaskWrapper> CTaskWrapperPtr;

	// ����أ��Ժ���չ�����������ԣ��ݶ�Ϊ�����ȷ����Ժ���Ը����������ȼ���ȷ����
	// ���߸��������ڴ�ʱ����ȷ����
	// ��map��������֯����أ������Ƚ�������
	class LIB_ICECORE_EXPORT CTaskPool : public IceUtil::Shared
	{
	public:
		CTaskPool(const std::string& StrName);

		virtual ~CTaskPool();

		// ��ȡ����������������
		CTaskWrapper* getTask(int taskID = 0,bool erase = false);

		// ��õȴ���ִ�е�����
		CTaskWrapper* getWaitingTask();

		void getWaitingTasks(std::list<CTaskWrapper*>& waitingTasks);
		// ����IDΪ����ط��䣬���ⲿ��˵��͸����
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