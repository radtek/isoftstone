#ifndef METER_1_H
#define METER_1_H

#include "extitem.h"

class EXPORT_EXTITEM CMeterItem : public QGraphicsObject
{
    Q_OBJECT
public:

    CMeterItem(QGraphicsItem *parent = 0);

	QRectF boundingRect() const;

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void drawOuterCircle(QPainter* painter);
    void drawInnerCircle(QPainter* painter);
    void drawColorPies(QPainter* painter);
    void drawCoverLines(QPainter* painter);
    void drawCoverCircle(QPainter* painter);
    void drawMarkAndText(QPainter* painter);
    void drawGraph(QPainter* painter);
    void drawTextRect(QPainter* painter);
    void resetVariables(QPainter* painter);

private:
    qreal m_value;
    qreal m_outerRadius;
    qreal m_innerRadius;
    qreal m_colorPieRadius;
    qreal m_coverCircleRadius;
    qreal m_currentValue;
    qreal m_longHand;
    qreal m_okHand;
    qreal m_shortHand;
    qreal m_space;
    bool m_bReverse;
    QTimer* updateTimer;
    QPointF m_center;
    QRectF m_pieRect;

public slots:
    void setValue(qreal value);

private slots:
    void UpdateGraph();
};

#endif // CMeterItem_H
