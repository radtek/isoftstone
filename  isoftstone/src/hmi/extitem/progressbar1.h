#ifndef PROGRESSBAR1_H
#define PROGRESSBAR1_H

#define PYP_LEFT_SPACE1 10
#define PYP_TOP_SPACE1 5
#define PYP_RIGHT_SPACE1 7
#define PYP_TEXT_WIDTH 45
#define PYP_RECT_RADIUS 8
#define PYP_LINE_COUNT 20
#define PYP_LINE_WIDTH 2
#define PYP_D_LINE 7

#define PYP_LINE_COLOR Qt::black
#define PYP_BG_COLOR QColor(45,45,45)

#define PYP_BAR_START_COLOR QColor(85,255,0)
#define PYP_BAR_MIDDLE_COLOR QColor(249,216,47)
#define PYP_BAR_END_COLOR QColor(249,107,24)
#define PYP_UNDER_BAR_COLOR QColor(121,121,121)

#define PYP_TEXT_COLOR Qt::white

#include "extitem.h"

class EXPORT_EXTITEM CProgressBar1 : public QGraphicsObject
{
    Q_OBJECT
public:
    CProgressBar1(QGraphicsItem *parent = 0);

public:
    void setRange(qreal min,qreal max);

    void setValue(qreal value);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    void drawBg(QPainter* painter);

    void drawBar(QPainter* painter);

private:
    void initVariables();

private:
    qreal m_min;
    qreal m_max;
    qreal m_value;

};

#endif // MYPROGRESSBAR1_H
