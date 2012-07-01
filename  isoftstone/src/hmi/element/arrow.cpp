
#include <QtGui>

#include "const_type.h"
#include "arrow.h"
#include <math.h>

Arrow::Arrow()
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	m_Color = Qt::black;
	setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem,
			 QGraphicsItem *parent, QGraphicsScene *scene)
			: QGraphicsLineItem(parent, scene)
{
    m_StartItem = startItem;
    m_EndItem = endItem;
	m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
	// 图形为基类直线加上箭头多边形
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_ArrowHead);
    return path;
}

void Arrow::setColor(const QColor &color)
{ 
	m_Color = color; 
}

DiagramItem *Arrow::startItem() const
{
	return m_StartItem; 
}
DiagramItem *Arrow::endItem() const
{
	return m_EndItem; 
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(m_StartItem, 0, 0), mapFromItem(m_EndItem, 0, 0));
    setLine(line);
}

void Arrow::setScene(QGraphicsScene* scene)
{
	m_scene = scene;
}

void Arrow::drawArraw(QGraphicsScene* scene,QGraphicsLineItem **linkLine,const QColor& lineColor)
{
	QList<QGraphicsItem *> startItems = scene->items((*linkLine)->line().p1());
	if (startItems.count() && startItems.first() == (*linkLine)) 
	{
		startItems.removeFirst();
	}
	QList<QGraphicsItem *> endItems = scene->items((*linkLine)->line().p2());
	if (endItems.count() && endItems.first() == (*linkLine))
	{
		endItems.removeFirst();
	}

	scene->removeItem((*linkLine));
	delete *linkLine;
	(*linkLine) = NULL;

	if (startItems.count() > 0 && endItems.count() > 0 && // 两端具有图元
		startItems.first()->type() == DiagramItem::Type && // 图元类型符合条件
		endItems.first()->type() == DiagramItem::Type &&  // 图元不为同一个
		startItems.first() != endItems.first()) 
	{
			DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
			DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
			Arrow *arrow = new Arrow(startItem, endItem);
			arrow->setColor(lineColor);
			startItem->addArrow(arrow);
			endItem->addArrow(arrow);
			arrow->setZValue(-1000.0);
			scene->addItem(arrow);
			arrow->updatePosition();
	}
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (m_StartItem->collidesWithItem(m_EndItem)) return;

    QPen myPen = pen();
    myPen.setColor(m_Color);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(m_Color);

    QLineF centerLine(m_StartItem->pos(), m_EndItem->pos());
    QPolygonF endPolygon = m_EndItem->polygon();
    QPointF p1 = endPolygon.first() + m_EndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) 
	{
		p2 = endPolygon.at(i) + m_EndItem->pos();
		polyLine = QLineF(p1, p2);
		QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
		if (intersectType == QLineF::BoundedIntersection) break;
		p1 = p2;
    }

    setLine(QLineF(intersectPoint, m_StartItem->pos()));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
	{
        angle = (Pi * 2) - angle;
	}

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);

	// 此箭头需要时刻变化的
    m_ArrowHead.clear();
    m_ArrowHead << line().p1() << arrowP1 << arrowP2;

	if (isSelected())
	{
		painter->setPen(QPen(m_Color, 1, Qt::DashLine));
	}
	// 连接线被选中情况 , 可以通过复制一条直线然后translate来描述
    painter->drawLine(line());
    painter->drawPolygon(m_ArrowHead);
	
}


void Arrow::build()
{
	QGraphicsScene* sc = m_scene;
	QList<QGraphicsItem *> startItems = sc->items(line().p2());
	QList<QGraphicsItem *> endItems = sc->items(line().p1());

	if (startItems.count() > 0 && endItems.count() > 0 &&
		startItems.first()->type() == DiagramItem::Type &&
		endItems.first()->type() == DiagramItem::Type &&
		startItems.first() != endItems.first())
	{
		m_StartItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
		m_EndItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());

		setColor(m_Color);
		m_StartItem->addArrow(this);
		m_EndItem->addArrow(this);
		setZValue(-1000.0);
	}
}


void Arrow::serialize(QDataStream& out) const
{
	out << shape();
	out << pen();
	out << m_Color;
	out << line();
	out << *this;
}

void Arrow::deserialize( QDataStream& out)
{
	QPainterPath path;
	out >> path;

	QPen pen;
	out >> pen;
	setPen(pen);

	QColor color;
	out >> color;
	m_Color = color;

	QLineF line;
	out >> line;
	setLine(line);

	out >> *this;
}
