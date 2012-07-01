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

#ifndef QPIXELTOOL_H
#define QPIXELTOOL_H

#include <qwidget.h>
#include <qpixmap.h>

QT_BEGIN_NAMESPACE

class QPixelTool : public QWidget
{
    Q_OBJECT
public:
    QPixelTool(QWidget *parent = 0);
    ~QPixelTool();

    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

    QSize sizeHint() const;

    void setPreviewImage(const QImage &image);

public slots:
    void setZoom(int zoom);
    void setGridSize(int gridSize);
    void toggleGrid();
    void toggleFreeze();
    void setZoomVisible(bool visible);
    void copyToClipboard();
    void saveToFile();
    void increaseGridSize() { setGridSize(m_gridSize + 1); }
    void decreaseGridSize() { setGridSize(m_gridSize - 1); }
    void increaseZoom() { setZoom(m_zoom + 1); }
    void decreaseZoom() { setZoom(m_zoom - 1); }

private:
    void grabScreen();
    void startZoomVisibleTimer();
    void startGridSizeVisibleTimer();

    bool m_freeze;
    bool m_displayZoom;
    bool m_displayGridSize;
    bool m_mouseDown;
    bool m_autoUpdate;
    bool m_preview_mode;

    int m_gridActive;
    int m_zoom;
    int m_gridSize;

    int m_updateId;
    int m_displayZoomId;
    int m_displayGridSizeId;

    int m_currentColor;

    QPoint m_lastMousePos;
    QPoint m_dragStart;
    QPoint m_dragCurrent;
    QPixmap m_buffer;

    QSize m_initialSize;

    QImage m_preview_image;
};

QT_END_NAMESPACE

#endif // QPIXELTOOL_H
