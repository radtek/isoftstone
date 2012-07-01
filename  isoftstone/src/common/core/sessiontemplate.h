// **********************************************************************
//
// 定义会话模板类-- 刘瑞功
//
// **********************************************************************

#ifndef __SESSIONTEMPLATE_H__
#define __SESSIONTEMPLATE_H__

#include <Ice/Ice.h>
#include <list>
#include <ostream>
#include "activity.h"
#include "llogger.h"
#include "escore.h"
#include "Macro.h"
using namespace std;

template<class SessionFactory>
class  SessionTemplate : public HiRTDB::CActivity 
{
public:

	SessionTemplate(const string& name,SessionFactory* sessionFactory)	
		:HiRTDB::CActivity(name)
		,m_sessionFactory(sessionFactory),
		m_timestamp(IceUtil::Time::now(IceUtil::Time::Monotonic)),
		m_destroy(false)
	{
		m_session_name = name;
		ostringstream out;
		out << " 会话：【 " << m_session_name << " 】被创建." << "\n";
		CLogger::instance()->info(out.str());
	}

	virtual ~SessionTemplate()
	{

	}

	template<class CObject>
	CObject* createObject(const Ice::Current& c)
	{
		Hi_UNUSED(c);
		if(m_destroy)
		{
			throw Ice::ObjectNotExistException(__FILE__, __LINE__);
		}

		CObject* obj = new CObject();
		return obj;
	}

    virtual void refreshSession(const Ice::Current& c)
	{
		Hi_UNUSED(c);
		IceUtil::Mutex::Lock sysc(m_sessionMetex);
		if(m_destroy)
		{
			throw Ice::ObjectNotExistException(__FILE__, __LINE__);
		}

		m_timestamp = IceUtil::Time::now(IceUtil::Time::Monotonic);
	}

    virtual std::string getSessionName(const Ice::Current& c) const
	{
		Hi_UNUSED(c);
		IceUtil::Mutex::Lock sysc(m_sessionMetex);
		if(m_destroy)
		{
			throw Ice::ObjectNotExistException(__FILE__, __LINE__);
		}

		return m_session_name;
	}

	template <class ObjectList>
	void destroySession(std::map<std::string,ObjectList > objectmap, const Ice::Current& cur)
	{
		IceUtil::Mutex::Lock sysc(m_sessionMetex);
		if(m_destroy)
		{
			throw Ice::ObjectNotExistException(__FILE__, __LINE__);
		}

		try
		{
			for (std::map<std::string,ObjectList >::iterator iter = objectmap.begin() ; iter != objectmap.end() ; iter++)
			{
				ObjectList& objectList = iter->second;
			
				for(ObjectList::const_iterator p = objectList.begin(); p != objectList.end(); ++p)
				{
					cur.adapter->remove((*p)->ice_getIdentity());
				}
			}
		}

		catch(const Ice::ObjectAdapterDeactivatedException&)
		{
		}

		objectmap.clear();
		/// 因为是Session 先销毁，所以要通知管理工厂进行显示销毁
	
		ostringstream out;
		out << " 会话：【 " << m_session_name << " 】被销毁." << "\n";
		CLogger::instance()->info(out.str());
	}
	

    IceUtil::Time timestamp() const
	{
		IceUtil::Mutex::Lock sysc(m_sessionMetex);
		if(m_destroy)
		{
			throw Ice::ObjectNotExistException(__FILE__, __LINE__);
		}
		return m_timestamp;
	}


protected:

    std::string m_session_name;
    IceUtil::Time m_timestamp; // 会话最后更新时间
	int m_self_sessionid;
    bool m_destroy;
	SessionFactory* m_sessionFactory;

	IceUtil::Mutex m_sessionMetex;
};

#endif
