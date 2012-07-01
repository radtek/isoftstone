
#include "progress.h"

CProgressBar::CProgressBar(QWidget *parent) :QWidget(parent)
{

    initVariables();
}

void CProgressBar::initVariables()
{
    m_nMin = 0;
    m_nMax = 100;
    m_nCurrValue = 0;
}

void CProgressBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    drawBackground(&painter);
    drawRects(&painter);
}

void CProgressBar::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient bgGradient(QPoint(0,0),QPoint(0,height()));
    bgGradient.setColorAt(0.05,QColor(240,240,240));
    bgGradient.setColorAt(0.5,Qt::white);
    bgGradient.setColorAt(0.95,QColor(240,240,240));

    painter->setBrush(QColor(70,70,70));
    painter->drawRect(rect());
    painter->restore();
}

void CProgressBar::drawRects(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing);

    qreal initX = PI_EXTRA_SPACE;
    qreal top = PI_EXTRA_SPACE;
    qreal bottom = height() - PI_EXTRA_SPACE;
    qreal rectWidth = (qreal)(width() - PI_RECT_COUNT * PI_EXTRA_SPACE)/PI_RECT_COUNT;

    for(int rectIndex = 0 ; rectIndex <= PI_RECT_COUNT ; rectIndex++)
    {
        QPointF topLeft(initX,top);
        QPointF bottomRight(initX + rectWidth,bottom);
        QRectF theRect(topLeft,bottomRight);

        if(rectIndex <= m_nCurrValue )
        {
            QLinearGradient rectGradient(theRect.topLeft(),theRect.topRight());
            rectGradient.setColorAt(0.0,QColor(85,120,0));
            rectGradient.setColorAt(0.1,QColor(70,150,20));
            rectGradient.setColorAt(0.5,QColor(70,220,20));
            rectGradient.setColorAt(0.9,QColor(70,150,20));
            rectGradient.setColorAt(1.0,QColor(85,120,0));
            painter->setBrush(rectGradient);

            if(rectIndex == m_nCurrValue)
            {
                emit sig_Finished();
            }
        }
		else
		{
            QLinearGradient rectGradient(theRect.topLeft(),theRect.topRight());
            rectGradient.setColorAt(0.0,QColor(120,120,120));
            rectGradient.setColorAt(0.1,QColor(160,160,160));
            rectGradient.setColorAt(0.5,QColor(210,210,210));
            rectGradient.setColorAt(0.9,QColor(160,160,160));
            rectGradient.setColorAt(1.0,QColor(120,120,120));
            painter->setBrush(rectGradient);
        }
        painter->drawRoundedRect(theRect,PI_ANGLE_RADIUS,PI_ANGLE_RADIUS);

        initX +=rectWidth + PI_EXTRA_SPACE;

    }

    painter->restore();
}

void CProgressBar::setRange(int min, int max)
{
    Q_ASSERT(max > min);
    m_nMin = min;
    m_nMax = max;

    m_nCurrValue = (int) (m_nMax - m_nMin )/PI_RECT_COUNT;
    update();
}

void CProgressBar::setValue(int value)
{
    m_nCurrValue = (int) value/((m_nMax - m_nMin )/PI_RECT_COUNT);
    qDebug() << __FUNCTION__ << "m_nCurrValue:" << m_nCurrValue;
    update();
}
