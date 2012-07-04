
#ifndef THREAD_H
#define THREAD_H

#include <vector>
#include <string>
#include <QObject>
#include <QThread>
#include <QRunnable>

#include "common.h"

class EXPORT_COMMON CThread :public QThread
{
public:

	CThread(const QString& strName,QObject* parent = 0);

	void addTask(QRunnable* task);

	void setInternal(int ms = 1000);

	void exit(int returnCode = 0);

	void setThreadName(const QString& strName);
	
	QString getThreadName();

protected:

	virtual void run();

private slots:

	void clear();

private:

	bool m_bExit;

	std::vector<QRunnable*> m_tasks;

	int	m_internal;

	QString m_threadName;

};

#endif