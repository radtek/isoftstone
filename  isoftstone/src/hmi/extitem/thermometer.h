#ifndef THERMOMETHER_H
#define THERMOMETHER_H

#define LONG3 7
#define OK3 5
#define SHORT3 3
#define MARK_BUCKET_SPACE3 20

#include "extitem.h"

class EXPORT_EXTITEM CThermoMeterItem : public QGraphicsObject
{
    Q_OBJECT
public:
    CThermoMeterItem(QGraphicsItem *parent = 0);

    void SetGraphColor(QColor c);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void drawMark(QPainter* painter);
    void drawBucket(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawGraph(QPainter* painter);
    void resetDrawingVariables(QPainter* painter);

private:
    qreal m_value;
    qreal m_currentValue;
    qreal m_bucketWidth;
    QTimer* updateTimer;
    bool  m_bReverse;
    qreal m_markSpace;
    qreal m_topSpace;
    QColor m_markClr;
    QColor graphcolor;
    QRectF m_bucketRect;

private:
    void initVariables();

private slots:
    void UpdateGraph();

public slots:
    void setValue(qreal value);
    void setMarkColor(const QColor& clr);

};

#endif // CThermoMeterItem_H
