
#ifndef VLISTWIDGET_H
#define VLISTWIDGET_H

#include <QListWidget>
#include <QPainter>
#include <QPaintEvent>

#include "customdef.h"

#define VLW_H_CNT 8
#define VLW_V_CNT 16

#define VLW_LIGHT_COLOR Qt::white
#define VLW_DARK_COLOR QColor(150,150,150)

class EXPORT_WIDGET CListWidget : public QListWidget
{
Q_OBJECT
public:
    explicit CListWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);

private:
    void drawBackground(QPainter* painter);
};

#endif 
