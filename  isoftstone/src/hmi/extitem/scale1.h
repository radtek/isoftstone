#ifndef SCALE_1_H
#define SCALE_1_H

/* ¿Ì¶È³ß */

#define LEFT_SPACE1 30
#define TOP_SPACE1 40

#include "extitem.h"

class EXPORT_EXTITEM CScale1 : public QGraphicsObject
{
    Q_OBJECT
public:
    CScale1(QGraphicsItem *parent = 0);

    void SetmyTopColor(QColor c);

	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void drawBackground(QPainter* painter);
    void drawRule(QPainter* painter);
    void drawHandle(QPainter* painter);
    void drawHorizontalLine(QPainter* painter);
    void drawVerticalLines(QPainter* painter);
    void resetVariables(QPainter* painter);
    void drawTip(QPainter* painter);

private:
    int m_nMin;
    int m_nMax;
    int m_length;
    qreal m_value;
    qreal m_longHand;
    qreal m_okHand;
    qreal m_shortHand;
    qreal m_handleWidth;
    qreal m_handleHeight;
    qreal m_indicatorLength;
    QPointF m_indicatorTopPot;
    QPointF m_indicatorLastPot;
    QPointF m_indicatorBottomLeftPot;
    QPointF m_indicatorBottomRightPot;
    QPointF m_lineLeftPot;
    QPointF m_lineRightPot;
    QRectF  m_handleRect;
    QPointF m_lastPos;
    QTimer* tipTimer;
    QTimer* eraseTimer;
    QRectF m_tipRect;
    qreal m_currentValue;

    bool m_bDrag;
    bool m_bShowTip;

    QColor myTopColor;

private:
    void initVariables();
    void initSettings();

private slots:
    void ShowTip();
    void HideTip();

signals:
    void valueChanged(qreal value);

public slots:
    void setRange(int min,int max);
    void setValue(qreal value);
};

#endif // MYGAUGE3_H
