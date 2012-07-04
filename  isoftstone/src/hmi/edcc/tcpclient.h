#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>

static const int MaxBufferSize = 102400;
static const int PingInterval = 30;

class CTcpClient : public QTcpSocket
{
	Q_OBJECT

public:

	CTcpClient(bool bPing = false,QObject *parent = 0);

signals:

	void newPackage(QByteArray br);

private slots:

	void slot_Connected();
	void slot_ReadyRead();
	void slot_Ping();

private:

	void processData();

	QTimer	m_pingTimer;
	bool	m_bPing;
	QByteArray m_buffer;
};

class CClientProxy : public QObject
{
	Q_OBJECT

public:

	CClientProxy(QTcpSocket* socket);
	
signals:

	void newPackage(QByteArray br);

private:

	void processData();

private:

	QTcpSocket* m_tcpSocket;

};

#endif