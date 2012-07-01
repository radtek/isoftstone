#include <qapplication.h>
#include <qtextcodec.h>
#include <QtGlobal>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QMainWindow>
#include <QtGui/QSplashScreen>
#include <QSharedMemory>
#include <QMessageBox>

#include "mainwindow.h"
#include "server.h"

QFile* g_LogFile = NULL;
QTextStream* g_LogStream = NULL;

void visMessageOutput(QtMsgType type, const char *msg)
{

	// 保证在屏幕输出
	fprintf(stdout, "%s\n", msg);
	fflush(stdout);

	QString strTxt;
	switch (type)
	{
	case QtDebugMsg:
		strTxt = QString("\nDebug:") + QString::fromLocal8Bit(msg);
		break;
	case QtWarningMsg:
		strTxt = QString("\nWarning:") + QString::fromLocal8Bit(msg);
		break;
	case QtCriticalMsg:
		strTxt = QString("\nCritical:") + QString::fromLocal8Bit(msg);
		break;
	case QtFatalMsg:
		strTxt = QString("\nFatal:") + QString::fromLocal8Bit(msg);
		abort();
	}
	if (g_LogFile == NULL)
	{
		QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm") + ".log";
		QByteArray qbr = qgetenv(PROJECT_HOME);
		QString logDir = QObject::tr(qbr.data() )+ "/log/" ;

		QDir dir = QDir::home();
		if (dir.exists(logDir) == false)
		{
			dir.mkdir(logDir);
		}

		fileName = logDir + fileName;
		g_LogFile = new QFile(fileName);
		g_LogFile->open(QIODevice::WriteOnly | QIODevice::Append);

		g_LogStream = new QTextStream(g_LogFile);
	}
	if (g_LogStream)
	{
		*g_LogStream << strTxt;
		g_LogStream->flush();
	}
}

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	//程序运行一个实例
// 	QSharedMemory mem(QString::fromLocal8Bit("SystemObject"));
// 	if (!mem.create(1) && mem.error() == QSharedMemory::AlreadyExists)
// 	{
// 		QMessageBox::information(0,  QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("对不起，程序已经运行！"), QMessageBox::Ok);
// 		return 0;
// 
	QStringList args = QCoreApplication::arguments();
	if (!(args.count() > 1 && args[1] == "stdout"))
	{
		qInstallMsgHandler(visMessageOutput);
	}
	
	QThreadPool::globalInstance()->setMaxThreadCount(10);

	CService service;
	service.start();
	CMainWindow mainwindow;
	//mainwindow.setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

	mainwindow.showMaximized();
	QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

	int iret = app.exec();
	
	service.stop();
	if (g_LogStream)
	{
		g_LogFile->close();
		qFree(g_LogStream);
		qFree(g_LogFile);
	}

	return iret;
}

