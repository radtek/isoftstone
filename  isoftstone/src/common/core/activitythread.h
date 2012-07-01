
#ifndef __ACTIVITY_THREAD_H
#define __ACTIVITY_THREAD_H

#include <IceUtil/IceUtil.h>
#include <list>
#include "escore.h"
#include "activity.h"
#include "threadwrapper.h"

using namespace HiRTDB;

class LIBCORE_EXPORT CActivityThread : public CThreadWrapper
{
public:

    CActivityThread();

	virtual ~CActivityThread();

    virtual void work();

	CActivity* getSession(const std::string& name);

    bool registerSession(CActivity* act);

	bool unregisterSession(const std::string&);

private:

    const IceUtil::Time m_timeout;

	IceUtil::Mutex m_sessionMutex;

	typedef std::map<std::string,CActivity*> ActivityMap;
	typedef ActivityMap::iterator ActivityIterator;
	typedef ActivityMap::const_iterator const_ActivityIterator;

	ActivityMap m_sessions;

};
typedef IceUtil::Handle<CActivityThread> CActivityThreadPtr;

#endif
