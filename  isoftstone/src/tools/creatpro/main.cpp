
#include "creatpro.h"

#include <QCoreApplication>
#include <QApplication>
#include <QStringList>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//���������в���
    QStringList lstArgs = QCoreApplication::arguments();

	//�ҵ����ļ��µ����ļ�
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
