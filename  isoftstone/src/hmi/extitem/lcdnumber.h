#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#define LCDNUMBER_SPACE 2

#include "extitem.h"

class EXPORT_EXTITEM CLCDNumber : public QGraphicsObject
{
    Q_OBJECT
public:
    CLCDNumber(QGraphicsItem *parent = 0);

signals:

public slots:
    void setValue(int num);
	
	void resize(qreal width,qreal height);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawNumber(QPainter* painter);

private:
    int m_nNum;
    qreal m_min;
    qreal m_rectWidth;
    QPointF m_center;

	qreal m_width;
	qreal m_height;
    void initVariables();

};

#endif // MYLCDNUMBER_H
