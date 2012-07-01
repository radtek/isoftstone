
#include "Logger.h"

#include <QtGlobal>
#include <QDateTime>
#include <QByteArray>
#include <QDir>
#include <iostream>
#include <QString>

static LoggerI* s_loggerInstance = NULL;

Logger* LoggerI::instance()
{
	if (s_loggerInstance == NULL)
	{
		s_loggerInstance = new LoggerI("Load_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm")," : ");
	}
	return s_loggerInstance;
}

LoggerI::LoggerI(const QString& file,const QString& prefix)
{
    if(!prefix.isEmpty())
    {
        m_prefix = prefix + ": ";
    }

	m_file = NULL;
	m_bTag = true;

    if(!file.isEmpty())
    {
		QByteArray bar = qgetenv("VISDIR");
		QString logDir = QObject::tr(bar.data() )+ "/log/" ;

		QDir dir = QDir::home();
		if (dir.exists(logDir) == false)
		{
			dir.mkdir(logDir);
		}

        m_fileName = logDir + file + ".log";
		m_file = new QFile(m_fileName);
		m_file->open(QIODevice::WriteOnly | QIODevice::Append);
		m_out.setDevice(m_file);
    }
}


LoggerI::~LoggerI()
{
	if (m_file)
	{
		m_out.flush();
		m_file->close();

		delete m_file;
	}
	
}

void LoggerI::setPrintTag(bool btag)
{
	m_bTag = btag;
}

void LoggerI::print(const QString& message)
{
    write(message, false);
}

void LoggerI::trace(const QString& category, const QString& message)
{
	QString s = "-- " + QDateTime::currentDateTime().toString() + " " + m_prefix;
    if(!category.isEmpty())
    {
        s += category + ": ";
    }
    s += message;

    write(s, true);
}

void LoggerI::warning(const QString& message)
{
	write("-! " + QDateTime::currentDateTime().toString() + " " + m_prefix + "warning: " + message, true);
}

void LoggerI::error(const QString& message)
{
    write("!! " + QDateTime::currentDateTime().toString() + " " + m_prefix + "error: " + message, true);
}


void LoggerI::write(const QString& message, bool indent)
{
	if (!m_bTag)
	{
		return;
	}

    QMutexLocker locker(&m_Mutex);

    QString s = message;

    if(indent)
    {
		int idx = 0;
        while((idx = s.indexOf("\n", idx)) != -1)
        {
            s.insert(idx + 1, "   ");
            ++idx;
        }
    }
	
	if (m_out.status() == QTextStream::Ok)
	{
		m_out << s << "\n";
		m_out.flush();
	}
    else
    {
		std::cerr << s.toStdString() << "\n";
    }
}
