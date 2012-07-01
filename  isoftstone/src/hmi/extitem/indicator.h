#ifndef INDICATOR_H
#define INDICATOR_H

#include "extitem.h"
#include "lcdnumber.h"

const int INDICATOR_COUNT = 3;
const int INDICATOR_PEN_WIDTH = 2;
const QColor INDICATOR_FRAME_COLOR = QColor(255,170,0);
const QColor INDICATOR_GRAPH_COLOR = QColor(85,255,0);

class EXPORT_EXTITEM CIndicator : public QGraphicsObject
{
    Q_OBJECT
public:
    CIndicator(QGraphicsItem *parent = 0);
    void SetForeColor(QColor c);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawLCDNums(QPainter* painter);
    void drawRect(QPainter* painter);
    void drawBars(QPainter* painter);
    void drawGraph(QPainter* painter);

private:
    void initVariables();

private:
    CLCDNumber* lcd[INDICATOR_COUNT];
    qreal m_leftSpace;
    qreal m_topSpace;
    qreal m_lcdWidth;
    qreal m_lcdHeight;
    int m_value;
    int m_currValue;
    bool m_bReverse;

    QTimer* updateTimer;
    QPointF m_rectTopLeft;
    QPointF m_rectBottomRight;
    QColor forecolor;

private slots:
    void UpdateData();

public slots:
    void setValue(int value);

};

#endif // MYINDICATOR_H
