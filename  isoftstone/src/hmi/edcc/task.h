
#ifndef TASK_H
#define TASK_H

#include <QRunnable>

// ���ݲɼ�����

class QextSerialBase;

class CDCTask : public QRunnable
{
public:

	CDCTask(QextSerialBase* pSerial);

	virtual void run();

private:

	QextSerialBase*	m_serial;

};

// ���ݴ�������
class CDealDataTask : public QRunnable
{
public:

	CDealDataTask();

	virtual void run();

};

#endif