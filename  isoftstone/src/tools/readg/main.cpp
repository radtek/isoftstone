
#include "func.h"

bool bMultiThread = false;

QMap<QString,QString> attrTypeMap;
QMap<QString,QString> valueMap;

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

	readType("attr.ini",attrTypeMap);

	std::string dir;
	std::cout << "输入文件夹路径:";
	std::cin >> dir;
	if (dir.length() == 1)
	{
		dir = "D:/vis/data/graph_client/display";
	}

	while (true && std::cin.good())
	{
		std::cout << "\n 输入操作:\n";
		std::cout << "\n 0 生成 info.h:\n";
		std::cout << "\n 1 生成枚举:\n";
		std::cout << "\n 2 生成串行化信息:\n";
		std::cout << "\n 3 生成派生实现类:\n";
		std::cout << "\n 4 生成工厂:\n";

		int nOp = 0;
		std::cin >> nOp;
		switch(nOp)
		{
		case 0:
			createInfo_H(dir);
			break;
		case 1:
			printClass("info.h",1);
			break;
		case 2:
			printClass("info.h",2);
			break;
		case 3:
			printClass("info.h",3);
			break;
		case 4:
			printClass("info.h",4);
			break;
		default:
			goto over;
		}

		std::cout << "操作完成！!!" ;
	}

over:
    return 0;
}

