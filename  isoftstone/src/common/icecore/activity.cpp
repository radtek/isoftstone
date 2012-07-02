#include "activity.h"
#include <IceUtil/Timer.h>
#include <IceUtil/Time.h>

Juint32 HiRTDB::CActivity::s_defaultIdleSeconds = 60;

HiRTDB::CActivity::CActivity(const std::string& strServiceName)
: m_strServiceName(strServiceName),
m_maxIdleTime(s_defaultIdleSeconds),
m_lastActiveTime(IceUtil::Time::now())
{
	m_removed = JFALSE;
}

HiRTDB::CActivity::CActivity(const std::string& strServiceName, Juint32 nSeconds)
: m_strServiceName(strServiceName),
m_maxIdleTime(nSeconds),
m_lastActiveTime(IceUtil::Time::now())
{
	m_removed = JFALSE;
}

HiRTDB::CActivity::~CActivity(void)
{
}

Jboolean HiRTDB::CActivity::isAlive(void)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	// 当前 CPU 滴答时间 - 上次活动 CPU 滴答时间
	return !m_removed && ((IceUtil::Time::now().toSeconds() - m_lastActiveTime.toSeconds()) < m_maxIdleTime);
}

Jboolean HiRTDB::CActivity::isAlive(const IceUtil::Time& lastTime)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	// 当前 CPU 滴答时间 - 上次活动 CPU 滴答时间
	return !m_removed && ((lastTime.toSeconds() - m_lastActiveTime.toSeconds()) < m_maxIdleTime);
}

void HiRTDB::CActivity::keepAlive(void) 
{
	IceUtil::Mutex::Lock lock (m_mutex);

	if (!m_removed)
	{
		m_lastActiveTime = IceUtil::Time::now();
	}
	else
	{
		// throw Ice::Exception
	}
}

void HiRTDB::CActivity::keepAlive(const IceUtil::Time& lastTime)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	if (!m_removed)
	{
		m_lastActiveTime = lastTime;
	}
	else
	{
		//throw 
	}
}

std::string HiRTDB::CActivity::getServiceName(void) const
{
	return m_strServiceName;
}

void HiRTDB::CActivity::setMaxIdleTime(Juint32 nSeconds)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	m_maxIdleTime = nSeconds;
}

Juint32 HiRTDB::CActivity::getMaxIdleTime(void) const
{
	IceUtil::Mutex::Lock lock (m_mutex);

	return m_maxIdleTime;
}

bool HiRTDB::CActivity::remove(void)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	Jboolean bRet;
	if (!m_removed)
	{
		m_removed = JTRUE;
		bRet = JTRUE;
	}
	else
	{
		bRet = JFALSE;
	}
	return bRet;
}

bool HiRTDB::CActivity::isRemoved(void)
{
	IceUtil::Mutex::Lock lock (m_mutex);

	return m_removed;
}


void HiRTDB::CActivity::destroySession()
{
}