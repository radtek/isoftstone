
#ifndef VTOOLBAR_H
#define VTOOLBAR_H

#include <QToolBar>
#include <QPaintEvent>
#include <QPainter>

#include "customdef.h"

class EXPORT_WIDGET CToolBar : public QToolBar
{
	Q_OBJECT
public:
    explicit CToolBar(QWidget *parent = 0);
    explicit CToolBar(const QString& str,QWidget* parent=0);


protected:
    void paintEvent(QPaintEvent *event);


private:
    void draw(QPainter* painter);
};

#endif
