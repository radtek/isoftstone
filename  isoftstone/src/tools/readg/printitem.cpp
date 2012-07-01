
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>

#include <QPen>
#include <QColor>
#include <QFont>
#include <QObject>
#include <QPainterPath>

#include <QStringList>

#include "printitem.h"

#define GET_VALUE(ATTR) m_AttrMap["ATTR"]

void CGraphicsItemBase::setAttrMap(const QMap<QString,QString>& attrMap)
{	
	m_AttrMap = attrMap;
}

QPen CGraphicsItemBase::drawPen()
{
	QPen pen;
	QStringList lstLc = GET_VALUE(lc).split(',');
	QColor lc = QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt());
	pen.setColor(lc);
	pen.setWidth(GET_VALUE(lw).toInt());
	pen.setStyle(Qt::PenStyle(GET_VALUE(ls).toInt()));
	return pen;
}

void CGraphicsItemBase::drawPen(QAbstractGraphicsShapeItem* pItem)
{
	pItem->setPen(drawPen());
}

void CGraphicsItemBase::drawPen(QGraphicsLineItem* pItem)
{
	pItem->setPen(drawPen());
}

void CGraphicsItemBase::drawBrush(QAbstractGraphicsShapeItem* pItem)
{
	QBrush brush;
	QStringList lstFc = GET_VALUE(fc).split(',');
	QColor fc = QColor::fromRgb(lstFc[0].toInt(),lstFc[1].toInt(),lstFc[2].toInt());
	brush.setColor(fc);
	brush.setStyle(Qt::BrushStyle(GET_VALUE(fm).toInt()));
	pItem->setBrush(brush);
}

// text
CGraphicsTextItem::CGraphicsTextItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsTextItem::createItem()
{
	QGraphicsSimpleTextItem* pItem = new QGraphicsSimpleTextItem(m_Parent);
	QFont font;
	//字体宽度
	font.setWeight(GET_VALUE(p_FontWidth).toInt());
	//字体大小
	font.setPixelSize(GET_VALUE(fs).toInt());
	//字间距
	font.setWordSpacing(GET_VALUE(p_FontInterval).toInt());
	//字体高度
	//字体类型
	QString strFamily(GET_VALUE(ff));

	if (!strFamily.isEmpty())
	{
		font.setFamily(strFamily);
	}

	pItem->setFont(font);

	//字体颜色
	QPen pen;
	QStringList lstLc = GET_VALUE(lc).split(',');
	pen.setColor(QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt()));
	pItem->setPen(pen);

	pItem->setText(GET_VALUE(ts));
	return pItem;

}

QGraphicsItem* CGraphicsTextItem::clone()
{
	return NULL;
}

// Line
CGraphicsLineItem::CGraphicsLineItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsLineItem::createItem()
{
	QGraphicsLineItem* pItem = new QGraphicsLineItem(m_Parent);

	drawPen(pItem);
	
	QPointF start;
	start.setX(GET_VALUE(x1).toFloat());
	start.setY(GET_VALUE(y1).toFloat());
	QPointF end;
	end.setX(GET_VALUE(x2).toFloat());
	end.setY(GET_VALUE(y2).toFloat());
	
	QLineF line(start,end);
	pItem->setLine(line);

	return pItem;
}

QGraphicsItem* CGraphicsLineItem::clone()
{
	return NULL;
}

// rect
CGraphicsRectItem::CGraphicsRectItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsRectItem::createItem()
{
	QGraphicsRectItem* pItem = new QGraphicsRectItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	pItem->setRect(GET_VALUE(x).toInt(),GET_VALUE(y).toInt(),GET_VALUE(w).toInt(),GET_VALUE(h).toInt());
	return pItem;
}

QGraphicsItem* CGraphicsRectItem::clone()
{
	return NULL;
}

// circle
CGraphicsCircleItem::CGraphicsCircleItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsCircleItem::createItem()
{
	QGraphicsEllipseItem* pItem = new QGraphicsEllipseItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	pItem->setRect(GET_VALUE(cx).toInt(), GET_VALUE(cy).toInt(), GET_VALUE(r).toInt(), GET_VALUE(r).toInt());
	return pItem;
}

