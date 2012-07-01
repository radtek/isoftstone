
#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <QThreadPool>

#include "thread.h"

class CService
{
public:

	CService();

	void start();

	void stop();

private:

	void init();

private:

	std::vector<CThread*> m_Threads;
	
};

#endif