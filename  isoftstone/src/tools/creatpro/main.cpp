
#include <QCoreApplication>
#include <QApplication>
#include <QTextCodec>
#include <QStringList>
#include <QDir>
#include <QUuid>


#include "creatpro.h"
#include "createsln.h"

// qmake -tp vc -r 
int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));  //设置为utf8  

#ifdef WIN32
	setlocale(LC_ALL,"");
#endif
    QApplication a(argc, argv);
	
	//输入命令行参数
    QStringList lstArgs = QCoreApplication::arguments();

	//找到本文件下的子文件
    if(lstArgs.count() > 1)
    {
        QString mainDir = lstArgs[1];
        if(QDir::home().exists(mainDir))
        {
			int op = 2;
			if(op == 1)
			{
				CCreatPro cp;
				cp.execute(mainDir);
			}
			else if (op == 2)
			{
				CCreateSln sln;
				sln.setSlnName(mainDir);
				sln.run();
			}
        }
        return -1;
    }
    return -1;
}
