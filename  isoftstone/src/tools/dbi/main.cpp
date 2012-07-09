
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
// 	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); // QString::fromLocal8Bit() 会使用此 codec

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif
	
	QApplication app(argc,NULL);

	QTabWidget* tabWid = new QTabWidget;
	CDataWidget*  dataWid = new CDataWidget(tabWid);
	CModelWidget* modelWid = new CModelWidget(tabWid);
	
	tabWid->addTab(dataWid,dataWid->windowTitle());
	tabWid->addTab(modelWid,modelWid->windowTitle());
	QObject::connect(tabWid,SIGNAL(currentChanged(int)),dataWid,SLOT(slot_active_data_widget(int)));
	tabWid->showMaximized();
	app.exec();

    return 0;
}

