

#ifndef _LAPPLICATION_LCSH_H
#define _LAPPLICATION_LCSH_H

#include <Ice/Ice.h>
#include <Ice/Service.h>
#include <Ice/Connection.h>

#include "timerreactor.h"
#include "activitythread.h"
#include "macro2.h"
#include "icecore.h"

class LIB_ICECORE_EXPORT CLApplication : public PlatApplication
{
public:

	CLApplication(const std::string& process);

	virtual ~CLApplication();

protected:

	std::string m_processName;

	std::vector< Ice::ObjectAdapterPtr > m_adapterPtrs;

	HiRTDB::CTimerReactorPtr m_timerReactorPtr;

	CActivityThread* m_sessionReaper;

	bool m_isDestroy;

protected:

	int init_begin(int, char*[]);

	virtual int init() = 0 ;

	int init_wait();

	virtual int run(int argc, char* argv[])
	{
		init_begin(argc,argv);
		return init_wait();
	}

	void addActive(int adapter,Ice::ObjectPtr objPtr , const std::string& objName);

	void destroyApp();

	virtual void exitServer(){};

	void startThreadPool(int minSize,int maxSize);

#ifdef _SERVICE_

protected:

#if defined(_MSC_VER) && (_MSC_VER < 1500)

	virtual bool start(int argc,char* argv[])
#else

	virtual bool start(int argc,char* argv[],int& initParam)
#endif
	{
		return !run(argc,argv);
	}

	virtual bool stop()
	{
		destroyApp();
		return Ice::Service::stop();
	}

#endif
};

template <class SERVER>
int L_main(int argc, char* argv[],SERVER*& g_app)
{
#ifndef _VC80_UPGRADE
	setlocale(LC_ALL,"");
	std::locale prev_loc = std::locale::global( std::locale("chs")) ;
#endif

	SERVER app;
	g_app = &app;
	return app.main(argc, argv);
}

#endif