/*********************************************************************************
 *
 * @file	threadmonitor.h
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


#ifndef __THREADMONITOR_H
#define __THREADMONITOR_H

#include <IceUtil/IceUtil.h>
#include <string>
#include "icecore.h"


namespace HiRTDB
{

class CThreadWrapper;

/** 
 * @class CThreadMonitor
 *
 * @brief �߳������൥��
 *
 * ���г����ڵ��߳�ע�ᵽ�̹߳���������
 */

class LIB_ICECORE_EXPORT CThreadMonitor : virtual public IceUtil::Shared
{
public :

	static CThreadMonitor* instance(void);

	void start();

	void destroy();

	void registerThread(const unsigned long& lThreadID,CThreadWrapper* cthread);

	void unRegisterThread(const unsigned long& lThreadID);

	void updateThreadInfo(unsigned long lThreadID,CThreadWrapper* cthread);

	volatile unsigned long m_DefaultThreadNum;

private:

	typedef std::map<unsigned long,CThreadWrapper* ,std::less<unsigned long> > ThreadContainerMap;

	ThreadContainerMap m_ThreadContainer;

	CThreadMonitor(void);

	~CThreadMonitor(void);

	CThreadMonitor(const CThreadMonitor& right);

	CThreadMonitor operator=(const CThreadMonitor& right);

	IceUtil::Mutex m_MonitorMutex;

	static CThreadMonitor* sm_Instance;

	static IceUtil::Mutex m_InstanceMutex; 

	friend class CCheckActivityThread;

	class CCheckActivityThread : public CThreadWrapper
	{
	public:

		CCheckActivityThread(CThreadMonitor* monitor,const std::string& name);

		virtual void run();
		
		CThreadMonitor* m_monitor;

	private:

	};
	typedef IceUtil::Handle<CCheckActivityThread> CCheckActivityThreadPtr;

	CCheckActivityThreadPtr m_checkThread;

};

}

#endif __THREADMONITOR_H

