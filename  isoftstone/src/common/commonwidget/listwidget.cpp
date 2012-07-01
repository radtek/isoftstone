
#include "listwidget.h"

CListWidget::CListWidget(QWidget *parent) :QListWidget(parent)
{

}

void CListWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(viewport());
    drawBackground(&painter);

    QListWidget::paintEvent(e);
}


void CListWidget::drawBackground(QPainter *painter)
{

#if 0
    painter->save();
    qreal thisWidth = width();
    qreal thisHeight = height();

    qreal rectWidth = (qreal)width()/VLW_H_CNT;
    qreal rectHeight = (qreal)height()/VLW_V_CNT;

    qreal initY = 0;

    painter->setPen(Qt::NoPen);
    for(int vIndex = 0 ;vIndex < VLW_V_CNT ; vIndex++)
    {
        qreal initX = 0;
        int guard = 0;
        if(vIndex%2)
        {
            guard = 0;
        }else{
            guard = 1;
        }
        for(int hIndex = 0; hIndex < VLW_H_CNT ; hIndex++)
        {
            QPointF topLeft(initX,initY);
            QPointF bottomRight(initX + rectWidth,initY + rectHeight);

            if(guard++%2)
            {
                painter->setBrush(VLW_LIGHT_COLOR);
            }else{
                painter->setBrush(VLW_DARK_COLOR);
            }

            painter->drawRect(QRectF(topLeft,bottomRight));

            initX += rectWidth;
        }

        initY += rectHeight;
    }
    painter->restore();
#endif

#if 1
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0,0),QPoint(width(),0));
    bgGradient.setColorAt(0.0,START_COLOR);
    bgGradient.setColorAt(1.0,END_COLOR);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());

    painter->restore();
#endif

}

