
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
	QTextCodec::setCodecForTr(codec); // tr() ��ʹ�ô� codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() ��ʹ�ô� codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() ��ʹ�ô� codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	readType("attr.ini",attrTypeMap);

	std::string dir;
	std::cout << "�����ļ���·��:";
	std::cin >> dir;
	if (dir.length() == 1)
	{
		dir = "D:/vis/data/graph_client/display";
	}

	while (true && std::cin.good())
	{
		std::cout << "\n �������:\n";
		std::cout << "\n 0 ���� info.h:\n";
		std::cout << "\n 1 ����ö��:\n";
		std::cout << "\n 2 ���ɴ��л���Ϣ:\n";
		std::cout << "\n 3 ��������ʵ����:\n";
		std::cout << "\n 4 ���ɹ���:\n";

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

		std::cout << "������ɣ�!!" ;
	}

over:
    return 0;
}

