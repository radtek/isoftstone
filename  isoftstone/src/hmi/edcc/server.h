
#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <QTcpServer>
#include <QTcpSocket>

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

	std::vector<CThread*>	m_Threads;		/* �̶߳����� */
	QTcpServer				m_localServer;	/* ���ط�����ն� */
	
	
};

#endif