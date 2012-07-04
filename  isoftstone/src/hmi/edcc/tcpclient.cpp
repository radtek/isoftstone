
#include <QtNetwork>
#include "tcpclient.h"

CTcpClient::CTcpClient(bool bTimer,QObject *parent): QTcpSocket(parent),m_bTimer(bTimer)
{
	QObject::connect(this, SIGNAL(connected()),this, SLOT(slot_Connected()));
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slot_ReadyRead()));
//    QObject::connect(this, SIGNAL(disconnected()), &m_Timer, SLOT(stop()));
    QObject::connect(&m_Timer, SIGNAL(timeout()), this, SLOT(slot_Timeout()));

	m_byteArray = new QByteArray(MaxBufferSize,Qt::Uninitialized);
	m_buffer.setBuffer(m_byteArray);
	m_buffer.open(QIODevice::ReadWrite);

	setTimeout(DefaultInterval);
}

void CTcpClient::setTimeout(int sec)
{
	if (m_bTimer)
	{
		m_Timer.stop();
		m_timeout = sec;
		m_Timer.setInterval(sec*1000);
		m_Timer.start();
	}
}

bool CTcpClient::connect(const QString& host,int port)
{
	m_host = host;
	m_port = port;
	return reconnect();
}

bool CTcpClient::reconnect()
{
	bool bret = true;
	try
	{
		connectToHost(QHostAddress(m_host),m_port,QIODevice::ReadWrite);
	}
	catch(SocketError err)
	{
		qDebug() << (int)err;
		bret = false;
	}
	catch(...)
	{
		bret = false;
	}
	return bret;
}

void CTcpClient::disconnect()
{
	if (state() == QAbstractSocket::ConnectedState)
	{
		flush();
		disconnectFromHost();
	}
	// 断开连接后需要关闭定时器
	if (m_bTimer)
	{
		m_Timer.stop();
	}
	m_buffer.buffer().clear();
	m_buffer.close();
}

bool CTcpClient::isConnected()
{
	return isValid();
}

void CTcpClient::slot_Connected()
{
	qDebug() << "Connect Success!";
}

void CTcpClient::slot_ReadyRead()
{
	do 
	{
		QByteArray br = read(MaxBufferSize);
		m_buffer.buffer().append(br);

	} while (bytesAvailable() > 0);

	processData();
}

void CTcpClient::slot_Timeout()
{
	// 如果连接成功，则发送请求数据，否则重练
	if (state() == QAbstractSocket::ConnectedState)
	{
		write("ping");
	}
	else
	{
		reconnect();
	}
	
}

void CTcpClient::processData()
{
	qDebug() << QString::fromLocal8Bit(m_buffer.data());

	emit newPackage(m_buffer.buffer());
	m_buffer.buffer().clear();
}

/// 代理类

CClientProxy::CClientProxy(QTcpSocket* socket)
{
	m_tcpSocket = socket;
}

void CClientProxy::processData()
{
	
}