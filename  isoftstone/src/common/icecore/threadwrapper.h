/*********************************************************************************
 *
 * @file	threadwrapper.h
 * @version	1.0
 * @date	2010-01-15
 * @author	����
 *
 * @brief	�̻߳���
 *
 ********************************************************************************/
 // ��Ȩ(C) 2009 - 2010 ��������Ƽ�
 // �Ķ���ʷ
 // ����		����	�Ķ�����
 // 2010-01-15	����	�����ļ�
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
 * @brief �̷߳�װ����
 *
 * ����ʹ���̴߳ӻ����������������
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
	 * ���ܽӿ�
	 * ͨ��ʵ��run��ʵ����Ҫ�ù���
	*/

	IceUtil::ThreadControl start(size_t = 0);

	virtual void run() ;

	virtual void work(){};

	/**
	 ʹ�ò��ԣ�
	 �������ͬ���ź�����ֱ�ӵ����̻߳���exit()
	 �����ͬ���ź�������Ҫ��������дexit()
	 ���磺
	 virtual void exit()
	 {
		 g_app->m_monitor.notify();
		 CThreadWrapper::exit();
	 } 
	 Ŀ���ǽ���źŷ���
	*/

	virtual void exit();

	void setThreadName(const std::string& StrThreadName);

	std::string getThreadName();

	unsigned long getThreadID();

	void notify(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void notifyAll(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void wait(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	void timeWait(IceUtil::Monitor<IceUtil::Mutex>& monitor);

	// ��������ʱ��
	void setSleepTime(IceUtil::Time sleepTime);

	// �����������ʱ��
	void setRunTime(IceUtil::Time runTime);

	IceUtil::Time getLastTime();

	IceUtil::Time getRunTime();

	// ����������⣬����ͨ���ж��߳�ִ��ʱ�����ж��Ƿ�����
	// ��������������ò��������Լ��÷���������ͨ����������������ж���

	bool isDeadLock();

	bool isWaitingTask();

protected:
	
	void init();

	// �����߳���Ҫ������ִ�й����е��ø÷������Ա�ˢ���ϴθ���ʱ��
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

	// ��������ʱ��Ϊ�뼶ʱ��

	IceUtil::Time m_sleepTime;

	IceUtil::Time m_runTime;

	// ˢ��ʱ��ΪICEʱ�䣬��ԭ��ʱ��
	IceUtil::Time m_lastRefresh;

};

}

#endif __THREADWRAPPER_H


