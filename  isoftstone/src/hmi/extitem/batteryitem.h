#ifndef BATTERY_ITEM_H
#define BATTERY_ITEM_H

#include "extitem.h"

class EXPORT_EXTITEM CBatteryItem : public QGraphicsObject
{
    Q_OBJECT
public:
    CBatteryItem(QGraphicsItem *parent = 0);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    void drawFrame(QPainter* painter);
    void drawBattery(QPainter* painter);

private:
    QTimer* updateTimer;
    bool    m_bReverse;
    qreal   m_headWidth;
    qreal   m_value;
    qreal   m_currentValue;
    QRectF  m_batteryRect;

signals:
    void valueChanged(qreal value);

private slots:
    void UpdateGraph();

public slots:
    void setValue(qreal value);

};

#endif // MYBATTERY_H
