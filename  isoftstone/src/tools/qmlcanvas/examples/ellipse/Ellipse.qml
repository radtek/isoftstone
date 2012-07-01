/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

import Qt 4.7
import "../../Canvas"

Canvas {
    width:100
    height:100

    property variant color: "white"
    property Border border: Border{}
    property variant gradient;

    function createEllipse(ctx, aX, aY, aWidth, aHeight){
        var hB = (aWidth / 2) * .5522848,
            vB = (aHeight / 2) * .5522848,
            eX = aX + aWidth,
            eY = aY + aHeight,
            mX = aX + aWidth / 2,
            mY = aY + aHeight / 2;
        ctx.beginPath();
        ctx.moveTo(aX, mY);
        ctx.bezierCurveTo(aX, mY - vB, mX - hB, aY, mX, aY);
        ctx.bezierCurveTo(mX + hB, aY, eX, mY - vB, eX, mY);
        ctx.bezierCurveTo(eX, mY + vB, mX + hB, eY, mX, eY);
        ctx.bezierCurveTo(mX - hB, eY, aX, mY + vB, aX, mY);
        ctx.closePath();
    }

    onPaint: {
        var ctx = getContext();
        ctx.save();
        ctx.strokeStyle = border.color;
        ctx.fillStyle = color;
        ctx.lineWidth = 1
        createEllipse(ctx, 0, 0, width, height);

        var radgrad = ctx.createRadialGradient(45,45,10,52,50,30);
        if (gradient != undefined ){
            for (var i= 0 ; i< gradient.stops.length; ++i)
                radgrad.addColorStop(gradient.stops[i].position, gradient.stops[i].color);
            ctx.fillStyle = radgrad;
        }
        ctx.fill();
        ctx.stroke();
        ctx.restore();
    }
}