QGraphicsItem* CGraphicsCircleItem::clone()
{
	return NULL;
}

// pin
CGraphicsPinItem::CGraphicsPinItem(QGraphicsItem* parent):CGraphicsCircleItem(m_Parent)
{

}

QGraphicsItem* CGraphicsPinItem::createItem()
{
	return CGraphicsCircleItem::createItem();
}

QGraphicsItem* CGraphicsPinItem::clone()
{
	return NULL;
}

// ellipse
CGraphicsEllipseItem::CGraphicsEllipseItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsEllipseItem::createItem()
{
	QGraphicsEllipseItem* pItem = new QGraphicsEllipseItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	pItem->setRect(GET_VALUE(cx).toInt(), GET_VALUE(cy).toInt(), GET_VALUE(rx).toInt(), GET_VALUE(ry).toInt());
	return pItem;
}

QGraphicsItem* CGraphicsEllipseItem::clone()
{
	return NULL;
}

// polygon
CGraphicsPolygonItem::CGraphicsPolygonItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsPolygonItem::createItem()
{
	QGraphicsPolygonItem* pItem = new QGraphicsPolygonItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	QPolygonF d;
	QStringList lstPath = GET_VALUE(d).split(' ');
	int iCount = lstPath.size();
	for (int j = 0; j < iCount; j++)
	{
		QStringList lstPoint = lstPath[j].split(',');
		d.append(QPointF(lstPoint[0].toDouble(), lstPoint[1].toDouble()));
		lstPoint.clear();
	}
	pItem->setPolygon(d);

	return pItem;
}

QGraphicsItem* CGraphicsPolygonItem::clone()
{
	return NULL;
}

// triangle
CGraphicsTriangleItem::CGraphicsTriangleItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsTriangleItem::createItem()
{
	QGraphicsPolygonItem* pItem = new QGraphicsPolygonItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	QPolygonF d;
	d.append(QPointF(-GET_VALUE(w).toDouble()/2,GET_VALUE(h).toDouble()/2));
	d.append(QPointF(GET_VALUE(w).toDouble()/2,GET_VALUE(h).toDouble()/2));
	d.append(QPointF(0,-GET_VALUE(h).toDouble()/2));
	pItem->setPolygon(d);

	return pItem;
}

QGraphicsItem* CGraphicsTriangleItem::clone()
{
	return NULL;
}

// diamond
CGraphicsDiamondItem::CGraphicsDiamondItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsDiamondItem::createItem()
{
	QGraphicsPolygonItem* pItem = new QGraphicsPolygonItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	qreal x;
	qreal y;
	qreal w;
	qreal h;

	x = GET_VALUE(x).toFloat();
	y = GET_VALUE(y).toFloat();
	w = GET_VALUE(w).toFloat();
	h = GET_VALUE(h).toFloat();

	QPolygonF d;
	d.append(QPointF(x + w/2,y));
	d.append(QPointF(x + w,y + h/2));
	d.append(QPointF(x + w/2,y + h));
	d.append(QPointF(x,y + h/2));
	pItem->setPolygon(d);

	return pItem;
}

QGraphicsItem* CGraphicsDiamondItem::clone()
{
	return NULL;
}

// polyline
CGraphicsPolylineItem::CGraphicsPolylineItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsPolylineItem::createItem()
{
	QGraphicsPathItem* pItem = new QGraphicsPathItem(m_Parent);
	drawPen(pItem);
	QPainterPath path;
	QPolygonF d;
	QStringList lstPath = GET_VALUE(d).split(' ');
	int iCount = lstPath.size();
	for (int j = 0; j < iCount; j++)
	{
		QStringList lstPoint = lstPath[j].split(',');
		d.append(QPointF(lstPoint[0].toDouble(), lstPoint[1].toDouble()));
		lstPoint.clear();
	}
	if (d.count() > 0)
	{
		path.moveTo(d[0]);
	}
	for (int i = 1; i < d.count() ; i++)
	{
		path.lineTo(d[i]);
	}
	pItem->setPath(path);
	return pItem;
}

