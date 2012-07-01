/****************************************************************************
**
** Copyright (C) 2011 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
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

import QtQuick 1.0

BorderImage {
    id: image

    property alias text : displayText.text
    property alias currentOperation : operationText

    source: "images/display.png"
    border { left: 10; top: 10; right: 10; bottom: 10 }

    Text {
        id: displayText
        anchors {
            right: parent.right; verticalCenter: parent.verticalCenter; verticalCenterOffset: -1
            rightMargin: 6; left: operationText.right
        }
        font.pixelSize: parent.height * .6; text: "0"; horizontalAlignment: Text.AlignRight; elide: Text.ElideRight
        color: "#343434"; smooth: true; font.bold: true
    }
    Text {
        id: operationText
        font.bold: true; font.pixelSize: parent.height * .7
        color: "#343434"; smooth: true
        anchors { left: parent.left; leftMargin: 6; verticalCenterOffset: -3; verticalCenter: parent.verticalCenter }
    }
}
