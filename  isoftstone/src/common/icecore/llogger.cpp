
#include "llogger.h"

#include <log4cplus/tstring.h>
#include <IceUtil/MutexPtrLock.h>
#include <exception>
#include <iostream>
#include <string>

#include "macro2.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

CLogger* CLogger::s_logger = NULL;
using IceUtil::Mutex;


GLOBALMUTEX

CLogger* CLogger::instance(void)
{
	if (s_logger == NULL)
	{
		IceUtilInternal::MutexPtrLock<IceUtil::Mutex> lock(staticMutex);
		if (s_logger == NULL)
		{
			s_logger = new CLogger();
		}
	}
	return s_logger;
}

CLogger::CLogger(): mutex(LOG4CPLUS_MUTEX_CREATE)
{
	m_isDestory = false;
	m_logName.clear();
	m_logServerIP.clear();
	m_logServerPort.clear();
}

CLogger::~CLogger()
{
//	IceUtilInternal::MutexPtrLock<IceUtil::Mutex> lock(staticMutex);
	if (!m_isDestory)
	{
		destroy();
	}
}

void CLogger::setLogFile(const std::string& logFile)
{
#ifdef UNICODE
	m_logName = log4cplus::helpers::towstring(logFile);
#else
	m_logName = logFile;
#endif // UNICODE
	
}

void CLogger::setLogFile(const char* logFile)
{
// #ifdef UNICODE
// 	m_logName = log4cplus::helpers::towstring(logFile);
// #else
	m_logName = logFile;
//#endif // UNICODE
}

void CLogger::setLogServer(const std::string& serverIp,const std::string& serverPort)
{
// #ifdef UNICODE
// 	m_logServerIP = log4cplus::helpers::towstring(serverIp);
// #else
	m_logServerIP = serverIp;
//#endif // UNICODE
	
	m_logServerPort = serverPort;
}

void CLogger::setLogAppend(EAppendLogType type)
{
	m_appendType = type;
}

void CLogger::init()
{
	try 
	{
		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
		log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("log"));
		log4cplus::Logger::getRoot().setLogLevel(NOT_SET_LOG_LEVEL);

		if ((m_appendType & eConsoleAppend) == eConsoleAppend)
		{
			m_append_console = new ConsoleAppender();
			m_append_console->setLayout( std::auto_ptr<Layout>(new log4cplus::TTCCLayout()) );
			log4cplus::Logger::getRoot().addAppender(m_append_console);
			m_append_console->setName(LOG4CPLUS_TEXT("console"));
		}
		if ((m_appendType & eFileAppend) == eFileAppend)
		{
			m_append_file = new RollingFileAppender(m_logName, 200*1024, 6);  
			m_append_file->setLayout( std::auto_ptr<Layout>(new log4cplus::TTCCLayout()) ); 
			log4cplus::Logger::getRoot().addAppender(m_append_file);
			m_append_file->setName(LOG4CPLUS_TEXT("filelog"));
		}
		if ((m_appendType & eSocketAppend) == eSocketAppend)
		{
			if (!m_logServerIP.empty() && !m_logServerPort.empty())
			{
				m_append_socket = new SocketAppender(m_logServerIP, atoi(m_logServerPort.c_str()));
				m_append_socket->setLayout( std::auto_ptr<Layout>(new log4cplus::TTCCLayout()) ); 
				log4cplus::Logger::getRoot().addAppender(m_append_socket);
				m_append_socket->setName(LOG4CPLUS_TEXT("socketlog"));
			}
		}
		if (m_appendType <= eNoneAppend || m_appendType > eAllAppend)
		{
			m_append_None = new NullAppender();
			m_append_None->setLayout( std::auto_ptr<Layout>(new log4cplus::TTCCLayout()) ); 
			log4cplus::Logger::getRoot().addAppender(m_append_None);
			m_append_None->setName(LOG4CPLUS_TEXT("nonelog"));
		}
	}
	catch(std::exception& e)
	{
		LOG4CPLUS_FATAL(log4cplus::Logger::getRoot(), "日志系统初始化发生异常: " << e.what());
	}
	catch(...) 
	{
		LOG4CPLUS_FATAL(log4cplus::Logger::getRoot(), "日志系统初始化发生未知异常！！");
	}

}

