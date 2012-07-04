
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

	std::vector<CThread*>	m_Threads;		/* 线程对象类 */
	QTcpServer				m_localServer;	/* 本地服务接收端 */
	std::map<QString,QTcpSocket*>	m_clientMap;
	
	CTcpClient				m_localClient;	/*  连接上位机客户端 */
	QextSerialBase*			m_serialComm;	/*  串口通信接口 */
	QIODevice*				m_comProxy;		/* 数据上传方式代理，可以为网络或者串口方式 */
};

#endif