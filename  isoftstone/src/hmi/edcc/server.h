
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
#include "qextserialbase.h"

class CService : public QObject
{
	Q_OBJECT

public:

	CService();
	~CService();

	void start();
	void stop();

private slots:

	void slot_newConnection();
	void slot_disconnected();
	void slot_readRead();

private:

	void init();
	void initServer();
	void initClient();
	void initSerial();

private:

	std::vector<CThread*>	m_Threads;		/* �̶߳����� */
	QTcpServer				m_localServer;	/* ���ط�����ն� */
	std::map<QString,QTcpSocket*>	m_clientMap;
	
	CTcpClient				m_localClient;	/*  ������λ���ͻ��� */
	QextSerialBase*			m_serialComm;	/*  ����ͨ�Žӿ� */
	QIODevice*				m_comProxy;		/* �����ϴ���ʽ��������Ϊ������ߴ��ڷ�ʽ */
};

#endif