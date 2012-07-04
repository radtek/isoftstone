
#include "edcc-global.h"
#include "server.h"
#include "task.h"
#include "setting.h"
#include "config.h"

#ifdef WIN32
#include "win_qextserialport.h"
#else
#include "posix_qextserialport.h"
#endif

#include <QThreadPool>

CService::CService()
{
	init();
}

CService::~CService()
{
	stop();
}

void CService::init()
{
	// tcp ��λ����λ��ͨ��
	initServer();
	initClient();

	// ���ڷ���

	initSerial();

	// �����ļ��������ݿ��װ��

	// ��ԼЭ�������

	// �������߳�

	// ǰ�òɼ��߳�

	// ��ʱ�����߳�

	// �����ش��߳�

	// ������Ϣ�����߳�

	// ��ʷ���ݱ����߳�

	// ��ʷ��澯��ѯ�߳�

	start();
	
}

void CService::initServer()
{
	// ���������˿�
	QString configFile = CConfig::instance()->getConfigDir() + CONFIG_FILE;
	CSettings cst(configFile);
	int nPort = cst.getValue("SERVER","PORT","10000").toInt();
	if (!m_localServer.listen(QHostAddress::Any,nPort)) 
	{
		qDebug() << m_localServer.errorString();
	}
	connect(&m_localServer, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));

	
}

void CService::initClient()
{
	QString configFile = CConfig::instance()->getConfigDir() + CONFIG_FILE;
	CSettings cst(configFile);
	QString host = cst.getValue("SERVER","UPPERIP","127.0.0.1");
	int port = cst.getValue("SERVER","UPPERPORT","60000").toInt();
	int timeout = cst.getValue("SERVER","UPPERTIMEOUT","20").toInt();
	m_localClient.setTimeout(timeout);
	m_localClient.connect(host,port);
}

void CService::initSerial()
{
	m_serialComm = NULL;
#ifdef WIN32
	m_serialComm = new Win_QextSerialPort("COM2");
#else
	m_serialComm = new Posix_QextSerialPort("COM2");
#endif
	m_serialComm->open();

	QRunnable* dcTask = new CDCTask(m_serialComm);
	CThread* thread = new CThread(QObject::tr("���ݲɼ��߳�"));
	thread->addTask(dcTask);
	m_Threads.push_back(thread);
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
	client->write(buffer);
	client->flush();
}