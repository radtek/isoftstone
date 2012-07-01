
#include "macro.h"
#include "lightitem.h"

CLightItem::CLightItem(QGraphicsItem *parent) :QGraphicsObject(parent)
{
	init();
}

void CLightItem::init()
{
	m_value = 20;
	m_count = 100;
	m_angle = 45;
	m_brush = Qt::green;
	m_pen.setColor(Qt::darkGray);
	m_pen.setWidth(1);
}

QRectF CLightItem::boundingRect() const
{
	return QRectF(0,0,200,50);
}	

void CLightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	paintSun(painter);
	paintRect(painter);
}

void CLightItem::paintSun(QPainter* painter)
{
	painter->save();
	painter->setPen(m_pen);
	painter->setBrush(m_brush);
	QRectF boundRect = boundingRect();
	qreal w = boundRect.width()/20;
	qreal h = boundRect.height();
	QPointF center(boundRect.left() + w*2,boundRect.top() + h/2);
	QPointF diff(h/4,h/4);
	QRectF rect(center - diff,center + diff);
	painter->drawEllipse(center,h/4,h/4);

	for (int i = 0 ; i < 360/m_angle;i++)
	{
		QPointF pos1 = center + QPointF(h/3*COS(i*m_angle),h/3*SIN(i*m_angle));
		QPointF pos2 = center + QPointF(h/2*COS(i*m_angle),h/2*SIN(i*m_angle));

		painter->drawLine(pos1,pos2);
	}

	painter->restore();
}

void CLightItem::drawSingleRect(QPainter* painter,int num,bool bFill)
{
	QRectF boundRect = boundingRect();
	qreal w = boundRect.width()/20;
	qreal h = boundRect.height();
	if (bFill)
	{
		painter->setBrush(m_brush);
	}
	else
	{
		painter->setBrush(Qt::NoBrush);
	}
	QRectF rect(QPointF(boundRect.left() + 5*w + w*num,boundRect.top()),QSizeF(w/3*2,h));
	painter->drawRect(rect);
}

void CLightItem::paintRect(QPainter* painter)
{
	painter->save();
	painter->setPen(m_pen);

	bool bFill = false;
	for (int i = 0 ; i < 15;i++)
	{
		bFill = false;
		if (i < (float)m_value/m_count*15)
		{
			bFill = true;
		}
		drawSingleRect(painter,i,bFill);
	}

	painter->restore();
}

void CLightItem::setValue(int num)
{
	if (num > m_count)
	{
		m_value = m_count;
	}
	m_value = num;
	update();
}
