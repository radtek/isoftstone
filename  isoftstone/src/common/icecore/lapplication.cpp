
#include "LApplication.h"
#include "Properties.h"
#include "llogger.h"
#include "ThreadMonitor.h"
#include "ThreadPool.h"
#include "stringlist.h"

CLApplication::CLApplication(const std::string& process):m_processName(process)
{
	m_isDestroy = false;
}

CLApplication::~CLApplication()
{
	if (!m_isDestroy)
	{
		destroyApp();
	}
}

void CLApplication::startThreadPool(int minSize,int maxSize)
{
	CThreadPool::instance()->setThreadRange(minSize,maxSize);
	CThreadPool::instance()->start();
}

int CLApplication::init_begin(int argc, char* argv[])
{
	Hi_UNUSED(argc);
	std::string logName = HiRTDB::CEnvVariable::instance()->getLogPath( m_processName );
	Ice::PropertiesPtr argPropertyPtr = communicator()->getProperties();
	std::string serverConfig = HiRTDB::CEnvVariable::instance()->getConfigPath( m_processName );
	argPropertyPtr->load(serverConfig.c_str());


	CLogger::instance()->setLogFile(logName);
	CLogger::instance()->setLogServer("127.0.0.1","9998");
	CLogger::instance()->setLogAppend((EAppendLogType)(3));
	CLogger::instance()->init();


	if(argc > 1)
	{
		CLogger::instance()->error(": too many arguments\n");
		return EXIT_FAILURE;
	}

	// 会话状态监视线程
	m_sessionReaper = new CActivityThread();
	m_sessionReaper->start();

	// 开启主线程定时器,定时器自动启动
	m_timerReactorPtr = new CTimerReactor("主线程定时器");

	CThreadMonitor::instance()->start();

	try
	{
		init();
	}
	catch (IceUtil::ThreadSyscallException& e)
	{
		CLogger::instance()->fatal(e.what());
	}
	catch(Ice::Exception ex)
	{
		CLogger::instance()->fatal(ex.what());
	}
	catch (...)
	{
	}

	return EXIT_SUCCESS;
}

int CLApplication::init_wait()
{
#ifndef _SERVICE_
	callbackOnInterrupt();

	communicator()->waitForShutdown();
#endif

	for (size_t i = 0 ;i < m_adapterPtrs.size() ; i++)
	{
		m_adapterPtrs[i]->activate();
	}

	return EXIT_SUCCESS;
}

void CLApplication::addActive(int adapter,Ice::ObjectPtr objPtr , const std::string& objName)
{
	Ice::Identity ident = communicator()->stringToIdentity( objName );
	m_adapterPtrs[adapter]->add(objPtr , ident );
	
	string msg = "适配器：";
	msg.append(m_adapterPtrs[adapter]->getName());
	msg.append(" 增加活动对象 :");
	msg.append(objName);
	CLogger::instance()->info(msg);
}

void CLApplication::destroyApp()
{
	CLogger::instance()->info("开始销毁服务器应用程序对象");
	CThreadPool::instance()->destroy();
	CThreadMonitor::instance()->destroy();

	m_sessionReaper->exit();
	m_timerReactorPtr->exit();
	m_sessionReaper = NULL;
	m_timerReactorPtr = NULL;

	exitServer();

	for (size_t i = 0 ;i < i++ ; i++)
	{
		m_adapterPtrs[i]->waitForDeactivate();
	}

	communicator()->shutdown();
	CLogger::instance()->info("成功停止服务器应用程序！！");
	CLogger::instance()->destroy();

	
	m_isDestroy = true;
}

