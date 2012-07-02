/*********************************************************************************
 *
 * @file	threadwrapper.h
 * @version	1.0
 * @date	2010-01-15
 * @author	刘瑞功
 *
 * @brief	线程基类
 *
 ********************************************************************************/
 // 版权(C) 2009 - 2010 海信网络科技
 // 改动历史
 // 日期		作者	改动内容
 // 2010-01-15	刘瑞功	创建文件
 //===============================================================================


#ifndef __THREADWRAPPER_H
#define __THREADWRAPPER_H

#include <IceUtil/IceUtil.h>
#include <Ice/LoggerUtil.h>
#include <IceUtil/Thread.h>
#include <string>
#include <map>
#include "icecore.h"

/** 
 * @class CThreadWrapper
 *
 * @brief 线程封装基类
 *
 * 所有使用线程从基类派生，方便管理
 */

namespace HiRTDB
{

class  LIB_ICECORE_EXPORT CThreadWrapper : public IceUtil::Thread
{
public:

	CThreadWrapper();

	CThreadWrapper(const std::string& StrName);

	virtual ~CThreadWrapper();

	/**
	 * 功能接口
	 * 通过实现run来实现所要得功能
	*/

	IceUtil::ThreadControl start(size_t = 0);

	virtual void run() ;

	virtual void work(){};

	/**
	 使用策略：
	 如果不带同步信号锁，直接调用线程基类exit()
	 如果带同步信号锁，需要派生类重写exit()
	 例如：
	 virtual void exit()
	 {
		 g_app->m_monitor.notify();
		 CThreadWrapper::exit();
	 } 
	 目的是解除信号封锁
	*/

	virtual void exit();

	void setThreadName(const std::string& StrThreadName);

	std::string getThreadName();

	unsigned long getThreadID();

	void notify(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void notifyAll(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void wait(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void timeWait(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	// 设置休眠时间
	void setSleepTime(IceUtil::Time sleepTime);

	// 设置最大运行时间
	void setRunTime(IceUtil::Time runTime);

	IceUtil::Time getLastTime();

	IceUtil::Time getRunTime();

	// 用于死锁检测，基类通过判定线程执行时间来判定是否死锁
	// 派生子类如果觉得不够或有自己得方法，可以通过重载这个方法来判定。

	bool isDeadLock();

	bool isWaitingTask();

protected:
	
	void init();

	// 所有线程需要在任务执行过程中调用该方法，以便刷新上次更新时间
	virtual void beginWork();

	virtual void endWork();

	virtual bool detectDeadLock();

	void sleep(IceUtil::Int64 sec = 1,IceUtil::Int64 millisec = 0,IceUtil::Int64 macrosec = 0);

	void sleep(const IceUtil::Time& time);

	void sleep();

	std::string m_ThreadName;

	bool m_Exit;

	bool m_deadLock;

	bool m_waitingTask;

private:

	void registerd();

	void unRegisterd();

	unsigned long m_ThreadID;

	// 下面所有时间为秒级时间

	IceUtil::Time m_sleepTime;

	IceUtil::Time m_runTime;

	// 刷新时间为ICE时间，是原子时间
	IceUtil::Time m_lastRefresh;

};

}

#endif __THREADWRAPPER_H


