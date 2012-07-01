
#include "qmlitem.h"

#include <QPainter>
#include <QDeclarativeEngine>

CQMLItem::CQMLItem(QDeclarativeItem* parent):QDeclarativeItem(parent)
{
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QColor CQMLItem::fill() const
{
	return m_fill;
}

void CQMLItem::setFill(const QColor &fill)
{
	m_fill = fill;
}

QColor CQMLItem::color() const
{
	return m_color;
}

void CQMLItem::setColor(const QColor &color)
{
	m_color = color;
}

int CQMLItem::width() const
{
	return m_width;
}

void CQMLItem::setWidth(const int& width)
{
	m_width = width;
}

CQMLRectItem::CQMLRectItem(QDeclarativeItem *parent ):CQMLItem(parent)
{

}

QRect CQMLRectItem::bound() const
{
	return m_bound;
}

void CQMLRectItem::setBound(const QRect& bound)
{
	m_bound = bound;
}

CQMLPolyItem::CQMLPolyItem(QDeclarativeItem *parent ):CQMLItem(parent)
{

}

QString CQMLPolyItem::points() const
{
	QString ret = "";
	for (int i = 0 ; i < m_points.count() ; i++)
	{
		ret = ret + QString::number(m_points[i].x()) + "," + QString::number(m_points[i].y()) + " ";
	}
	return ret;
}
void CQMLPolyItem::setPoints(const QString& points)
{
	m_points.clear();
	QStringList lstPoints = points.split(' ');
	foreach(QString point,lstPoints)
	{
		QStringList lstPoint = point.split(',');
		if (lstPoint.count() > 1)
		{
			m_points.append(QPointF(lstPoint[0].toFloat(),lstPoint[1].toFloat()));
		}
	}
}

CQMLEllipseItem::CQMLEllipseItem(QDeclarativeItem* parent):CQMLRectItem(parent)
{

}

int CQMLEllipseItem::rx() const
{
	return m_rx;
}

void CQMLEllipseItem::setRX(const int& rx)
{
	m_rx = rx;
}

int CQMLEllipseItem::ry() const
{
	return m_rx;
}

void CQMLEllipseItem::setRY(const int& ry)
{
	m_ry = ry;
}

CQMLLine::CQMLLine(QDeclarativeItem *parent): CQMLItem(parent)
{
    
}

int CQMLLine::x1() const
{
    return m_x1;
}

void CQMLLine::setX1(const int& x1)
{
    m_x1 = x1;
}

int CQMLLine::y1() const
{
	return m_y1;
}

void CQMLLine::setY1(const int& y1)
{
	m_y1 = y1;
}

int CQMLLine::x2() const
{
	return m_x2;
}

void CQMLLine::setX2(const int& x2)
{
	m_x2 = x2;
}

int CQMLLine::y2() const
{
	return m_y2;
}

void CQMLLine::setY2(const int& y2)
{
	m_y2 = y2;
}


void CQMLLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(m_color, m_width);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawLine(QPointF(m_x1,m_y1),QPointF(m_x2,m_y2));
}

CQMLRoundRect::CQMLRoundRect(QDeclarativeItem *parent ):CQMLEllipseItem(parent)
{

}


void CQMLRoundRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);

	painter->drawRoundedRect(m_bound,m_rx,m_ry);
}

///  circle

CQMLCircle::CQMLCircle(QDeclarativeItem *parent): CQMLEllipseItem(parent)
{
}

int CQMLCircle::cx() const
{
	return m_cx;
}

void CQMLCircle::setCX(const int& cx)
{
	m_cx = cx;
}

int CQMLCircle::cy() const
{
	return m_cy;
}

void CQMLCircle::setCY(const int& cy)
{
	m_cy = cy;
}

int CQMLCircle::radius() const
{
	return m_radius;
}

void CQMLCircle::setRadius(const int& radius)
{
	m_radius = radius;
}


void CQMLCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);
	painter->drawEllipse(QPointF(m_cx,m_cy),m_radius,m_radius);
}

// ellipse

CQMLEllipse::CQMLEllipse(QDeclarativeItem *parent):CQMLCircle(parent)
{
	
}

void CQMLEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);
	painter->drawEllipse(QPointF(m_cx,m_cy),m_rx,m_ry);
}


// circlearc

CQMLCircleArc::CQMLCircleArc(QDeclarativeItem *parent): CQMLRectItem(parent)
{
}


int CQMLCircleArc::startAngle() const
{
	return m_startAngle;
}

void CQMLCircleArc::setStartAngle(const int& startAngle)
{
	m_startAngle = startAngle;
}

int CQMLCircleArc::spanAngle() const
{
	return m_spanAngle;
}

void CQMLCircleArc::setSpanAngle(const int& spanAngle)
{
	m_spanAngle = spanAngle;
}

void CQMLCircleArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);
	painter->drawArc(m_bound,m_startAngle*16,m_spanAngle*16);
}

// diamond

CQMLDiamond::CQMLDiamond(QDeclarativeItem *parent): CQMLRectItem(parent)
{
}


void CQMLDiamond::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);

	QPolygonF points;
	points.append(QPointF(m_bound.x() + m_bound.width()/2,m_bound.y()));
	points.append(QPointF(m_bound.x() + m_bound.width(),m_bound.y() + m_bound.height()/2));
	points.append(QPointF(m_bound.x() + m_bound.width()/2,m_bound.y() + m_bound.height()));
	points.append(QPointF(m_bound.x() ,m_bound.y() + m_bound.height()/2));

	painter->drawPolygon(points);
}

CQMLTriangle::CQMLTriangle(QDeclarativeItem *parent): CQMLRectItem(parent)
{
}


void CQMLTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);

	QPolygonF points;
	points.append(QPointF(m_bound.x() + m_bound.width()/2,m_bound.y()));
	points.append(QPointF(m_bound.x() + m_bound.width(),m_bound.y() + m_bound.height()));
	points.append(QPointF(m_bound.x() ,m_bound.y() + m_bound.height()));

	painter->drawPolygon(points);
}

// polygon

CQMLPolygon::CQMLPolygon(QDeclarativeItem *parent): CQMLPolyItem(parent)
{
}


void CQMLPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);

	painter->drawPolygon(m_points);
}

// polyline

CQMLPolyline::CQMLPolyline(QDeclarativeItem *parent): CQMLPolyItem(parent)
{
}


void CQMLPolyline::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen(m_color, m_width);
	painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
	painter->setRenderHints(QPainter::Antialiasing, true);

	painter->drawPolyline(m_points);
}

CDecorateItem::CDecorateItem(QDeclarativeItem* parent):CQMLRectItem(parent)
{
	m_refItem = NULL;
}

QString CDecorateItem::devref()
{
	return m_devref;
}

void CDecorateItem::setDevref(const QString& devref)
{
	m_devref = devref;

	QDeclarativeEngine *engine = new QDeclarativeEngine(NULL);
	QDeclarativeComponent component(engine, QUrl::fromLocalFile(m_devref));

	QObject *obj = component.create();
	QDeclarativeItem *pItem = qobject_cast<QDeclarativeItem*>(obj);
	if (pItem)
	{
		m_refItem = pItem;
	}
}

void CDecorateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_refItem)
	{
		m_refItem->paint(painter,option,widget);
	}
}