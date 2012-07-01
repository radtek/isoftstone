
#include "qmlitem.h"

#include <QTextCodec>

#include <qdeclarative.h>
#include <QDeclarativeView>
#include <QApplication>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

    QApplication app(argc, argv);

    qmlRegisterType<CQMLLine>("QmlItem", 1, 0, "Line");
	qmlRegisterType<CQMLCircle>("QmlItem", 1, 0, "Circle");
	qmlRegisterType<CQMLCircleArc>("QmlItem", 1, 0, "CircleArc");

    QDeclarativeView view;
	view.setBackgroundBrush(QBrush("black"));
    view.setSource(QUrl::fromLocalFile("app.qml"));
    view.show();
    return app.exec();
}
