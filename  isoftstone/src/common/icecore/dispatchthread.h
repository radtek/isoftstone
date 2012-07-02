
#ifndef _DISPATCH_THREAD_H_
#define _DISPATCH_THREAD_H_

#include <IceUtil/IceUtil.h>
#include <list>
#include "ThreadWrapper.h"
#include "icecore.h"

template < class AMD_Dispatch_Ptr,class CResult >
struct CallbackEntry
{
	AMD_Dispatch_Ptr amd_ptr;
	IceUtil::Int64 createTime;
	IceUtil::Int64 delay;
	bool notifyResult;
	CResult result;
};

/*
	先来先派送式推动模式
*/

template < class AMD_Dispatch_Ptr,class CResult >
class LIB_ICECORE_EXPORT CDataNotifyDispatchThread : public HiRTDB::CThreadWrapper
{
	typedef CallbackEntry<AMD_Dispatch_Ptr,CResult> CallbackEntry;

public:

	CDataNotifyDispatchThread():HiRTDB::CThreadWrapper("数据组装式派送延迟回调线程")
	{
		m_done = false;
	}

	virtual ~CDataNotifyDispatchThread(){}

	virtual void work()
	{
		 IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);

		 if(m_callbacks.size() == 0)
		 {
			 m_monitor.wait();
		 }
		 else()
		 {
			 CallbackEntry entry = m_callbacks.front();

			 m_monitor.timedWait(IceUtil::Time::milliSeconds(entry.delay));

			 if(!m_done)
			 {
				 m_callbacks.pop_front();
				 if (entry.notifyResult)
				 {
					entry.amd_ptr->ice_response(entry.result);
				 }
				 else
				 {
					entry.amd_ptr->ice_response();
				 }
			 }
		 }
	}

	virtual void endWork()
	{
		std::list<CallbackEntry>::const_iterator iter;
		for(iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
		{
			iter->amd_ptr->ice_exception( Ice::TimeoutException() );
		}
	}

	void notify(const AMD_Dispatch_Ptr& const_amd_ptr , const CResult& const_result , const IceUtil::Int64& const_delay,const bool& bNotifyResult = false)
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);

		if(!m_done)
		{
			CallbackEntry entry;
			entry.amd_ptr = const_amd_ptr;
			entry.delay = const_delay;
			entry.notifyResult = bNotifyResult;
			entry.result = const_result;
			entry.createTime = IceUtil::Time::now().toMilliSeconds();

			if(m_callbacks.size() == 0)
			{
				m_monitor.notify();
			}
			m_callbacks.push_back(entry);
		}
		else
		{
			const_amd_ptr->ice_exception(Ice::TimeoutException());
		}
	}

private:

	IceUtil::Monitor<IceUtil::Mutex> m_monitor;

	std::list<CallbackEntry > m_callbacks;

	bool m_done;
};

/*
	轮询式检查式推动模式
*/

template < class AMD_Dispatch_Ptr,class CResult >
class LIB_ICECORE_EXPORT CPollDispatchThread : public HiRTDB::CThreadWrapper
{
	typedef CallbackEntry<AMD_Dispatch_Ptr,CResult> CallbackEntry;

public:

	CPollDispatchThread():HiRTDB::CThreadWrapper("数据组装式轮询延迟回调线程")
	{
		m_done = false;
	}

	virtual ~CPollDispatchThread(){}

	virtual void work()
	{
		IceUtil::Mutex::Lock lock(m_mutex);

		std::list<CallbackEntry>::const_iterator iter;
		for(iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
		{
			if (IceUtil::Time::now().toMilliSeconds() - iter->createTime > iter->delay)
			{
				if (iter->notifyResult)
				{
					iter->amd_ptr->ice_response(iter->result);
				}
				else
				{
					iter->amd_ptr->ice_response();
				}
			}
		}
		sleep(IceUtil::Time::milliSeconds(10));
	}

	void notify(const AMD_Dispatch_Ptr& const_amd_ptr , const CResult& const_result , const IceUtil::Int64& const_delay,const bool& bNotifyResult = false)
	{
		IceUtil::Mutex::Lock lock(m_mutex);

		CallbackEntry entry;
		entry.amd_ptr = const_amd_ptr;
		entry.delay = const_delay;
		entry.notifyResult = bNotifyResult;
		entry.result = const_result;
		entry.createTime = IceUtil::Time::now().toMilliSeconds();

		m_callbacks.push_back( entry );
	}

private:

	IceUtil::Mutex m_mutex;

	std::list<CallbackEntry> m_callbacks;
};

#endif