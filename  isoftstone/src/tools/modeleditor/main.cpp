#include <QApplication>

#include "modelwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CModelWindow mainWin;
#if defined(Q_OS_SYMBIAN)
    mainWin.showMaximized();
#else
    mainWin.show();
#endif
    return app.exec();
}
