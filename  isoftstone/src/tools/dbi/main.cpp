
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QTextCodec>
#include <QtCore>
#include <QApplication>
#include <QTabWidget>

#include "modelwidget.h"
#include "datawidget.h"


int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

// 	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
// 	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
// 	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); // QString::fromLocal8Bit() ��ʹ�ô� codec

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() ��ʹ�ô� codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() ��ʹ�ô� codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() ��ʹ�ô� codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif
	
	QApplication app(argc,NULL);

	QTabWidget* tabWid = new QTabWidget;
	CModelWidget* modelWid = new CModelWidget(tabWid);
	CDataWidget*  dataWid = new CDataWidget(tabWid);
	
	tabWid->addTab(dataWid,dataWid->windowTitle());
	tabWid->addTab(modelWid,modelWid->windowTitle());
	tabWid->showMaximized();
	app.exec();

    return 0;
}

