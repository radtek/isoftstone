
#include "toolbar.h"

CToolBar::CToolBar(QWidget *parent) :QToolBar(parent)
{
    this->setContentsMargins(0,0,0,0);
}

CToolBar::CToolBar(const QString &str, QWidget *parent):QToolBar(str,parent)
{
    this->setContentsMargins(0,0,0,0);
}

void CToolBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    draw(&painter);

    QToolBar::paintEvent(event);
}


void CToolBar::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0,0),QPoint(0,height()));
//    bgGradient.setColorAt(0.0,QColor(250,250,250));
    bgGradient.setColorAt(0.0,START_COLOR);
    bgGradient.setColorAt(1.0,END_COLOR);
//    bgGradient.setColorAt(1.0,QColor(170,170,170));
//    bgGradient.setColorAt(1.0,QColor(250,250,250));

    painter->setBrush(bgGradient);
    painter->drawRect(rect());

    painter->restore();
}
