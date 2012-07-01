
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
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif
	initFuncPointer();

	QString dirName = "";

	readSymbols("symbols.xml",g_SymbolMap);

	while (true && std::cin.good())
	{
		std::cout << "\n 输入操作:\n";
		std::cout << "\n 0 转换g文件到svg:\n";
		std::cout << "\n 1 批量生成svg:\n";
		std::cout << "\n 2 写入图元符号(symbol):\n";
		std::cout << "\n 3 读取图元符号:\n";

		int nOp = 0;
		std::cin >> nOp;
		switch(nOp)
		{
		case 0:
			{
				std::string filename;
				std::cout << "输入文件路径:";
				std::cin >> filename;
				QString svgFile;
				transformG2SVG(QString::fromStdString(filename),svgFile);
			}
			break;
		case 1:
			{
				std::string dir;
				std::cout << "输入文件夹路径:";
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
				std::cout << "输入文件夹路径:";
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

		std::cout << "操作完成！!!" ;
	}

over:
	return 0;

}

