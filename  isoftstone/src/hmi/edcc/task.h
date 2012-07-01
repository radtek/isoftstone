
#ifndef TASK_H
#define TASK_H

#include <QRunnable>

// 数据处理任务
class CDealDataTask : public QRunnable
{
public:

	CDealDataTask();

	virtual void run();

};

#endif