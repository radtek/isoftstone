
#include <QtNetwork>

#include "localserver.h"

CLocalServer::CLocalServer(QObject *parent): QTcpServer(parent)
{
	
}

void CLocalServer::incomingConnection(int socketDescriptor)
{

}
