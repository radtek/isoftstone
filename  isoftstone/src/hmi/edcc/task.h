
#ifndef TASK_H
#define TASK_H

#include <QRunnable>

// ���ݴ�������
class CDealDataTask : public QRunnable
{
public:

	CDealDataTask();

	virtual void run();

};

#endif