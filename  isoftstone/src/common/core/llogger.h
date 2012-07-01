
#ifndef __LLOGGER_H__
#define __LLOGGER_H__

#include <IceUtil/Mutex.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/nullappender.h>
#include <log4cplus/appender.h>
#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/threads.h>
#include <log4cplus/streams.h>
#include <ostream>
#include <strstream>
#include "escore.h"

#  pragma warning( disable : 4099 )

#define MAX_BUFFER_LENGTH 4096

enum ELogLevel
{
	eLogDebug = 0,
	eLogTrace,
	eLogInfo,
	eLogWarn,
	eLogError,
	eLogFatal,
	eLogEnd
};

// 日志显示方式
enum EAppendLogType
{
	eNoneAppend = 0,
	eConsoleAppend = 1,
	eFileAppend = 2,
	eSocketAppend = 4,
	eConsoleFileAppend = 3,
	eConsoleSocketAppend = 5,
	eFileSocketAppend = 6,
	eAllAppend = 7
};

//#define LOG4PLUS_LOG(TYPE,LOGGER,msg) \
//LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex ) \
//LOG4CPLUS_##TYPE(LOGGER,msg); \
//LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;

#define LOG4PLUS_LOG(TYPE,LOGGER,msg) \
LOG4CPLUS_##TYPE(LOGGER,msg);

class  LIBCORE_EXPORT CLogger
{
public:

	static CLogger* instance(void);

	void destroy();

	void trace(const std::string& msg);

	void info(const std::string& msg);

	void debug(const std::string& msg);

	void warn(const std::string& msg);

	void error(const std::string& msg);

	void fatal(const std::string& msg);

	void trace(const char* msg);

	void info(const char* msg);

	void debug(const char* msg);

	void warn(const char* msg);

	void error(const char* msg);

	void fatal(const char* msg);

	void setLogFile(const std::string& logFile);

	void setLogFile(const char* logFile);

	void setLogServer(const std::string& serverIp,const std::string& serverPort);

	void setLogAppend(EAppendLogType type = eConsoleFileAppend);

	void init();

	std::string getFormatString(const char *szFormat, ...);

	std::string getFormatWithList(const char *szFormat,va_list& argp);

	void log( const char *fileName, const char *functionName, int line, const char* formatstr, int type = eLogDebug);

	void log( const char *fileName, const char *functionName, int line, int type ,const char *szFormat = "", ...);

private:

	CLogger(void);

	~CLogger(void);

	log4cplus::helpers::SharedObjectPtr<log4cplus::Appender> m_append_console;

	log4cplus::helpers::SharedObjectPtr<log4cplus::Appender> m_append_file;

	log4cplus::helpers::SharedObjectPtr<log4cplus::Appender> m_append_socket;

	log4cplus::helpers::SharedObjectPtr<log4cplus::Appender> m_append_None;

	log4cplus::tstring m_logName;

	log4cplus::tstring m_logServerIP;

	std::string m_logServerPort;

	EAppendLogType m_appendType;

	LOG4CPLUS_MUTEX_PTR_DECLARE mutex;

	bool m_isDestory;

	static CLogger* s_logger;

};

/*
	如果出现的链接错误，则是Unicode编码问题。
	log4cplus::Logger::forcedLog
	解决方案：
	1.常规-字符集-使用Unicode字符集。
	2.增加_UNICODE ，	UNICODE 预处理定义

*/

#define HI_LOG4PLUS_LOG(TYPE,logEvent)  \
{ \
std::stringstream sstream; \
sstream << logEvent; \
CLogger::instance()->TYPE(sstream.str()); \
}

#define HI_LOG4CPLUS_DEBUG(logEvent) HI_LOG4PLUS_LOG(debug,logEvent)
#define HI_LOG4CPLUS_WARN(logEvent) HI_LOG4PLUS_LOG(warn,logEvent)
#define HI_LOG4CPLUS_FATAL(logEvent) HI_LOG4PLUS_LOG(debug,logEvent)
#define HI_LOG4CPLUS_TRACE(logEvent) HI_LOG4PLUS_LOG(trace,logEvent)
#define HI_LOG4CPLUS_ERROR(logEvent) HI_LOG4PLUS_LOG(error,logEvent)
#define HI_LOG4CPLUS_INFO(logEvent) HI_LOG4PLUS_LOG(info,logEvent)

#define HI_LOG_WITH_FFL(type,...) \
	do \
	{ \
		CLogger::instance()->log_Arg(__FILE__,__FUNCTION__,__LINE__,type,__VA_ARGS__); \
	} while (0);


#endif