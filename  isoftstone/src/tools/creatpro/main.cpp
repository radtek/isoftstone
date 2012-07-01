
#include "creatpro.h"

#include <QCoreApplication>
#include <QApplication>
#include <QStringList>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//输入命令行参数
    QStringList lstArgs = QCoreApplication::arguments();

	//找到本文件下的子文件
    if(lstArgs.count() > 1)
    {
        QString mainDir = lstArgs[1];
        if(QDir::home().exists(mainDir))
        {
            CCreatPro cp(mainDir);
            cp.execute();
        }
        return -1;
    }
    return -1;
}
