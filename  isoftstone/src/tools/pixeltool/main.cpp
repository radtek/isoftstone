/****************************************************************************
**
** Copyright (C) 2011 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the 
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  
** 
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
** 
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
****************************************************************************/

#include "qpixeltool.h"

#include <qapplication.h>
#include <qfileinfo.h>

QT_USE_NAMESPACE

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QPixelTool pt;

    if (app.arguments().size() > 1 && QFileInfo(app.arguments().at(1)).exists()) {
        pt.setPreviewImage(QImage(app.arguments().at(1)));
    }

    pt.show();

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    int ret = app.exec();
    return ret;
}
