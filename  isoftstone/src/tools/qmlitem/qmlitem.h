
#ifndef QML_ITEM_H
#define QML_ITEM_H

#include <QDeclarativeItem>
#include <QColor>

class CQMLItem : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor)
	Q_PROPERTY(QColor fill READ fill WRITE setFill)
	Q_PROPERTY(int width READ width WRITE setWidth)

public:

	CQMLItem(QDeclarativeItem* parent);

	QColor fill() const;
	void setFill(const QColor &fill);

	QColor color() const;
	void setColor(const QColor &color);

	int	width() const;
	void setWidth(const int& width);

protected:

	QColor m_fill;
	QColor m_color;
	int m_width;
};

class CQMLRectItem : public CQMLItem
{
	Q_OBJECT

	Q_PROPERTY(QRect bound READ bound WRITE setBound)

public:
	CQMLRectItem(QDeclarativeItem *parent = 0);

	QRect bound() const;
	void setBound(const QRect& bound);

protected:

	QRect m_bound;
};

class CQMLPolyItem: public CQMLItem
{
	Q_OBJECT

		Q_PROPERTY(QString points READ points WRITE setPoints)

public:
	CQMLPolyItem(QDeclarativeItem *parent = 0);

	QString points() const;
	void setPoints(const QString& points);

protected:

	QPolygonF m_points;
};

class CQMLEllipseItem : public CQMLRectItem
{
	Q_OBJECT

		Q_PROPERTY(qreal rx READ rx WRITE setRX)
		Q_PROPERTY(qreal ry READ ry WRITE setRY)

public:

	CQMLEllipseItem(QDeclarativeItem* parent);

	int	rx() const;
	void setRX(const int& rx);

	int	ry() const;
	void setRY(const int& ry);

protected:

	int m_rx;
	int m_ry;
};

class CQMLLine : public CQMLItem
{
    Q_OBJECT
   
    Q_PROPERTY(int x1 READ x1 WRITE setX1)
	Q_PROPERTY(int y1 READ y1 WRITE setY1)
	Q_PROPERTY(int x2 READ x2 WRITE setX2)
	Q_PROPERTY(int y2 READ y2 WRITE setY2)

public:
    CQMLLine(QDeclarativeItem *parent = 0);

	int	x1() const;
	void setX1(const int& x1);

	int	y1() const;
	void setY1(const int& y1);

	int	x2() const;
	void setX2(const int& x2);

	int	y2() const;
	void setY2(const int& y2);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;

};

class CQMLRoundRect : public CQMLEllipseItem
{
	Q_OBJECT

		Q_PROPERTY(qreal rx READ rx WRITE setRX)
		Q_PROPERTY(qreal ry READ ry WRITE setRY)

public:

	CQMLRoundRect(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};


class CQMLCircle : public CQMLEllipseItem
{
	Q_OBJECT

		Q_PROPERTY(int cx READ cx WRITE setCX)
		Q_PROPERTY(int cy READ cy WRITE setCY)
		Q_PROPERTY(qreal radius READ radius WRITE setRadius)

public:
	CQMLCircle(QDeclarativeItem *parent = 0);

	int	cx() const;
	void setCX(const int& cx);

	int	cy() const;
	void setCY(const int& cy);

	int	radius() const;
	void setRadius(const int& r);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

	int m_cx;
	int m_cy;
	int m_radius;

};

class CQMLEllipse : public CQMLCircle
{
	Q_OBJECT

public:

	CQMLEllipse(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};

class CQMLCircleArc : public CQMLRectItem
{
	Q_OBJECT

		Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
		Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)

public:
	CQMLCircleArc(QDeclarativeItem *parent = 0);

	int	startAngle() const;
	void setStartAngle(const int& cx);

	int	spanAngle() const;
	void setSpanAngle(const int& cy);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

	int m_startAngle;
	int m_spanAngle;
};

typedef CQMLCircleArc CQMLEllipseArc;

class CQMLDiamond : public CQMLRectItem
{
	Q_OBJECT

public:
	CQMLDiamond(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};

class CQMLTriangle : public CQMLRectItem
{
	Q_OBJECT

public:
	CQMLTriangle(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};

class CQMLPolygon : public CQMLPolyItem
{
	Q_OBJECT

public:
	CQMLPolygon(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};

class CQMLPolyline : public CQMLPolyItem
{
	Q_OBJECT

public:
	CQMLPolyline(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

};

class CDecorateItem : public CQMLRectItem
{
	Q_OBJECT

	Q_PROPERTY(QString devref READ devref WRITE setDevref)

public:

	CDecorateItem(QDeclarativeItem* parent);

	QString devref();
	void setDevref(const QString& devref);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:

	QString m_devref;
	QDeclarativeItem* m_refItem;
};

#endif

