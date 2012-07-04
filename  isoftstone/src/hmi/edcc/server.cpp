
#include "edcc-global.h"
#include "server.h"
#include "task.h"
#include "setting.h"
#include "config.h"

#include <QThreadPool>

CService::CService()
{
	init();
}

void CService::init()
{
	initServer();
	// 创建主线程

	// 前置采集线程

	// 定时传送线程

	// 命令消息处理线程

	// 历史数据保存线程

	// 历史与告警查询线程

	// 协议管理类
}

void CService::initServer()
{
	// 启动监听端口
	QString configFile = CConfig::instance()->getConfigDir() + CONFIG_FILE;
	CSettings cst(configFile);
	int nPort = cst.getValue("SERVER","PORT","10000").toInt();
	if (!m_localServer.listen(QHostAddress::Any,nPort)) 
	{
		qDebug() << m_localServer.errorString();
	}
	connect(&m_localServer, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));
}

void CService::start()
{
	for (int i = 0 ; i < m_Threads.size() ; i++)
	{
		m_Threads[i]->start();
	}
}

void CService::stop()
{
	for (int i = 0 ; i < m_Threads.size() ; i++)
	{
		m_Threads[i]->exit();
	}

	m_localServer.close();
}

void CService::slot_newConnection()
{
	QTcpSocket* client = m_localServer.nextPendingConnection();
	connect(client, SIGNAL(disconnected()),this, SLOT(slot_disconnected()));
	connect(client, SIGNAL(readyRead()), this, SLOT(slot_readRead()));
	QString strIp = client->peerAddress().toString();
	if (m_clientMap.find(strIp) != m_clientMap.end())
	{
		QTcpSocket* oldClient = m_clientMap[strIp];
		oldClient->disconnectFromHost();
	}
	m_clientMap.insert(std::make_pair(strIp,client));
	
}

void CService::slot_disconnected()
{
	QObject* sed = sender();
	QTcpSocket* client = qobject_cast<QTcpSocket*>(sed);
	if (client)
	{
		QString strIp = client->peerAddress().toString();
		std::map<QString,QTcpSocket*>::iterator iter = m_clientMap.find(strIp);
		if (iter != m_clientMap.end())
		{
			m_clientMap.erase(iter);
		}
		client->deleteLater();
	}
}

void CService::slot_readRead()
{
	QObject* sed = sender();
	QByteArray buffer;
	QTcpSocket* client = qobject_cast<QTcpSocket*>(sed);
	if (client)
	{
		do 
		{
			QByteArray br = client->read(MaxBufferSize);
			buffer.append(br);
		} while (client->bytesAvailable() > 0);
		qDebug() << QString::fromLocal8Bit(buffer.data());
	}
}