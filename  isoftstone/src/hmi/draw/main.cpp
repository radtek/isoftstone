
#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(diagramscene);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	QThreadPool::globalInstance()->setMaxThreadCount(10);

    QApplication app(argv, args);
    MainWindow mainWindow;
   // mainWindow.setGeometry(100, 100, 800, 500);
	mainWindow.showMaximized();

    return app.exec();
}
