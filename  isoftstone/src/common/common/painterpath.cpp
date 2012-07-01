

#include <math.h>

#include "painterpath.h"
#include "macro.h"

void CPainterPath::drawRoundRect(QPainterPath& path,const QRectF& rect,qreal width )
{
	qreal sweepLength = 90;

	qreal diff = width/2;
	qreal right = rect.right();
	qreal left = rect.left();
	qreal bottom = rect.bottom();
	qreal top = rect.top();

	qreal x = rect.right() + width ;
	qreal y = rect.top() + diff;
	path.moveTo(x,y);

	path.arcTo(QRectF(rect.topRight(),QSizeF(width,width)),0,sweepLength);
	path.lineTo(left + diff,top);

	path.arcTo(QRectF(rect.topLeft(),QSizeF(width,width)),90,sweepLength);
	path.lineTo(left ,bottom + diff);

	path.arcTo(QRectF(rect.bottomLeft(),QSizeF(width,width)),180,sweepLength);
	path.lineTo(right + diff,bottom + width);

	path.arcTo(QRectF(rect.bottomRight(),QSizeF(width,width)),270,sweepLength);

	path.closeSubpath();

}

QPainterPath CPainterPath::drawRoundRect(const QRectF& rect,qreal width )
{
	QPainterPath path;
	drawRoundRect(path,rect,width);
	return path;
}

void CPainterPath::drawEllipse(QPainterPath& path,const QRectF& rect)
{
	qreal x = rect.left() + rect.width() ;
	qreal y = rect.top() + rect.height() /2;
	path.moveTo(x,y);
	path.arcTo(rect, 0.0, 360.0);
}

QPainterPath CPainterPath::drawEllipse(const QRectF& rect)
{
	QPainterPath path;
	drawEllipse(path,rect);
	return path;
}

void CPainterPath::drawCircle(QPainterPath& path,const QPointF& start,qreal radius)
{
	drawEllipse(path,QRectF(start,start + QPointF(2*radius,2*radius)));
}

QPainterPath CPainterPath::drawCircle(const QPointF& start,qreal radius)
{
	QPainterPath path;
	drawCircle(path,start,radius);
	return path;
}

void CPainterPath::drawPie(QPainterPath& path,const QRectF& rect,qreal startAngle,qreal endAngle)
{
	qreal x = rect.left() + rect.width() ;
	qreal y = rect.top() + rect.height() /2;
	path.moveTo(x,y);
	path.arcTo(rect, startAngle,endAngle);
	path.closeSubpath();
}

QPainterPath CPainterPath::drawPie(const QRectF& rect,qreal startAngle,qreal endAngle)
{
	QPainterPath path;
	drawPie(path,rect,startAngle,endAngle);
	return path;
}

void CPainterPath::drawStar(QPainterPath& path,const QPointF& start,qreal radius)
{
// #define COS(X) (cos(X/180*3.1415926))
// #define SIN(X) (sin(-1*X/180*3.1415926))

	//qreal Pi = 3.1415926;
	qreal angel = 360.0 / 5;
	qreal startAngle = 90 - angel;
	QPointF center = start + QPointF(radius,radius);
	QPointF startPoint = center + QPointF(radius * COS(startAngle),radius * SIN(startAngle));
	path.moveTo(startPoint);

	QPointF nextPoint;
	for (int i = 1; i < 5; ++i)
	{
		qreal nextAngle = startAngle + 2 * i * angel;
		nextPoint = center + QPointF(radius * COS(nextAngle),radius * SIN(nextAngle));
		path.lineTo(nextPoint);
	}
	path.closeSubpath();

#undef COS
#undef SIN
}

void CPainterPath::drawCircleStar(QPainterPath& path,const QPointF& start,qreal radius)
{
	drawCircle(path,start,radius);
	drawStar(path,start,radius);
}
