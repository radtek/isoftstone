
#include "Curve.h"

#define COS_1(X) (cos((float)X*3.1415926/180))
#define SIN_1(X) (sin(1*(float)X*3.1415926/180))

CCurve::CCurve(QGraphicsItem* parent ):QGraphicsObject(parent)
{
	setAcceptDrops(true);

	m_width = 240;
	m_height = 120;
	m_title = QObject::tr("");
	m_xTitle = QObject::tr("X");
	m_yTitle = QObject::tr("Y");
	m_xStart = 0;
	m_xEnd = 24;
	m_xStep = 1;
	m_yStart = 0;
	m_yEnd = 100;
	m_yStep = 10;
	m_bReal = true;
	m_bGrid = true;
	m_bMaxMin = false;
	m_bBack = false;
	m_bkColor = Qt::black;

	init();
}

CCurve::~CCurve()
{
	if (m_timerID > -1)
	{
		killTimer(m_timerID);
	}
}

void CCurve::init()
{
	addCurve(200,Qt::blue);
	srand(100);
	m_timerID = startTimer(1000);
}

void CCurve::setCurveTitle(const QString& title)
{
	m_title = title;
}

void CCurve::setXTitle(const QString& title)
{
	m_xTitle = title;
}

void CCurve::setYTitle(const QString& title)
{
	m_yTitle = title;
}

void CCurve::setWidth(int width)
{
	m_width = width;
}

void CCurve::setHeight(int height)
{
	m_height = height;
}

void CCurve::setXAxis(qreal fStart,qreal fEnd,qreal fStep)
{
	m_xStart = fStart;
	m_xEnd = fEnd;
	m_xStep = fStep;
}

void CCurve::setYAxis(qreal fStart,qreal fEnd,qreal fStep)
{
	m_yStart = fStart;
	m_yEnd = fEnd;
	m_yStep = fStep;
}

void CCurve::setShowReal(bool breal)
{
	m_bReal = breal;
}

void CCurve::setShowGrid(bool bgrid)
{
	m_bGrid = bgrid;
}

void CCurve::setShowMaxMin(bool bmaxmin)
{
	m_bMaxMin = bmaxmin;
}

void CCurve::setShowBackGround(bool bBack)
{
	m_bBack = bBack;
}

void CCurve::setBackGround(QColor bkColor)
{
	m_bkColor = bkColor;
}


void CCurve::setLineColor(quint64 keyid,QColor color)
{
	m_colorMap[keyid] = color;
}

QColor CCurve::getLineColor(quint64 keyid)
{
	return m_colorMap[keyid];	
}

void CCurve::addCurve(quint64 keyid,QColor color)
{
	m_colorMap[keyid] = color;
	m_ValueMap[keyid].clear();
}

void CCurve::removeCurve(quint64 keyid)
{
	m_colorMap.remove(keyid);
	m_ValueMap.remove(keyid);
}

QRectF CCurve::boundingRect() const
{
	return QRectF(0,0,m_width,m_height);
}

void CCurve::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	painter->save();
	int	height = m_height - 20;
	int width = m_width - 10;
	int diff = 10;
	int arrow = 6;
	QPointF oPos(diff,height + diff);
	QPointF xPos(diff + width,height + diff);
	QPointF yPos(diff,diff);

	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(1);
	painter->setPen(pen);

	// 画轴
	painter->drawLine(oPos,xPos);
	painter->drawLine(oPos,yPos);

	// 画箭头
	QPointF Pos1(diff - arrow ,diff + arrow);
	QPointF Pos2(diff + arrow, diff + arrow);
	QPointF Pos3(xPos.x() - arrow,xPos.y() - arrow);
	QPointF Pos4(xPos.x() - arrow,xPos.y() + arrow);

	painter->drawLine(Pos1,yPos);
	painter->drawLine(yPos,Pos2);
	painter->drawLine(Pos3,xPos);
	painter->drawLine(xPos,Pos4);

	// 画网格
	int xCount = (m_xEnd - m_xStart)/m_xStep;
	int xPix = (m_width - diff - arrow)/xCount;
	int yCount = (m_yEnd - m_yStart)/m_yStep;
	int yPix = (m_height - diff -diff - arrow)/yCount;

	QPointF lPos(oPos.x() + xPix*xCount,oPos.y());
	QPointF uPos(oPos.x(),oPos.y() - yPix*yCount);

	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(0.2);
 	painter->setPen(pen);

	QFont font("Times", 5, QFont::Normal);
	painter->setFont(font);

	// 设置原点数值
	painter->drawText(oPos.x() - 3,oPos.y() + 8,QString::number(m_xStart));
	painter->drawText(oPos.x() - 13,oPos.y()+ yPix /3,QString::number(m_yStart));
	for (int i = 0 ; i < xCount ; i++)
	{
		QPointF start(oPos.x() + xPix*(i+1),oPos.y());
		QPointF end(uPos.x() + xPix*(i+1),uPos.y());
		painter->drawLine(start,end);

		// 标刻度
		painter->drawText(start.x() - 3,start.y() + 8,QString::number(m_xStart + (i + 1)*m_xStep));
	}

	for (int i = 0 ; i < yCount ; i++)
	{
		QPointF start(oPos.x() ,oPos.y() - yPix*(i+1));
		QPointF end(lPos.x() ,lPos.y() - yPix*(i+1));
		painter->drawLine(start,end);

		// 标刻度
		painter->drawText(start.x() - 13,start.y() + yPix /3,QString::number(m_yStart + (i + 1)*m_yStep));
	}

	// 绘制曲线
	QMapIterator<quint64,QVector<QVector2D > > iter(m_ValueMap);
	while (iter.hasNext())
	{
		iter.next();

		quint64 keyid = iter.key();
		const QVector<QVector2D >& vecValue = iter.value();

		pen.setColor(m_colorMap[keyid]);
		painter->setPen(pen);
		QVector<QPointF> vecPoints;
		foreach (QVector2D value,vecValue)
		{
			QDateTime dt;
			dt.setTime_t(value.x());
			QPointF pos;
			pos.setX(oPos.x() + (dt.time().hour()*60.0f + dt.time().minute())/(24*60*1.0f)*(xPix*xCount));
			pos.setY(oPos.y() - (value.y() - m_yStart)/(m_yEnd - m_yStart)*(yPix*yCount));
			vecPoints.append(pos);
		}

		painter->drawPolyline(QPolygonF(vecPoints));
	}
	painter->restore();
}

void CCurve::timerEvent(QTimerEvent * event)
{
	QMapIterator<quint64,QVector<QVector2D > > iter(m_ValueMap);
	while (iter.hasNext())
	{
		iter.next();

		QVector<QVector2D >& vecValue = m_ValueMap[iter.key()];
		QVector2D value;
		value.setX(QDateTime::currentDateTime().toTime_t()  +  vecValue.count()*60*5);
		value.setY(50 + 20*COS_1(vecValue.count()*3));
		vecValue.append(value);
	}

	update();
}

void CCurve::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsObject::mouseDoubleClickEvent(event);
}

void CCurve::wheelEvent ( QGraphicsSceneWheelEvent * event )
{
	QGraphicsObject::wheelEvent(event);
}

void CCurve::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
	QGraphicsObject::dragEnterEvent(event);
}

void CCurve::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
{
	QGraphicsObject::dragLeaveEvent(event);
}

void CCurve::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
{
	QGraphicsObject::dragMoveEvent(event);
}

void CCurve::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
	QGraphicsObject::dropEvent(event);
}