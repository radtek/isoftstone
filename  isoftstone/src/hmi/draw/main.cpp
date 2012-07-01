
#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(diagramscene);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() ��ʹ�ô� codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() ��ʹ�ô� codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() ��ʹ�ô� codec
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
