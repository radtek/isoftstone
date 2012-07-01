
#include "activitythread.h"
#include "llogger.h"


using namespace std;

CActivityThread::CActivityThread() :CThreadWrapper("�Ựά���߳�"),
m_timeout(IceUtil::Time::seconds(2))
{

}

CActivityThread::~CActivityThread()
{
	HI_LOG4CPLUS_INFO( getThreadName() << " ������ " );
}

void CActivityThread::work()
{
    if(m_sessionMutex.tryLock())
    {
		ActivityIterator iter = m_sessions.begin();
        while(iter != m_sessions.end())
        {
            try
            {
                if(FALSE == (*iter).second->isAlive())
                {
					HI_LOG4CPLUS_DEBUG("  ��⵽�Ự �� " << (*iter).first << " �� �����٣���");
					(*iter).second->destroySession();
                    iter = m_sessions.erase( iter );
                }
                else
                {
                    ++iter;
                }
            }
            catch(...) // �쳣�����
            {
                iter = m_sessions.erase( iter );
            }
        }
    }
	m_sessionMutex.unlock();
	sleep(m_timeout);
}

CActivity* CActivityThread::getSession(const std::string& name)
{
	CActivity* session = NULL;
	if (m_sessionMutex.tryLock() && m_sessions.find(name) != m_sessions.end())
	{
		session =  m_sessions[name];
	}
	m_sessionMutex.unlock();
	return session;
}

bool CActivityThread::registerSession(CActivity* act)
{
	if (m_sessionMutex.tryLock())
	{
		m_sessions.insert(std::make_pair(act->getServiceName(),act));
		m_sessionMutex.unlock();
		return true;
	}
	return false;
}

bool CActivityThread::unregisterSession(const std::string& sessionname)
{
	if (m_sessionMutex.tryLock())
	{
		m_sessions.erase(sessionname);
		m_sessionMutex.unlock();
		return true;
	}
	return false;
}