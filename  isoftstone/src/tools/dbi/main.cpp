
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QTextCodec>
#include <QtCore>

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() ��ʹ�ô� codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() ��ʹ�ô� codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() ��ʹ�ô� codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif


    return 0;
}

