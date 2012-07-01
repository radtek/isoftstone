
#include "sounditem.h"

CSoundItem::CSoundItem(QGraphicsItem *parent) :QGraphicsObject(parent)
{
    init();
}

void CSoundItem::init()
{
	m_value = 20;
	m_count = 100;
	m_brush = Qt::green;
	m_pen.setColor(Qt::darkGray);
	m_pen.setWidth(1);
}

QRectF CSoundItem::boundingRect() const
{
	return QRectF(0,0,200,30);
}	

void CSoundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	paintAlarm(painter);
	paintRect(painter);
	//paintNumber(painter);
}

void CSoundItem::paintAlarm(QPainter* painter)
{
	painter->save();
	painter->setPen(m_pen);
	painter->setBrush(m_brush);
	QRectF boundRect = boundingRect();
	qreal w = boundRect.width()/30;
	qreal h = boundRect.height()/4;

	QRectF rect(QPointF(boundRect.left(),boundRect.top() + h),QPointF(boundRect.left() + w,boundRect.top() + h*3));
	painter->drawRect(rect);

	QPolygonF polygons;
	polygons.append(QPointF(boundRect.left() + w,boundRect.top() + h));
	polygons.append(QPointF(boundRect.left() + w*3,boundRect.top() ));
	polygons.append(QPointF(boundRect.left() + w*3,boundRect.bottom()));
	polygons.append(QPointF(boundRect.left() + w,boundRect.top() + h*3));
	painter->drawPolygon(polygons);
	painter->restore();
}

void CSoundItem::paintRect(QPainter* painter)
{
	painter->save();
	painter->setPen(m_pen);
	QRectF boundRect = boundingRect();
	qreal w = boundRect.width()/30;
	qreal h = boundRect.height()/5;
	QRectF rect1(QPointF(boundRect.left() + w*5,boundRect.top() + h),QPointF(boundRect.left() + 30*w ,boundRect.top() + h*4));
	painter->drawRect(rect1);

	QRectF rect2(QPointF(boundRect.left() + w*5,boundRect.top() + h),QPointF(boundRect.left() + w*30*((float)m_value/(float)(m_count)),boundRect.top() + h*4));
	painter->setBrush(m_brush);
	painter->drawRect(rect2);
	painter->restore();
}

void CSoundItem::paintNumber(QPainter* painter)
{

}

void CSoundItem::setValue(int num)
{
	if (num > m_count)
	{
		m_value = m_count;
	}
	m_value = num;
    update();
}