void CLogger::destroy()
{
	log4cplus::Logger::shutdown();
	m_isDestory = true;
}

void CLogger::trace(const std::string& msg)
{
	LOG4PLUS_LOG(TRACE,log4cplus::Logger::getRoot(),msg.c_str());
}

void CLogger::info(const std::string& msg)
{
	LOG4PLUS_LOG(INFO,log4cplus::Logger::getRoot(),msg.c_str());
}

void CLogger::debug(const std::string& msg)
{
	LOG4PLUS_LOG(DEBUG,log4cplus::Logger::getRoot(),msg.c_str());
}

void CLogger::warn(const std::string& msg)
{
	LOG4PLUS_LOG(WARN,log4cplus::Logger::getRoot(),msg.c_str());
}


void CLogger::error(const std::string& msg)
{
	LOG4PLUS_LOG(ERROR,log4cplus::Logger::getRoot(),msg.c_str());
}


void CLogger::fatal(const std::string& msg)
{
	LOG4PLUS_LOG(FATAL,log4cplus::Logger::getRoot(),msg.c_str());
}

void CLogger::trace(const char* msg)
{
	LOG4PLUS_LOG(TRACE,log4cplus::Logger::getRoot(),msg);
}

void CLogger::info(const char* msg)
{
	LOG4PLUS_LOG(INFO,log4cplus::Logger::getRoot(),msg);
}

void CLogger::debug(const char* msg)
{
	LOG4PLUS_LOG(DEBUG,log4cplus::Logger::getRoot(),msg);
}

void CLogger::warn(const char* msg)
{
	LOG4PLUS_LOG(WARN,log4cplus::Logger::getRoot(),msg);
}


void CLogger::error(const char* msg)
{
	LOG4PLUS_LOG(ERROR,log4cplus::Logger::getRoot(),msg);
}


void CLogger::fatal(const char* msg)
{
	LOG4PLUS_LOG(FATAL,log4cplus::Logger::getRoot(),msg);
}

std::string CLogger::getFormatString(const char *szFormat, ... )
{
	va_list argp;
	va_start (argp, szFormat);
	std::string formatStr = getFormatWithList(szFormat,argp);
	return formatStr;
}

std::string CLogger::getFormatWithList(const char *szFormat,va_list& argp)
{
	int nLen = -1;
	std::string formatStr = "";
	char* acBuffer = NULL;
#if defined(_WIN32)
	nLen =  _vscprintf( szFormat, argp ) + 1;
	acBuffer = (char*)malloc( nLen * sizeof(char) );
	nLen = vsprintf_s(acBuffer,nLen,szFormat,argp);
#else
	acBuffer = malloc(MAX_BUFFER_LENGTH + 1);
	nLen = sprintf_s(acBuffer,szFormat,argp);
#endif

	cout << nLen << endl; 
	formatStr = acBuffer ;
	free(acBuffer);
	return formatStr;
}
void CLogger::log( const char *fileName, const char *functionName, int line, const char* formatstr, int type )
{
	std::stringstream sstream;
	sstream << fileName << " " << functionName << " " << line << " " << formatstr << std::endl;
	switch(type)
	{
	case eLogDebug:
		debug(sstream.str());
		break;
	case eLogInfo:
		info(sstream.str());
		break;
	case eLogWarn:
		warn(sstream.str());
		break;
	case eLogError:
		error(sstream.str());
		break;
	case eLogFatal:
		fatal(sstream.str());
		break;
	case eLogTrace:
	default:
		trace(sstream.str());
		break;
	}
}

void CLogger::log( const char *fileName, const char *functionName, int line, int type ,const char *szFormat, ...)
{
	va_list argp;
	va_start (argp, szFormat);
	std::string formatStr = getFormatWithList(szFormat,argp);
	va_end (argp);
	log(fileName,functionName,line,formatStr.c_str(),type);
}
