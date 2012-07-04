
#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <list>
#include <map>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

#include "thread.h"
#include "tcpclient.h"

class CService : public QObject
{
	Q_OBJECT

public:

	CService();

	void start();

	void stop();

private slots:

	void slot_newConnection();
	void slot_disconnected();
	void slot_readRead();

private:

	void init();
	void initServer();

private:

	std::vector<CThread*>	m_Threads;		/* �̶߳����� */
	QTcpServer				m_localServer;	/* ���ط�����ն� */
	std::map<QString,QTcpSocket*>	m_clientMap;
	
	
};

#endif