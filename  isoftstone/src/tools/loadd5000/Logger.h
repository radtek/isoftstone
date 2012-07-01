
#ifndef SF_LOGGER_I_H
#define SF_LOGGER_I_H

#include <QString>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>

class Logger
{
public :

	virtual void setPrintTag(bool bTag) = 0;
	virtual void print(const QString&) = 0;
	virtual void trace(const QString&, const QString&) = 0;
	virtual void warning(const QString&) = 0;
	virtual void error(const QString&) = 0;
};


class LoggerI : public Logger
{
public:

	static Logger* instance();

    LoggerI(const QString&, const QString&);
    ~LoggerI();

	virtual void setPrintTag(bool bTag);
    virtual void print(const QString&);
    virtual void trace(const QString&, const QString&);
    virtual void warning(const QString&);
    virtual void error(const QString&);

private:

    void write(const QString&, bool);

	bool		 m_bTag;
    QString		 m_prefix;
    QTextStream  m_out;
	QMutex		 m_Mutex;
    QString		 m_fileName;
	QFile*		 m_file;

};


#endif
