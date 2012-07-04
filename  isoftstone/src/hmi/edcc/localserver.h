
#ifndef LOCAL_SERVER_H
#define LOCAL_SERVER_H

#include <QTcpServer>

class CLocalServer : public QTcpServer
{
	Q_OBJECT

public:
	CLocalServer(QObject *parent = 0);

signals:
	void newConnection(QTcpSocket *client);

protected:
	void incomingConnection(int socketDescriptor);
};


#endif