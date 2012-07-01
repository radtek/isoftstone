
#ifndef PAINTER_PATH_H
#define PAINTER_PATH_H

#include <QtGui>

#include "common.h"

class EXPORT_COMMON CPainterPath
{
public:

	static void drawRoundRect(QPainterPath& path,const QRectF& rect,qreal width = 10);

	static QPainterPath drawRoundRect(const QRectF& rect,qreal width = 10);

	static void drawEllipse(QPainterPath& path,const QRectF& rect);

	static QPainterPath drawEllipse(const QRectF& rect);

	static void drawCircle(QPainterPath& path,const QPointF& start,qreal radius);

	static QPainterPath drawCircle(const QPointF& start,qreal radius);

	static void drawPie(QPainterPath& path,const QRectF& rect,qreal startAngle,qreal endAngle);

	static QPainterPath drawPie(const QRectF& rect,qreal startAngle,qreal endAngle);

	static void drawStar(QPainterPath& path,const QPointF& start,qreal radius);

	static void drawCircleStar(QPainterPath& path,const QPointF& start,qreal radius);
};


#endif