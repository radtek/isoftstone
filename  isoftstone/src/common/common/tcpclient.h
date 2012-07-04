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

	QTimer	m_Timer;	/* ����Ͽ���ʱ������������Ӷ�ʱ����pingָ�� */
	bool	m_bTimer;	/* �Ƿ����������� */
	QBuffer m_buffer;	/* ����buffer��Ŀ������Ϊ���ṩ��IODEVICE�Ĳ��������Է��㶨λ�Ͳ��� */
	QByteArray* m_byteArray;/* �������� */
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