QGraphicsItem* CGraphicsPolylineItem::clone()
{
	return NULL;
}

// circlearc
CGraphicsCircleArcItem::CGraphicsCircleArcItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsCircleArcItem::createItem()
{
	QGraphicsPathItem* pItem = new QGraphicsPathItem(m_Parent);
	drawPen(pItem);
	drawBrush(pItem);
	QPainterPath path;
	qreal cx = GET_VALUE(cx).toFloat();
	qreal cy = GET_VALUE(cy).toFloat();
	qreal r  = GET_VALUE(r).toFloat();
	qreal a1 = GET_VALUE(a1).toFloat();
	qreal a2 = GET_VALUE(a2).toFloat();

	QRectF round(cx-r,cy-r,2*r,2*r);
	qreal  span = a2 - a1;
	path.arcTo(round,a1*16,span*16);
	pItem->setPath(path);
	return pItem;
}

QGraphicsItem* CGraphicsCircleArcItem::clone()
{
	return NULL;
}

// ellipsearc
CGraphicsEllipseArcItem::CGraphicsEllipseArcItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsEllipseArcItem::createItem()
{
	QGraphicsPathItem* pItem = new QGraphicsPathItem(m_Parent);
	drawPen(pItem);
	drawBrush(pItem);
	QPainterPath path;
	qreal cx = GET_VALUE(cx).toFloat();
	qreal cy = GET_VALUE(cy).toFloat();
	qreal rx = GET_VALUE(rx).toFloat();
	qreal ry = GET_VALUE(ry).toFloat();
	qreal a1 = GET_VALUE(a1).toFloat();
	qreal a2 = GET_VALUE(a2).toFloat();

	QRectF round(cx-rx,cy-ry,2*rx,2*ry);
	qreal  span = a2 - a1;
	path.arcTo(round,a1*16,span*16);
	pItem->setPath(path);
	return pItem;
}

QGraphicsItem* CGraphicsEllipseArcItem::clone()
{
	return NULL;
}

// roundrect
CGraphicsRoundRectItem::CGraphicsRoundRectItem(QGraphicsItem* parent)
{

}

QGraphicsItem* CGraphicsRoundRectItem::createItem()
{
	QGraphicsPathItem* pItem = new QGraphicsPathItem(m_Parent);
	drawPen(pItem);
	drawBrush(pItem);
	QPainterPath path;
	qreal x = GET_VALUE(x).toFloat();
	qreal y = GET_VALUE(y).toFloat();
	qreal w = GET_VALUE(w).toFloat();
	qreal h = GET_VALUE(h).toFloat();
	qreal cx = GET_VALUE(cx).toFloat();
	qreal cy = GET_VALUE(cy).toFloat();

	path.addRoundedRect(x,y,w,h,cx,cy);
	pItem->setPath(path);
	return pItem;
}

QGraphicsItem* CGraphicsRoundRectItem::clone()
{
	return NULL;
}

// pixmap
CGraphicsPixmapItem::CGraphicsPixmapItem(QGraphicsItem* parent)
{
	QByteArray qbr = qgetenv("STONEDIR");
	m_imageDir = QString(qbr.data()) + "/image/";
}

QGraphicsItem* CGraphicsPixmapItem::createItem()
{
	QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem(m_Parent);
	qreal x = GET_VALUE(x).toFloat();
	qreal y = GET_VALUE(y).toFloat();
	qreal w = GET_VALUE(w).toFloat();
	qreal h = GET_VALUE(h).toFloat();
	QPixmap pix(w,h);
	QString strFile = m_imageDir + GET_VALUE(ahref);
	pix.load(strFile);
	pItem->setOffset(x,y);
	pItem->setPixmap(pix);
	return pItem;
}

QGraphicsItem* CGraphicsPixmapItem::clone()
{
	return NULL;
}