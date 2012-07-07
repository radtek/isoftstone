
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QTextCodec>
#include <QtCore>

#include "rtdb_api.h"

#include "uiwidget.h"
#include "tabletree.h"


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
	
	CRtTable table(1);
	QVector< QVariantList > vecRows;
	table.getTableRecs(vecRows);
	table.getTableNoByName("calculator");

	QVariantList rowValue;
	table.getRecByID(3,rowValue);

	QApplication app(argc,NULL);

// 	CTableModelForm* wid = new CTableModelForm;
// 	wid->show();

	CTableTree ttree;
	ttree.show();

	app.exec();

    return 0;
}

