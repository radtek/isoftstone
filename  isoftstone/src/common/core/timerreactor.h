
// 定时器基类
#ifndef __TIMERREACTOR_H_
#define  __TIMERREACTOR_H_

#include <IceUtil/IceUtil.h>
#include <Ice/Initialize.h>
#include <Ice/LoggerUtil.h>
#include <IceUtil/Timer.h>
#include "taskpool.h"
#include "llogger.h"
#include "escore.h"

namespace HiRTDB
{

class  LIBCORE_EXPORT CTimerReactor :public IceUtil::Shared
{
public:


	CTimerReactor(const std::string& StrName)
	{
		m_ReactorName = StrName;
		m_taskTimer = new IceUtil::Timer();
		m_taskPool = new CTaskPool(StrName);
		m_destroy = false;

		HI_LOG4CPLUS_INFO("创建定时器：" << m_ReactorName << "\n");
	}
	
	virtual ~CTimerReactor()
	{
		if (!m_destroy)
		{
			exit();
		}
	}

	void exit()
	{
		
	   bool bret = true;
	   std::ostringstream out; 
	   while (m_taskPool->empty() == false)
	   {
		   CTaskWrapper* task = m_taskPool->getTask(0,true);
		   HI_LOG4CPLUS_INFO("永久工作任务【 "<< task->getTaskName() <<"】被定时器【 " << m_ReactorName << " 】注销" <<"\n");
		   bret = m_taskTimer->cancel(task);
	   }
	   if (bret)
	   {
		   HI_LOG4CPLUS_INFO("开始销毁定时器：" << m_ReactorName << "\n");
		   m_taskTimer->destroy();
		   m_taskTimer = NULL;
	   }
	   m_taskPool->clear();
	   m_destroy = true;
	   out.clear();
	   out << "成功销毁定时器：" << m_ReactorName << "\n";
	   CLogger::instance()->info(out.str());
	}

	std::string getReactorName()
	{
		return m_ReactorName;
	}

	void registerd(CTaskWrapper* task)
	{
		std::ostringstream out;
		out.clear();
		if (task->getPersistent() == HiRTDB::eOnceTime)
		{
			out << "一次性工作任务【 "<< task->getTaskName() <<"】被定时器【 " << m_ReactorName << " 】注册执行" <<"\n";
			CLogger::instance()->info(out.str());
			m_taskTimer->schedule(task,IceUtil::Time::seconds(0));
		}
		else
		{
			out.clear();
			out << "永久工作任务【 "<< task->getTaskName() <<"】被注册到定时器【 " << m_ReactorName << " 】" <<"\n";
			CLogger::instance()->info(out.str());
			m_taskPool->registerTask(task);
			m_taskTimer->scheduleRepeated(task,IceUtil::Time::milliSeconds(task->getDelayTime()));
		}
	}

protected:
	
	std::string m_ReactorName;

	// 在构造函数中创建对象并启动线程
	IceUtil::TimerPtr m_taskTimer; 

	IceUtil::TimerTaskPtr m_taskPtr;

	CTaskPoolPtr m_taskPool;

	bool m_destroy;

private:

	CTimerReactor(){}

};

typedef IceUtil::Handle<CTimerReactor> CTimerReactorPtr;

}



#endif