
#ifndef TASK_H
#define TASK_H

#include <QRunnable>

// 数据采集任务

class QextSerialBase;

class CDCTask : public QRunnable
{
public:

	CDCTask(QextSerialBase* pSerial);

	virtual void run();

private:

	QextSerialBase*	m_serial;

};

// 数据处理任务
class CDealDataTask : public QRunnable
{
public:

	CDealDataTask();

	virtual void run();

};

#endif