
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include <QtCore>
#include <QThreadPool>
#include <iostream>


int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	QString sourceDir;
	QString destDir;
	if (argc > 2)
	{
		sourceDir = argv[1];
		destDir = argv[2];
	}


	qDebug() << sourceDir;
	qDebug() << destDir;

	return 0;

}

