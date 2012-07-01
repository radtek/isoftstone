#include <QtGui/QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    CMenuMgrWindow w;

    w.show();

    return a.exec();
}
