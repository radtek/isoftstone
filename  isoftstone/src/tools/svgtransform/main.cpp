
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include <QtCore>
#include <QThreadPool>

#include <iostream>

#include "common.h"
#include "transform.h"
#include "symbol.h"

QMap<QString,QString> g_SymbolMap;

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
	initFuncPointer();

	QString dirName = "";

	readSymbols("symbols.xml",g_SymbolMap);

	while (true && std::cin.good())
	{
		std::cout << "\n �������:\n";
		std::cout << "\n 0 ת��g�ļ���svg:\n";
		std::cout << "\n 1 ��������svg:\n";
		std::cout << "\n 2 д��ͼԪ����(symbol):\n";
		std::cout << "\n 3 ��ȡͼԪ����:\n";

		int nOp = 0;
		std::cin >> nOp;
		switch(nOp)
		{
		case 0:
			{
				std::string filename;
				std::cout << "�����ļ�·��:";
				std::cin >> filename;
				QString svgFile;
				transformG2SVG(QString::fromStdString(filename),svgFile);
			}
			break;
		case 1:
			{
				std::string dir;
				std::cout << "�����ļ���·��:";
				std::cin >> dir;
				if (dir.length() == 1)
				{
					dir = "D:\\iSoftStone\\graph\\element";
				}
				transformGDir(dirName);
			}

			break;
		case 2:
			{
				std::string dir;
				std::cout << "�����ļ���·��:";
				std::cin >> dir;
				if (dir.length() == 1)
				{
					dir = "D:\\iSoftStone\\graph\\element";
				}
				writeSymbols(dirName,"symbols.xml");
			}
			
			break;
		case 3:
			readSymbols("symbols.xml",g_SymbolMap);
			break;
		default:
			goto over;
		}

		std::cout << "������ɣ�!!" ;
	}

over:
	return 0;

}

