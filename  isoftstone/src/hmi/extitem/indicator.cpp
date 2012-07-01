#include "indicator.h"

CIndicator::CIndicator(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    initVariables();
}

void CIndicator::initVariables()
{
    for(int i = 0;i < INDICATOR_COUNT; i++)
    {
        lcd[i]=new CLCDNumber(this);
    }
    m_value=0;
    m_currValue=0;
    m_bReverse=false;

    m_topSpace=0;
    m_leftSpace=0;
    m_lcdWidth=0;
    m_lcdHeight=0;
    forecolor=Qt::darkGreen;

    updateTimer=new QTimer(this);
    updateTimer->setInterval(10);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateData()));
}

QRectF CIndicator::boundingRect() const
{
	return QRectF(0,0,70,300);
}	

void CIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    drawVariables(painter);
    drawBackground(painter);
    drawLCDNums(painter);
    drawRect(painter);
    drawGraph(painter);
    drawBars(painter);
}

void CIndicator::drawVariables(QPainter *painter)
{
    m_leftSpace=boundingRect().width()/10;
    m_topSpace=boundingRect().height()/25;
    m_lcdWidth=(boundingRect().width()-(boundingRect().width()/5))/3;
    m_lcdHeight=boundingRect().height()/12;

    QPointF topLeftPot(m_leftSpace,m_topSpace);
    m_rectTopLeft=topLeftPot;
    QPointF bottomRightPot(boundingRect().width()-m_leftSpace,boundingRect().height()-2*m_topSpace-m_lcdHeight);
    m_rectBottomRight=bottomRightPot;
}

void CIndicator::drawBackground(QPainter* painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(boundingRect().width(),0));
    bgGradient.setColorAt(0.0,QColor(30,30,30));
    bgGradient.setColorAt(0.1,QColor(30,30,30));
    bgGradient.setColorAt(0.9,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(30,30,30));

    painter->setPen(Qt::NoPen);
    painter->setBrush(bgGradient);
    painter->drawRect(boundingRect());
    painter->restore();
}

void CIndicator::drawLCDNums(QPainter* painter)
{
    painter->save();

    int topLeftX=boundingRect().width()/10;
    int topLeftY=boundingRect().height()-m_topSpace-m_lcdHeight;
    QPointF topLeft(topLeftX,topLeftY);

    for(int i=0;i<INDICATOR_COUNT;i++)
    {
        lcd[i]->resize(m_lcdWidth,m_lcdHeight);
        lcd[i]->moveBy(topLeftX,topLeftY);
        topLeftX+=m_lcdWidth;
    }
    painter->restore();
}

void CIndicator::drawRect(QPainter* painter)
{
    painter->save();
    QRectF theRect(m_rectTopLeft,m_rectBottomRight);
    painter->setPen(QPen(INDICATOR_FRAME_COLOR,INDICATOR_PEN_WIDTH));
    painter->setBrush(QBrush(INDICATOR_FRAME_COLOR,Qt::Dense4Pattern));
    painter->drawRect(theRect);
    painter->restore();
}

void CIndicator::SetForeColor(QColor c)
{
    this->forecolor=c;
}

void CIndicator::drawGraph(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(Qt::transparent,INDICATOR_PEN_WIDTH));

    QLinearGradient graphGradient(m_rectTopLeft,QPointF(m_rectTopLeft.x(),m_rectBottomRight.y()));
    graphGradient.setColorAt(0.0,forecolor);
    painter->setBrush(graphGradient);

    qreal dY=(qreal)(m_rectTopLeft.y()-m_rectBottomRight.y())/100;

    qreal yValue=dY*m_currValue;

    QPointF topLeftPot(m_rectTopLeft.x()+INDICATOR_PEN_WIDTH,m_rectBottomRight.y()+yValue);
    QPointF bottomRightPot(m_rectBottomRight.x()-INDICATOR_PEN_WIDTH,m_rectBottomRight.y());
    QRectF graphRect(topLeftPot,bottomRightPot);
    painter->drawRect(graphRect);

    QString strCurrValue;
    strCurrValue=tr("%1").arg((m_currValue));
    if(m_currValue<10)
    {
        lcd[0]->setValue(0);
        lcd[1]->setValue(0);
        lcd[2]->setValue(m_currValue);
    }
    else if(m_currValue < 100 && m_currValue >= 10)
    {
        lcd[0]->setValue(0);
        lcd[1]->setValue(strCurrValue.at(0).digitValue());
        lcd[2]->setValue(strCurrValue.at(1).digitValue());
    }
    else
    {
        lcd[0]->setValue(1);
        lcd[1]->setValue(0);
        lcd[2]->setValue(0);
    }
    painter->restore();
}

void CIndicator::drawBars(QPainter* painter)
{
    painter->save();
    painter->setPen(QPen(INDICATOR_FRAME_COLOR,INDICATOR_PEN_WIDTH));

    qreal left=m_rectTopLeft.x();
    qreal right=m_rectBottomRight.x();

    qreal top=m_rectTopLeft.y();
    qreal bottom=m_rectBottomRight.y();
    qreal increment=(bottom-top)/10;

    while(top<bottom)
    {
        QPointF leftPot(left,top);
        QPointF rightPot(right,top);
        painter->drawLine(leftPot,rightPot);
        top+=increment;
    }
    painter->restore();

}

void CIndicator::UpdateData()
{
    if(m_bReverse)
    {
        m_currValue--;

        if(m_currValue<=m_value)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_currValue++;

        if(m_currValue>=m_value)
        {
            updateTimer->stop();
        }
    }
    update();
}


void CIndicator::setValue(int value)
{
    if(m_value==value)
    {
        return ;
    }

    if(value>m_value)
    {
        m_bReverse=false;
    }else{
        m_bReverse=true;
    }
    m_value=value;

    updateTimer->start();
}
