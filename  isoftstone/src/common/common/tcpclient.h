#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QBuffer>

#include "common.h"

static const int MaxBufferSize = 102400;
static const int DefaultInterval = 20;

class EXPORT_COMMON CTcpClient : public QTcpSocket
{
	Q_OBJECT

public:

	CTcpClient(bool bTimer = true,QObject *parent = 0);
	void setTimeout(int sec);
	bool connect(const QString& host,int port);
	void disconnect();
	bool isConnected();
	bool reconnect();

signals:

	void newPackage(QByteArray br);

private slots:

	void slot_Connected();
	void slot_ReadyRead();
	void slot_Timeout();

private:

	void processData();

private:

	QTimer	m_Timer;	/* 如果断开定时重练，如果连接定时发送ping指令 */
	bool	m_bTimer;	/* 是否开启重练机制 */
	QBuffer m_buffer;	/* 采用buffer的目的是因为它提供了IODEVICE的操作，可以方便定位和查找 */
	QByteArray* m_byteArray;/* 缓存容器 */
	QString m_host;	
	int		m_port;
	int		m_timeout;

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