#ifndef LIGHT_ITEM_H
#define LIGHT_ITEM_H


#include "extitem.h"

class EXPORT_EXTITEM CLightItem : public QGraphicsObject
{
	Q_OBJECT
public:
	CLightItem(QGraphicsItem *parent = 0);

public slots:

	void setValue(int num);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

	void paintSun(QPainter* painter);
	void paintRect(QPainter* painter);
	void drawSingleRect(QPainter* painter,int num,bool bFill);

	void init();

private:

	int		m_value;
	QBrush	m_brush;
	QPen	m_pen;
	int		m_count;
	int		m_angle;
};

#endif // MYLCDNUMBER_H
