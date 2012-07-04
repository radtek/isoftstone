
#include <QtNetwork>
#include "tcpclient.h"

CTcpClient::CTcpClient(bool bPing,QObject *parent): QTcpSocket(parent),m_bPing(bPing)
{
	m_pingTimer.setInterval(PingInterval*1000);

	QObject::connect(this, SIGNAL(connected()),this, SLOT(slot_Connected()));
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slot_ReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &m_pingTimer, SLOT(stop()));
    QObject::connect(&m_pingTimer, SIGNAL(timeout()), this, SLOT(slot_Ping()));

	if (m_bPing)
	{
		m_pingTimer.start();
	}
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
		m_buffer.append(br);
	} while (bytesAvailable() > 0);
	processData();
}

void CTcpClient::slot_Ping()
{
	write("ping");
}

void CTcpClient::processData()
{
	qDebug() << QString::fromLocal8Bit(m_buffer.data());

	emit newPackage(m_buffer);
	m_buffer.clear();
}

/// ´úÀíÀà

CClientProxy::CClientProxy(QTcpSocket* socket)
{
	m_tcpSocket = socket;
}

void CClientProxy::processData()
{
	
}