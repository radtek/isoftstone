
#include "thread.h"


CThread::CThread(QObject* parent):QThread(parent)
{
	m_bExit = false;
	m_internal = 500;

}

void CThread::addTask(QRunnable* task)
{
	m_tasks.push_back(task);
}

void CThread::setInternal(int ms)
{
	m_internal = ms;
}

void CThread::exit(int returnCode )
{
	m_bExit = true;
	QThread::exit(returnCode);
}

void CThread::clear()
{
	for (int i = 0 ; i < m_tasks.size() ; i++)
	{
		QRunnable* task = m_tasks[i];
		if (task->autoDelete())
		{
			delete task;
		}
	}
}

void CThread::run()
{
	while(!m_bExit)
	{
		for (int i = 0 ; i < m_tasks.size() ; i++)
		{
			if (m_bExit)
			{
				return;
			}
			m_tasks[i]->run();
		}

		msleep(m_internal);
	}
}