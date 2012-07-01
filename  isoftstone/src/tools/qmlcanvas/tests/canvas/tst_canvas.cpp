/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qtest.h>
#include <QTextDocument>
#include <QDir>
#include <QtDeclarative>
#include <QDeclarativeEngine>
#include "../../src/canvas.h"

class tst_canvas : public QObject

{
    Q_OBJECT

private slots:
    void create();
    void setInterval();
    void setTimeout();
    void initTestCase();

private:
    QDeclarativeEngine engine;
};

void tst_canvas::initTestCase()
{
    const char *uri ="com.nokia.qmlcanvas";
    qmlRegisterType<Canvas>(uri, 1, 0, "Canvas");
    qmlRegisterType<Context2D>(uri, 1, 0, "Context2D");
    qmlRegisterUncreatableType<CanvasImage>(uri, 1, 0, "CanvasImage", QString());
    qmlRegisterUncreatableType<CanvasGradient>(uri, 1, 0, "Gradient", QString());
}


void tst_canvas::create()
{
    QString componentStr = "import Qt 4.7 \n"
            "import com.nokia.qmlcanvas 1.0\n"
            "Canvas { width: 300; height: 300 }";
    QDeclarativeComponent component(&engine);
    component.setData(componentStr.toLatin1(), QUrl::fromLocalFile(""));
    Canvas *obj = qobject_cast<Canvas*>(component.create());
    QVERIFY(obj != 0);
    QCOMPARE(obj->width(), 300.);
    QCOMPARE(obj->height(), 300.);
    QCOMPARE(obj->fillMode(), Canvas::Stretch);
    delete obj;
}

void tst_canvas::setTimeout()
{
    QString componentStr =
            "import Qt 4.7 \n"
            "import com.nokia.qmlcanvas 1.0\n"
            "Canvas {"
            "property int count:0;"
            "function test() { count++; }"
            "Component.onCompleted:setTimeout(test, 0)"
            "}";
    QDeclarativeComponent component(&engine);
    component.setData(componentStr.toLatin1(), QUrl::fromLocalFile(""));
    Canvas *obj = qobject_cast<Canvas*>(component.create());
    QTest::qWait(100);
    QCOMPARE(obj->property("count").toInt(), 1);
    delete obj;

    // Starts two timers where the second cancels the first
    componentStr =
            "import Qt 4.7 \n"
            "import com.nokia.qmlcanvas 1.0\n"
            "Canvas {"
            "property int count:0;"
            "function test() { count++ } "
            "function cancel() { clearTimeout(test) } "
            "Component.onCompleted:{ setTimeout(test, 50); setTimeout(cancel, 25); }"
            "}";
    QDeclarativeComponent component2(&engine);
    component2.setData(componentStr.toLatin1(), QUrl::fromLocalFile(""));
    obj = qobject_cast<Canvas*>(component2.create());
    QTest::qWait(100);
    QCOMPARE(obj->property("count").toInt(), 0);
    delete obj;
}

void tst_canvas::setInterval()
{
    QString componentStr =
            "import Qt 4.7 \n"
            "import com.nokia.qmlcanvas 1.0\n"
            "Canvas {"
            "property int count:0;"
            "function test() { count++; }"
            "Component.onCompleted:setInterval(test, 40)"
            "}";
    QDeclarativeComponent component(&engine);
    component.setData(componentStr.toLatin1(), QUrl::fromLocalFile(""));
    Canvas *obj = qobject_cast<Canvas*>(component.create());
    QTest::qWait(100);
    QCOMPARE(obj->property("count").toInt(), 2);
    delete obj;
}


QTEST_MAIN(tst_canvas)

#include "tst_canvas.moc"
