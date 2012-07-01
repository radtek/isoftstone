
#include "thermometer.h"

CThermoMeterItem::CThermoMeterItem(QGraphicsItem *parent) :QGraphicsObject(parent)
{
    initVariables();
}

void CThermoMeterItem::initVariables()
{
    m_markClr=Qt::white;
    graphcolor=Qt::darkGreen;
    m_value=0;
    m_currentValue=0;
    m_bucketWidth=boundingRect().width()/3;
    m_markSpace=(qreal)boundingRect().width()/4;
    m_topSpace=(qreal)boundingRect().height()/15;
    updateTimer=new QTimer(this);
    updateTimer->setInterval(10);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));
    m_bReverse=false;
}

QRectF CThermoMeterItem::boundingRect() const
{
	return QRectF(0,0,80,200);
}	

void CThermoMeterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->save();
    resetDrawingVariables(painter);
    drawBackground(painter);
    drawMark(painter);
    drawBucket(painter);
    drawGraph(painter);
	painter->restore();
}

void CThermoMeterItem::drawBackground(QPainter *painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,boundingRect().height()));
    bgGradient.setColorAt(0.0,QColor(200,200,200));
    bgGradient.setColorAt(0.2,QColor(100,100,100));
    bgGradient.setColorAt(0.9,QColor(100,100,100));
    bgGradient.setColorAt(1.0,QColor(200,200,200));

    painter->setBrush(bgGradient);
    painter->drawRect(boundingRect());
    painter->restore();
}
void CThermoMeterItem::drawMark(QPainter *painter)
{
    painter->save();

    qreal initY=m_topSpace;
    qreal initX=m_markSpace;
    qreal length=boundingRect().height()-2*m_topSpace;
    qreal increment=length/100;
    painter->setPen(m_markClr);

    // draw vertical line
    QPointF topPot(m_markSpace,m_topSpace);
    QPointF bottomPot(m_markSpace,boundingRect().height()-m_topSpace);
    painter->drawLine(topPot,bottomPot);

    int vvalue=100;
    QString strValue;
    for(int i=0;i<=100;i++)
    {
        if(i%10==0)
        {
            QPointF leftPot(initX+LONG3,initY);
            QPointF rightPot(initX,initY);
            painter->drawLine(leftPot,rightPot);

            strValue=tr("%1").arg(vvalue);
            qreal fontWidth=painter->fontMetrics().width(strValue);
            qreal fontHeight=painter->fontMetrics().height();

            QPointF textPot(initX-fontWidth-5,initY+fontHeight/2);
            painter->drawText(textPot,strValue);

            vvalue-=10;

        }
        else if(i%5==0 && i%10!=0)
        {
            QPointF leftPot(initX+OK3,initY);
            QPointF rightPot(initX,initY);
            painter->drawLine(leftPot,rightPot);
        }
        else
        {
            QPointF leftPot(initX+SHORT3,initY);
            QPointF rightPot(initX,initY);
            painter->drawLine(leftPot,rightPot);
        }
        initY+=increment;
    }
    painter->restore();
}

void CThermoMeterItem::SetGraphColor(QColor c)
{
    this->graphcolor=c;
}


void CThermoMeterItem::drawGraph(QPainter *painter)
{
    painter->save();
    qreal bucketHeight=m_bucketRect.height();
    qreal increment=(qreal)bucketHeight/100;

    QPointF bottomRightPot(m_bucketRect.bottomRight());
    qreal currentY=m_currentValue*increment;

    QPointF topLeftPot(m_bucketRect.topLeft().x(),m_bucketRect.bottomLeft().y()-currentY);
    QRectF graphRect(topLeftPot,bottomRightPot);
    painter->setPen(Qt::NoPen);

    QLinearGradient graphGradient(graphRect.topLeft(),graphRect.topRight());
    painter->setOpacity(0.7);

    graphGradient.setColorAt(0.0,this->graphcolor);

    painter->setBrush(graphGradient);
    painter->drawRect(graphRect);
    painter->restore();
}

void CThermoMeterItem::drawBucket(QPainter *painter)
{
    painter->save();

    QPointF bucketTopLeftPot(m_markSpace+MARK_BUCKET_SPACE3,m_topSpace);
    QPointF bucketBottomRightPot(m_markSpace+MARK_BUCKET_SPACE3+m_bucketWidth,boundingRect().height()-m_topSpace);
    QRectF bucketRect(bucketTopLeftPot,bucketBottomRightPot);
    m_bucketRect=bucketRect;

    QLinearGradient bucketGradient(bucketRect.topLeft(),bucketRect.topRight());
    bucketGradient.setColorAt(0.0,QColor(100,100,100));    
    bucketGradient.setColorAt(0.6,QColor(200,200,200));
    bucketGradient.setColorAt(1.0,QColor(150,150,150));

    painter->setPen(Qt::NoPen);
    painter->setBrush(bucketGradient);
    painter->drawRect(bucketRect);
    painter->restore();
}

void CThermoMeterItem::resetDrawingVariables(QPainter *painter)
{
    m_markSpace=(qreal)boundingRect().width()/4;
    m_bucketWidth=(qreal)boundingRect().width()/3;
    m_topSpace=(qreal)boundingRect().height()/15;
}


void CThermoMeterItem::setValue(qreal value)
{
    if(value>m_value)
    {
        m_bReverse=false;
    }
    else if(value<m_value)
    {
        m_bReverse=true;
    }
    else
    {
        return ;
    }
     m_value=value;
    updateTimer->start();
}

void CThermoMeterItem::setMarkColor(const QColor &clr)
{
    m_markClr=clr;
    update();
}


void CThermoMeterItem::UpdateGraph()
{
    if(!m_bReverse)
    {
        m_currentValue+=0.5;
        if(m_currentValue>=m_value)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_currentValue-=0.5;

        if(m_currentValue<=m_value)
        {
            updateTimer->stop();
        }
    }
    update();
}
